//WinQLOleCache2Impl.cpp

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
#include "WinQL/COM/OleCache2Impl.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_COMCLASS_ID( COleCacheImpl, IOleCache, 0x0000011e,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 );

	//--------------------------------------------------------------------------------
	COleCacheImpl::COleCacheImpl( CIUnknownImplBase<>* pImpl ) : CInterfaceImplBase( pImpl )
	{
		_WINQ_FCONTEXT( "COleCacheImpl::COleCacheImpl" );
	}

	//--------------------------------------------------------------------------------
	COleCacheImpl::~COleCacheImpl()
	{
		_WINQ_FCONTEXT( "COleCacheImpl::~COleCacheImpl" );
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCacheImpl::Cache( FormatEtc* pformatetc, unsigned long advf, unsigned long* pdwConnection )
	{
		_WINQ_FCONTEXT( "COleCacheImpl::Cache" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCacheImpl::Uncache( unsigned long dwConnection )
	{
		_WINQ_FCONTEXT( "COleCacheImpl::Uncache" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCacheImpl::EnumCache( IEnumSTATDATA** ppenumSTATDATA )
	{
		_WINQ_FCONTEXT( "COleCacheImpl::EnumCache" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCacheImpl::InitCache( IDataObject* pDataObject )
	{
		_WINQ_FCONTEXT( "COleCacheImpl::InitCache" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCacheImpl::SetData( FormatEtc* pformatetc, StgMedium* pmedium, int fRelease )
	{
		_WINQ_FCONTEXT( "COleCacheImpl::SetData" );
		return S_OK;
	}

	__QOR_IMPLEMENT_COMCLASS_ID( COleCache2Impl, IOleCache2, 0x00000128,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 );

	//--------------------------------------------------------------------------------
	COleCache2Impl::COleCache2Impl( CIUnknownImplBase<>* pImpl ) : CInterfaceImplBase( pImpl )
	{
		_WINQ_FCONTEXT( "COleCache2Impl::COleCache2Impl" );
	}

	//--------------------------------------------------------------------------------
	COleCache2Impl::~COleCache2Impl()
	{
		_WINQ_FCONTEXT( "COleCache2Impl::~COleCache2Impl" );
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCache2Impl::SaveObject( void )
	{
		_WINQ_FCONTEXT( "COleCache2Impl::SaveObject" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCache2Impl::GetMoniker( unsigned long dwAssign, unsigned long dwWhichMoniker, IMoniker** ppmk )
	{
		_WINQ_FCONTEXT( "COleCache2Impl::GetMoniker" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCache2Impl::GetContainer( IOleContainer** ppContainer )
	{
		_WINQ_FCONTEXT( "COleCache2Impl::GetContainer" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCache2Impl::ShowObject( void )
	{
		_WINQ_FCONTEXT( "COleCache2Impl::ShowObject" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCache2Impl::OnShowWindow( int fShow )
	{
		_WINQ_FCONTEXT( "COleCache2Impl::OnShowWindow" );
		return S_OK;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION COleCache2Impl::RequestNewObjectLayout( void )
	{
		_WINQ_FCONTEXT( "COleCache2Impl::RequestNewObjectLayout" );
		return S_OK;
	}

}//nsWin32
