//IBMXL.h

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
/*
// (C) Copyright Douglas Gregor 2010
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  compiler setup for IBM XL C/C++ for Linux (Little Endian) based on clang.

#define BOOST_HAS_PRAGMA_ONCE

// Detecting `-fms-extension` compiler flag assuming that _MSC_VER defined when that flag is used.
#if defined (_MSC_VER) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4))
#   define BOOST_HAS_PRAGMA_DETECT_MISMATCH
#endif

// When compiling with clang before __has_extension was defined,
// even if one writes 'defined(__has_extension) && __has_extension(xxx)',
// clang reports a compiler error. So the only workaround found is:

#ifndef __has_extension
#define __has_extension __has_feature
#endif

#if !__has_feature(cxx_exceptions) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif

#if !__has_feature(cxx_rtti) && !defined(BOOST_NO_RTTI)
#  define BOOST_NO_RTTI
#endif

#if !__has_feature(cxx_rtti) && !defined(BOOST_NO_TYPEID)
#  define BOOST_NO_TYPEID
#endif

#if defined(__int64) && !defined(__GNUC__)
#  define BOOST_HAS_MS_INT64
#endif

#define BOOST_HAS_NRVO

// Branch prediction hints
#if defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define BOOST_LIKELY(x) __builtin_expect(x, 1)
#define BOOST_UNLIKELY(x) __builtin_expect(x, 0)
#endif
#endif

// Clang supports "long long" in all compilation modes.
#define BOOST_HAS_LONG_LONG

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  define BOOST_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define BOOST_SYMBOL_IMPORT
#  define BOOST_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#endif

//
// The BOOST_FALLTHROUGH macro can be used to annotate implicit fall-through
// between switch labels.
//
#if __cplusplus >= 201103L && defined(__has_warning)
#  if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#    define BOOST_FALLTHROUGH [[clang::fallthrough]]
#  endif
#endif

#if !__has_feature(cxx_auto_type)
#  define BOOST_NO_CXX11_AUTO_DECLARATIONS
#  define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif

//
// Currently clang on Windows using VC++ RTL does not support C++11's char16_t or char32_t
//
#if defined(_MSC_VER) || !(defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#endif

#if !__has_feature(cxx_constexpr)
#  define BOOST_NO_CXX11_CONSTEXPR
#endif

#if !__has_feature(cxx_decltype)
#  define BOOST_NO_CXX11_DECLTYPE
#endif

#if !__has_feature(cxx_decltype_incomplete_return_types)
#  define BOOST_NO_CXX11_DECLTYPE_N3276
#endif

#if !__has_feature(cxx_defaulted_functions)
#  define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

#if !__has_feature(cxx_deleted_functions)
#  define BOOST_NO_CXX11_DELETED_FUNCTIONS
#endif

#if !__has_feature(cxx_explicit_conversions)
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif

#if !__has_feature(cxx_default_function_template_args)
#  define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif

#if !__has_feature(cxx_lambdas)
#  define BOOST_NO_CXX11_LAMBDAS
#endif

#if !__has_feature(cxx_local_type_template_args)
#  define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif

#if !__has_feature(cxx_noexcept)
#  define BOOST_NO_CXX11_NOEXCEPT
#endif

#if !__has_feature(cxx_nullptr)
#  define BOOST_NO_CXX11_NULLPTR
#endif

#if !__has_feature(cxx_range_for)
#  define BOOST_NO_CXX11_RANGE_BASED_FOR
#endif

#if !__has_feature(cxx_raw_string_literals)
#  define BOOST_NO_CXX11_RAW_LITERALS
#endif

#if !__has_feature(cxx_reference_qualified_functions)
#  define BOOST_NO_CXX11_REF_QUALIFIERS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

#if !__has_feature(cxx_rvalue_references)
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#endif

#if !__has_feature(cxx_strong_enums)
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#endif

#if !__has_feature(cxx_static_assert)
#  define BOOST_NO_CXX11_STATIC_ASSERT
#endif

#if !__has_feature(cxx_alias_templates)
#  define BOOST_NO_CXX11_TEMPLATE_ALIASES
#endif

#if !__has_feature(cxx_unicode_literals)
#  define BOOST_NO_CXX11_UNICODE_LITERALS
#endif

#if !__has_feature(cxx_variadic_templates)
#  define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif

#if !__has_feature(cxx_user_literals)
#  define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#endif

#if !__has_feature(cxx_alignas)
#  define BOOST_NO_CXX11_ALIGNAS
#endif

#if !__has_feature(cxx_trailing_return)
#  define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#endif

#if !__has_feature(cxx_inline_namespaces)
#  define BOOST_NO_CXX11_INLINE_NAMESPACES
#endif

#if !__has_feature(cxx_override_control)
#  define BOOST_NO_CXX11_FINAL
#endif

#if !(__has_feature(__cxx_binary_literals__) || __has_extension(__cxx_binary_literals__))
#  define BOOST_NO_CXX14_BINARY_LITERALS
#endif

#if !__has_feature(__cxx_decltype_auto__)
#  define BOOST_NO_CXX14_DECLTYPE_AUTO
#endif

#if !__has_feature(__cxx_aggregate_nsdmi__)
#  define BOOST_NO_CXX14_AGGREGATE_NSDMI
#endif

#if !__has_feature(__cxx_init_captures__)
#  define BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif

#if !__has_feature(__cxx_generic_lambdas__)
#  define BOOST_NO_CXX14_GENERIC_LAMBDAS
#endif

// clang < 3.5 has a defect with dependent type, like following.
//
//  template <class T>
//  constexpr typename enable_if<pred<T> >::type foo(T &)
//  { } // error: no return statement in constexpr function
//
// This issue also affects C++11 mode, but C++11 constexpr requires return stmt.
// Therefore we don't care such case.
//
// Note that we can't check Clang version directly as the numbering system changes depending who's
// creating the Clang release (see https://github.com/boostorg/config/pull/39#issuecomment-59927873)
// so instead verify that we have a feature that was introduced at the same time as working C++14
// constexpr (generic lambda's in this case):
//
#if !__has_feature(__cxx_generic_lambdas__) || !__has_feature(__cxx_relaxed_constexpr__)
#  define BOOST_NO_CXX14_CONSTEXPR
#endif

#if !__has_feature(__cxx_return_type_deduction__)
#  define BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif

#if !__has_feature(__cxx_variable_templates__)
#  define BOOST_NO_CXX14_VARIABLE_TEMPLATES
#endif

#if __cplusplus < 201400
// All versions with __cplusplus above this value seem to support this:
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#endif


// Unused attribute:
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  define BOOST_ATTRIBUTE_UNUSED __attribute__((unused))
#endif

#ifndef BOOST_COMPILER
#  define BOOST_COMPILER "Clang version " __clang_version__
#endif

// Macro used to identify the Clang compiler.
#define BOOST_CLANG 1

*/