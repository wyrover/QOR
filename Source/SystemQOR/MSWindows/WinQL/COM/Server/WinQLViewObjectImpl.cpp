//WinQLViewObjectImpl.cpp

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
#include "WinQL/COM/ViewObject2Impl.h"
#include "WinQAPI/OLE32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	__QOR_IMPLEMENT_COMCLASS_ID( CViewObjectImpl, IViewObject, 0x0000010d,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 );
	__QOR_IMPLEMENT_COMCLASS_ID( CViewObject2Impl, IViewObject2, 0x00000127,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 );

	//--------------------------------------------------------------------------------
	CViewObjectImpl::CViewObjectImpl( CIUnknownImplBase<>* pImpl ) : CInterfaceImplBase( pImpl )
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::CViewObjectImpl" );
	}

	//--------------------------------------------------------------------------------
	CViewObjectImpl::~CViewObjectImpl()
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::~CViewObjectImpl" );
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CViewObjectImpl::Draw( unsigned long dwDrawAspect, long lindex, void* pvAspect, DVTargetDevice* ptd, void* phdcTargetDev, void* phdcDraw, const RECT* lprcBounds, const RECT* lprcWBounds, int ( __QCMP_STDCALLCONVENTION *pfnContinue )( Cmp_ulong_ptr dwContinue ), Cmp_ulong_ptr dwContinue )
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::Draw" );
		return E_NotImpl;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CViewObjectImpl::GetColorSet( unsigned long dwDrawAspect, long lindex, void* pvAspect, DVTargetDevice* ptd, void* phicTargetDev, LOGPALETTE** ppColorSet )
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::GetColorSet" );
		return E_NotImpl;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CViewObjectImpl::Freeze( unsigned long dwDrawAspect, long lindex, void* pvAspect, unsigned long* pdwFreeze )
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::Freeze" );
		return E_NotImpl;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CViewObjectImpl::Unfreeze( unsigned long dwFreeze )
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::Unfreeze" );
		return E_NotImpl;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CViewObjectImpl::SetAdvise( unsigned long aspects, unsigned long advf, IAdviseSink* pAdvSink )
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::SetAdvise" );
		return E_NotImpl;
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CViewObjectImpl::GetAdvise( unsigned long* pAspects, unsigned long* pAdvf, IAdviseSink** ppAdvSink )
	{
		_WINQ_FCONTEXT( "CViewObjectImpl::GetAdvise" );
		return E_NotImpl;
	}


	//--------------------------------------------------------------------------------
	CViewObject2Impl::CViewObject2Impl( CIUnknownImplBase<>* pImpl ) : CInterfaceImplBase( pImpl )
	{
		_WINQ_FCONTEXT( "CViewObject2Impl::CViewObject2Impl" );
	}

	//--------------------------------------------------------------------------------
	CViewObject2Impl::~CViewObject2Impl()
	{
		_WINQ_FCONTEXT( "CViewObject2Impl::~CViewObject2Impl" );
	}

	//--------------------------------------------------------------------------------
	long __QCMP_STDCALLCONVENTION CViewObject2Impl::GetExtent( unsigned long dwDrawAspect, long lindex, DVTargetDevice* ptd, SIZE* lpsizel )
	{
		_WINQ_FCONTEXT( "CViewObject2Impl::GetExtent" );
		return E_NotImpl;
	}

}//nsWin32

