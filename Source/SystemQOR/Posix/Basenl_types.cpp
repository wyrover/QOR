//Basenl_types.cpp

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

#include "SystemQOR/Posix/Basenl_types.h"
#include <errno.h>
#include "CodeQOR/Tracing/FunctionContextBase.h"

//--------------------------------------------------------------------------------
namespace nsBaseCRT
{
	__QOR_IMPLEMENT_OCLASS_LUID( Cnl_types );

	//--------------------------------------------------------------------------------
	Cnl_types::Cnl_types()
	{
		__QCS_MEMBER_FCONTEXT( "Cnl_types::Cnl_types" );
	}

	//--------------------------------------------------------------------------------
	Cnl_types::~Cnl_types()
	{
		__QCS_MEMBER_FCONTEXT( "Cnl_types::~Cnl_types" );
	}

	//--------------------------------------------------------------------------------
	int Cnl_types::catclose( nl_catd )
	{
		__QCS_MEMBER_FCONTEXT( "Cnl_types::catclose" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	char* Cnl_types::catgets( nl_catd, int, int, const char* )
	{
		__QCS_MEMBER_FCONTEXT( "Cnl_types::catgets" );
		errno = ENOSYS;
		return 0;
	}

	//--------------------------------------------------------------------------------
	nl_catd Cnl_types::catopen( const char*, int )
	{
		__QCS_MEMBER_FCONTEXT( "Cnl_types::catopen" );
		errno = ENOSYS;
		return 0;
	}

}//nsBaseCRT
