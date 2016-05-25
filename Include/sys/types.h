//types.h

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

#ifndef QOR_SYS_TYPES_H_3
#define QOR_SYS_TYPES_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMSYSTYPES(types)

//include definitions for at least the following types:

typedef nsPlatform::blkcnt_t				blkcnt_t;				//Used for file block counts.//blkcnt_t and off_t shall be signed integer types.
typedef nsPlatform::blksize_t				blksize_t;				//Used for block sizes.//blksize_t, pid_t, and ssize_t shall be signed integer types.
typedef nsPlatform::clock_t					clock_t;				//[XSI]  Used for system times in clock ticks or CLOCKS_PER_SEC; see <time.h>./time_t and clock_t shall be integer or real-floating types.
typedef nsPlatform::clockid_t				clockid_t;				//[TMR]  Used for clock ID type in the clock and timer functions.
typedef nsPlatform::dev_t					dev_t;					//Used for device IDs.
typedef nsPlatform::fsblkcnt_t				fsblkcnt_t;				//[XSI]  Used for file system block counts. // fsblkcnt_t, fsfilcnt_t,   and ino_t shall be defined as unsigned integer types.
typedef nsPlatform::fsfilcnt_t				fsfilcnt_t;				//[XSI]  Used for file system file counts.
typedef nsPlatform::gid_t					gid_t;					//Used for group IDs.//nlink_t, uid_t, gid_t, and id_t shall be integer types.
typedef nsPlatform::id_t					id_t;					//[XSI]  Used as a general identifier; can be used to contain at least a pid_t, uid_t, or gid_t.
typedef nsPlatform::ino_t					ino_t;					//Used for file serial numbers. fsblkcnt_t, fsfilcnt_t,   and ino_t shall be defined as unsigned integer types.
typedef nsPlatform::key_t					key_t;					//[XSI]  Used for XSI interprocess communication.
typedef nsPlatform::mode_t					mode_t;					//Used for some file attributes.//mode_t shall be an integer type.
typedef nsPlatform::nlink_t					nlink_t;				//Used for link counts.//nlink_t, uid_t, gid_t, and id_t shall be integer types.
typedef nsPlatform::off_t					off_t;					//Used for file sizes.//blkcnt_t and off_t shall be signed integer types.
typedef nsPlatform::pid_t					pid_t;					//Used for process IDs and process group IDs.//blksize_t, pid_t, and ssize_t shall be signed integer types.
typedef nsPlatform::pthread_attr_t			pthread_attr_t;			//[THR]  Used to identify a thread attribute object.
typedef nsPlatform::pthread_barrier_t		pthread_barrier_t;		//[BAR]  Used to identify a barrier.
typedef nsPlatform::pthread_barrierattr_t	pthread_barrierattr_t;	//[BAR]  Used to define a barrier attributes object.
typedef nsPlatform::pthread_cond_t			pthread_cond_t;			//[THR]  Used for condition variables.
typedef nsPlatform::pthread_condattr_t		pthread_condattr_t;		//[THR]  Used to identify a condition attribute object.
typedef nsPlatform::pthread_key_t			pthread_key_t;			//[THR]  Used for thread-specific data keys.
typedef nsPlatform::pthread_mutex_t			pthread_mutex_t;		//[THR]  Used for mutexes.
typedef nsPlatform::pthread_mutexattr_t		pthread_mutexattr_t;	//[THR]  Used to identify a mutex attribute object.
typedef nsPlatform::pthread_once_t			pthread_once_t;			//[THR]  Used for dynamic package initialization.
typedef nsPlatform::pthread_rwlock_t		pthread_rwlock_t;		//[THR]  Used for read-write locks.
typedef nsPlatform::pthread_rwlockattr_t	pthread_rwlockattr_t;	//[THR]  Used for read-write lock attributes.
typedef nsPlatform::pthread_spinlock_t		pthread_spinlock_t;		//[SPI]  Used to identify a spin lock.
typedef nsPlatform::pthread_t				pthread_t;				//[THR]  Used to identify a thread.
//typedef nsPlatform::size_t				size_t;					//Used for sizes of objects.//size_t shall be an unsigned integer type.
typedef nsPlatform::ssize_t					ssize_t;				//Used for a count of bytes or an error indication.
typedef nsPlatform::suseconds_t				suseconds_t;			//[XSI]  Used for time in microseconds.
typedef nsPlatform::time_t					time_t;					//Used for time in seconds.//time_t and clock_t shall be integer or real-floating types.
typedef nsPlatform::timer_t					timer_t;				//[TMR]  Used for timer ID returned by timer_create().

//typedef nsPlatform::trace_attr_t			trace_attr_t;
typedef nsPlatform::trace_event_id_t		trace_event_id_t;		//[TRC]  Used to identify a trace event type.
typedef nsPlatform::trace_event_set_t		trace_event_set_t;		//[TRC TEF]  Used to identify a trace event type set.
typedef nsPlatform::trace_id_t				trace_id_t;				//[TRC]  Used to identify a trace stream.

typedef nsPlatform::uid_t					uid_t;					//Used for user IDs.//nlink_t, uid_t, gid_t, and id_t shall be integer types.
typedef nsPlatform::useconds_t				useconds_t;				//[XSI]  Used for time in microseconds.

#endif//QOR_SYS_TYPES_H_3