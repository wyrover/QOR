//excpt.h

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

#ifndef _WINCMPSUPVC_EXCPT_H_
#define _WINCMPSUPVC_EXCPT_H_

#include "CompilerQOR.h"

__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
//Exception disposition return values.
 
typedef enum _EXCEPTION_DISPOSITION 
{
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;

//--------------------------------------------------------------------------------
#ifdef  _MSC_VER

	#define GetExceptionCode            _exception_code
	#define exception_code              _exception_code
	#define GetExceptionInformation     (struct nsWin32::_EXCEPTION_POINTERS *)_exception_info
	#define exception_info              (struct nsWin32::_EXCEPTION_POINTERS *)_exception_info
	#define AbnormalTermination         _abnormal_termination
	#define abnormal_termination        _abnormal_termination

	unsigned long __cdecl _exception_code(void);
	void *        __cdecl _exception_info(void);
	int           __cdecl _abnormal_termination(void);

#endif


//Legal values for expression in except().

#define EXCEPTION_EXECUTE_HANDLER       1
#define EXCEPTION_CONTINUE_SEARCH       0
#define EXCEPTION_CONTINUE_EXECUTION    -1

__QCMP_ENDLINKAGE_C

#endif //_WINCMPSUPVC_EXCPT_H_