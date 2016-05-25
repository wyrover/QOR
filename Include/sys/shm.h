//shm.h

// Copyright Querysoft Limited 2015
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

#ifndef	QOR_SYS_SHM_H_3
#define QOR_SYS_SHM_H_3

#include <sys/ipc.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMSYSTYPES(shm)

#define SHM_RDONLY				( nsPlatform::ShMReadOnly )				//Attach read-only (else read-write). 
#define SHM_RND					( nsPlatform::ShMRound )				//Round attach address to SHMLBA. 
#define SHMLBA					( nsPlatform::ShMLowBoundAddrMult )		//Segment low boundary address multiple. 

typedef nsPlatform::shmatt_t shmatt_t;									//Unsigned integer used for the number of current attaches that must be able to store values at least as large as a type unsigned short. 
typedef nsPlatform::shmid_ds shmid_ds;
typedef nsPlatform::pid_t pid_t;
//typedef nsPlatform::size_t size_t;
typedef nsPlatform::time_t time_t;

__QCMP_STARTLINKAGE_C
	__QOR_INTERFACE( __CQOR ) void* shmat( int, const void*, int );
	__QOR_INTERFACE( __CQOR ) int shmctl( int, int, ::shmid_ds* );
	__QOR_INTERFACE( __CQOR ) int shmdt( const void* );
	__QOR_INTERFACE( __CQOR ) int shmget( ::key_t, size_t, int );
__QCMP_ENDLINKAGE_C

#endif//QOR_SYS_SHM_H_3