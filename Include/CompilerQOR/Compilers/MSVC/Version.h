//Version.h

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

//Detect and include the header for the version of Microsoft Visual C++ being used

#ifndef QCMP_MSVC_VERSION_H_1
#define QCMP_MSVC_VERSION_H_1

#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Microsoft Visual C++ compiler" )
#endif

//Detect the compiler version so we can determine the rest of the supported settings
#if(_MSC_VER==600)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - C Compiler version 6.0" )
#endif
#	error("Sorry: A 32bit C++ compiler is required to build Querysoft Open Runtime libraries." )
#elif(_MSC_VER==700)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - C/C++ compiler version 7.0" )
#endif
#	error( "Sorry: A 32bit compiler is required to build Querysoft Open Runtime libraries." )
#elif(_MSC_VER==800)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual C++, Windows, version 1.0 or Visual C++, 32-bit, version 1.0" )
#	pragma message( "Version is older than MSVC6/EVC4 and may not work much at all, MSVC 6.0 config will be used. There will be errors." )
#endif
#	define __QCMP_COMPILER_NAME "Visual C++, Windows, version 1.0 or Visual C++, 32-bit, version 1.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VC6)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC6.h)
#elif(_MSC_VER==900)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual C++, Windows, version 2.0 or Visual C++, 32-bit, version 2.x" )
#	pragma message( "Version is older than MSVC6/EVC4 and may not work much at all, MSVC 6.0 config will be used. There will be errors" )
#endif
#	define __QCMP_COMPILER_NAME "Visual C++, Windows, version 2.0 or Visual C++, 32-bit, version 2.x"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VC6)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC6.h)
#elif(_MSC_VER==1000)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual C++, 32-bit, version 4.0" )
#	pragma message( "Version is older than MSVC6/EVC4 and may not work much at all, MSVC 6.0 config will be used. There will be errors" )
#endif
#	define __QCMP_COMPILER_NAME "Visual C++, 32-bit, version 4.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VC6)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC6.h)
#elif(_MSC_VER==1100)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual C++, 32-bit, version 5.0" )
#	pragma message( "Version is older than MSVC6/EVC4 and may not work much at all, MSVC 6.0 config will be used. There will be errors" )
#endif
#	define __QCMP_COMPILER_NAME "Visual C++, 32-bit, version 5.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VC6)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC6.h)
#elif(_MSC_VER>=1200 && _MSC_VER < 1300)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual C++, 32-bit, version 6.0" )
#	pragma message( "There are many standards compliance issues with this compiler especially with regards to templates. Expect some errors." )
#endif
#	define __QCMP_COMPILER_NAME "Visual C++, 32-bit, version 6.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VC6)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC6.h)
#elif(_MSC_VER==1300)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual Studio 2002, VC 7.0" )
#endif
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2002)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC2002.h)
#elif(_MSC_VER==1310)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual Studio 2003, VC 7.1" )
#endif
#	define __QCMP_COMPILER_NAME "Visual Studio 2003, VC 7.1"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2003)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC2003.h)
#elif(_MSC_VER==1400)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual Studio 2005, VC 8.0" )
#endif
#	define __QCMP_COMPILER_NAME "Visual Studio 2005, VC 8.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2005)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC2005.h)
#elif(_MSC_VER==1500)
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual Studio 2008, VC 9.0" )
#endif
#	define __QCMP_COMPILER_NAME "Visual Studio 2008, VC 9.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2008)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC2008.h)
#elif( _MSC_VER==1600 )
#	if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#		pragma message( "Version is - Visual Studio 2010, VC 10.0" )
#	endif
#	define __QCMP_COMPILER_VERSION_FOLDER VS2010
#	define __QCMP_COMPILER_NAME "Visual Studio 2010, VC 10.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2010)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC2010.h)
#elif( _MSC_VER==1700 )
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual Studio 2012, VC 11.0" )
#endif
#	define __QCMP_COMPILER_VERSION_FOLDER VS2012
#	define __QCMP_COMPILER_NAME "Visual Studio 2012, VC 11.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2012)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC11.h)
#elif( _MSC_VER==1800 )
#if ( __QCMP_REPORTCONIG == __QCS_YES_ )
#	pragma message( "Version is - Visual Studio 2013, VC 12.0" )
#endif
#	define __QCMP_COMPILER_VERSION_FOLDER VS2013
#	define __QCMP_COMPILER_NAME "Visual Studio 2013, VC 12.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2013)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC12.h)
#elif( _MSC_VER==1900 )
#if ( __QCMP_REPORTCONFIG == __QCS_YES_ )
#	pragma message( "Version is Visual Studio 2015, VC 14.0" )
#endif
#	define __QCMP_COMPILER_VERSION_FOLDER VS2015
#	define __QCMP_COMPILER_NAME "Visual Studio 2015, VC 14.0"
#	define __QCMP_COMPILER_FOLDER QOR_PP_CAT(__QCMP_COMPILER_ROOT_FOLDER,/VS2015)
#	define __QCMP_COMPILER_HEADER QOR_PP_CAT(__QCMP_COMPILER_FOLDER,/MSVC14.h)
#elif( _MSC_VER > 1900 )
//NOTE: ("Add new MSVC version support here" )
#	error "Version is later than VS2015: Please update this file: "
#else
#	error "Unable to determine Microsoft Compiler Version!"
#endif

#endif//QCMP_MSVC_VERSION_H_1
