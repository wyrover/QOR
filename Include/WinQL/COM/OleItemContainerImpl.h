//OleItemContainerImpl.h

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

#ifndef WINQL_COM_OLEITEMCONTAINERIMPL_H_3
#define WINQL_COM_OLEITEMCONTAINERIMPL_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Security.h"
#include "WinQL/Definitions/Interfaces.h"
#include "WinQL/COM/TInterfaceMember.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) CParseDisplayNameImpl : public CInterfaceImplBase< IParseDisplayName >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( CParseDisplayNameImpl );

		CParseDisplayNameImpl( CIUnknownImplBase<>* pImpl );
		virtual ~CParseDisplayNameImpl();
		virtual long __QCMP_STDCALLCONVENTION ParseDisplayName( IBindCtx* pbc, wchar_t* pszDisplayName, unsigned long* pchEaten, IMoniker** ppmkOut );

	private:

		CParseDisplayNameImpl();
		CParseDisplayNameImpl( const CParseDisplayNameImpl& );
		CParseDisplayNameImpl& operator = ( const CParseDisplayNameImpl& );
	};

#		undef GetObject

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) COleContainerImpl : public CInterfaceImplBase< IOleContainer, CParseDisplayNameImpl >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( COleContainerImpl );

		COleContainerImpl( CIUnknownImplBase<>* pImpl );
		virtual ~COleContainerImpl();
		virtual long __QCMP_STDCALLCONVENTION EnumObjects( unsigned long grfFlags, IEnumUnknown** ppenum );
		virtual long __QCMP_STDCALLCONVENTION LockContainer( int fLock );

	private:

		COleContainerImpl();
		COleContainerImpl( const COleContainerImpl& );
		COleContainerImpl& operator = ( const COleContainerImpl& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) COleItemContainerImpl : public CInterfaceImplBase< IOleItemContainer, COleContainerImpl >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( COleItemContainerImpl );

		COleItemContainerImpl( CIUnknownImplBase<>* pImpl );
		virtual ~COleItemContainerImpl();

		virtual long __QCMP_STDCALLCONVENTION GetObject( wchar_t* pszItem, unsigned long dwSpeedNeeded, IBindCtx *pbc, const GUID& riid, void** ppvObject );
		virtual long __QCMP_STDCALLCONVENTION GetObjectStorage( wchar_t* pszItem, IBindCtx *pbc, const GUID& riid, void** ppvStorage );
		virtual long __QCMP_STDCALLCONVENTION IsRunning( wchar_t* pszItem );

	private:

		COleItemContainerImpl();
		COleItemContainerImpl( const COleItemContainerImpl& );
		COleItemContainerImpl& operator = ( const COleItemContainerImpl& );
	};

}//nsWin32

#endif//WINQL_COM_OLEITEMCONTAINERIMPL_H_3

