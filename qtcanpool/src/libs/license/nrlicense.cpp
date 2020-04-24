/***************************************************************************
 **
 **  Copyright (C) 2019 MaMinJie <canpool@163.com>
 **  Contact: https://github.com/canpool
 **
 **  This program is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program.  If not, see http://www.gnu.org/licenses/.
 **
****************************************************************************/
#include "nrlicense_p.h"
#include <time.h>

static NR_CHAR g_licenseFile[NR_FILENAME_LEN] = ".nrlicense";

static const int HostIDOrderFit[6] = {
    5, 1, 2, 4, 3, 0
};

static const int hostToLicense[16] = {
    10, 6, 15, 3, 13, 7, 2, 5, 14, 8, 12, 9, 1, 2, 8, 11
};

static const char CharList[16] = {
    '0', '2', '8', '6', '0', '1', '9', '5', '3', '7', '4', '1', '6', '2', '7', '8'
};

#if defined(WIN32) || defined(Q_OS_WIN32)
#include <winsock2.h>
#include <iphlpapi.h>
#include <time.h>

#include <windows.h>
#include <wincon.h>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <io.h>
#include <fstream>

using namespace std;

typedef struct _ASTAT_ {
    ADAPTER_STATUS adapt;
    NAME_BUFFER    NameBuff[30];
} ASTAT, * PASTAT;

#define LICENSE_SUBKEY "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\xxx"
#define LICENSE_VALUE_NAME "LICENSE"
#define HOMEFILE "USERPROFILE"

// https://technet.microsoft.com/zh-cn/office/aa365917(v=vs.80)
// GetAdaptersInfo
typedef NR_DWORD (WINAPI *PtrGetAdaptersInfoFun)(_Out_ PIP_ADAPTER_INFO pAdapterInfo,
        _Inout_ PULONG pOutBufLen);

// https://technet.microsoft.com/zh-cn/aa365915(v=vs.105)
// GetAdaptersAddresses
typedef NR_ULONG (WINAPI *PtrGetAdaptersAddressesFun)(_In_ ULONG Family,
        _In_ ULONG Flags,
        _In_ PVOID Reserved,
        _Inout_ PIP_ADAPTER_ADDRESSES AdapterAddresses,
        _Inout_ PULONG SizePointer);

// https://technet.microsoft.com/zh-cn/aa365968(v=vs.90)
// GetNetworkParams
typedef NR_DWORD (WINAPI *PtrGetNetworkParamsFun)(_Out_ PFIXED_INFO pFixedInfo,
        _In_ PULONG pOutBufLen);


static PtrGetAdaptersAddressesFun g_ptrGetAdaptersAddressesFun = NR_NULL;
static PtrGetAdaptersInfoFun g_ptrGetAdaptersInfoFun = NR_NULL;
static PtrGetNetworkParamsFun g_ptrGetNetworkParamsFun = NR_NULL;


NR_LOCAL NR_INT InterfaceListingWinXP(NR_INT64 *pMacList, NR_UINT lstSize, NR_UINT *pnCnt)
{
    IP_ADAPTER_ADDRESSES staticBuf[2]; // 2 is arbitrary
    PIP_ADAPTER_ADDRESSES pAdapter = staticBuf;
    NR_ULONG bufSize = sizeof(staticBuf);
    NR_ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
    NR_ULONG retVal = g_ptrGetAdaptersAddressesFun(AF_UNSPEC, flags, NR_NULL, pAdapter, &bufSize);

    if (retVal == ERROR_BUFFER_OVERFLOW) {
        // need more memory
        pAdapter = (IP_ADAPTER_ADDRESSES *)NR_MALLOC(bufSize);

        if (!pAdapter) {
            NR_LOG_ERROR("GetAdaptersAddresses() failed!");
            return NR_ERROR;
        }

        // try again
        if (g_ptrGetAdaptersAddressesFun(AF_UNSPEC, flags, NR_NULL, pAdapter, &bufSize) != ERROR_SUCCESS) {
            NR_LOG_ERROR("GetAdaptersAddresses() failed again.");
            NR_FREE(pAdapter);
            return NR_ERROR;
        }
    } else if (retVal != ERROR_SUCCESS) {
        NR_LOG_ERROR("GetAdaptersAddresses() failed, ret=%lu", retVal);
        return NR_ERROR;
    }

    // iterate over the list and add the entries to our listing
    NR_UINT nIdx = 0;
    PIP_ADAPTER_ADDRESSES ptr;

    for (ptr = pAdapter; ptr; ptr = ptr->Next) {
        if (ptr->PhysicalAddressLength == 0) {
            continue;
        }

        if (ptr->IfType != IF_TYPE_ETHERNET_CSMACD) {
            continue;
        }

        if (nIdx >= lstSize) {
            NR_LOG_INFO("The number of adapters is greater than %u", lstSize);
            break;
        }

        NR_INT64 nMacId = 0;
        NR_DWORD i;

        for (i = 0; i < ptr->PhysicalAddressLength; ++i) {
            nMacId += ((NR_INT64)ptr->PhysicalAddress[i]) << (i * 8);
        }

#ifdef NR_DEBUG_ENABLE
        char sMacId[100] = {'\0'};

        for (i = 0; i < ptr->PhysicalAddressLength; ++i) {
            char sMacTmp[10] = {'\0'};

            if (i == ptr->PhysicalAddressLength - 1) {
                sprintf(sMacTmp, "%02x", ptr->PhysicalAddress[i]);
            } else {
                sprintf(sMacTmp, "%02x:", ptr->PhysicalAddress[i]);
            }

            strcat(sMacId, sMacTmp);
        }

        NR_PRINTF("macid:  %s\n", sMacId);
        NR_PRINTF("macid:  %lld\n", nMacId);
#endif

        if (nMacId == 0) {
            continue;
        }

        NR_UINT nMacNo = 0;

        for (nMacNo = 0; nMacNo < nIdx; ++nMacNo)  {
            if (pMacList[nMacNo] == nMacId) {
                break;
            }
        }

        if (nMacNo == nIdx) {
            pMacList[nIdx] = nMacId;
            nIdx++;
        }
    }

    *pnCnt = nIdx;
    NR_FREE(pAdapter);
    return NR_OK;
}

NR_LOCAL NR_INT InterfaceListingWin2k(NR_INT64 *pMacList, NR_UINT lstSize, NR_UINT *pnCnt)
{
    IP_ADAPTER_INFO staticBuf[2]; // 2 is arbitrary
    PIP_ADAPTER_INFO pAdapter = staticBuf;
    NR_ULONG bufSize = sizeof staticBuf;
    NR_DWORD retVal = g_ptrGetAdaptersInfoFun(pAdapter, &bufSize);

    if (retVal == ERROR_BUFFER_OVERFLOW) {
        // need more memory
        pAdapter = (IP_ADAPTER_INFO *)NR_MALLOC(bufSize);

        if (!pAdapter) {
            NR_LOG_ERROR("GetAdaptersInfo() failed!");
            return NR_ERROR;
        }

        // try again
        if (g_ptrGetAdaptersInfoFun(pAdapter, &bufSize) != ERROR_SUCCESS) {
            NR_LOG_ERROR("GetAdaptersInfo() failed again.");
            NR_FREE(pAdapter);
            return NR_ERROR;
        }
    } else if (retVal != ERROR_SUCCESS) {
        NR_LOG_ERROR("GetAdaptersInfo() failed, ret=%lu", retVal);
        return NR_ERROR;
    }

    // iterate over the list and add the entries to our listing
    NR_UINT nIdx = 0;
    PIP_ADAPTER_INFO ptr;

    for (ptr = pAdapter; ptr; ptr = ptr->Next) {
        if (ptr->AddressLength == 0) {
            continue;
        }

        if (ptr->Type != MIB_IF_TYPE_ETHERNET) {
            NR_LOG_INFO("Type: %d", ptr->Type);
            continue;
        }

        if (nIdx >= lstSize) {
            NR_LOG_INFO("The number of adapters is greater than %u", lstSize);
            break;
        }

        NR_INT64 nMacId = 0;
        NR_DWORD i;

        for (i = 0; i < ptr->AddressLength; ++i) {
            nMacId += ((NR_INT64)ptr->Address[i]) << (i * 8);
        }

        if (nMacId == 0) {
            continue;
        }

        NR_UINT nMacNo = 0;

        for (nMacNo = 0; nMacNo < nIdx; ++nMacNo)  {
            if (pMacList[nMacNo] == nMacId) {
                break;
            }
        }

        if (nMacNo == nIdx) {
            pMacList[nIdx] = nMacId;
            nIdx++;
        }
    }

    *pnCnt = nIdx;
    NR_FREE(pAdapter);
    return NR_OK;
}

#elif defined(__linux__) || defined(__LINUX__) || defined(Q_OS_LINUX)

//#include <asm/io.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#include <sys/io.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <net/if.h>
#include <net/if_arp.h>
#include <scsi/sg.h>

#include <linux/hdreg.h>
#include <linux/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/procfs.h>

#include <features.h>
#include <netpacket/packet.h>

#include <fstream>
#include <iostream>

using namespace std;

#define SG_CHECK_CONDITION      0x02
#define SG_DRIVER_SENSE         0x08
#define SG_ATA_16               0x85
#define SG_ATA_16_LEN           16
#define SG_ATA_LBA48            1
#define SG_ATA_PROTO_NON_DATA   (3<<1)
#define SG_ATA_PROTO_PIO_IN     (4<<1)
#define SG_ATA_PROTO_PIO_OUT    (5<<1)
#define SG_ATA_PROTO_DMA        (6<<1)
#define SG_ATA_PROTO_UDMA_IN    (11<<1) /* not yet supported in libata */
#define SG_ATA_PROTO_UDMA_OUT   (12<<1) /* not yet supported in libata */
#define ATA_USING_LBA           (1<<6)

#define START_SERIAL            10  /* ASCII serial number */
#define LENGTH_SERIAL           4  /* 10 words (8 bytes or characters) */

enum {
    ATA_OP_CHECKPOWERMODE1        = 0xe5,
    ATA_OP_CHECKPOWERMODE2        = 0x98,
    ATA_OP_DOORLOCK               = 0xde,
    ATA_OP_DOORUNLOCK             = 0xdf,
    ATA_OP_FLUSHCACHE             = 0xe7,
    ATA_OP_FLUSHCACHE_EXT         = 0xea,
    ATA_OP_IDENTIFY               = 0xec,
    ATA_OP_PIDENTIFY              = 0xa1,
    ATA_OP_SECURITY_DISABLE       = 0xf6,
    ATA_OP_SECURITY_ERASE_PREPARE = 0xf3,
    ATA_OP_SECURITY_ERASE_UNIT    = 0xf4,
    ATA_OP_SECURITY_FREEZE_LOCK   = 0xf5,
    ATA_OP_SECURITY_SET_PASS      = 0xf1,
    ATA_OP_SECURITY_UNLOCK        = 0xf2,
    ATA_OP_SETFEATURES            = 0xef,
    ATA_OP_SETIDLE1               = 0xe3,
    ATA_OP_SETIDLE2               = 0x97,
    ATA_OP_SLEEPNOW1              = 0xe5,
    ATA_OP_SLEEPNOW2              = 0x99,
    ATA_OP_SMART                  = 0xb0,
    ATA_OP_STANDBYNOW1            = 0xe0,
    ATA_OP_STANDBYNOW2            = 0x94,
};

enum {
    SG_CDB2_TLEN_NODATA     = 0 << 0,
    SG_CDB2_TLEN_FEAT       = 1 << 0,
    SG_CDB2_TLEN_NSECT      = 2 << 0,
    SG_CDB2_TLEN_BYTES      = 0 << 2,
    SG_CDB2_TLEN_SECTORS    = 1 << 2,
    SG_CDB2_TDIR_TO_DEV     = 0 << 3,
    SG_CDB2_TDIR_FROM_DEV   = 1 << 3,
    SG_CDB2_CHECK_COND      = 1 << 5,
};

#define MAXINTERFACES   16

#ifndef MAX_IFINDEX
#define MAX_IFINDEX 8
#endif

const char sNRLicenseDir[100] = "/users/ems";
const char sNRLicenseFile[100] = "/users/ems/.nrlicense";
#define HOMEFILE "HOME"
#define USER "USER"
#define USERNAME "USERNAME"

#elif defined(__sun) || defined(__solaris__) || defined(__SOLARIS__) || defined(Q_OS_SOLARIS)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/procfs.h>
#include <sys/sockio.h>
#include <sys/scsi/generic/commands.h>
#include <sys/scsi/generic/inquiry.h>
#include <sys/scsi/impl/uscsi.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>

#include <fstream.h>
#include "iostream.h"

using namespace std;

#define MAXINTERFACES   16

const char sNRLicenseDir[100] = "/users/ems";
const char sNRLicenseFile[100] = "/users/ems/.nrlicense";
#define HOMEFILE "HOME"
#define USER "USER"
#define USERNAME "USERNAME"

char *GetStrStr(const char *src, const char *dest)
{
    if (strlen(dest) <= 0) {
        return NR_NULL;
    }

    char *sTempstr = (char *)NR_MALLOC(256);
    memset(sTempstr, 0, 101);
    char ststr[256] = {'\0'};
    char ssstr[256] = {'\0'};
    memcpy(ststr, src, 256);
    int nSrcLen = strlen(src);
    int nDestLen = strlen(dest);
    int nIdx = 0;
    int i = 0;
    int j = 0;
    int offset = 0;

    while (i < nSrcLen) {
        sscanf(ststr, "%[^ ]", ssstr);

        if (strcasecmp(ssstr, dest) == 0) {
            while (ststr[strlen(ssstr) + offset + 1] == ' ') {
                offset++;
            }

            if (strcasecmp(dest, "Vendor:") == 0) {
                sscanf(ststr + strlen(ssstr) + 1 + offset, "%[^Product]", sTempstr);
            } else if (strcasecmp(dest, "Product:") == 0) {
                sscanf(ststr + strlen(ssstr) + 1 + offset, "%[^Revision]", sTempstr);
            } else if (strcasecmp(dest, "Revision:") == 0) {
                sscanf(ststr + strlen(ssstr) + 1 + offset, "%[^Serial]", sTempstr);
            } else {
                sscanf(ststr + strlen(ssstr) + 1 + offset, "%[^ ]", sTempstr);
            }

            break;
        }

        i = i + strlen(ssstr) + 1;
        memset(ststr, 0, sizeof(ststr));

        while (src[i] == ' ') {
            i++;
        }

        memcpy(ststr, src + i, 256);
//      NR_PRINTF("%s\n", ststr);
    }

    return sTempstr;
}

#elif defined(__aix__) || defined(__AIX__) || defined(Q_OS_AIX) || defined(_AIX)

//#include <sys/sockio.h>
//#include <sys/scsi/generic/commands.h>
//#include <sys/scsi/generic/inquiry.h>
//#include <sys/scsi/impl/uscsi.h>

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ndd_var.h>
#include <sys/kinfo.h>

#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/procfs.h>

#include <fstream.h>
#include "iostream.h"

using namespace std;

const char sNRLicenseDir[100] = "/users/ems";
const char sNRLicenseFile[100] = "/users/ems/.nrlicense";
#define HOMEFILE "HOME"
#define USER "USER"
#define USERNAME "USERNAME"

//#include <net/if.h>
//#include <net/if_arp.h>

#include <libperfstat.h>
#include <sys/stat.h>

extern "C"
{
    getkerninfo ( int, struct kinfo_ndd *, int *, NR_INT64 );
}

#elif defined(Q_OS_HPUX) || defined(__HPUX) || defined(__hpux)

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream.h>
#include "iostream.h"

const char sNRLicenseDir[100] = "/users/ems";
const char sNRLicenseFile[100] = "/users/ems/.nrlicense";
#define HOMEFILE "HOME"
#define USER "USER"
#define USERNAME "USERNAME"

#endif

NR_LOCAL NR_INT GetMacIDList(NR_INT64 *pMacList, NR_UINT lstSize, NR_UINT *pnCnt)
{
#if defined(WIN32)
    static NR_BOOL done = NR_FALSE;

    if (done == NR_FALSE) {
        done = NR_TRUE;
        HINSTANCE iphlpapiHnd = LoadLibrary(L"iphlpapi");

        if (iphlpapiHnd == NR_NULL) {
            return NR_ERROR;
        }

#if defined(WINCE) || defined(_WIN32_WCE)
        g_ptrGetAdaptersInfoFun = (PtrGetAdaptersInfoFun)GetProcAddress(iphlpapiHnd, L"GetAdaptersInfo");
        g_ptrGetAdaptersAddressesFun = (PtrGetAdaptersAddressesFun)GetProcAddress(iphlpapiHnd, L"GetAdaptersAddresses");
        g_ptrGetNetworkParamsFun = (PtrGetNetworkParamsFun)GetProcAddress(iphlpapiHnd, L"GetNetworkParams");
#else
        g_ptrGetAdaptersInfoFun = (PtrGetAdaptersInfoFun)GetProcAddress(iphlpapiHnd, "GetAdaptersInfo");
        g_ptrGetAdaptersAddressesFun = (PtrGetAdaptersAddressesFun)GetProcAddress(iphlpapiHnd, "GetAdaptersAddresses");
        g_ptrGetNetworkParamsFun = (PtrGetNetworkParamsFun)GetProcAddress(iphlpapiHnd, "GetNetworkParams");
#endif
    }

    if (g_ptrGetAdaptersAddressesFun != NR_NULL) {
        InterfaceListingWinXP(pMacList, lstSize, pnCnt);
    } else if (g_ptrGetAdaptersInfoFun != NR_NULL) {
        InterfaceListingWin2k(pMacList, lstSize, pnCnt);
    }

    return NR_OK;
#elif (defined(__linux__) || defined(__linux)) &&  __GLIBC__ - 0 >= 2 && __GLIBC_MINOR__ - 0 >= 1
    int socket;

    if ((socket = qt_safe_socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) {
        return NR_ERROR;      // error
    }

    ifaddrs *interfaceListing;

    if (getifaddrs(&interfaceListing) == -1) {
        ::close(socket);
        return NR_ERROR;
    }

    // on Linux we use AF_PACKET and sockaddr_ll to obtain hHwAddress
    NR_INT64 nMacId = 0;
    NR_UINT nIdx = 0;

    for (ifaddrs *ptr = interfaceListing; ptr; ptr = ptr->ifa_next) {
        if (!ptr->ifa_addr) {
            continue;
        }

        if (nIdx >= lstSize) {
            break;
        }

        if (ptr->ifa_addr->sa_family == AF_PACKET) {
            sockaddr_ll *sll = (sockaddr_ll *)ptr->ifa_addr;
            int i;

            for (i = 0; i < sll->sll_halen; ++i) {
                nMacId += ((NR_INT64)sll->sll_addr[i]) << (i * 8);
            }

#ifdef NR_LOG_ENABLE
            char sMacId[100] = {'\0'};

            for (i = 0; i < sll->sll_halen; ++i) {
                char sMacTemp[10] = {'\0'};

                if (i == sll->sll_halen - 1) {
                    sprintf(sMacTemp, "%02x", (NR_BYTE)sll->sll_addr[i]);
                } else {
                    sprintf(sMacTemp, "%02x:", (NR_BYTE)sll->sll_addr[i]);
                }

                strcat(sMacId, sMacTemp);
            }

            NR_PRINTF("macid:  %s\n", sMacId);
            NR_PRINTF("macid:  %lld\n", nMacId);
#endif

            if (nMacId == 0) {
                continue;
            }

            NR_UINT nMacNo = 0;

            for (nMacNo = 0; nMacNo < nIdx; ++nMacNo) {
                if (pMacList[nMacNo] == nMacId) {
                    break;
                }
            }

            if (nMacNo == nIdx) {
                pMacList[nIdx] = nMacId;
                nIdx++;
            }
        }
    }

    *pnCnt = nIdx;
    freeifaddrs(interfaceListing);
    ::close(socket);
    return NR_OK;
#elif defined(__sun) || defined(__solaris__) || defined(__SOLARIS__)
    int fd, intrface;
    struct ifreq buf[MAXINTERFACES];
    struct arpreq arp;
    struct ifconf ifc;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        return NR_ERROR;      // error
    }

    ifc.ifc_len = sizeof buf;
    ifc.ifc_buf = ( caddr_t ) buf;
    NR_INT64 nMacId = 0;
    NR_UINT nIdx = 0;

    if (ioctl(fd, SIOCGIFCONF, (char *)&ifc) >= 0) {
        intrface = ifc.ifc_len / sizeof(struct ifreq);

        while (intrface-- > 0) {
            /* this section can't get Hardware Address,I don't know whether the reason is module driver*/
            arp.arp_pa.sa_family = AF_INET;
            arp.arp_ha.sa_family = AF_INET;
            ((struct sockaddr_in *)&arp.arp_pa)->sin_addr.s_addr =
                ((struct sockaddr_in *)(&buf[intrface].ifr_addr))->sin_addr.s_addr;

            if (nIdx >= lstSize) {
                break;
            }

            nMacId = 0;

            if ((ioctl(fd, SIOCGARP, (char *)&arp)) >= 0) {
                nMacId += (((NR_INT64)(arp.arp_ha.sa_data[0])) << 40);
                nMacId += (((NR_INT64)(arp.arp_ha.sa_data[1])) << 32);
                nMacId += (((NR_INT64)(arp.arp_ha.sa_data[2])) << 24);
                nMacId += (((NR_INT64)(arp.arp_ha.sa_data[3])) << 16);
                nMacId += (((NR_INT64)(arp.arp_ha.sa_data[4])) << 8);
                nMacId += (NR_INT64)(arp.arp_ha.sa_data[5]);
#ifdef NR_LOG_ENABLE
                char sMacId[100] = {'\0'};
                sprintf(sMacId, "%02x:%02x:%02x:%02x:%02x:%02x",
                        (NR_BYTE)arp.arp_ha.sa_data[0], (NR_BYTE)arp.arp_ha.sa_data[1],
                        (NR_BYTE)arp.arp_ha.sa_data[2], (NR_BYTE)arp.arp_ha.sa_data[3],
                        (NR_BYTE)arp.arp_ha.sa_data[4], (NR_BYTE)arp.arp_ha.sa_data[5]);
                NR_PRINTF("macid:  %s\n", sMacId);
                NR_PRINTF("macid:  %lld\n", nMacId);
#endif

                if (nMacId == 0) {
                    continue;
                }

                NR_UINT nMacNo = 0;

                for (nMacNo = 0; nMacNo < nIdx; ++nMacNo) {
                    if (pMacList[nMacNo] == nMacId) {
                        break;
                    }
                }

                if (nMacNo == nIdx) {
                    pMacList[nIdx] = nMacId;
                    nIdx++;
                }
            }
        } // while

        close(fd);
        *pnCnt = nIdx;
        return NR_OK;
    }

    close(fd);
    return NR_ERROR;
#elif defined(__aix__) || defined(__AIX__) || defined(_AIX)
    NR_INT64 nMacId = 0;
    NR_UINT nIdx = 0;
#ifdef SIOCGIFHWADDR
    // has SIOCGIFHWADDR
    int socket;

    if ((socket = qt_safe_socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) {
        return NR_ERROR;      // error
    }

    // use if_nameindex
    struct if_nameindex *interfaceList = ::if_nameindex();
    struct if_nameindex *ptr;

    for (ptr = interfaceList; ptr && ptr->if_name; ++ptr) {
        if (nIdx >= lstSize) {
            break;
        }

        int nlength = 0;
        ifreq req;
        memset(&req, 0, sizeof(ifreq));

        if (sizeof(ptr->if_name) - 1 > sizeof(req.ifr_name) - 1) {
            nlength = sizeof(req.ifr_name) - 1;
        } else {
            nlength = sizeof(ptr->if_name) - 1;
        }

        memcpy(req.ifr_name, ptr->if_name, nlength);
        // Get the HW address
        nMacId = 0;

        if (qt_safe_ioctl(socket, SIOCGIFHWADDR, &req) >= 0) {
            uchar *addr = (uchar *)&req.ifr_addr;
            int i;

            for (i = 0; i < 6; i++) {
                nMacId += ((NR_INT64)addr[i]) << (i * 8);
            }

#ifdef NR_LOG_ENABLE
            char sMacId[100] = {'\0'};
            sprintf(sMacId, "%02x:%02x:%02x:%02x:%02x:%02x", addr[0],
                    addr[1], addr[2], addr[3], addr[4], addr[5]);
            NR_PRINTF("macid:   %s\n", sMacId);
#endif
            free(addr);
        }

        if (nMacId == 0) {
            continue;
        }

        NR_UINT nMacNo = 0;

        for (nMacNo = 0; nMacNo < nIdx; ++nMacNo) {
            if (pMacList[nMacNo] == nMacId) {
                break;
            }
        }

        if (nMacNo == nIdx) {
            pMacList[nIdx] = nMacId;
            nIdx++;
        }
    }

    if_freenameindex(interfaceList);
    ::close(socket);
#else

    // no SIOCGIFHWADDR
    do {
        int size = 0;
        struct kinfo_ndd *nddp;
        void *end;
        size = getkerninfo(KINFO_NDD, 0, 0, 0);

        if (size <= 0) {
            return NR_ERROR;
        }

        nddp = (struct kinfo_ndd *)NR_MALLOC(size);

        if (!nddp) {
            return NR_ERROR;
        }

        if (getkerninfo(KINFO_NDD, nddp, &size, 0) < 0) {
            NR_FREE(nddp);
            return NR_ERROR;
        }

        end = nddp + size;
        int nSizeIdx = 0;

        while ((nddp < end) && nSizeIdx < size) {
            if (nIdx >= lstSize) {
                break;
            }

            nSizeIdx++;
            nMacId = 0;
            char *ptest = strstr(nddp->ndd_alias, "ent");
            char *ptest1 = strstr(nddp->ndd_name, "ent");

            if (ptest || ptest1) {
                int i;

                for (i = 0; i < 6; ++i) {
                    nMacId += ((NR_INT64)nddp->ndd_addr[i]) << (i * 8);
                }

#ifdef NR_LOG_ENABLE
                char sMacId[100] = {'\0'};
                NR_PRINTF("nddp->ndd_alias:%s, nddp->ndd_name:%s\n", nddp->ndd_alias, nddp->ndd_name);
                NR_PRINTF("%02x:%02x:%02x:%02x:%02x:%02x\n", nddp->ndd_addr[0], nddp->ndd_addr[1],
                          nddp->ndd_addr[2], nddp->ndd_addr[3], nddp->ndd_addr[4], nddp->ndd_addr[5]);
                sprintf(sMacId, "%02x:%02x:%02x:%02x:%02x:%02x", nddp->ndd_addr[0], nddp->ndd_addr[1],
                        nddp->ndd_addr[2], nddp->ndd_addr[3], nddp->ndd_addr[4], nddp->ndd_addr[5]);
                NR_PRINTF("macid:   %s\n", sMacId);
#endif
            }

            if (nMacId == 0) {
                nddp++;
                continue;
            }

            NR_UINT nMacNo = 0;

            for (nMacNo = 0; nMacNo < nIdx; ++nMacNo) {
                if (pMacList[nMacNo] == nMacId) {
                    break;
                }
            }

            if (nMacNo == nIdx) {
                pMacList[nIdx] = nMacId;
                nIdx++;
            }

            nddp++;
        }
    } while (0);

#endif
    *pnCnt = nIdx;
    return NR_OK;
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
    int socket;

    if ((socket = qt_safe_socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) {
        return NR_ERROR;      // error
    }

    ifaddrs *interfaceListing;

    if (getifaddrs(&interfaceListing) == -1) {
        ::close(socket);
        return NR_ERROR;
    }

    // on NetBSD we use AF_LINK and sockaddr_dl
    // scan the list for that family
    NR_INT64 nMacId = 0;
    NR_UINT nIdx = 0;
    ifaddrs *ptr;

    for (ptr = interfaceListing; ptr; ptr = ptr->ifa_next) {
        if (nIdx >= lstSize) {
            break;
        }

        if (ptr->ifa_addr && ptr->ifa_addr->sa_family == AF_LINK) {
            sockaddr_dl *sdl = (sockaddr_dl *)ptr->ifa_addr;
            int i;

            for (i = 0; i < sdl->sdl_alen; ++i) {
                nMacId += ((NR_INT64)sdl->sdl_alen[i]) << (i * 8);
            }

            if (nMacId == 0) {
                continue;
            }

            NR_UINT nMacNo = 0;

            for (nMacNo = 0; nMacNo < nIdx; ++nMacNo) {
                if (pMacList[nMacNo] == nMacId) {
                    break;
                }
            }

            if (nMacNo == nIdx) {
                pMacList[nIdx] = nMacId;
                nIdx++;
            }
        }
    }

    *pnCnt = nIdx;
    freeifaddrs(interfaceListing);
    ::close(socket);
    return NR_OK;
#else
    return NR_ERROR;
#endif
    return NR_ERROR;
}

NR_INT CreateCPUID(NR_INT64 *pCpuID)
{
#if defined(WIN32) || defined(Q_OS_WIN32)
    /*
     * https://technet.microsoft.com/zh-cn/interopmigration/ms724958(v=vs.90)
     * cpuID is not the serial number of the CPU, but a combination of the following three variables.
     *
     * 1. wProcessorArchitecture:
     *      The processor architecture of the installed operating system.
     * This member can be one of the following values.
     *
     * PROCESSOR_ARCHITECTURE_AMD64     9       x64(AMD or Intel)
     * PROCESSOR_ARCHITECTURE_ARM       5       ARM
     * PROCESSOR_ARCHITECTURE_ARM64     12      ARM64
     * PROCESSOR_ARCHITECTURE_IA64      6       Intel Itanium-based
     * PROCESSOR_ARCHITECTURE_INTEL     0       x86
     * PROCESSOR_ARCHITECTURE_INTEL
     * PROCESSOR_ARCHITECTURE_UNKNOWN   0xffff  Unknown architecture
     *      Windows NT: PROCESSOR_ARCHITECTURE_MIPS
     *      Windows NT: PROCESSOR_ARCHITECTURE_ALPHA
     *      Windows NT: PROCESSOR_ARCHITECTURE_PPC
     * ================================================================================================
     * 2. wProcessorRevision
     * The architecture-dependent processor revision. The following table shows how the revision value is
     * assembled for each type of processor architecture.
     *
     *  PROCESSOR_INTEL_386
     *  PROCESSOR_INTEL_486
     *  PROCESSOR_INTEL_PENTIUM
     *      Windows NT: PROCESSOR_MIPS_R4000
     *      Windows NT: PROCESSOR_ALPHA_21064
     * ------------------------------------------------------------------------------------------------
     *   Processor             |            Value
     * ------------------------|-----------------------------------------------------------------------
     *   Intel Pentium, Cyrix, |  The high byte is the model and the low byte is the stepping. For example,
     *   or NextGen 586        |  if the value is xxyy, the model number and stepping can be displayed as follows:
     *                         |  Model xx, Stepping yy
     * ------------------------|-----------------------------------------------------------------------
     *   Intel 80386 or 80486  |  A value of the form xxyz.
     *                         |  If xx is equal to 0xFF, y - 0xA is the model number, and z is the stepping identifier.
     *                         |  If xx is not equal to 0xFF, xx + 'A' is the stepping letter and yz is the minor stepping.
     * ------------------------|-----------------------------------------------------------------------
     *   ARM                   |  Reserved.
     * ------------------------------------------------------------------------------------------------
     * ================================================================================================
     * 3. wProcessorLevel
     *      The architecture-dependent processor level. It should be used only for display purposes.
     * To determine the feature set of a processor, use the IsProcessorFeaturePresent function.
     * If wProcessorArchitecture is PROCESSOR_ARCHITECTURE_INTEL, wProcessorLevel is defined by the CPU vendor.
     * If wProcessorArchitecture is PROCESSOR_ARCHITECTURE_IA64, wProcessorLevel is set to 1.
     */
    SYSTEM_INFO sysInfo;
    NR_BZERO(&sysInfo, sizeof(sysInfo));
    GetSystemInfo(&sysInfo);
    *pCpuID = sysInfo.wProcessorArchitecture +
              (((NR_INT64)sysInfo.wProcessorRevision) << 16) +
              (((NR_INT64)sysInfo.wProcessorLevel) << 32);
    return NR_OK;
#elif defined(__linux__) || defined(__LINUX__)
    /*
     * Whether the serial number of CPU can be obtained depends on
     * whether the bit of the 18th bit of edx is 1 when eax=01h.
     *
     * If not 1, the serial number is not supported and edx+ecx is used as cpuid.
     * If 1, the serial number is supported, and the data in ecx and edx is the CPU's serial number
     * Ecx low 32 bit, edx high 32 bit;
     */
    NR_DWORD dweax, dwebx, dwecx, dwedx, unuseda, unusedb, unusedc, unusedd;
    // execute cpuid，eax=1
    asm ( "cpuid"
          : "=a" ( unuseda ),
          "=b" ( unusedb ),
          "=c" ( unusedc ),
          "=d" ( unusedd )
          : "a" ( 1 ) );
    int isSupport = unusedd & (1 << 18);

    if (!isSupport) {
        *pCpuID += (NR_INT64)unusedc;
        *pCpuID += (NR_INT64)unusedd << 32;
        return NR_OK;
    }

    // execute cpuid，eax=3
    asm ( "cpuid"
          : "=a" ( dweax ),
          "=b" ( dwebx ),
          "=c" ( dwecx ),
          "=d" ( dwedx )
          : "a" ( 3 ) );
    *pCpuID += (NR_INT64)dwecx;
    *pCpuID += (NR_INT64)dwedx << 32;
    return NR_OK;
#elif defined(__sun) || defined(__solaris__) || defined(__SOLARIS__) || defined(Q_OS_SOLARIS)
#if defined(__i386) // x86
    NR_DWORD dweax, dwebx, dwecx, dwedx, unuseda, unusedb, unusedc, unusedd;
    asm volatile (
        "pushl %%ebx      \n\t" /* save %ebx */
        "cpuid            \n\t"
        "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
        "popl %%ebx       \n\t" /* restore the old %ebx */
        : "=a" ( unuseda ),
        "=r" ( unusedb ),
        "=c" ( unusedc ),
        "=d" ( unusedd )
        : "a" ( 1 )
        : "cc" );
    int isSupport = unusedd & (1 << 18);

    if (!isSupport) {
        *pCpuID += (NR_INT64)unusedc;
        *pCpuID += (NR_INT64)unusedd << 32;
        return NR_OK;
    }

    asm volatile (
        "pushl %%ebx      \n\t" /* save %ebx */
        "cpuid            \n\t"
        "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
        "popl %%ebx       \n\t" /* restore the old %ebx */
        : "=a" ( dweax ),
        "=r" ( dwebx ),
        "=c" ( dwecx ),
        "=d" ( dwedx )
        : "a" ( 3 )
        : "cc" );
    *pCpuID += (NR_INT64)dwecx;
    *pCpuID += (NR_INT64)dwedx << 32;
#elif defined(__sparc) // sparc
#ifdef __ASSEMBLY__
    int idcpu;
    __asm__ __volatile__(
        "sethi %%hi(___b_hard_smp_processor_id), %0\n\t"
        "sethi %%hi(boot_cpu_id), %0\n\t"
        "ldub [%0 + %%lo(boot_cpu_id)], %0\n\t" :
        "=&r" (idcpu));
    __asm__ __volatile__(
        "rd %%tbr, %0\n\t"
        "srl %0, 12, %0\n\t"
        "and %0, 3, %0\n\t"
        :"=&r" (idcpu));
#endif
    NR_DWORD dweax, dwebx, dwecx, dwedx, unuseda, unusedb, unusedc, unusedd;
    __asm__ volatile (
        "pushl %%ebx      \n\t" /* save %ebx */
        "cpuid            \n\t"
        "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
        "popl %%ebx       \n\t" /* restore the old %ebx */
        : "=a" ( unuseda ),
        "=r" ( unusedb ),
        "=c" ( unusedc ),
        "=d" ( unusedd )
        : "a" ( 1 )
        : "cc"
    );
    int isSupport = unusedd & (1 << 18);

    if (!isSupport) {
        *pCpuID += (NR_INT64)unusedc;
        *pCpuID += (NR_INT64)unusedd << 32;
        return NR_OK;
    }

    __asm__ __volatile__ (
        "pushl %%ebx      \n\t" /* save %ebx */
        "cpuid            \n\t"
        "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
        "popl %%ebx       \n\t" /* restore the old %ebx */
        : "=a" ( dweax ),
        "=r" ( dwebx ),
        "=c" ( dwecx ),
        "=d" ( dwedx )
        : "a" ( 3 )
        : "cc" );
    *pCpuID += (NR_INT64)dwecx;
    *pCpuID += (NR_INT64)dwedx << 32;
#endif
    return NR_OK;
#elif defined(__aix__) || defined(__AIX__) || defined(_AIX)
    NR_DWORD dweax, dwebx, dwecx, dwedx, unuseda, unusedb, unusedc, unusedd;
    asm volatile(
        "pushl %%ebx      \n\t" /* save %ebx */
        "cpuid            \n\t"
        "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
        "popl %%ebx       \n\t" /* restore the old %ebx */
        :"=a"(unuseda),
        "=b"(unusedb),
        "=c"(unusedc),
        "=d"(unusedd)
        :"a"(1)
        :"cc");
    int isSupport = unusedd & (1 << 18);

    if (!isSupport) {
        *pCpuID += (NR_INT64)unusedc;
        *pCpuID += (NR_INT64)unusedd << 32;
        return NR_OK;
    }

    asm volatile(
        "pushl %%ebx      \n\t" /* save %ebx */
        "cpuid            \n\t"
        "movl %%ebx, %1   \n\t" /* save what cpuid just put in %ebx */
        "popl %%ebx       \n\t" /* restore the old %ebx */
        :"=a"(dweax),
        "=r"(dwebx),
        "=c"(dwecx),
        "=d"(dwedx)
        :"a"(3)
        :"cc");
    *pCpuID += (NR_INT64)dwecx;
    *pCpuID += (NR_INT64)dwedx << 32;
    return NR_OK;
#elif defined(Q_OS_HPUX) || defined(__HPUX) || defined(__hpux)
    *pCpuID = 0;
    return NR_ERROR;
#endif
    return NR_ERROR;
}

NR_INT CreateHardID(NR_INT64 *pHardID)
{
#if defined(WIN32) || defined(Q_OS_WIN32)
    // get disk driver C: information
    char szVolumename[64], szFileSystemNameBuffer[32];
    NR_DWORD dwVolumeSerialNumber = 0;
    NR_DWORD dwMaximumComponentLength = 0;
    NR_DWORD dwFileSystemFlags = 0;
    GetVolumeInformationA("C:\\", szVolumename, 64,
                          &dwVolumeSerialNumber, &dwMaximumComponentLength,
                          &dwFileSystemFlags, szFileSystemNameBuffer, 32 );
    *pHardID += ((NR_INT64)dwVolumeSerialNumber ) << 8;
    return NR_OK;
#elif defined(__linux__) || defined(__LINUX__)
    int fd;
    struct hd_driveid hid;
    FILE *fp;
    DIR *dir_name;
    struct dirent *Device;
    char line[0x100], *disk, *root, *p;
    fp = fopen("/etc/mtab", "r");
    fd = -1;

    if (fp != NR_NULL) {
        while (fgets(line, sizeof line, fp) != NR_NULL) {
            disk = strtok(line, " ");

            if (disk == NR_NULL) {
                continue;
            }

            root = strtok(NR_NULL, " ");

            if (root == NR_NULL) {
                continue;
            }

            if (strcmp(root, "/") == 0) {
                for (p = disk + strlen(disk) - 1; p >= disk && isdigit(*p); --p) {
                    *p = 0;
                }

                fd = open(disk, O_RDONLY);
                break;
            }
        }
    }

    fclose(fp);

    // If no hard disk is found, go to the /dev directory and look for hda or sda
    if (fd < 0) {
//      perror(disk);
        close(fd);
        disk = NR_NULL;
        dir_name = opendir("/dev/");

        while ((Device = readdir(dir_name))) {
            if (!strcmp(Device->d_name, "sda1")) {
                disk = (char *)"/dev/sda";
            } else if (!strcmp(Device->d_name, "hda1")) {
                disk = (char *)"/dev/hda";
            }
        }

        closedir(dir_name);
        fd = open(disk, O_RDONLY);
    }

    if (fd < 0) {
//      perror(disk);
        close(fd);
        *pHardID = 0;
        return NR_ERROR;
    }

    unsigned int i;

    if (ioctl(fd, HDIO_GET_IDENTITY, &hid) != -1) {
        unsigned char *pSerial = hid.serial_no;
        *pHardID = 0;

        for (i = 0; i < 8; ++i) {
            *pHardID += (NR_INT64)pSerial[i] << (i * 8);
        }

        close(fd);
        return NR_OK;
    }

    // If not, then find the following way
    static unsigned char args[512] = { 0 };
//  unsigned short *id = (void *)(args);
    unsigned char *data = (args);
    unsigned int data_bytes = 512;
    unsigned char cdb[SG_ATA_16_LEN] = { 0 };
    unsigned char sb[32], *desc;
    unsigned char ata_status, ata_error;
    struct sg_io_hdr io_hdr;
    // cmdp
    cdb[0] = SG_ATA_16;
    cdb[1] = SG_ATA_PROTO_PIO_IN;
    cdb[2] = SG_CDB2_CHECK_COND;
    cdb[2] |= SG_CDB2_TLEN_NSECT | SG_CDB2_TLEN_SECTORS;
    cdb[2] |= SG_CDB2_TDIR_FROM_DEV;
    cdb[13] = ATA_USING_LBA;
    cdb[14] = ATA_OP_IDENTIFY;
    // sdp
    memset(&(sb[0]), 0, sizeof(sb));
    // sg_io_hdr
    memset(&io_hdr, 0, sizeof(struct sg_io_hdr));
    io_hdr.interface_id     = 'S';
    io_hdr.cmd_len          = SG_ATA_16_LEN;
    io_hdr.mx_sb_len        = sizeof(sb);
    io_hdr.dxfer_direction  = SG_DXFER_FROM_DEV;
    io_hdr.dxfer_len        = data_bytes;
    io_hdr.dxferp           = data;
    io_hdr.cmdp             = cdb;
    io_hdr.sbp              = sb;
    io_hdr.timeout          = 10000; /* msecs */

    // ioctl
    if (ioctl(fd, SG_IO, &io_hdr) == -1) {
        fprintf(stderr, "SG_IO ioctl not supported\n");
        close(fd);
        *pHardID = 0;
        return NR_ERROR;
    }

    // g_io_hdr
    if (io_hdr.host_status || io_hdr.driver_status != SG_DRIVER_SENSE
            || (io_hdr.status && io_hdr.status != SG_CHECK_CONDITION)) {
        errno = EIO;
        close(fd);
        *pHardID = 0;
        return NR_ERROR;
    }

    // dp
    if (sb[0] != 0x72 || sb[7] < 14) {
        errno = EIO;
        close(fd);
        *pHardID = 0;
        return NR_ERROR;
    }

    desc = sb + 8;

    if (desc[0] != 9 || desc[1] < 12) {
        errno = EIO;
        close(fd);
        *pHardID = 0;
        return NR_ERROR;
    }

    ata_error = desc[3];
    ata_status = desc[13];

    if (ata_status & 0x01) {
        /* ERR_STAT */
        errno = EIO;
        close(fd);
        *pHardID = 0;
        return NR_ERROR;
    }

    unsigned char *pHard = data;
    *pHardID = 0;

    for (i = 0; i < 8; ++i) {
        *pHardID += (NR_INT64)pHard[i] << (i * 8);
    }

    close(fd);
    return NR_OK;
#elif defined(__sun) || defined(__solaris__) || defined(__SOLARIS__) || defined(Q_OS_SOLARIS)
    char buf[256] = {'\0'};
    char sVendor[256] = {'\0'};
    char sProduct[256] = {'\0'};
    char sRevision[256] = {'\0'};
    char sSerial[256] = {'\0'};
    char splitch = ' ';
    sprintf(buf, "iostat -E | grep 'Vendor'");
    FILE *fp = popen(buf, "r") ;

    if (fp == NULL) {
        return NR_ERROR;
    }

    while (fgets(buf, 256, fp)) {
        if (strlen(buf) > 0) {
            buf[strlen(buf) - 1] = '\0' ;
        }

//      NR_PRINTF("%s\n", buf);
        char *ssv = GetStrStr(buf, "Vendor:");
        char *ssp = GetStrStr(buf, "Product:");
        char *ssr = GetStrStr(buf, "Revision:");
        char *sse = GetStrStr(buf, "No:");
        strncpy(sVendor, ssv, 256);
        strncpy(sProduct, ssp, 256);
        strncpy(sRevision, ssr, 256);
        strncpy(sSerial, sse, 256);
        free(sse);
        free(ssr);
        free(ssp);
        free(ssv);
//      NR_PRINTF("vendor:%s\n",sVendor);
//      NR_PRINTF("product:%s\n",sProduct);
//      NR_PRINTF("revision:%s\n",sRevision);
//      NR_PRINTF("serial:%s\n",sSerial);
        int nVendor = strlen(sVendor);
        int nProduct = strlen(sProduct);
        int nRevision = strlen(sRevision);
        int nSerial = strlen(sSerial);
//      NR_PRINTF("vendor:%d\n",nVendor);
//      NR_PRINTF("product:%d\n",nProduct);
//      NR_PRINTF("revision:%d\n",nRevision);
//      NR_PRINTF("serial:%d\n",nSerial);
        int i;

        for (i = nVendor - 1; i >= 0; --i) {
            if (nVendor - 1 - i >= 8 || i < 0) {
                break;
            }

            *pHardID += ((NR_INT64)sVendor[i]) << ((nVendor - i - 1) * 8);
        }

//      NR_PRINTF("HardID:%x\n", *pHardID);
        for (i = nProduct - 1; i >= 0; --i) {
            if (nProduct - 1 - i >= 8 || i < 0) {
                break;
            }

            *pHardID += ((NR_INT64)sProduct[i]) << ((nProduct - i - 1) * 8);
        }

//      NR_PRINTF("HardID:%x\n", *pHardID);
        for (i = nRevision - 1; i >= 0; --i) {
            if (nRevision - 1 - i >= 8 || i < 0) {
                break;
            }

            *pHardID += ((NR_INT64)sRevision[i]) << ((nRevision - i - 1) * 8);
        }

//      NR_PRINTF("HardID:%x\n", *pHardID);
        for (i = nSerial - 1; i >= 0; --i) {
            if (nSerial - 1 - i >= 8 || i < 0) {
                break;
            }

            *pHardID += ((NR_INT64)sSerial[i]) << ((nSerial - i - 1) * 8);
        }

//      NR_PRINTF("HardID:%x\n", *pHardID);
        break;
    }

    pclose(fp) ;
    return NR_OK;
#elif defined(__aix__) || defined(__AIX__) || defined(_AIX)
    char buf[256] = {'\0'};
    char sSystemModel[256] = {'\0'};
    char sSerialNumber[256] = {'\0'};
    char sTemp[256] = {'\0'};
    sprintf(buf, "uname -mu");
    FILE *fp = popen(buf, "r") ;

    if (fp == NULL) {
        return NR_ERROR;
    }

    int idx = 0;

    while (fgets(buf, 256, fp)) {
        if (strlen(buf) > 0) {
            buf[strlen(buf) - 1] = '\0';
        }

        idx++;
        sscanf(buf, "%[^ ]", sTemp);
        memcpy(sSystemModel, sTemp, 256);
        //sscanf(sTemp,"%*[^,],%s",sSystemModel);
        sscanf(buf, "%*[^ ]%s", sTemp);
        sscanf(sTemp, "%*[^,], %s", sSerialNumber);
        break;
    }

    int nSystem = strlen(sSystemModel);
    int nSerial = strlen(sSerialNumber);
    int i;

    for (i = nSystem - 1; i >= 0; --i) {
        *pHardID += ((NR_INT64)sSystemModel[i]) << ((nSystem - i - 1) * 8);
    }

    for (i = nSerial - 1; i >= 0; --i) {
        *pHardID += ((NR_INT64)sSerialNumber[i]) << ((nSerial - i - 1) * 8);
    }

    pclose(fp);
    return NR_OK;
#elif defined(Q_OS_HPUX) || defined(__HPUX) || defined(__hpux)
    char buf[256] = {'\0'};
    char sIdentification[256] = {'\0'};
    char sMachineSerial[256] = {'\0'};
    char sTemp[256] = {'\0'};
    int idx = 0;
    sprintf(buf, "uname -i");
    FILE *fp = popen(buf, "r");

    if (fp != NULL) {
        while (fgets(buf, 256, fp)) {
            if (strlen(buf) > 0) {
                buf[strlen(buf) - 1] = '\0';
            }

            idx++;
            memcpy(sIdentification, buf, 256);
            break;
        }
    }

    sprintf(buf, "getconf MACHINE_SERIAL");
    fp = popen(buf, "r");

    if (fp != NULL) {
        idx = 0;

        while (fgets(buf, 256, fp)) {
            if (strlen(buf) > 0) {
                buf[strlen(buf) - 1] = '\0';
            }

            idx++;
            memcpy(sMachineSerial, buf, 256);
            break;
        }
    }

#ifdef NR_LOG_ENABLE
    NR_PRINTF("%s\n", sIdentification);
    NR_PRINTF("%s\n", sMachineSerial);
#endif
    int nIdent = strlen(sIdentification);
    int nSerial = strlen(sMachineSerial);
    int i;

    for (i = nIdent - 1; i >= 0; --i) {
        *pHardID += ((NR_INT64)sIdentification[i]) << ((nIdent - i - 1) * 8);
    }

    for (i = nSerial - 1; i >= 0; --i) {
        *pHardID += ((NR_INT64)sMachineSerial[i]) << ((nSerial - i - 1) * 8);
    }

    pclose(fp);
    return NR_OK;
#endif
    return NR_ERROR;
}

NR_EXTERN LICENSE_EXPORT NR_INT CreateMACID(NR_OUT NR_INT64 *pMacID)
{
#if defined(WIN32) || defined(Q_OS_WIN32)
    ASTAT Adapter;
    NCB Ncb;
    UCHAR uRetCode;
    LANA_ENUM   lenum;
    int      i;
    NR_BZERO(&Ncb, sizeof(Ncb));
    Ncb.ncb_command = NCBENUM;
    Ncb.ncb_buffer = (UCHAR *)&lenum;
    Ncb.ncb_length = sizeof(lenum);
    uRetCode = Netbios(&Ncb);

    for (i = 0; i < lenum.length; ++i) {
        NR_BZERO(&Ncb, sizeof(Ncb));
        Ncb.ncb_command = NCBRESET;
        Ncb.ncb_lana_num = lenum.lana[i];
        uRetCode = Netbios(&Ncb);
        NR_BZERO(&Ncb, sizeof(Ncb));
        Ncb.ncb_command = NCBASTAT;
        Ncb.ncb_lana_num = lenum.lana[i];
        strcpy((char *)Ncb.ncb_callname, "*               " );
        Ncb.ncb_buffer = (BYTE *)&Adapter;
        Ncb.ncb_length = sizeof(Adapter);
        uRetCode = Netbios(&Ncb);

        if (Adapter.adapt.adapter_address[0] == 0 &&
                Adapter.adapt.adapter_address[1] == 0 &&
                Adapter.adapt.adapter_address[2] == 0 &&
                Adapter.adapt.adapter_address[3] == 0 &&
                Adapter.adapt.adapter_address[4] == 0 &&
                Adapter.adapt.adapter_address[5] == 0) {
            continue;
        }

        if (uRetCode == 0) {
            *pMacID += (NR_INT64)Adapter.adapt.adapter_address[0];
            *pMacID += (NR_INT64)Adapter.adapt.adapter_address[1] << 8;
            *pMacID += (NR_INT64)Adapter.adapt.adapter_address[2] << 16;
            *pMacID += (NR_INT64)Adapter.adapt.adapter_address[3] << 24;
            *pMacID += (NR_INT64)Adapter.adapt.adapter_address[4] << 32;
            *pMacID += (NR_INT64)Adapter.adapt.adapter_address[5] << 40;
            return NR_OK;
        }
    }

    return NR_ERROR;
#elif defined(__linux__) || defined(__LINUX__)
    int fd, intrface;
    struct ifreq buf[MAXINTERFACES];
    struct ifconf ifc;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;

        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {
            intrface = ifc.ifc_len / (int)sizeof(struct ifreq);

            while (intrface-- > 0) {
                /* this section can't get Hardware Address,I don't know whether the reason is module driver */
                if (!(ioctl(fd, SIOCGIFHWADDR, (char *)&buf[intrface]))) {
                    *pMacID += ((NR_INT64)buf[intrface].ifr_hwaddr.sa_data[0]) << 40;
                    *pMacID += ((NR_INT64)buf[intrface].ifr_hwaddr.sa_data[1]) << 32;
                    *pMacID += ((NR_INT64)buf[intrface].ifr_hwaddr.sa_data[2]) << 24;
                    *pMacID += ((NR_INT64)buf[intrface].ifr_hwaddr.sa_data[3]) << 16;
                    *pMacID += ((NR_INT64)buf[intrface].ifr_hwaddr.sa_data[4]) << 8;
                    *pMacID += (NR_INT64)buf[intrface].ifr_hwaddr.sa_data[5];
                    close(fd);
                    return NR_OK;
                }
            } // while
        }
    }

    close(fd);
    *pMacID = 0;
    return NR_ERROR;
#elif defined(__sun) || defined(__solaris__) || defined(__SOLARIS__) || defined(Q_OS_SOLARIS)
    register int fd, intrface;
    struct ifreq buf[MAXINTERFACES];
    struct arpreq arp;
    struct ifconf ifc;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0) {
        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = (caddr_t)buf;

        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {
            intrface = ifc.ifc_len / sizeof(struct ifreq);

            while (intrface-- > 0) {
                /* this section can't get Hardware Address,I don't know whether the reason is module driver */
                arp.arp_pa.sa_family = AF_INET;
                arp.arp_ha.sa_family = AF_INET;
                ((struct sockaddr_in *)&arp.arp_pa)->sin_addr.s_addr =
                    ((struct sockaddr_in *)(&buf[intrface].ifr_addr))->sin_addr.s_addr;

                if (!(ioctl (fd, SIOCGARP, (char *) &arp))) {
                    *pMacID += ((NR_INT64)arp.arp_ha.sa_data[0] ) << 40;
                    *pMacID += ((NR_INT64)arp.arp_ha.sa_data[1] ) << 32;
                    *pMacID += ((NR_INT64)arp.arp_ha.sa_data[2] ) << 24;
                    *pMacID += ((NR_INT64)arp.arp_ha.sa_data[3] ) << 16;
                    *pMacID += ((NR_INT64)arp.arp_ha.sa_data[4] ) << 8;
                    *pMacID += (NR_INT64)arp.arp_ha.sa_data[5];
                    close(fd);
                    return NR_OK;
                }
            } // while
        }
    }

    close(fd);
    *pMacID = 0;
    return NR_ERROR;
#elif defined(__aix__) || defined(__AIX__) || defined(_AIX)
    int size;
    struct kinfo_ndd *nddp;
    char addr[6];
    size = getkerninfo(KINFO_NDD, 0, 0, 0);

    if (size <= 0) {
        *pMacID = 0;
        return NR_ERROR;
    }

    nddp = (struct kinfo_ndd *)NR_MALLOC(size);

    if (!nddp) {
        *pMacID = 0;
        return NR_ERROR;
    }

    if (getkerninfo(KINFO_NDD, nddp, &size, 0) < 0) {
        NR_FREE(nddp);
        *pMacID = 0;
        return NR_ERROR;
    }

    *pMacID += ((NR_INT64)nddp->ndd_addr[0]) << 40;
    *pMacID += ((NR_INT64)nddp->ndd_addr[1]) << 32;
    *pMacID += ((NR_INT64)nddp->ndd_addr[2]) << 24;
    *pMacID += ((NR_INT64)nddp->ndd_addr[3]) << 16;
    *pMacID += ((NR_INT64)nddp->ndd_addr[4]) << 8;
    *pMacID += ((NR_INT64)nddp->ndd_addr[5]);
    NR_FREE(nddp);
    return NR_OK;
#elif defined(Q_OS_HPUX) || defined(__HPUX) || defined(__hpux)
    char buf[256] = {'\0'};
    char sSerial[256] = {'\0'};
    sprintf(buf, "lanscan -a");
    FILE *fp = popen(buf, "r") ;

    if (fp != NR_NULL) {
        while (fgets(buf, 256, fp)) {
            if (strlen(buf) > 0) {
                buf[strlen(buf) - 1] = '\0' ;
                sscanf(buf, "%*[^x]x%s", sSerial);
                break;
            }
        }
    }

    int nSerial = strlen(sSerial);
    int i;

    for (i = nSerial - 1; i >= 0; --i) {
        *pMacID += ((NR_INT64)sSerial[i]) << ((nSerial - i - 1) * 8);
    }

    pclose(fp);
    return NR_OK;
#endif
    return NR_ERROR;
}

NR_LOCAL NR_INT FormatLicense(const NR_CHAR *src, NR_CHAR *dest)
{
    const NR_CHAR *p;
    NR_CHAR *q;
    NR_INT i, j;

    for (i = 0, j = 0; i < NR_LICENSE_LEN - 4; i += 4, j += 5) {
        p = &src[i];
        q = &dest[j];
        memcpy(q, p, 4);
        dest[j + 4] = '-';
    }

    dest[j - 5 + 4] = 0; // reset last
    return NR_OK;
}

NR_EXTERN LICENSE_EXPORT NR_INT NR_API CreateLicense(
    NR_IN const NR_CHAR *szSoftName,
    NR_IN const NR_CHAR *szHostID,
    NR_OUT NR_CHAR szLicense[NR_LICENSE_BUFSIZE])
{
    if (szSoftName == NR_NULL || szHostID == NR_NULL || szLicense == NR_NULL) {
        NR_LOG_ERROR("Invalid params!");
        return NR_ERROR;
    }

    NR_BZERO(szLicense, NR_LICENSE_BUFSIZE);
    // xxxx-xxxx-xxxx-xxxx-xxxx-xxxx
    NR_INT len = NR_LICENSE_LEN - 4;
    NR_CHAR pLicense[NR_LICENSE_LEN - 3] = {0};
    NR_INT hostIdLen = (int)strlen(szHostID);
    NR_INT i = 0;

    for (i = 0; i < len; ++i) {
        pLicense[i] = szHostID[i % hostIdLen];
    }

    for (i = 0; i < len; ++i) {
        pLicense[i] = szHostID[hostToLicense[i % 16] % hostIdLen];
    }

    for (i = 0; i < (NR_INT)strlen(szSoftName); ++i) {
        pLicense[i % len] = CharList[(pLicense[i % len] + abs((int)szSoftName[i])) % 16];
    }

    for (i = 0; i < len; ++i) {
        pLicense[i] = CharList[(pLicense[i] + i) % 16];

        if (pLicense[i] >= '0' && pLicense[i] <= '9') {
            pLicense[i] = CharList[(pLicense[i] + 3 * i) % 16];
        }
    }

    for (i = 0; i < len; ++i) {
        if (pLicense[i] >= '0' && pLicense[i] <= '9') {
            pLicense[i] = CharList[(pLicense[i] + pLicense[(i + 1) % len] + pLicense[(i + 2) % len] +
                                    pLicense[(i + 3) % len]) % 16];
        }
    }

    if (FormatLicense(pLicense, szLicense) != NR_OK) {
        return NR_ERROR;
    }

    return NR_OK;
}

NR_EXTERN LICENSE_EXPORT NR_INT NR_API CreateTempLicense(
    NR_IN const NR_CHAR *szSoftName,
    NR_IN const NR_INT nYear,
    NR_IN const NR_INT nMon,
    NR_IN const NR_INT nDay,
    NR_OUT NR_CHAR szTempLicense[NR_TEMPLICENSE_BUFSIZE])
{
    if (szSoftName == NR_NULL || szTempLicense == NR_NULL) {
        NR_LOG_ERROR("Invalid params!");
        return NR_ERROR;
    }

    memset(szTempLicense, 0, NR_TEMPLICENSE_BUFSIZE);
    sprintf(szTempLicense, "Temlic%04d-%02d-%02d-", nYear, nMon, nDay);
    NR_CHAR szLicense[NR_LICENSE_BUFSIZE] = {0};
    NR_CHAR szHostId[NR_HOSTID_BUFSIZE] = {0};
    NR_INT i = 0;

    for (i = 0; i < NR_HOSTID_LEN; ++i) {
        szHostId[i] = szTempLicense[i + 4];
    }

    szHostId[6] = szTempLicense[1];
    szHostId[9] = szTempLicense[2];

    if (CreateLicense(szSoftName, szHostId, szLicense) != NR_OK) {
        NR_LOG_ERROR("CreateLicense() failed!");
        return NR_ERROR;
    }

    strcat(szTempLicense, szLicense);
    return NR_OK;
}

NR_EXTERN LICENSE_EXPORT NR_INT NR_API CreateMACIDNew(
    NR_OUT NR_INT64 *pMacID,
    NR_IN NR_UINT unIndex)
{
    if (pMacID == NR_NULL) {
        NR_LOG_ERROR("Invalid params!");
        return NR_ERROR;
    }

    NR_INT64 pMacIDList[NR_MAX_MACID_NUMBER] = {0};
    NR_UINT unCount = 0;

    if (GetMacIDList(pMacIDList, NR_MAX_MACID_NUMBER, &unCount) != NR_OK) {
        return NR_ERROR;
    }

    if (unCount <= unIndex) {
        return NR_ERROR;
    }

    *pMacID = pMacIDList[unIndex];
    return NR_OK;
}

NR_EXTERN LICENSE_EXPORT NR_INT NR_API CreateHostID(
    NR_OUT NR_CHAR szHostID[NR_HOSTID_BUFSIZE])
{
    NR_INT64 cpuID = 0;
    NR_INT64 hardID = 0;
    NR_INT64 macID = 0;
    NR_INT64 HostID = 0;
    NR_BZERO(szHostID, NR_HOSTID_BUFSIZE);

    if (CreateCPUID(&cpuID) != NR_OK) {
        cpuID = 0;
    }

    if (CreateHardID(&hardID) != NR_OK) {
        hardID = 0;
    }

    if (CreateMACID(&macID) != NR_OK) {
        macID = 0;
    }

    if (cpuID == 0 && hardID == 0 && macID == 0) {
        return NR_ERROR;
    }

    HostID += cpuID;
    HostID += hardID;
    NR_BYTE *pFeatureMacID = (NR_BYTE *)&macID;
    NR_INT i;

    for (i = 0; i < 6; ++i) {
        pFeatureMacID[i] ^= pFeatureMacID[HostIDOrderFit[i]];
    }

    NR_BYTE *pFeatureHostID = (NR_BYTE *)&HostID;

    for (i = 0; i < 6; ++i) {
        pFeatureHostID[i] ^= pFeatureMacID[5 - i];
    }

    sprintf(szHostID, "%02x%02x%02x%02x%02x%02x",
            pFeatureHostID[0], pFeatureHostID[1], pFeatureHostID[2],
            pFeatureHostID[3], pFeatureHostID[4], pFeatureHostID[5]);
    return NR_OK;
}

NR_INT CreateHostIDNewPrivate(NR_CHAR szHostID[NR_HOSTID_BUFSIZE], NR_INT64 macID)
{
    NR_INT64 cpuID = 31415926535;
    NR_INT64 hardID = 299792458;
    NR_INT64 HostID = 2718281828459;

    if (cpuID == 0 && hardID == 0 && macID == 0) {
        return NR_ERROR;
    }

    HostID += cpuID;
    HostID += hardID;
    NR_BYTE *pFeatureMacID = (NR_BYTE *)&macID;
    NR_INT i;

    for (i = 0; i < 6; ++i) {
        pFeatureMacID[i] ^= pFeatureMacID[HostIDOrderFit[i]];
    }

    NR_BYTE *pFeatureHostID = (NR_BYTE *)&HostID;

    for (i = 0; i < 6; ++i) {
        pFeatureHostID[i] ^= pFeatureMacID[5 - i];
    }

    NR_BZERO(szHostID, NR_HOSTID_BUFSIZE);
    sprintf(szHostID, "%02x%02x%02x%02x%02x%02x",
            pFeatureHostID[0], pFeatureHostID[1], pFeatureHostID[2],
            pFeatureHostID[3], pFeatureHostID[4], pFeatureHostID[5]);
    return NR_OK;
}

NR_EXTERN LICENSE_EXPORT NR_INT NR_API CreateHostIDNew(
    NR_OUT NR_CHAR szHostID[NR_HOSTID_BUFSIZE],
    NR_IN NR_UINT unIndex)
{
    if (szHostID == NR_NULL) {
        NR_LOG_ERROR("Invalid params!");
        return NR_ERROR;
    }

    NR_INT64 macID = 0;

    if (CreateMACIDNew(&macID, unIndex) != NR_OK) {
        macID = 0;
    }

    return CreateHostIDNewPrivate(szHostID, macID);
}

NR_LOCAL NR_INT EncryptStr(const NR_CHAR *szSrc, const NR_UINT srcLen,
                           NR_CHAR *szDest, const NR_UINT destLen)
{
    if (szSrc == NR_NULL || szDest == NR_NULL || srcLen < 1 || (srcLen << 1) > destLen) {
        return NR_ERROR;
    }

    NR_UINT i;

    for (i = 0; i < srcLen; ++i) {
        NR_CHAR j = szSrc[i];
        szDest[2 * i] = K1 + j / K2;
        szDest[2 * i + 1] = K1 + j % K2;
    }

    return NR_OK;
}

NR_LOCAL NR_INT DecryptStr(const NR_CHAR *szSrc, const NR_UINT srcLen,
                           NR_CHAR *szDest, const NR_UINT destLen)
{
    if (szSrc == NR_NULL || szDest == NR_NULL || srcLen < 2 || (destLen << 1) < srcLen) {
        return NR_ERROR;
    }

    NR_UINT i;

    for (i = 0; i < srcLen / 2; ++i) {
        int j = (szSrc[2 * i] - K1) * K2;
        j += szSrc[2 * i + 1] - K1;
        szDest[i] = (NR_CHAR)j;
    }

    return NR_OK;
}

NR_EXTERN LICENSE_EXPORT NR_INT NR_API SetLicenseFile(NR_IN const NR_CHAR *szFileName)
{
    if (szFileName == NR_NULL) {
        return NR_ERROR;
    }

    const NR_CHAR *p = szFileName;
    while (*p == '/') {
        p++;
    }

    size_t filenameLen = strlen(p);

    if (filenameLen == 0 || filenameLen >= NR_FILENAME_LEN) {
        return NR_ERROR;
    }

    strncpy(g_licenseFile, p, filenameLen);
    g_licenseFile[filenameLen] = '\0';
    return NR_OK;
}

NR_LOCAL NR_INT GetLineFromString(const NR_CHAR *src, NR_CHAR *dest, NR_UINT destLen)
{
    NR_BZERO(dest, destLen);
    NR_UINT srcLen = (NR_UINT)strlen(src);
    NR_UINT i, cnt;

    for (i = 0; i < srcLen; i++) {
        if (src[i] == 0x0d || src[i] == 0x0a) {
            break;
        }
    }

    cnt = ((i == srcLen) ? i : (i + 1));
    strncpy(dest, src, NR_MIN(destLen - 1, cnt));
    return NR_OK;
}


NR_LOCAL NR_INT GetLicenseInfo(NR_IN const NR_CHAR *szSoftName,
                               NR_OUT NR_CHAR szLicense[NR_TEMPLICENSE_BUFSIZE])
{
    if (szSoftName == NR_NULL || szLicense == NR_NULL) {
        return NR_ERROR;
    }

    NR_CHAR sUserFile[96] = {0};
#ifdef WIN32
    std::locale loc = std::locale::global(std::locale(""));
    sprintf(sUserFile, "%s\\%s", getenv(HOMEFILE), g_licenseFile);
#else

    if (getenv(HOMEFILE)) {
        sprintf(sUserFile, "%s", getenv(HOMEFILE));
    } else {
        if (getenv(USER)) {
            sprintf(sUserFile, "%s%s", "/users/", getenv(USER));
        } else if (getenv(USERNAME)) {
            sprintf(sUserFile, "%s%s", "/users/", getenv(USERNAME));
        } else {
            sprintf(sUserFile, "%s%s", "/users/", "ems");
        }
    }

    if (access(sUserFile, 0) == -1) {
        char sDir[128] = {0};
        sprintf(sDir, "mkdir -p %s", sUserFile);
        system(sDir);
    }

    strcat(sUserFile, "/");
    strcat(sUserFile, g_licenseFile);
#endif
    NR_CHAR *pSrcData = (NR_CHAR *)NR_MALLOC(NR_CONFIG_FILE_SIZE);

    if (pSrcData == NR_NULL) {
        return NR_ERROR;
    }

    NR_BZERO(pSrcData, NR_CONFIG_FILE_SIZE);
    NR_CHAR sLine[NR_LINE_BUFSIZE] = {'\0'};
    const NR_CHAR *pcSoftName = NR_NULL;

    if (strlen(szSoftName) == 0) {
        pcSoftName = "Temlic";
    } else {
        pcSoftName = szSoftName;
    }

    // read license infor
    NR_UINT uiTotalLen = 0;
    ifstream fin(sUserFile);

    while (fin.getline(sLine, NR_LINE_BUFSIZE)) {
        NR_UINT uiLineLen = (NR_UINT)strlen(sLine);

        if (uiLineLen < 1) {
            continue;
        }

        uiTotalLen += uiLineLen;

        if (uiTotalLen + uiLineLen >= NR_CONFIG_FILE_SIZE) {
            NR_LOG_ERROR("The space of license file is not enough!");
            fin.close();
            NR_FREE(pSrcData);
            return NR_ERROR;
        }

        strcat(pSrcData, sLine);
    }

    fin.close();
    fin.clear();
    NR_CHAR *pDestData = (NR_CHAR *)NR_MALLOC(NR_CONFIG_FILE_SIZE);

    if (pDestData == NR_NULL) {
        NR_FREE(pSrcData);
        return NR_ERROR;
    }

    NR_BZERO(pDestData, NR_CONFIG_FILE_SIZE);
    NR_INT ret = DecryptStr(pSrcData, (NR_UINT)strlen(pSrcData), pDestData, NR_CONFIG_FILE_SIZE);
    NR_FREE(pSrcData);

    if (ret != NR_OK) {
        NR_FREE(pDestData);
        return NR_ERROR;
    }

    NR_CHAR sTempStr[NR_LINE_BUFSIZE] = {'\0'};
    NR_UINT uiCurPos = 0;
    NR_UINT i = 0;
    NR_UINT nLen = (NR_UINT)strlen(pDestData);

    for (i = 0; i < nLen; ++i) {
        GetLineFromString(pDestData + uiCurPos, sLine, sizeof(sLine));

        if (sLine[0] == '#') {
            sscanf(sLine, "%*s%s", sTempStr);
            NR_UINT nOffset = uiCurPos + (NR_UINT)strlen(sLine);

            if (NR_STRCMP(sTempStr, pcSoftName) == 0) {
                NR_BZERO(sTempStr, sizeof(sTempStr));
                GetLineFromString(pDestData + nOffset, sLine, sizeof(sLine));     // LicenseId
                nOffset += strlen(sLine);
                GetLineFromString(pDestData + nOffset, sLine, sizeof(sLine)); // LicenseKeyExt
                sscanf(sLine, "LicenseKeyExt=%s", szLicense);
                nOffset += strlen(sLine);
                uiCurPos += nOffset;
                break;
            }
        }

        if (strlen(sLine) == 0) {
            NR_FREE(pDestData);
            return NR_ERROR;
        }

        uiCurPos += strlen(sLine);
        i = uiCurPos;
    }

    NR_FREE(pDestData);
    return NR_OK;
}

NR_LOCAL NR_STATUS CheckLicenseNewPrivate(const NR_CHAR *szSoftName)
{
    NR_INT64 pMacIDList[NR_MAX_MACID_NUMBER] = {0};
    NR_UINT nCount = 0;

    if (GetMacIDList(pMacIDList, NR_MAX_MACID_NUMBER, &nCount) != NR_OK) {
        return NR_LICENSE_FAIL;
    }

    NR_DWORD dwLicenseLen = NR_TEMPLICENSE_LEN + 1;
    NR_CHAR szUserLicense[NR_LICENSE_BUFSIZE] = {'\0'};
    NR_CHAR szLicense[NR_LICENSE_BUFSIZE] = {'\0'};
    NR_CHAR szRegLicense[NR_TEMPLICENSE_BUFSIZE] = {'\0'};

    if (GetLicenseInfo(szSoftName, szRegLicense) != NR_OK) {
        return NR_LICENSE_FAIL;
    }

    NR_UINT nMacNo;

    for (nMacNo = 0; nMacNo < nCount && nMacNo < NR_MAX_MACID_NUMBER; ++nMacNo) {
        NR_INT64 macID = pMacIDList[nMacNo];
        NR_CHAR szHostId[NR_HOSTID_BUFSIZE] = {'\0'};
        NR_BZERO(szLicense, sizeof(szLicense));
        NR_BZERO(szUserLicense, sizeof(szUserLicense));
        NR_BZERO(szHostId, sizeof(szHostId));
        dwLicenseLen = (NR_DWORD)strlen(szRegLicense);

        if ((dwLicenseLen != NR_LICENSE_LEN) && (dwLicenseLen != NR_TEMPLICENSE_LEN)) {
            goto CONTINUE;
        }

        NR_UINT i;

        // try to create the  license
        if (dwLicenseLen == NR_LICENSE_LEN) { // true license
            for (i = 0; i < (NR_UINT)strlen(szRegLicense) && i < NR_LICENSE_BUFSIZE; ++i) {
                szUserLicense[i] = szRegLicense[i];
            }

            if (CreateHostIDNewPrivate(szHostId, macID) != NR_OK) {
                goto CONTINUE;
            }

            if (CreateLicense(szSoftName, szHostId, szLicense) != NR_OK) {
                goto CONTINUE;
            }

            szLicense[sizeof(szLicense) - 1] = '\0';

            if (NR_STRCMP(szLicense, szRegLicense) != 0) {
                goto CONTINUE;
            }

            return NR_LICENSE_FULL;
        }

        if (dwLicenseLen == NR_TEMPLICENSE_LEN ) { // temperary license
            for (i = 0; i < NR_LICENSE_BUFSIZE; ++i) {
                szUserLicense[i] = szRegLicense[i + NR_TEMPLICENSE_PREFIX_LEN];
            }

            for (i = 0; i < NR_HOSTID_LEN; ++i) {
                szHostId[i] = szRegLicense[i + 4];
            }

            szHostId[6] = szRegLicense[1];
            szHostId[9] = szRegLicense[2];

            if (CreateLicense(szSoftName, szHostId, szLicense) != NR_OK) {
                goto CONTINUE;
            }

            szLicense[sizeof(szLicense) - 1] = '\0';

            if (NR_STRCMP(szLicense, szUserLicense) != 0) {
                goto CONTINUE;
            }

            int nYear = 0, nMon = 0, nDay = 0;
            int nYearCur = 0, nMonCur = 0, nDayCur = 0;
            sscanf(szRegLicense, "%*6s%d-%d-%d[^-]", &nYear, &nMon, &nDay);
            char ctime[30] = {'\0'};
            time_t curTime = time(NR_NULL);
            strftime(ctime, sizeof(ctime), "%Y-%m-%d %X", localtime(&curTime));
            sscanf(ctime, "%d-%d-%d", &nYearCur, &nMonCur, &nDayCur);

            if ((nYear < nYearCur) || (nYear == nYearCur && nMon < nMonCur) ||
                    (nYear == nYearCur && nMon == nMonCur && nDay < nDayCur)) {
                goto CONTINUE;
            }

            return NR_LICENSE_TEMP;
        }

CONTINUE:

        if (nMacNo == nCount - 1 || nMacNo == NR_MAX_MACID_NUMBER - 1) {
            return NR_LICENSE_FAIL;
        } else {
            continue;
        }
    }

    return NR_LICENSE_SUCCESS;
}

NR_EXTERN LICENSE_EXPORT NR_STATUS NR_API CheckLicense(NR_IN const NR_CHAR *szSoftName)
{
    return CheckLicenseNewPrivate(szSoftName);
}

NR_EXTERN LICENSE_EXPORT NR_INT NR_API RegisterLicense(
    NR_IN const NR_CHAR *szSoftName,
    NR_IN const NR_CHAR *szHostID,
    NR_IN const NR_CHAR *szLicense)
{
    if (szSoftName == NR_NULL || szHostID == NR_NULL || szLicense == NR_NULL) {
        return NR_ERROR;
    }

    NR_CHAR sUserFile[96] = {0};
#ifdef WIN32
    std::locale loc = std::locale::global(std::locale(""));
    sprintf(sUserFile, "%s\\%s", getenv(HOMEFILE), g_licenseFile);
#else

    if (getenv(HOMEFILE)) {
        sprintf(sUserFile, "%s", getenv(HOMEFILE));
    } else {
        if (getenv(USER)) {
            sprintf(sUserFile, "%s%s", "/users/", getenv(USER));
        } else if (getenv(USERNAME)) {
            sprintf(sUserFile, "%s%s", "/users/", getenv(USERNAME));
        } else {
            sprintf(sUserFile, "%s%s", "/users/", "ems");
        }
    }

    if (access(sUserFile, 0) == -1) {
        char sDir[128] = {0};
        sprintf(sDir, "mkdir -p %s", sUserFile);
        system(sDir);
    }

    strcat(sUserFile, "/");
    strcat(sUserFile, g_licenseFile);
#endif
    NR_CHAR *pSrcData = (NR_CHAR *)NR_MALLOC(NR_CONFIG_FILE_SIZE);
    if (pSrcData == NR_NULL) {
        return NR_ERROR;
    }
    NR_BZERO(pSrcData, NR_CONFIG_FILE_SIZE);

    NR_CHAR sLine[NR_LINE_BUFSIZE] = {'\0'};
    const NR_CHAR *pcSoftName = NR_NULL;
    if (strlen(szSoftName) == 0) {
        pcSoftName = "Temlic";
    } else {
        pcSoftName = szSoftName;
    }

    // read license infor
    NR_UINT uiTotalLen = 0;
    ifstream fin(sUserFile);

    while (fin.getline(sLine, NR_LINE_BUFSIZE)) {
        NR_UINT uiLineLen = (NR_UINT)strlen(sLine);

        if (uiLineLen < 1) {
            continue;
        }

        uiTotalLen += uiLineLen;

        if (uiTotalLen + uiLineLen >= NR_CONFIG_FILE_SIZE) {
            NR_LOG_ERROR("The space of license file is not enough!");
            fin.close();
            NR_FREE(pSrcData);
            return NR_ERROR;
        }

        strcat(pSrcData, sLine);
    }
    fin.close();
    fin.clear();

    NR_CHAR *pDestData = (NR_CHAR *)NR_MALLOC(NR_CONFIG_FILE_SIZE);
    if (pDestData == NR_NULL) {
        NR_FREE(pSrcData);
        return NR_ERROR;
    }
    NR_BZERO(pDestData, NR_CONFIG_FILE_SIZE);

    NR_INT ret = DecryptStr(pSrcData, (NR_UINT)strlen(pSrcData), pDestData, NR_CONFIG_FILE_SIZE);
    NR_BZERO(pSrcData, NR_CONFIG_FILE_SIZE);
    NR_CHAR sTempStr[NR_LINE_BUFSIZE] = {'\0'};
    NR_UINT uiCurPos = 0;
    NR_UINT i = 0;

    if (ret == NR_OK) {
        NR_UINT nLen = (NR_UINT)strlen(pDestData);

        for (i = 0; i < nLen; ++i) {
            GetLineFromString(pDestData + uiCurPos, sLine, sizeof(sLine));

            if (sLine[0] == '#') {
                sscanf(sLine, "%*s%s", sTempStr);
                NR_UINT nOffset = uiCurPos + (NR_UINT)strlen(sLine);

                if (NR_STRCMP(sTempStr, pcSoftName) == 0) {
                    NR_BZERO(sTempStr, sizeof(sTempStr));
                    GetLineFromString(pDestData + nOffset, sLine, sizeof(sLine));     // LicenseId
                    nOffset += strlen(sLine);
                    sscanf(sLine, "LicenseId=%s", sTempStr);

                    if (NR_STRCMP(sTempStr, szHostID) == 0) {
                        GetLineFromString(pDestData + nOffset, sLine, sizeof(sLine)); // LicenseKeyExt
                        nOffset += strlen(sLine);
                        uiCurPos += nOffset;
                        break;
                    }
                }
            }

            uiCurPos += strlen(sLine);
            strcat(pSrcData, sLine);
            i = uiCurPos;
        }

        for (i = uiCurPos; i < nLen; ++i) {
            GetLineFromString(pDestData + uiCurPos, sLine, sizeof(sLine));
            uiCurPos += strlen(sLine);
            strcat(pSrcData, sLine);
            i = uiCurPos;
        }
    }

    // add new license
    NR_BZERO(sTempStr, NR_LINE_BUFSIZE);
    sprintf(sTempStr, "# %s license", pcSoftName);
    strcat(pSrcData, sTempStr);
    strcat(pSrcData, "\n");
    NR_BZERO(sTempStr, NR_LINE_BUFSIZE);
    sprintf(sTempStr, "LicenseId=%s", szHostID);
    strcat(pSrcData, sTempStr);
    strcat(pSrcData, "\n");
    NR_BZERO(sTempStr, NR_LINE_BUFSIZE);
    sprintf(sTempStr, "LicenseKeyExt=%s", szLicense);
    strcat(pSrcData, sTempStr);
    strcat(pSrcData, "\n");

    // encrypt license data
    if (EncryptStr(pSrcData, (NR_UINT)strlen(pSrcData), pDestData, NR_CONFIG_FILE_SIZE) != NR_OK) {
        NR_LOG_ERROR("EncryptStr() failed, srcLen=%u", strlen(pSrcData));
        NR_FREE(pSrcData);
        NR_FREE(pDestData);
        return NR_ERROR;
    }

    // divide by NR_LINE_LEN(100)
    NR_UINT uiLength = (NR_UINT)strlen(pDestData);
    NR_BZERO(pSrcData, NR_CONFIG_FILE_SIZE);

    for (i = 0; i < uiLength / NR_LINE_LEN; ++i) {
        NR_BZERO(sTempStr, NR_LINE_BUFSIZE);
        strncpy(sTempStr, pDestData + i * NR_LINE_LEN, NR_LINE_LEN);
        strcat(pSrcData, sTempStr);
        strcat(pSrcData, "\n");
    }

    NR_BZERO(sTempStr, NR_LINE_BUFSIZE);
    strncpy(sTempStr, pDestData + (uiLength / NR_LINE_LEN) * NR_LINE_LEN, uiLength % NR_LINE_LEN);
    strcat(pSrcData, sTempStr);
    strcat(pSrcData, "\n");
#ifdef WIN32
    ofstream foutwin(sUserFile);
    foutwin << pSrcData;
    foutwin.close();
    std::locale::global(loc);
#else
    ofstream foutlinux(sUserFile);
    foutlinux << pSrcData;
    foutlinux.close();
#endif
    NR_FREE(pSrcData);
    NR_FREE(pDestData);
    return NR_OK;
}
