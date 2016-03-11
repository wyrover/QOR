//MSVC2002.h

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

//Header for MSVC 7.0 Compiler

#ifndef QCMP_MSVC2002_H_1
#define QCMP_MSVC2002_H_1

#include "../VC6/MSVC6.h"

#undef  __QCMP_THISCALL
#define __QCMP_THISCALL	__thiscall

//--------------------------------------------------------------------------------
//This version is the first to have 64 bit support
#if !defined(__midl) && ( defined(_X86_) || defined(_M_IX86) )
	#undef  _W64
	#define _W64 __w64
#endif


//--------------------------------------------------------------------------------
namespace nsCompiler
{
	//--------------------------------------------------------------------------------
	namespace EH
	{
		struct HandlerType;
	}//EH

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QCMP ) CMSVCCompiler7 : public CMSVCCompiler6
	{
	public:

		CMSVCCompiler7()
		{
		}

		virtual ~CMSVCCompiler7()
		{
		}

		//Visual C++ 7 adds 64bit types and 64bit compilation support

		typedef long long					mxc_long_long;
		typedef const long long				mxc_c_long_long;
		typedef volatile long long			mxc_v_long_long;
		typedef unsigned long long			mxc_unsigned_long_long;
		typedef const unsigned long long	mxc_c_unsigned_long_long;
		typedef volatile unsigned long long	mxc_v_unsigned_long_long;
				
		#if defined(_WIN64)
			typedef mxc__int64				mxc_int_ptr, *pmxc_int_ptr;
			typedef mxc_unsigned__int64		mxc_uint_ptr, *pmxc_uint_ptr;

			typedef mxc__int64				mxc_long_ptr, *pmxc_long_ptr;
			typedef mxc_unsigned__int64		mxc_ulong_ptr, *pmxc_ulong_ptr;

			typedef mxc__int64				mxc__int3264;

		#else
			typedef _W64 mxc_int			mxc_int_ptr, *pmxc_int_ptr;
			typedef _W64 mxc_unsigned_int	mxc_uint_ptr, *pmxc_uint_ptr;

			typedef _W64 mxc_long			mxc_long_ptr, *pmxc_long_ptr;
			typedef _W64 mxc_unsigned_long	mxc_ulong_ptr, *pmxc_ulong_ptr;

			typedef mxc__int32				mxc__int3264;

		#endif

		__QCMP_STATIC_CONSTANT( unsigned int, EH_MAGIC					= 0x19930521 );
	
		//--------------------------------------------------------------------------------
		//An additional pointer member gets added to the definition of FuncInfo
		struct FuncInfo : public CMSVCCompiler6::FuncInfo 
		{
			struct nsCompiler::EH::HandlerType*   m_pHandlerType;
		};

	};

}//nsCompiler

#endif//QCMP_MSVC2002_H_1
