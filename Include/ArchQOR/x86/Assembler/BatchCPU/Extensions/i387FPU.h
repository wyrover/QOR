//i387FPU.h

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

#ifndef ARCHQOR_X86PC_I387FPU_H_2
#define ARCHQOR_X86PC_I387FPU_H_2

#include "CompilerQOR.h"
#include "ArchQOR/Common/Assembler/BatchCPU/FPUBase.h"
#include "ArchQOR/x86/Assembler/BatchCPU/x86CPUCore.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/MMReg.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/XMMReg.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/GPReg.h"
#include "ArchQOR/x86/Assembler/Operands/Mem.h"
#include "ArchQOR/x86/Assembler/Operands/Registers/X87Reg.h"
#include "ArchQOR/x86/Assembler/Operands/Imm.h"
#include "ArchQOR/x86/Assembler/Operands/Label.h"
#include "ArchQOR/x86/Assembler/BatchCPU/x86ISetExtension.h"


//------------------------------------------------------------------------------
namespace nsArch
{
//------------------------------------------------------------------------------
namespace nsx86
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __ARCHQOR ) C387FPU : public Cx86ISetExtension, public nsArch::CFPUBase
	{
	public:

		typedef unsigned int fexcept_t;

		//--------------------------------------------------------------------------------
		typedef struct
		{
			fexcept_t __excepts;				
		} fenv_t;

		C387FPU( Cx86CPUCore& refCPU );
		virtual ~C387FPU();
		void f2xm1();//Compute 2^x - 1 (FPU).
		void fabs();//Absolute Value of st(0) (FPU).
		void fadd( const CX87Reg& dst, const CX87Reg& src );//Add src to dst and store result in dst (FPU). Note One of dst or src must be st( 0 ).
		void fadd( const CMem& src );//Add src to st( 0 ) and store result in st( 0 ) (FPU). Note SP-FP or DP-FP determined by adr size.
		void faddp( const CX87Reg& dst = nsArch::nsx86::st( 1 ) );//Add st(0) to dst and POP register stack (FPU).
		void fbld( const CMem& src );//Load Binary Coded Decimal (FPU).
		void fbstp( const CMem& dst );//Store BCD Integer and Pop (FPU).
		void fchs();//Change st(0) Sign (FPU).
		void fclex();//Clear Exceptions (FPU).
		void fcmovb( const CX87Reg& src );//FP Conditional Move (FPU).
		void fcmovbe( const CX87Reg& src );//FP Conditional Move (FPU).
		void fcmove( const CX87Reg& src );//FP Conditional Move (FPU).
		void fcmovnb( const CX87Reg& src );//FP Conditional Move (FPU).
		void fcmovnbe( const CX87Reg& src );//FP Conditional Move (FPU).		
		void fcmovne( const CX87Reg& src );//FP Conditional Move (FPU).
		void fcmovnu( const CX87Reg& src );//FP Conditional Move (FPU).
		void fcmovu( const CX87Reg& src );//FP Conditional Move (FPU).
		void fcom( const CX87Reg& reg = st( 1 ) );//Compare st(0) with reg (FPU).
		void fcom( const CMem& src );//Compare st(0) with 4-byte or 8-byte FP at src (FPU).
		void fcomp( const CX87Reg& reg = st( 1 ) );//Compare st(0) with reg and pop the stack (FPU).
		void fcomp( const CMem& mem );//Compare st(0) with 4-byte or 8-byte FP at adr and pop the stack (FPU).		
		void fcompp();//Compare st(0) with st(1) and pop register stack twice (FPU).		
		void fcomi( const CX87Reg& reg );//Compare st(0) and reg and Set EFLAGS (FPU).		
		void fcomip( const CX87Reg& reg );//Compare st(0) and reg and Set EFLAGS and pop the stack (FPU).
		void fcos();		//Cosine (FPU). This instruction calculates the cosine of the source operand in register st(0) and stores the result in st(0).
		void fdecstp();//Decrement Stack-Top Pointer (FPU).
		void fdiv( const CX87Reg& dst, const CX87Reg& src );//Divide dst by src (FPU). Note One of dst or src register must be st(0).
		void fdiv( const CMem& src );//Divide st(0) by 32-bit or 64-bit FP value (FPU).
		void fdivp( const CX87Reg& reg = st( 1 ) );//Divide reg by st(0) (FPU).
		void fdivr( const CX87Reg& dst, const CX87Reg& src );//Reverse Divide dst by src (FPU). Note One of dst or src register must be st( 0 ).
		void fdivr( const CMem& src );//Reverse Divide st(0) by 32-bit or 64-bit FP value (FPU).		
		void fdivrp( const CX87Reg& reg = st( 1 ) );//Reverse Divide reg by st(0) (FPU).
		void ffree( const CX87Reg& reg );//Free Floating-Point Register (FPU).		
		void fiadd( const CMem& src );//Add 16-bit or 32-bit integer to st(0) (FPU).		
		void ficom( const CMem& src );//Compare st(0) with 16-bit or 32-bit Integer (FPU).
		void ficomp( const CMem& src );//Compare st(0) with 16-bit or 32-bit Integer and pop the stack (FPU).
		void fidiv( const CMem& src );//Divide st(0) by 32-bit or 16-bit integer (FPU).		
		void fidivr( const CMem& src );//Reverse Divide st(0) by 32-bit or 16-bit integer (FPU).
		void fild( const CMem& src );//Load 16-bit, 32-bit or 64-bit Integer and push it to the stack (FPU).
		void fimul( const CMem& src );//Multiply st(0) by 16-bit or 32-bit integer and store it to st(0) (FPU).
		void fincstp();//Increment Stack-Top Pointer (FPU).
		void finit();//Initialize Floating-Point Unit (FPU).
		void fisub( const CMem& src );//Subtract 16-bit or 32-bit integer from st(0) and store result to st(0) (FPU).
		void fisubr( const CMem& src );//Reverse Subtract 16-bit or 32-bit integer from st(0) and store result to  st(0) (FPU).
		void fninit();//Initialize Floating-Point Unit (FPU). Initialize FPU without checking for pending unmasked floating-point exceptions.		
		void fist( const CMem& dst );//Store st(0) as 16-bit or 32-bit Integer to dst (FPU).
		void fistp( const CMem& dst );		//Store st(0) as 16-bit, 32-bit or 64-bit Integer to dst and pop stack (FPU).
		void fld( const CMem& src );//Push 32-bit, 64-bit or 80-bit Floating Point Value onto the FPU register stack (FPU).
		void fld( const CX87Reg& reg );//Push reg onto the FPU register stack (FPU).		
		void fld1();//Push +1.0 onto the FPU register stack (FPU).		
		void fldl2t();//Push log2(10) onto the FPU register stack (FPU).		
		void fldl2e();//Push log2(e) onto the FPU register stack (FPU).		
		void fldpi();//Push pi onto the FPU register stack (FPU).		
		void fldlg2();//Push log10(2) onto the FPU register stack (FPU).		
		void fldln2();//Push ln(2) onto the FPU register stack (FPU).		
		void fldz();//Push +0.0 onto the FPU register stack (FPU).		
		void fldcw( const CMem& src );//Load x87 FPU Control Word (2 bytes) (FPU).
		void fldenv( const CMem& src );//Load x87 FPU Environment (14 or 28 bytes) (FPU).		
		void fmul( const CX87Reg& dst, const CX87Reg& src );//Multiply dst by src and store result in dst (FPU). Note One of dst or src must be st(0).
		void fmul( const CMem& src );//Multiply st(0) by src and store result in st(0) (FPU). Note SP-FP or DP-FP determined by adr size.		
		void fmulp( const CX87Reg& dst = st( 1 ) );//Multiply st(0) by dst and POP register stack (FPU).
		void fnclex();//Clear Exceptions (FPU).
		void fnop();//No Operation (FPU).		
		void fnsave( const CMem& dst );//Save FPU State (FPU).
		void fnstenv( const CMem& dst );//Store x87 FPU Environment (FPU).
		void fnstcw( const CMem& dst );//Store x87 FPU Control Word (FPU).		
		void fnstsw( const CGPReg& dst );//Store x87 FPU Status Word (2 Bytes) (FPU).	
		void fnstsw( const CMem& dst );//Store x87 FPU Status Word (2 Bytes) (FPU).
		void fpatan();//Partial Arctangent (FPU).
		void fprem();//Partial Remainder (FPU).
		void fprem1();//Partial Remainder (FPU).
		void fptan();//Partial Tangent (FPU).		
		void frndint();//Round to Integer (FPU).
		void frstor( const CMem& src );//Restore FPU State (FPU).
		void fsave( const CMem& dst );//Save FPU State (FPU).
		void fscale();//Scale (FPU).
		void fsin();//Sine (FPU).
		void fsincos();//Sine and Cosine (FPU).
		void fsqrt();//Square Root (FPU).
		void fst( const CMem& dst );//Store Floating Point Value (FPU).
		void fst( const CX87Reg& reg );//Store Floating Point Value (FPU).
		void fstp( const CMem& dst );//Store Floating Point Value and Pop Register Stack (FPU).
		void fstp( const CX87Reg& reg );//Store Floating Point Value and Pop Register Stack (FPU).
		void fstcw( const CMem& dst );//Store x87 FPU Control Word (FPU).
		void fstenv( const CMem& dst );		//Store x87 FPU Environment (FPU).
		void fstsw( const CGPReg& dst );//Store x87 FPU Status Word (2 Bytes) (FPU).
		void fstsw( const CMem& dst );//Store x87 FPU Status Word (2 Bytes) (FPU).
		void fsub( const CX87Reg& dst, const CX87Reg& src );//Subtract src from dst and store result in dst (FPU).
		void fsub( const CMem& src );//Subtract src from st(0) and store result in st(0) (FPU).
		void fsubp( const CX87Reg& dst = st( 1 ) );//Subtract st(0) from dst and POP register stack (FPU).
		void fsubr( const CX87Reg& dst, const CX87Reg& src );//Reverse Subtract src from dst and store result in dst (FPU).
		void fsubr( const CMem& src );//Reverse Subtract src from st( 0 ) and store result in st( 0 ) (FPU).
		void fsubrp( const CX87Reg& dst = st( 1 ) );//Reverse Subtract st(0) from dst and POP register stack (FPU).		
		void ftst();//Floating point test - Compare st(0) with 0.0. (FPU).
		void fucom( const CX87Reg& reg = st( 1 ) );//Unordered Compare st(0) with reg (FPU).		
		void fucomi( const CX87Reg& reg );//Unordered Compare st(0) and reg, check for ordered values and Set EFLAGS (FPU).		
		void fucomip( const CX87Reg& reg = st( 1 ) );//UnorderedCompare st(0) and reg, Check for ordered values and Set EFLAGS and pop the stack (FPU).
		void fucomp( const CX87Reg& reg = st( 1 ) );//Unordered Compare st(0) with reg and pop register stack (FPU).		
		void fucompp();//Unordered compare st(0) with st(1) and pop register stack twice (FPU).
		void fwait();
		void fxam();//Examine st(0) (FPU).
		void fxch( const CX87Reg& reg = st( 1 ) );//Exchange Register Contents (FPU).
		void fxrstor( const CMem& src );//Restore FP And MMX(tm) State And Streaming SIMD Extension State (FPU, MMX, SSE).
		void fxsave( const CMem& dst );//Store FP and MMX(tm) State and Streaming SIMD Extension State (FPU, MMX, SSE).
		void fxtract();//Extract Exponent and Significand (FPU).
		void fyl2x();//Compute y * log2(x).
		void fyl2xp1();//Compute y * log_2(x+1).
		virtual int feclearexcept( int /*excepts*/ );
		virtual int fegetexceptflag( fexcept_t* /*flagp*/, int /*excepts*/ );
		virtual int feraiseexcept( int /*excepts*/ );
		virtual int fesetexceptflag( const fexcept_t* /*flagp*/, int /*excepts*/ );
		virtual int fetestexcept( int /*excepts*/ );
		virtual int fegetround( void );
		virtual int fesetround( int /*round*/ );
		virtual int fegetenv( fenv_t* /*envp*/ );
		virtual int feholdexcept( fenv_t* /*envp*/ );
		virtual int fesetenv( const fenv_t* /*envp*/ );
		virtual int feupdateenv( const fenv_t* /*envp*/ );

		__QCS_DECLARE_NONCOPYABLE( C387FPU );

	};

}//nsx86
}//nsArch

#endif//ARCHQOR_X86PC_I387FPU_H_2
