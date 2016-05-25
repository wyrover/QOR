//i286CPU.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
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

//Not really an 80286 16bit target, just the 80286 inherited instructions for 32 and 64 bit x86 targets.
//Breaks up x86 classes that would otherwise be too large.

#ifndef ARCHQOR_X86PC_I286CPU_H_2
#define ARCHQOR_X86PC_I286CPU_H_2

#include "i186CPU.h"

//------------------------------------------------------------------------------
namespace nsArch
{
//------------------------------------------------------------------------------
namespace nsx86
{
	//------------------------------------------------------------------------------
	//80286
	class __QOR_INTERFACE( __ARCHQOR ) Ci286CPU : public Ci186CPU
	{
	public:

		Ci286CPU( CCodeGeneratorBase* codeGenerator ) __QCMP_THROW;
		~Ci286CPU() __QCMP_THROW;

	private:

		Ci286CPU( const Ci286CPU& src );//no copy constructor
		Ci286CPU& operator = ( const Ci286CPU& src );//no assignment
/*

ARPL Adjust RPL field of selector
CLTS Clear task-switched flag in register CR0
LAR Load access rights byte
LGDT Load global descriptor table
LIDT Load interrupt descriptor table
LLDT Load local descriptor table
LMSW Load machine status word
LOADALL Load all CPU registers, including internal ones such as GDT. Undocumented, 80286 and 80386 only
LSL Load segment limit
LTR Load task register
SGDT Store global descriptor table
SIDT Store interrupt descriptor table
SLDT Store local descriptor table
SMSW Store machine status word
STR Store task register
VERR Verify a segment for reading
VERW Verify a segment for writing
*/
	};

}//nsx86
}//nsArch

#endif//ARCHQOR_X86PC_I286CPU_H_2
