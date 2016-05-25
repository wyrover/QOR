//WinQLWindowStation.cpp

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

#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/GUI/WindowStation.h"
#include "WinQAPI/User32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace ::nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CWindowStation );
	__QOR_IMPLEMENT_OCLASS_LUID( CWindowStationManager );

	__QCMP_WARNING_PUSH
	__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use" );

	//--------------------------------------------------------------------------------
	CWindowStationManager::CWindowStationManager() : m_User32Library( CUser32::Instance() )
	{
		_WINQ_FCONTEXT( "CWindowStationManager::CWindowStationManager" );
	}
	
	//--------------------------------------------------------------------------------
	CWindowStationManager::~CWindowStationManager()
	{
		_WINQ_FCONTEXT( "CWindowStationManager::~CWindowStationManager" );
	}

	//--------------------------------------------------------------------------------
	CWindowStation::refType CWindowStationManager::Current()
	{
		_WINQ_FCONTEXT( "CWindowStationManager::Current" );
		CWindowStation::refType Ref( new CWindowStation(), true );
		return Ref;
	}

	//--------------------------------------------------------------------------------
	CWindowStation::refType CWindowStationManager::Open( CTString& strWindowStation, bool bInherit, unsigned long ulDesiredAccess )
	{
		_WINQ_FCONTEXT( "CWindowStationManager::Open" );
		CWindowStation::refType Ref( new CWindowStation( strWindowStation.GetBuffer(), bInherit ? 1 : 0, ulDesiredAccess ), true );
		strWindowStation.ReleaseBuffer();
		return Ref;
	}

	//--------------------------------------------------------------------------------
	CWindowStation::refType CWindowStationManager::Create( CTString& strWindowStation, unsigned long ulFlags, unsigned long ulDesiredAccess, SECURITY_ATTRIBUTES* pSA )
	{
		_WINQ_FCONTEXT( "CWindowStationManager::Create" );
		CWindowStation::refType Ref( new CWindowStation( strWindowStation.GetBuffer(), ulFlags, ulDesiredAccess, pSA ), true );
		return Ref;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStationManager::Enumerate( nsWin32::WinStaEnumProc lpEnumFunc, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CWindowStationManager::Enumerate" );
		bool bResult = false;				
		__QOR_PROTECT
		{
			bResult = m_User32Library.EnumWindowStations( lpEnumFunc, lParam ) ? true : false;
		}__QOR_ENDPROTECT;
		return bResult;
	}




	//--------------------------------------------------------------------------------
	CWindowStation::CWindowStation() : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CWindowStation::CWindowStation" );
		__QOR_PROTECT
		{
			m_iStatus = 0;
			m_Handle = m_User32Library.GetProcessWindowStation();
			m_bNeedsClose = false;
			m_bDesktopsEnumerated = false;
		}__QOR_ENDPROTECT;
	}

	//--------------------------------------------------------------------------------
	CWindowStation::CWindowStation( TCHAR* lpszWinSta, int fInherit, unsigned long dwDesiredAccess ) : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CWindowStation::CWindowStation" );
		__QOR_PROTECT
		{
			m_iStatus = 0;
			m_Handle = m_User32Library.OpenWindowStation( lpszWinSta, fInherit, dwDesiredAccess );
			m_bNeedsClose = true;
			m_bDesktopsEnumerated = false;
		}__QOR_ENDPROTECT;
	}

	//--------------------------------------------------------------------------------
	CWindowStation::CWindowStation( const TCHAR* lpwinsta, unsigned long dwFlags, unsigned long dwDesiredAccess, nsWin32::LPSECURITY_ATTRIBUTES lpsa ) : m_User32Library( CUser32::Instance() )
	,	m_Handle( this, 0 )
	{
		_WINQ_FCONTEXT( "CWindowStation::CWindowStation" );
		__QOR_PROTECT
		{
			m_iStatus = 0;
			m_Handle = m_User32Library.CreateWindowStation( lpwinsta, dwFlags, dwDesiredAccess, reinterpret_cast< ::LPSECURITY_ATTRIBUTES >( lpsa ) );
			m_bNeedsClose = true;
			m_bDesktopsEnumerated = false;
		}__QOR_ENDPROTECT;
	}

	__QCMP_WARNING_POP

	//--------------------------------------------------------------------------------
	CWindowStation::~CWindowStation()
	{
		_WINQ_FCONTEXT( "CWindowStation::~CWindowStation" );
		__QOR_PROTECT
		{
			if( m_bNeedsClose )
			{
				m_iStatus = m_User32Library.CloseWindowStation( reinterpret_cast< ::HWINSTA >( m_Handle.Use() ) );
			}
		}__QOR_ENDPROTECT;
	}

	//--------------------------------------------------------------------------------
	int CWindowStation::Status()
	{
		return m_iStatus;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::SetAsProcessWindowStation()
	{
		_WINQ_FCONTEXT( "CWindowStation::SetAsProcessWindowStation" );
		bool bResult = false;
		__QOR_PROTECT
		{
			CTObjectLock< CWindowStation > Lock( this );
			bResult = m_User32Library.SetProcessWindowStation( reinterpret_cast< ::HWINSTA >( m_Handle.Use() ) ) ? true : false;
		}__QOR_ENDPROTECT;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::EnumDesktopsT( nsWin32::DesktopEnumProc lpEnumFunc, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CWindowStation::EnumDesktops" );
		bool bResult = false;
		__QOR_PROTECT
		{
			CTObjectLock< CWindowStation > Lock( this );
			bResult = m_User32Library.EnumDesktops(reinterpret_cast< ::HWINSTA >( m_Handle.Use() ), lpEnumFunc, lParam ) ? true : false;
		}__QOR_ENDPROTECT;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CDesktop::refType CWindowStation::GetThreadDesktop( unsigned long dwThreadId )
	{
		_WINQ_FCONTEXT( "CWindowStation::GetThreadDesktop" );
		
		__QOR_PROTECT
		{			
			CTObjectLock< CWindowStation > Lock( this );
			CDesktopHandle Handle( 0, (void*)( m_User32Library.GetThreadDesktop( dwThreadId ) ) );
			CDesktopHandle::refType refHandle( &Handle, false );			
			return CDesktop::FromHandle( refHandle );
		}__QOR_ENDPROTECT;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::GetInformation( int nIndex, nsCodeQOR::CTLRef< byte >& RefData )
	{
		_WINQ_FCONTEXT( "CWindowStation::GetInformation" );
		bool bResult = false;
		byte* pvInfo;
		__QOR_PROTECT
		{			
			CTObjectLock< CWindowStation > Lock( this );
			unsigned long ulLen = 0;
			bResult = m_User32Library.GetUserObjectInformation( m_Handle.Use(), nIndex, 0, 0, &ulLen ) ? true : false;

			if( bResult == false )
			{
				pvInfo = new byte[ ulLen ];
				bResult = m_User32Library.GetUserObjectInformation( m_Handle.Use(), nIndex, pvInfo, ulLen, 0) ? true : false;
				nsCodeQOR::CTLRef< byte > tmpRef( pvInfo, true );
				RefData = tmpRef;
			}			
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::SetInformation( int nIndex, const void* pvInfo, unsigned long nLength )
	{
		_WINQ_FCONTEXT( "CWindowStation::SetInformation" );
		bool bResult = false;
		__QOR_PROTECT
		{
			CTObjectLock< CWindowStation > Lock( this );
			bResult = m_User32Library.SetUserObjectInformation( m_Handle.Use(), nIndex, const_cast< ::PVOID >( pvInfo ), nLength ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::EnumAllDesktops()
	{
		bool bResult = false;
		m_DesktopNameMap.Clear();
		bResult = EnumDesktopsT( &CWindowStation::EnumAllDesktopsProc, reinterpret_cast< Cmp_long_ptr >( this ) );
		m_bDesktopsEnumerated = true;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::EnumDesktop( TCHAR* StrName )
	{
		bool bResult = true;
		CTString Name( StrName );
		DesktopNameMapItem Item( Name, 0 );
		m_DesktopNameMap.Append( Item );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	int __QCMP_STDCALLCONVENTION CWindowStation::EnumAllDesktopsProc( TCHAR* StrName, Cmp_long_ptr lParam )
	{
		bool bResult = true;
		CWindowStation* pThis = reinterpret_cast< CWindowStation* >( lParam );
		if( pThis != 0 )
		{
			bResult = pThis->EnumDesktop( StrName );
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CTString CWindowStation::GetName( void )
	{		
		_WINQ_FCONTEXT( "CWindowStation::GetName" );
		CTString strName;
		__QOR_PROTECT
		{
			CTObjectLock< CWindowStation > Lock( this );
			nsCodeQOR::CTLRef< byte > RefData( 0, true );
			bool bResult = GetInformation( nsWin32::CUserObject::UOI_Name, RefData );
			if( bResult )
			{
				nsCodeQOR::CTLRef< CTString::char_type > RefString( reinterpret_cast< CTString::char_type* >( RefData.operator byte *() ), false );
				strName = RefString;
			}
		}__QOR_ENDPROTECT
		return strName;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::GetFlags( USEROBJECTFLAGS& Flags )
	{
		_WINQ_FCONTEXT( "CWindowStation::GetFlags" );
		bool bResult = false;
		__QOR_PROTECT
		{
			CTObjectLock< CWindowStation > Lock( this );
			nsCodeQOR::CTLRef< byte > RefData( 0, true );
			bResult = GetInformation( nsWin32::CUserObject::UOI_Flags, RefData );
			if( bResult )
			{
				Flags = *( reinterpret_cast< nsWin32::USEROBJECTFLAGS* >( RefData.operator byte *() ) );
			}
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CWindowStation::SetFlags( USEROBJECTFLAGS& Flags )
	{
		_WINQ_FCONTEXT( "CWindowStation::GetFlags" );
		bool bResult = false;
		__QOR_PROTECT
		{
			CTObjectLock< CWindowStation > Lock( this );
			void* pvInfo = reinterpret_cast< void* >( &Flags );
			bResult = SetInformation( CUserObject::UOI_Flags, pvInfo, sizeof( USEROBJECTFLAGS ) );
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CTString CWindowStation::GetType()
	{	
		_WINQ_FCONTEXT( "CWindowStation::GetType" );
		CTString strType;
		__QOR_PROTECT
		{
			nsCodeQOR::CTLRef< byte > RefData( 0, true );
			CTObjectLock< CWindowStation > Lock( this );
			bool bResult = GetInformation( nsWin32::CUserObject::UOI_Type, RefData );
			if( bResult )
			{
				nsCodeQOR::CTLRef< CTString::char_type > RefString( reinterpret_cast< CTString::char_type* >( RefData.operator byte *() ), false );
				strType = RefString;
			}
		}__QOR_ENDPROTECT
		return strType;
	}

	//--------------------------------------------------------------------------------
	CSID CWindowStation::GetSID()
	{
		_WINQ_FCONTEXT( "CWindowStation::GetSID" );
		void* pResult = 0;
			
		__QOR_PROTECT
		{
			nsCodeQOR::CTLRef< byte > RefData( 0, true );
			CTObjectLock< CWindowStation > Lock( this );
			bool bResult = GetInformation( nsWin32::CUserObject::UOI_User_SID, RefData );
			if( bResult )
			{
				pResult = reinterpret_cast< void* >( RefData.operator byte *() );
			}
		}__QOR_ENDPROTECT
		CSID Sid( pResult );
		return Sid;
	}

	//--------------------------------------------------------------------------------
	CDesktop::refType CWindowStation::Desktop( CTString StrDesktop, const TCHAR* lpszDevice, LPDEVMODE pDevmode, unsigned long dwFlags, bool fInherit, unsigned long dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa )
	{
		_WINQ_FCONTEXT( "CWindowStation::Desktop" );

		CDesktop::refType Result( 0 );

		__QOR_PROTECT
		{
			if( StrDesktop.IsEmpty() )
			{	
				Result.Attach( new CDesktop(), true );
				//return CDesktop::refType( new CDesktop(), true );		//Default to the current thread desktop
			}
			else
			{
				CTObjectLock< CWindowStation > Lock( this );
				if( !m_bDesktopsEnumerated )
				{
					EnumAllDesktops();
				}

				bool bOwningRef = false;
				CDesktop* pResult = 0;

				pResult = m_DesktopNameMap.Find( StrDesktop );
				if( pResult == 0 )
				{	
					pResult = new CDesktop( StrDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa );
					m_DesktopNameMap.Insert( StrDesktop, pResult );
					bOwningRef = true;
				}
				Result.Attach( pResult, bOwningRef );
			}
		}__QOR_ENDPROTECT
		return Result;
	}

	//--------------------------------------------------------------------------------
	CWindowStation::refType CWindowStation::Ref( void )
	{
		return refType( this, false );
	}

}//nsWin32