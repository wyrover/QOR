//MSW_spawn.cpp

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

#include "SystemQOR.h"

#if		(QOR_SYS_OS == QOR_SYS_MSW)

#include "SystemQOR/MSWindows/MSW_spawn.h"
#include "WinQL/WinQL.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	Cspawn::Cspawn()
	{
		__QCS_MEMBER_FCONTEXT( "Cspawn::Cspawn" );
	}

	//--------------------------------------------------------------------------------
	Cspawn::~Cspawn()
	{
		__QCS_MEMBER_FCONTEXT( "Cspawn::~Cspawn" );
	}

	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawn( pid_t* , const char* , const posix_spawn_file_actions_t*, const posix_spawnattr_t* , char* const[], char* const[] )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawn_file_actions_addclose( posix_spawn_file_actions_t*, int )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawn_file_actions_adddup2( posix_spawn_file_actions_t*, int, int )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawn_file_actions_addopen( posix_spawn_file_actions_t* , int, const char* , int, mode_t )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawn_file_actions_destroy( posix_spawn_file_actions_t* )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawn_file_actions_init( posix_spawn_file_actions_t* )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_destroy( posix_spawnattr_t* )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_getflags( const posix_spawnattr_t* , short*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_getpgroup( const posix_spawnattr_t* , pid_t*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_getschedparam( const posix_spawnattr_t* , sched_param*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_getschedpolicy( const posix_spawnattr_t* , int*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_getsigdefault( const posix_spawnattr_t* , sigset_t*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_getsigmask( const posix_spawnattr_t* , sigset_t*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_init( posix_spawnattr_t* )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_setflags( posix_spawnattr_t*, short )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_setpgroup( posix_spawnattr_t*, pid_t )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_setschedparam( posix_spawnattr_t* , const sched_param*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_setschedpolicy( posix_spawnattr_t*, int )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_setsigdefault( posix_spawnattr_t* , const sigset_t*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnattr_setsigmask( posix_spawnattr_t* , const sigset_t*  )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}
	
	//--------------------------------------------------------------------------------
	int Cspawn::posix_spawnp( pid_t* , const char* , const posix_spawn_file_actions_t*, const posix_spawnattr_t* , char* const[], char* const[] )
	{
		//TODO:
		int iResult = -1;
		return iResult;
	}

}//nsWin32

#endif//(QOR_SYS_OS == QOR_SYS_MSW)
