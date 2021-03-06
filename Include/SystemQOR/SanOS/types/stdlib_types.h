//stdlib_types.h

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

//SanOS specific definitions associated with stdlib

#ifndef SYSTEMQOR_SAN_TYPES_STDLIB_H_1
#define SYSTEMQOR_SAN_TYPES_STDLIB_H_1

#include "stddef_types.h"
//#include "limits_types.h"
//#include "math_types.h"
//#include "sys/wait_types.h"
//#include "ctype_types.h"	//TODO:

//--------------------------------------------------------------------------------
namespace nsSanOS
{
	typedef int (__cdecl * _onexit_t)(void);

	//--------------------------------------------------------------------------------
	struct HeapInfo
	{
		int* _pentry;
		size_t _size;
		int _useflag;
	};

	typedef void (__cdecl *_PVFV)(void);
	typedef int  (__cdecl *_PIFV)(void);
	typedef void (__cdecl *_PVFI)(int);

	__QCMP_STATIC_CONSTANT( int, ExitFailure =			1 );				//Unsuccessful termination for exit(); evaluates to a non-zero value. 
	__QCMP_STATIC_CONSTANT( int, ExitSuccess =			0 );				//Successful termination for exit(); evaluates to 0. 
	__QCMP_STATIC_CONSTANT( int, Null =					0 );
	__QCMP_STATIC_CONSTANT( int, RandMax =				32767 );			//Maximum value returned by rand(); at least 32767. 

	//--------------------------------------------------------------------------------
	// Data structure definitions for div and ldiv runtimes.
	typedef struct _div_t 
	{
		int quot;
		int rem;
	} div_t;

	//--------------------------------------------------------------------------------
	typedef struct _ldiv_t 
	{
		long quot;
		long rem;
	} ldiv_t;

	//--------------------------------------------------------------------------------
	__extension__ typedef struct
	{
		Cmp_long_long quot;		// Quotient.
		Cmp_long_long rem;		// Remainder.
	} lldiv_t;

	//--------------------------------------------------------------------------------
	__QOR_INTERFACE( __QSYS )  int MBCurMax( void );
	//__QOR_INTERFACE( __QSYS )  int MBCurMax_l( locale_t );//TODO:

// Minimum and maximum macros

#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

//
// Sizes for buffers used by the _makepath() and _splitpath() functions.
// note that the sizes include space for 0-terminator
 
	__QCMP_STATIC_CONSTANT( int, MaxPath = 256 );		// Maximum filename length (including trailing zero)
	__QCMP_STATIC_CONSTANT( int, MaxDrive =		3 );			//max. length of drive component
	__QCMP_STATIC_CONSTANT( int, MaxDir =		256 );			//max. length of path component
	__QCMP_STATIC_CONSTANT( int, MaxFName =		256 );			//max. length of file name component
	__QCMP_STATIC_CONSTANT( int, MaxExt =		256 );			//max. length of extension component */

	__QCMP_STATIC_CONSTANT( int, WaitUntraced =		1 );
	__QCMP_STATIC_CONSTANT( int, WaitNoHang =		2 );

}//nsSanOS

#endif//SYSTEMQOR_SAN_TYPES_STDLIB_H_1
