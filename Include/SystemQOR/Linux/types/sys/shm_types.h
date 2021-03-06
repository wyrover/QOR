//shm_types.h

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

#ifndef SYSTEMQOR_LIN_TYPES_SYS_SHMTYPES_H_3
#define SYSTEMQOR_LIN_TYPES_SYS_SHMTYPES_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __NEED_size_t
#define __NEED_pid_t
#define __NEED_time_t

#include QOR_SYS_ARCHHEADER(alltypes.h)
#include <sys/ipc.h>

#ifdef _GNU_SOURCE
#   define __used_ids used_ids
#   define __swap_attempts swap_attempts
#   define __swap_successes swap_successes
#endif

#include QOR_SYS_ARCHHEADER(shm.h)

#define SHM_R 0400
#define SHM_W 0200

#define SHM_RDONLY 010000
#define SHM_RND    020000
#define SHM_REMAP  040000
#define SHM_EXEC   0100000

#define SHM_LOCK 11
#define SHM_UNLOCK 12
#define SHM_STAT 13
#define SHM_INFO 14
#define SHM_DEST 01000
#define SHM_LOCKED 02000
#define SHM_HUGETLB 04000
#define SHM_NORESERVE 010000
//------------------------------------------------------------------------------
namespace nsLinux
{
    typedef unsigned long shmatt_t;
}//nsLinux


#endif//SYSTEMQOR_LIN_TYPES_SYS_SEMTYPES_H_3
