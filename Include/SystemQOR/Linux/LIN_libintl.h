//LIN_libintl.h

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

//Linux overrides for libintl

#ifndef SYSTEMQOR_LIN_LIBINTL_H_3
#define SYSTEMQOR_LIN_LIBINTL_H_3

#include "SystemQOR.h"
#include "SystemQOR/Linux/types/libintl_types.h"
//#include "SystemQOR/Posix/Baseregex.h"

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Clibintl //: public nsBaseCRT::Cregex
	{
	public:

		Clibintl(){}
		~Clibintl(){}

		virtual char* gettext(const char *);
		virtual char* dgettext(const char *, const char *);
		virtual char* dcgettext(const char *, const char *, int);
		virtual char* ngettext(const char *, const char *, unsigned long);
		virtual char* dngettext(const char *, const char *, const char *, unsigned long);
		virtual char* dcngettext(const char *, const char *, const char *, unsigned long, int);
		virtual char* textdomain(const char *);
		virtual char* bindtextdomain (const char *, const char *);
		virtual char* bind_textdomain_codeset(const char *, const char *);

	private:

		Clibintl( const Clibintl& );
		Clibintl& operator = ( const Clibintl& );

	};

}//nsLinux

#endif//SYSTEMQOR_LIN_LIBINTL_H_3
