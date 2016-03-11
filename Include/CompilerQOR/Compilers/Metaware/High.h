//High.h

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

/*
This file provides the following definitions:
__QCMP_STRINGIZER(x)		produces "x" or L"x" under QOR_UNICODE on supporting compilers
__QCMP_PATHIFY(_X,_Y)		Make path by joining path to / to filename
__QCMP_PATHIFY3(_X,_Y,_Z)
__QCMP_PATHIFY4(_X,_Y,_Z,_A)
__QCMP_PATHIFY5(_X,_Y,_Z,_A,_B)
__QCMP_PATHIFY6(_X,_Y,_Z,_A,_B,_C)
__QCMP_ERROR( _X )			Ensure code location is reported for explicit compilation warnings and errors
__QCMP_WARNING( _X )
__QCMP_NAMELESS_STRUCT		Nameless struct/union extension support. Defined e,pty if supported otherwise a workaround to generate a name
__QCMP_TRY
__QCMP_EXCEPT( _COND )
__QCMP_EXCEPT_ALL
__QCMP_FINALLY
__QCMP_RETHROW
__QCMP_TEMPLATE_OPERATOR_SPECIFIER	Defined as 'template' if template is needed in template operator member specifications
__QCMP_OPTIMIZEINCLUDE		pragma once support
__QCMP_MESSAGE				macro pragma supported compile tim emessages
TODO(_Message)				__QCMP_MESSAGE based development build TODO: reporting
__QCMP_WARNING_PUSH						//Warning control pragmas
__QCMP_WARNING_DISABLE(_X, _Reason )
__QCMP_WARNING_POP
__QCMP_WARNING_ENABLE(_X)
__QCMP_SUPPORTS__FUNCSIG__	//1 if __FUNCSIG__ available
__QCMP_FUNCSIG__( _X )
__QCMP_LONG_SUFFIX( _X )			//Type suffixes e.g. _X##l
__QCMP_UNSIGNED_SUFFIX( _X )
__QCMP_UNSIGNEDLONG_SUFFIX( _X )
__QCMP_LONGLONG_SUFFIX( _X )
__QCMP_FLOAT_SUFFIX( _X )
__QCMP_i64_SUFFIX( _X )
__QCMP_ui64_SUFFIX( _X )
__QCMP_STATIC_CONSTANT		//Assignment at declaration support


//warnings
__QCMP_WARN_MACRO_REDEFINITION
__QCMP_WARN_COND_EXPR_IS_CONST
__QCMP_WARN_UNARY_MINUS_APPLIED_TO_UNSIGNED
__QCMP_WARN_EXTENSION_USED_ZERO_SIZED_ARRAY
__QCMP_WARN_NAMELESS_STRUCTUNION
__QCMP_WARN_EXTENSION_EXTERN_TEMPLATE_INSTANCE
__QCMP_WARN_CONV_FROM_LONG_DOUBLE_TO_DOUBLE
__QCMP_WARN_CLASS_NEEDS_TO_HAVE_DLL_INTERFACE
__QCMP_WARN_NON_EXPORTED_BASE_FOR_EXPORT
__QCMP_WARN_TRUNCATION_FROM_DOUBLE_TO_FLOAT
__QCMP_WARN_STRUCTURE_PADDED_DUE_TO_ALIGN
__QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST
__QCMP_WARN_NO_DEFINITION_FOR_TEMPLATE_INST_REQ
__QCMP_WARN_UNREF_LOCAL_FUNCTION
__QCMP_WARN_UNINIT_LOCAL_VAR_USED
__QCMP_WARN_ASSIGNMENT_WITHIN_COND_EXPR

//extensions e.g.
#define Unicode_Const_Str_Conversion_QCMPSUPPORTED		1	//Has L## builtin macro

//emulation of missing fundamental types e.g
#if ( !__QCMP_SUPPORTS( __QCMP_FEATURE_NATIVEWCHARTSUPPORT ) )
typedef unsigned short	wchar_t;
#endif

//Linkage modes
#ifdef __cplusplus
#	define __QCMP_LINKAGE_C					extern "C"
#	define __QCMP_STARTLINKAGE_C			extern "C" {
#	define __QCMP_ENDLINKAGE_C				}
#	define __QCMP_LINKAGE_CPP				extern "C++"
#	define __QCMP_STARTLINKAGE_CPP			extern "C++" {
#	define __QCMP_ENDLINKAGE_CPP			}
#else
#	define __QCMP_LINKAGE_C					extern
#	define __QCMP_STARTLINKAGE_C
#	define __QCMP_ENDLINKAGE_C
#endif//__cplusplus

//Calling conventions
#define __QCMP_CALLCON						__cdecl
#define __QCMP_STDCALLCONVENTION			__stdcall
#define __QCMP_THISCALL						//explicit __thiscall not supported? not sure why you'd need it anyway?
#define __QCMP_FASTCALL						__fastcall

//Attributes
#define __QCMP_ALWAYSINLINE					__forceinline
#define __QCMP_DECLARE_PERTHREAD			__declspec(thread)
#define __QCMP_DECLARE_NAKED				__declspec(naked)
#define __QCMP_DECLARE_NOTHROW				__declspec(nothrow)
#define __QCMP_DECLARE_MERGE_INITIALIZERS	__declspec(selectany)
#define __QCMP_DECLARE_NORETURN				__declspec(noreturn)
#define __QCMP_DECLARE_TYPE_GUID(_UID)		__declspec(uuid(_UID))
#define __QCMP_DECLARE_PROPERTY(_GET, _PUT)	__declspec( property( get=_GET, put=_PUT ) )
#define __QCMP_DECLARE_ALIGNED( _ALIGNMENT ) __declspec( align( _ALIGNMENT ) )
#define __QCMP_RESTRICT						//not supported
#define __QCMP_NORETURN						//not supported
#define deprecated( _X )					//not supported
#define __QCMP_DECLARE_DEPRECATED			//not supported
#define __QCMP_ALIGNOF						__alignof
#define __QCMP_ALIGNAS(x)					__declspec(align(__alignof(x)))
#define __QCMP_DATA_SEGMENT(_X)				data_seg(_X) //for pragma data_seg() declarations
#define __QCMP_DEFAULT_DATA_SEGMENT			data_seg()
#define __attribute__(__ATTRIB__)			//not supported
#ifndef DECLSPEC_NORETURN
#	define DECLSPEC_NORETURN				__QCMP_DECLARE_NORETURN//Enable MinGW32 Win32 headers to declare noreturn
#endif//DECLSPEC_NORETURN
#define	__extension__						//not supported
#ifdef __QCMP_ITANIUM
#	define __QCMP_DECLARE_UNALIGNED			__unaligned
#else
#	define __QCMP_DECLARE_UNALIGNED
#endif

#define __QCMP_TEMPLATE_INST

//Module Interface declarations
#define __QCMP_EXPORT						__declspec(dllexport)	//declare an item as exported from the module
#define __QCMP_IMPORT						__declspec(dllimport) //declare an item as imported from another module
#define __QCMP_LOCAL						//declare an item as being local to a module

//exception specifications
#define __QCMP_THROW0()
#define __QCMP_THROW1(x1)
#define __QCMP_THROW throw()
#define __QCMP_NO_THROW throw()
#ifndef __THROW
#	define __THROW
#endif
#ifndef __NTH
#	define __NTH(fct) fct __THROW
#endif

//const qualifiers
#ifndef __const__
#	define __const__ const
#endif

#ifndef __const
#	define __const const
#endif

*/
