//aio_types.h

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


#ifndef SYSTEMQOR_LIN_TYPES_AIO_H_3
#define SYSTEMQOR_LIN_TYPES_AIO_H_3

#include "SystemQOR/Linux/LIN_features.h"
#include "SystemQOR/Linux/types/signal_types.h"
#include "SystemQOR/Linux/types/time_types.h"

#define __NEED_ssize_t
#define __NEED_off_t

#include QOR_SYS_ARCHHEADER(alltypes.h)

//--------------------------------------------------------------------------------
namespace nsLinux
{
    //--------------------------------------------------------------------------------
    struct aiocb
    {
        int aio_fildes, aio_lio_opcode, aio_reqprio;
        volatile void* aio_buf;
        size_t aio_nbytes;
        sigevent aio_sigevent;
        void* __td;
        int __lock[ 2 ];
        int __err;
        ssize_t __ret;
        off_t aio_offset;
        void* __next, *__prev;
        char __dummy4[ 32 - 2 * sizeof(void*) ];
    };

    __QCMP_STATIC_CONSTANT( int, AIONotCancelled        = 0 );
    __QCMP_STATIC_CONSTANT( int, AIOCancelled           = 1 );
    __QCMP_STATIC_CONSTANT( int, AIOAllDone             = 2 );

    __QCMP_STATIC_CONSTANT( int, LIORead                = 0x0 );
    __QCMP_STATIC_CONSTANT( int, LIOWrite               = 0x1 );
    __QCMP_STATIC_CONSTANT( int, LIONoOp                = 0x2 );

    __QCMP_STATIC_CONSTANT( int, LIOWait                = 0x0 );
    __QCMP_STATIC_CONSTANT( int, LIONoWait              = 0x1 );

}//nsLinux

//#define AIO_CANCELED 0
//#define AIO_NOTCANCELED 1
//#define AIO_ALLDONE 2

//#define LIO_READ 0
//#define LIO_WRITE 1
//#define LIO_NOP 2

//#define LIO_WAIT 0
//#define LIO_NOWAIT 1


#endif//SYSTEMQOR_LIN_TYPES_AIO_H_3