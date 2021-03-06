//spawn.cpp

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

#include "CQOR/CQORPolicy.h"
#include <spawn.h>
#include <errno.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMHEADER(spawn.h)
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/ErrorSystem/Error.h"
#include "CQOR.h"

//--------------------------------------------------------------------------------
namespace
{
	nsPlatform::Cspawn _spawn;
}//anonymous


__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawn( pid_t* __QCMP_RESTRICT pid, const char* __QCMP_RESTRICT path, const posix_spawn_file_actions_t* file_actions, const posix_spawnattr_t* __QCMP_RESTRICT attrp, char* const argv[], char* const envp[] )
{
    __QCS_FCONTEXT( "posix_spawn" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawn( pid, path, file_actions, attrp, argv, envp );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_addclose( posix_spawn_file_actions_t* file_actions, int fd )
{
    __QCS_FCONTEXT( "posix_spawn_file_actions_addclose" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawn_file_actions_addclose( file_actions, fd );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_adddup2( posix_spawn_file_actions_t* file_actions, int fd, int newfd )
{
    __QCS_FCONTEXT( "posix_spawn_file_actions_adddup2" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawn_file_actions_adddup2( file_actions, fd, newfd );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_addopen( posix_spawn_file_actions_t* __QCMP_RESTRICT file_actions, int fd, const char* __QCMP_RESTRICT szPath, int oFlag, mode_t mode )
{
    __QCS_FCONTEXT( "posix_spawn_file_actions_addopen" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawn_file_actions_addopen( file_actions, fd, szPath, oFlag, mode );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_destroy( posix_spawn_file_actions_t* file_actions )
{
    __QCS_FCONTEXT( "posix_spawn_file_actions_destroy" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawn_file_actions_destroy( file_actions );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawn_file_actions_init( posix_spawn_file_actions_t* file_actions )
{
    __QCS_FCONTEXT( "posix_spawn_file_actions_init" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawn_file_actions_init( file_actions );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_destroy( posix_spawnattr_t* attr )
{
    __QCS_FCONTEXT( "posix_spawnattr_destroy" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_destroy( attr );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getflags( const posix_spawnattr_t* __QCMP_RESTRICT attr, short* __QCMP_RESTRICT pFlags )
{
    __QCS_FCONTEXT( "posix_spawnattr_getflags" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_getflags( attr, pFlags );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getpgroup( const posix_spawnattr_t* __QCMP_RESTRICT attr, pid_t* __QCMP_RESTRICT pPid )
{
    __QCS_FCONTEXT( "posix_spawnattr_getpgroup" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_getpgroup( attr, pPid );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getschedparam( const posix_spawnattr_t* __QCMP_RESTRICT attr, sched_param* __QCMP_RESTRICT pParam )
{
    __QCS_FCONTEXT( "posix_spawnattr_getschedparam" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_getschedparam( attr, pParam );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getschedpolicy( const posix_spawnattr_t* __QCMP_RESTRICT attr, int* __QCMP_RESTRICT pPolicy )
{
    __QCS_FCONTEXT( "posix_spawnattr_getschedpolicy" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_getschedpolicy( attr, pPolicy );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getsigdefault( const posix_spawnattr_t* __QCMP_RESTRICT attr, sigset_t* __QCMP_RESTRICT pSigSet )
{
    __QCS_FCONTEXT( "posix_spawnattr_getsigdefault" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_getsigdefault( attr, pSigSet );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_getsigmask( const posix_spawnattr_t* __QCMP_RESTRICT attr, sigset_t* __QCMP_RESTRICT pSigSet )
{
    __QCS_FCONTEXT( "posix_spawnattr_getsigmask" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_getsigmask( attr, pSigSet );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_init( posix_spawnattr_t* attr )
{
    __QCS_FCONTEXT( "posix_spawnattr_init" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_init( attr );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setflags( posix_spawnattr_t* attr, short Flags )
{
    __QCS_FCONTEXT( "posix_spawnattr_setflags" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_setflags( attr, Flags );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setpgroup( posix_spawnattr_t* attr, pid_t Pid )
{
    __QCS_FCONTEXT( "posix_spawnattr_setpgroup" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_setpgroup( attr, Pid );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setschedparam( posix_spawnattr_t* __QCMP_RESTRICT attr, const sched_param* __QCMP_RESTRICT pParam )
{
    __QCS_FCONTEXT( "posix_spawnattr_setschedparam" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_setschedparam( attr, pParam );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setschedpolicy( posix_spawnattr_t* attr, int iPolicy )
{
    __QCS_FCONTEXT( "posix_spawnattr_setschedpolicy" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_setschedpolicy( attr, iPolicy );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setsigdefault( posix_spawnattr_t* __QCMP_RESTRICT attr, const sigset_t* __QCMP_RESTRICT pSigSet )
{
    __QCS_FCONTEXT( "posix_spawnattr_setsigdefault" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_setsigdefault( attr, pSigSet );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnattr_setsigmask( posix_spawnattr_t* __QCMP_RESTRICT attr, const sigset_t* __QCMP_RESTRICT pSigSet )
{
    __QCS_FCONTEXT( "posix_spawnattr_setsigmask" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnattr_setsigmask( attr, pSigSet );
    }__QCS_ENDPROTECT
	return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_spawnp( pid_t* __QCMP_RESTRICT pPid, const char* __QCMP_RESTRICT szFile, const posix_spawn_file_actions_t* file_actions, const posix_spawnattr_t* __QCMP_RESTRICT attrp, char* const argv[], char* const envp[] )
{
    __QCS_FCONTEXT( "posix_spawnp" );

	int iResult = -1;
    __QCS_PROTECT
    {
		iResult = _spawn.posix_spawnp( pPid, szFile, file_actions, attrp, argv, envp );
    }__QCS_ENDPROTECT
	return iResult;
}

__QCMP_ENDLINKAGE_C


