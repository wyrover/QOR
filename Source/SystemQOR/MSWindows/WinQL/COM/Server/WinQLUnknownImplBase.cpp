//WinQLUnknownImplBase.cpp

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
#include "WinQL/COM/UnknownImplBase.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CIUnknownDeferBase );

	//--------------------------------------------------------------------------------
	CIUnknownDeferBase::CIUnknownDeferBase( CIUnknownImplBase<>* pImpl ) : m_pImpl( pImpl )
	{
		_WINQ_FCONTEXT( "CIUnknownDeferBase::CIUnknownDeferBase" );
	}

	//--------------------------------------------------------------------------------
	CIUnknownDeferBase::~CIUnknownDeferBase()
	{
		_WINQ_FCONTEXT( "CIUnknownDeferBase::~CIUnknownDeferBase" );
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CIUnknownDeferBase::QueryInterface( const GUID& riid, void **ppvObject )
	{
		_WINQ_FCONTEXT( "CIUnknownDeferBase::QueryInterface" );
		return m_pImpl->QueryInterface( riid, ppvObject );
	}

	//--------------------------------------------------------------------------------
	unsigned long __QCMP_STDCALLCONVENTION CIUnknownDeferBase::AddRef( void )
	{
		_WINQ_FCONTEXT( "CIUnknownDeferBase::AddRef" );
		return m_pImpl->AddRef();
	}

	//--------------------------------------------------------------------------------
	unsigned long __QCMP_STDCALLCONVENTION CIUnknownDeferBase::Release( void )
	{
		_WINQ_FCONTEXT( "CIUnknownDeferBase::Release" );
		return m_pImpl->Release();
	}

	//--------------------------------------------------------------------------------
	//Returns interface pointer but does no AddRef. Only called from within the object
	long CIUnknownDeferBase::Internal_QueryInterface( const GUID& riid, void **ppvObject )
	{
		_WINQ_FCONTEXT( "CIUnknownDeferBase::Internal_QueryInterface" );
		return m_pImpl->Internal_QueryInterface( riid, ppvObject );
	}

}//nsWin32
