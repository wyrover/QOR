//x86Version.h

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

#include "ArchQOR/Common/Endian.h"
#include "x86Definitions.h"

#if( QOR_ARCH == QOR_ARCH_X86_32 )
#	define QOR_ARCH_WORDSIZE 32
#	define QOR_ARCH_ENDIAN	QOR_ARCH_BYTE_LITTLE_ENDIAN
#   if defined(__I86__)
#       define QOR_ARCH_X86 QOR_VERSION_NUMBER(__I86__,0,0)
#   endif
#   if defined(_M_IX86)
#       define QOR_ARCH_X86 QOR_PP_VERSION_MAKE_10_VV00(_M_IX86)
#   endif
#   if defined(__i786__)
#       define QOR_ARCH_X86 QOR_VERSION_NUMBER(7,0,0)
#	endif
#   if defined(__i686__)
#       define QOR_ARCH_X86 QOR_VERSION_NUMBER(6,0,0)
#   endif
#   if defined(__i586__)
#       define QOR_ARCH_X86 QOR_VERSION_NUMBER(5,0,0)
#   endif
#   if defined(__i486__)
#       define QOR_ARCH_X86 QOR_VERSION_NUMBER(4,0,0)
#   endif
#   if defined(__i386__)
#       define QOR_ARCH_X86 QOR_VERSION_NUMBER(3,0,0)
#   endif
#	define QOR_ARCH_NAME "Intel x86-32"
#elif( QOR_ARCH == QOR_ARCH_X86_64 )
#	define QOR_ARCH_WORDSIZE 64
#	define QOR_ARCH_ENDIAN	QOR_ARCH_BYTE_LITTLE_ENDIAN
#	define QOR_ARCH_NAME "Intel x86-64"
#	define QOR_ARCH_X86 QOR_VERSION_NUMBER(64,0,0)
#endif

