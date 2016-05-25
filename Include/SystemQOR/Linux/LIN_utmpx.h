//LIN_utmpx.h

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

//Linux overrides for utmpx

#ifndef SYSTEMQOR_LIN_UTMPX_H_3
#define SYSTEMQOR_LIN_UTMPX_H_3

#include "SystemQOR/Linux/types/utmp_types.h"
#include "SystemQOR/Linux/types/utmpx_types.h"
//#include "SystemQOR/Posix/Baseregex.h"

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cutmpx //: public nsBaseCRT::Cregex
	{
	public:

		Cutmpx(){}
		~Cutmpx(){}

		void  endutent( void );
		utmp* getutent( void );
		utmp* getutid( const utmp* );
		utmp* getutline( const utmp* );
		utmp* pututline( const utmp* );
		void  setutent( void );
		void updwtmp( const char*, const utmp* );
		int login_tty( int );

		virtual void   endutxent(void);
		virtual utmpx* getutxent(void);
		virtual utmpx* getutxid(const utmpx* );
		virtual utmpx* getutxline(const utmpx* );
		virtual utmpx* pututxline(const utmpx* );
		virtual void setutxent(void);

#if defined(_BSD_SOURCE) | defined(_GNU_SOURCE)
		void updwtmpx( const char*, const utmpx* );
#endif

	private:

		Cutmpx( const Cutmpx& );
		Cutmpx& operator = ( const Cutmpx& );

	};

}//nsLinux

#endif//SYSTEMQOR_LIN_UTMPX_H_3