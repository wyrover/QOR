//SnapinHelpImpl.h

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

//Base class for implementing ISnapinHelp for MMC snapin

#ifndef WINQL_COM_MMC_SNAPINHELPIMPL_H_3
#define WINQL_COM_MMC_SNAPINHELPIMPL_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/COM/MMC/MMCInterfaces.h"
#include "WinQL/COM/TInterfaceMember.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) CSnapinHelpImpl : public CInterfaceImplBase< ISnapinHelp >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( CSnapinHelpImpl );

		CSnapinHelpImpl( CIUnknownImplBase<>* pImpl );
		virtual ~CSnapinHelpImpl();

		virtual long __QCMP_STDCALLCONVENTION GetHelpTopic( wchar_t** lpCompiledHelpFile );

	private:

		CSnapinHelpImpl();
		CSnapinHelpImpl( const CSnapinHelpImpl& );
		CSnapinHelpImpl& operator = ( const CSnapinHelpImpl& );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL_COM ) CSnapinHelp2Impl : public CInterfaceImplBase< ISnapinHelp2, CSnapinHelpImpl >
	{
	public:

		__QOR_DECLARE_COMCLASS_ID( CSnapinHelp2Impl );

		CSnapinHelp2Impl( CIUnknownImplBase<>* pImpl );
		virtual ~CSnapinHelp2Impl();

		virtual long __QCMP_STDCALLCONVENTION GetLinkedTopics( wchar_t** lpCompiledHelpFiles );
		
	private:

		CSnapinHelp2Impl();
		CSnapinHelp2Impl( const CSnapinHelp2Impl& );
		CSnapinHelp2Impl& operator = ( const CSnapinHelp2Impl& );
	};

}//nsWin32

#endif//WINQL_COM_MMC_SNAPINHELPIMPL_H_3
