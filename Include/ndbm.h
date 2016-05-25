//ndbm.h

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef	QOR_NDBM_H_3
#define QOR_NDBM_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(ndbm)

typedef nsPlatform::DBM DBM;
typedef nsPlatform::datum datum;
typedef nsPlatform::mode_t mode_t;

#define DBM_INSERT			( nsPlatform::DBMInsert )			//Insertion of new entries only. 
#define DBM_REPLACE			( nsPlatform::DBMReplace )			//Allow replacing existing entries.

__QCMP_STARTLINKAGE_C

    __QOR_INTERFACE( __CQOR ) int dbm_clearerr( DBM* );
    __QOR_INTERFACE( __CQOR ) void dbm_close( DBM* );
    __QOR_INTERFACE( __CQOR ) int dbm_delete( DBM*, datum );
    __QOR_INTERFACE( __CQOR ) int dbm_error( DBM* );
    __QOR_INTERFACE( __CQOR ) datum dbm_fetch( DBM*, datum );
    __QOR_INTERFACE( __CQOR ) datum dbm_firstkey( DBM* );
    __QOR_INTERFACE( __CQOR ) datum dbm_nextkey( DBM* );
    __QOR_INTERFACE( __CQOR ) DBM* dbm_open( const char *, int, mode_t );
    __QOR_INTERFACE( __CQOR ) int dbm_store( DBM*, datum, datum, int );

__QCMP_ENDLINKAGE_C

#endif//QOR_NDBM_H_3