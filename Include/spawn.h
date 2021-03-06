//spawn.h

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

#ifndef	QOR_SPAWN_H_3
#define QOR_SPAWN_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(spawn)

typedef nsPlatform::posix_spawnattr_t posix_spawnattr_t;
typedef nsPlatform::posix_spawn_file_actions_t posix_spawn_file_actions_t ;
typedef nsPlatform::mode_t mode_t;
typedef nsPlatform::pid_t pid_t;
typedef nsPlatform::sigset_t sigset_t;
typedef nsPlatform::sched_param sched_param;

#define POSIX_SPAWN_RESETIDS			( nsPlatform::PosixSpawnResetIDs )
#define POSIX_SPAWN_SETPGROUP			( nsPlatform::PosixSpawnSetPGroup )
#define POSIX_SPAWN_SETSCHEDPARAM		( nsPlatform::PosixSpawnSetSchedParam )
#define POSIX_SPAWN_SETSCHEDULER		( nsPlatform::PosixSpawnSetScheduler )
#define POSIX_SPAWN_SETSIGDEF			( nsPlatform::PosixSpawnSetSigDef )
#define POSIX_SPAWN_SETSIGMASK			( nsPlatform::PosixSpawnSetSigMask )

__QCMP_STARTLINKAGE_C

	__QOR_INTERFACE( __CQOR ) int posix_spawn( pid_t* __QCMP_RESTRICT, const char* __QCMP_RESTRICT, const posix_spawn_file_actions_t*, const posix_spawnattr_t* __QCMP_RESTRICT, char* const[], char* const[] );
	__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_addclose( posix_spawn_file_actions_t*, int );
	__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_adddup2( posix_spawn_file_actions_t*, int, int );
	__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_addopen( posix_spawn_file_actions_t* __QCMP_RESTRICT, int, const char* __QCMP_RESTRICT, int, mode_t );
	__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_destroy( posix_spawn_file_actions_t* );
	__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_init( posix_spawn_file_actions_t* );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_destroy( posix_spawnattr_t* );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getflags( const posix_spawnattr_t* __QCMP_RESTRICT, short* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getpgroup( const posix_spawnattr_t* __QCMP_RESTRICT, pid_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getschedparam( const posix_spawnattr_t* __QCMP_RESTRICT, sched_param* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getschedpolicy( const posix_spawnattr_t* __QCMP_RESTRICT, int* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getsigdefault( const posix_spawnattr_t* __QCMP_RESTRICT, sigset_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getsigmask( const posix_spawnattr_t* __QCMP_RESTRICT, sigset_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_init( posix_spawnattr_t* );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setflags( posix_spawnattr_t*, short );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setpgroup( posix_spawnattr_t*, pid_t );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setschedparam( posix_spawnattr_t* __QCMP_RESTRICT, const sched_param* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setschedpolicy( posix_spawnattr_t*, int );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setsigdefault( posix_spawnattr_t* __QCMP_RESTRICT, const sigset_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setsigmask( posix_spawnattr_t* __QCMP_RESTRICT, const sigset_t* __QCMP_RESTRICT );
	__QOR_INTERFACE( __CQOR ) int posix_spawnp( pid_t* __QCMP_RESTRICT, const char* __QCMP_RESTRICT, const posix_spawn_file_actions_t*, const posix_spawnattr_t* __QCMP_RESTRICT, char* const[], char* const[] );

__QCMP_ENDLINKAGE_C

#endif//QOR_SPAWN_H_3
