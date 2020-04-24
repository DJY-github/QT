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
#ifndef NR_LICENSE_H
#define NR_LICENSE_H

#include <QtCore/qglobal.h>

#ifdef __cplusplus
#define NR_EXTERN extern "C"
#else
#define NR_EXTERN extern
#endif

#ifndef NRLICENSE_LIBRARY_STATIC
#ifdef NRLICENSE_DLL
#define LICENSE_EXPORT  Q_DECL_EXPORT
#else
#define LICENSE_EXPORT  Q_DECL_IMPORT
#endif
#else
#define LICENSE_EXPORT
#endif

#define NR_IN
#define NR_OUT
#define NR_INOUT
#define NR_IO
#define NR_API

#define NR_STRUCT   typedef struct
#define NR_UNION    typedef union
#define NR_LOCAL    static

#define NR_OK       0
#define NR_ERROR    (~0)
#define NR_SUCC     NR_OK
#define NR_FAIL     NR_ERROR

#define NR_TRUE     1
#define NR_FALSE    0

#define NR_NULL     NULL

#ifdef WIN32
typedef			 long       NR_LONG;
typedef unsigned long       NR_ULONG;
typedef unsigned long       NR_DWORD;
#else
typedef          int        NR_LONG;
typedef unsigned int        NR_ULONG;
typedef unsigned int        NR_DWORD;
#endif

typedef long long           NR_INT64;

typedef unsigned char		NR_BYTE;
typedef unsigned char		NR_BOOL;
typedef unsigned char		NR_UCHAR;
typedef unsigned short int	NR_USHORT;
typedef unsigned short int	NR_WORD;
typedef unsigned       int	NR_UINT;
typedef void				NR_VOID;
typedef char				NR_CHAR;
typedef int					NR_INT;
typedef short int			NR_SHORT;

typedef NR_INT              NR_STATUS;


#define NR_LICENSE_STATUS_BASE      0

#define NR_LICENSE_FAIL				(NR_LICENSE_STATUS_BASE)
#define NR_LICENSE_WIND_FAIL		(NR_LICENSE_STATUS_BASE - 1)
#define NR_LICENSE_NO_DOG			(NR_LICENSE_STATUS_BASE - 2)
#define NR_LICENSE_NO_USER			(NR_LICENSE_STATUS_BASE - 3)
#define NR_LICENSE_ERROR_USER		(NR_LICENSE_STATUS_BASE - 4)
#define NR_LICENSE_NO_SOFTWARE		(NR_LICENSE_STATUS_BASE - 5)
#define NR_LICENSE_ERROR_SOFTWARE	(NR_LICENSE_STATUS_BASE - 6)
#define NR_LICENSE_NO_RIGHT			(NR_LICENSE_STATUS_BASE - 7)
#define NR_LICENSE_ERROR_RIGHT		(NR_LICENSE_STATUS_BASE - 8)

#define NR_LICENSE_SUCCESS			(NR_LICENSE_STATUS_BASE + 1)
#define NR_LICENSE_FULL				(NR_LICENSE_STATUS_BASE + 2)
#define NR_LICENSE_TEMP				(NR_LICENSE_STATUS_BASE + 3)
#define NR_LICENSE_DOMAIN			(NR_LICENSE_STATUS_BASE + 4)


#define NR_HOSTID_LEN               12
#define NR_HOSTID_BUFSIZE           (NR_HOSTID_LEN + 1)
#define NR_LICENSE_LEN              24
#define NR_LICENSE_BUFSIZE          (NR_LICENSE_LEN + 1)
// eg: Temlic2019-07-16-xxxxx-xxxxx-xxxxx-xxxxx-xxxxx
#define NR_TEMPLICENSE_PREFIX_LEN   17
#define NR_TEMPLICENSE_LEN          (NR_TEMPLICENSE_PREFIX_LEN + NR_LICENSE_LEN)
#define NR_TEMPLICENSE_BUFSIZE      (NR_TEMPLICENSE_LEN + 1)

#define NR_MAX_MACID_NUMBER 20

#ifdef __cplusplus
extern "C" {
#endif

LICENSE_EXPORT NR_INT NR_API SetLicenseFile(NR_IN const NR_CHAR *szFileName);

LICENSE_EXPORT NR_STATUS NR_API CheckLicense(NR_IN const NR_CHAR *szSoftName);

LICENSE_EXPORT NR_INT NR_API CreateLicense(NR_IN const NR_CHAR *szSoftName,
                                           NR_IN const NR_CHAR *szHostID,
                                           NR_OUT NR_CHAR szLicense[NR_LICENSE_BUFSIZE]);

LICENSE_EXPORT NR_INT NR_API CreateTempLicense(NR_IN const NR_CHAR *szSoftName,
                                               NR_IN const NR_INT nYear,
                                               NR_IN const NR_INT nMon,
                                               NR_IN const NR_INT nDay,
                                               NR_OUT NR_CHAR szTempLicense[NR_TEMPLICENSE_BUFSIZE]);

LICENSE_EXPORT NR_INT NR_API CreateHostIDNew(NR_OUT NR_CHAR szHostID[NR_HOSTID_BUFSIZE],
                                             NR_IN NR_UINT unIndex);

LICENSE_EXPORT NR_INT NR_API RegisterLicense(NR_IN const NR_CHAR *szSoftName,
                                             NR_IN const NR_CHAR *szHostID,
                                             NR_IN const NR_CHAR *szLicense);

#ifdef __cplusplus
}
#endif

#endif // NR_LICENSE_H
