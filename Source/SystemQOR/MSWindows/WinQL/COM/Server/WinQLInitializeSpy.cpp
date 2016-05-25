//WinQLInitializeSpy.cpp

// Copyright Querysoft Limited 2013, 2015
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

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/COM/InitializeSpy.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_COMCLASS_ID( CInitializeSpy, IInitializeSpy, 0x00000034, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 );

	const GUID IInitializeSpy::_IID = { 0x00000034, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

	//--------------------------------------------------------------------------------
	CInitializeSpy::CInitializeSpy()
	{
		_WINQ_FCONTEXT( "CInitializeSpy::CInitializeSpy" );
		RegisterInterface( dynamic_cast< IInitializeSpy* >( this ) );
	}

	//--------------------------------------------------------------------------------
	CInitializeSpy::~CInitializeSpy()
	{
		_WINQ_FCONTEXT( "CInitializeSpy::~CInitializeSpy" );
	}

	//--------------------------------------------------------------------------------
	long CInitializeSpy::PreInitialize( unsigned long dwCoInit, unsigned long dwCurThreadAptRefs )
	{
		_WINQ_FCONTEXT( "CInitializeSpy::PreInitialize" );
		QOR_PP_UNREF2( dwCoInit, dwCurThreadAptRefs );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long CInitializeSpy::PostInitialize( long hrCoInit, unsigned long dwCoInit, unsigned long dwNewThreadAptRefs)
	{
		_WINQ_FCONTEXT( "CInitializeSpy::PostInitialize" );
		QOR_PP_UNREF3( hrCoInit, dwCoInit, dwNewThreadAptRefs );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long CInitializeSpy::PreUninitialize( unsigned long dwCurThreadAptRefs)
	{
		_WINQ_FCONTEXT( "CInitializeSpy::PreUninitialize" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long CInitializeSpy::PostUninitialize( unsigned long dwNewThreadAptRefs)
	{
		_WINQ_FCONTEXT( "CInitializeSpy::PostUninitialize" );
		return S_OK;
	}

}//nsWin32