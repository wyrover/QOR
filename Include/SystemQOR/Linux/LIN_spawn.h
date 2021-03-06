//LIN_spawn.h

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

//Linux overrides for spawn

#ifndef SYSTEMQOR_LIN_SPAWN_H_3
#define SYSTEMQOR_LIN_SPAWN_H_3

#include "SystemQOR/Linux/types/spawn_types.h"
//#include "SystemQOR/Posix/Baseregex.h"

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cspawn //: public nsBaseCRT::Cregex
	{
	public:

		Cspawn(){}
		~Cspawn(){}

		int posix_spawn(pid_t *__restrict, const char *__restrict, const posix_spawn_file_actions_t *, const posix_spawnattr_t *__restrict, char *const *__restrict, char *const *__restrict);
		int posix_spawnp(pid_t *__restrict, const char *__restrict, const posix_spawn_file_actions_t *, const posix_spawnattr_t *__restrict, char *const *__restrict, char *const *__restrict);

		int posix_spawnattr_init(posix_spawnattr_t *);
		int posix_spawnattr_destroy(posix_spawnattr_t *);

		int posix_spawnattr_setflags(posix_spawnattr_t *, short);
		int posix_spawnattr_getflags(const posix_spawnattr_t *__restrict, short *__restrict);

		int posix_spawnattr_setpgroup(posix_spawnattr_t *, pid_t);
		int posix_spawnattr_getpgroup(const posix_spawnattr_t *__restrict, pid_t *__restrict);

		int posix_spawnattr_setsigmask(posix_spawnattr_t *__restrict, const sigset_t *__restrict);
		int posix_spawnattr_getsigmask(const posix_spawnattr_t *__restrict, sigset_t *__restrict);

		int posix_spawnattr_setsigdefault(posix_spawnattr_t *__restrict, const sigset_t *__restrict);
		int posix_spawnattr_getsigdefault(const posix_spawnattr_t *__restrict, sigset_t *__restrict);

		int posix_spawnattr_setschedparam(posix_spawnattr_t *__restrict, const struct sched_param *__restrict);
		int posix_spawnattr_getschedparam(const posix_spawnattr_t *__restrict, struct sched_param *__restrict);
		int posix_spawnattr_setschedpolicy(posix_spawnattr_t *, int);
		int posix_spawnattr_getschedpolicy(const posix_spawnattr_t *__restrict, int *__restrict);

		int posix_spawn_file_actions_init(posix_spawn_file_actions_t *);
		int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *);

		int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *__restrict, int, const char *__restrict, int, mode_t);
		int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *, int);
		int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *, int, int);

	private:

		Cspawn( const Cspawn& );
		Cspawn& operator = ( const Cspawn& );

	};

}//nsLinux

#endif//SYSTEMQOR_LIN_SPAWN_H_3
