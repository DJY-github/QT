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
#ifndef NR_LICENSE_P_H
#define NR_LICENSE_P_H

#include "nrlicense.h"

#define NR_PRINTF(fmt, ...) \
    do { \
        printf(fmt, ##__VA_ARGS__); fflush(stdout); \
    } while (0)

#define NR_LOG(szTip, fmt, ...) \
    do { \
        NR_PRINTF("[%s][%s:%d]" fmt "\r\n", szTip, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#define NR_LOG_ERROR(fmt, ...)      NR_LOG("ERROR", fmt, ##__VA_ARGS__)
#define NR_LOG_DEBUG(fmt, ...)      NR_LOG("DEBUG", fmt, ##__VA_ARGS__)
#define NR_LOG_INFO(fmt, ...)       NR_LOG("INFO", fmt, ##__VA_ARGS__)
#define NR_LOG_WARN(fmt, ...)       NR_LOG("WARN", fmt, ##__VA_ARGS__)


#ifdef WIN32
#define NR_STRCMP(a, b) strcmpi((a), (b))
#else
#define NR_STRCMP(a, b) strcasecmp((a), (b))
#endif

#define NR_BZERO(buf, size) memset((buf), 0, (size))

#define NR_MALLOC(size) malloc(size)
#define NR_FREE(p)      free(p)

#define NR_MIN(a, b) ((a) > (b) ? (b) : (a))
#define NR_MAX(a, b) ((a) > (b) ? (a) : (b))

#define K1    65
#define K2    26

#define NR_FILENAME_LEN         64
#define NR_CONFIG_FILE_SIZE     (20 << 10) // 20K
#define NR_LINE_LEN             100
#define NR_LINE_BUFSIZE         (NR_LINE_LEN + 1)


#if defined(WIN32) || defined(Q_OS_WIN32)

#else
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#if defined(VXWORKS)
#include <sockLib.h>
#endif

// for inet_addr
#include <netdb.h>
#include <arpa/inet.h>
#if defined(VXWORKS)
#include <hostLib.h>
#else
#include <resolv.h>
#endif

#if defined(__linux__) || defined(__linux)
#include <ifaddrs.h>
#include <errno.h>
#endif

#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#  include <net/if_dl.h>
#endif


// UnixWare 7 redefines socket -> _socket
static inline int qt_safe_socket(int domain, int type, int protocol, int flags = 0)
{	
    int fd;
#if defined(SOCK_CLOEXEC) && defined(SOCK_NONBLOCK)
    int newtype = type | SOCK_CLOEXEC;
    if (flags & O_NONBLOCK) {
        newtype |= SOCK_NONBLOCK;
    }
    fd = ::socket(domain, newtype, protocol);
    if (fd != -1 || errno != EINVAL) {
        return fd;
    }
#endif
	
    fd = ::socket(domain, type, protocol);
    if (fd == -1) {
        return -1;
    }
	
    ::fcntl(fd, F_SETFD, FD_CLOEXEC);
	
    // set non-block too?
    if (flags & O_NONBLOCK) {
        ::fcntl(fd, F_SETFL, ::fcntl(fd, F_GETFL) | O_NONBLOCK);
    }
	
    return fd;
}

#if defined(__aix__) || defined(__AIX__) || defined(_AIX)

// VxWorks' headers specify 'int' instead of '...' for the 3rd ioctl() parameter.
template <typename T>
static inline int qt_safe_ioctl(int sockfd, int request, T arg)
{
#ifdef VXWORKS
    return ::ioctl(sockfd, request, (int)arg);
#else
    return ::ioctl(sockfd, request, arg);
#endif
}

#endif

#endif

#endif // NR_LICENSE_P_H

