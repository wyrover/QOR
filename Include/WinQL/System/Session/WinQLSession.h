//WinQLSession.h

// Copyright Querysoft Limited 2015
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

#ifndef WINQL_OSSERV_SESSION_H_3
#define WINQL_OSSERV_SESSION_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Traits/ReferenceTraits.h"
#include "WinQL/Definitions/Handles.h"
#include "WinQL/Definitions/Data.h"
#include "WinQL/Definitions/Security.h"
#include "WinQL/GUI/WindowStation.h"
#include "WinQL/GUI/Window.h"
#include "WinQL/System/User/WinQLUser.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CUser32;
	class __QOR_INTERFACE( __WINQAPI ) CAdvAPI32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	typedef bool ( __QCMP_STDCALLCONVENTION* WindowStationEnumCallback )( TCHAR*, Cmp_long_ptr );

	//--------------------------------------------------------------------------------
	struct QuotaLimits 
	{
		Cmp_ulong_ptr PagedPoolLimit;
		Cmp_ulong_ptr NonPagedPoolLimit;
		Cmp_ulong_ptr MinimumWorkingSetSize;
		Cmp_ulong_ptr MaximumWorkingSetSize;
		Cmp_ulong_ptr PagefileLimit;
		LARGE_INTEGER TimeLimit;
	};

	//--------------------------------------------------------------------------------
	struct CypherBlock 
	{
		char data[ 8 ];
	};
    
	//--------------------------------------------------------------------------------
	struct LMOWFPassword 
	{
		CypherBlock data[ 2 ];
	};

	typedef LMOWFPassword	NTOWFPassword;

	//--------------------------------------------------------------------------------
	struct SamprEncryptedUserPassword
	{
		unsigned char Buffer[ (  256 * 2 ) + 4 ];
	};

	//--------------------------------------------------------------------------------
	struct EncryptedLMOWFPassword 
	{
		CypherBlock data[ 2 ];
	};

	typedef EncryptedLMOWFPassword	EncryptedNTOWFPassword;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSessionHelper
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CSessionHelper );

		CSessionHelper();
		virtual ~CSessionHelper();
		bool ExitWindowsEx( unsigned int uFlags, unsigned long dwReason );
		bool LockWorkStation( void );
		bool ShutdownBlockReasonCreate( COSWindow::refType Wnd, const wchar_t* pwszReason );
		bool ShutdownBlockReasonDestroy( COSWindow::refType Wnd );
		CWString ShutdownBlockReasonQuery( COSWindow::refType Wnd );
		bool EnumWindowStationsT( WindowStationEnumCallback lpEnumFunc, Cmp_long_ptr lParam );
		bool AbortSystemShutdownT( const TCHAR* lpMachineName );
		bool InitiateShutdownT( const TCHAR* lpMachineName, const TCHAR* lpMessage, unsigned long dwGracePeriod, unsigned long dwShutdownFlags, unsigned long dwReason );
		bool LogonUserT( wchar_t* lpszUsername, wchar_t* lpszDomain, wchar_t* lpszPassword, unsigned long dwLogonType, unsigned long dwLogonProvider, nsWin32::TOKEN_GROUPS* pTokenGroups, void** phToken, void** ppLogonSid, void** ppProfileBuffer, unsigned long* pdwProfileLength, nsWin32::QuotaLimits* pQuotaLimits );
		unsigned long MSChapSrvChangePassword( wchar_t* ServerName, wchar_t* UserName, unsigned char LmOldPresent, LMOWFPassword* LmOldOwfPassword, LMOWFPassword* LmNewOwfPassword, NTOWFPassword* NtOldOwfPassword, NTOWFPassword* NtNewOwfPassword );
		unsigned long MSChapSrvChangePassword2( wchar_t* ServerName, wchar_t* UserName, SamprEncryptedUserPassword* NewPasswordEncryptedWithOldNt, 
			EncryptedNTOWFPassword* OldNtOwfPasswordEncryptedWithNewNt, unsigned char LmPresent, SamprEncryptedUserPassword* NewPasswordEncryptedWithOldLm, EncryptedLMOWFPassword* OldLmOwfPasswordEncryptedWithNewLmOrNt );
			
	private:

		nsWinQAPI::CUser32& m_User32Library;
		nsWinQAPI::CAdvAPI32& m_AdvAPI32Library;

		__QCS_DECLARE_NONCOPYABLE( CSessionHelper );
	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CSession : public CSessionHelper
	{
		QOR_PP_WINQL_SHARED

	public:

		//--------------------------------------------------------------------------------
		class __QOR_INTERFACE( __WINQL ) CShutdownBlock
		{
		public:

			__QOR_DECLARE_REF_TYPE( CShutdownBlock );			

			//--------------------------------------------------------------------------------
			CShutdownBlock( CSession& Session, COSWindow::refType Wnd, const wchar_t* pwszReason ) : m_Session( Session ), m_WndShutdownBlock( Wnd )
			{
				m_bStatus = m_Session.BlockShutdown( Wnd, pwszReason );
			}

			//--------------------------------------------------------------------------------
			~CShutdownBlock()
			{
				m_bStatus = m_Session.ReleaseShutdown( m_WndShutdownBlock );
			}

			//--------------------------------------------------------------------------------
			CWString QueryReason()
			{
				return m_Session.QueryShutdownBlockReason( m_WndShutdownBlock );
			}

			//--------------------------------------------------------------------------------
			bool Status( void )
			{
				return m_bStatus;
			}

			//--------------------------------------------------------------------------------
			ref_type Ref( void )
			{
				return ref_type( this );
			}

		private:

			CShutdownBlock();
			CShutdownBlock( const CShutdownBlock& );
			CShutdownBlock& operator = ( const CShutdownBlock& );
			CSession& m_Session;
			bool m_bStatus;
			COSWindow::refType m_WndShutdownBlock;
		};

		friend class CShutdownBlock;

		//--------------------------------------------------------------------------------
		CSession() //: m_bWinStationsEnumerated( false )
		{				
		}

		//--------------------------------------------------------------------------------
		virtual ~CSession()
		{				
		}

		//--------------------------------------------------------------------------------
		CShutdownBlock::ref_type ShutdownBlock( COSWindow::refType Wnd, const wchar_t* pwszReason )
		{
			return CShutdownBlock::ref_type( new CShutdownBlock( *this, Wnd, pwszReason ), true );
		}

		//CWindowStation::refType WindowStation( CTString, unsigned long dwFlags = 0, bool fInherit = false, unsigned long dwDesiredAccess = Generic_All, nsWin32::LPSECURITY_ATTRIBUTES lpsa = 0 );

		//--------------------------------------------------------------------------------
		CUser& User( void );

	protected:			

		//--------------------------------------------------------------------------------
		bool BlockShutdown( COSWindow::refType Wnd, const wchar_t* pwszReason )
		{
			bool bResult = false;
			bResult = ShutdownBlockReasonCreate( Wnd, pwszReason );
			return bResult;
		}

		//--------------------------------------------------------------------------------
		bool ReleaseShutdown( COSWindow::refType Wnd )
		{
			return ShutdownBlockReasonDestroy( Wnd );
		}

		//--------------------------------------------------------------------------------
		CWString QueryShutdownBlockReason( COSWindow::refType Wnd )
		{
			return ShutdownBlockReasonQuery( Wnd );
		}

		//typedef nsCodeQOR::CTMap< CTString, CWindowStation* > WinStationNameMap;
		//typedef WinStationNameMap::TItem WinStationNameMapItem;

		//WinStationNameMap m_WinStationNameMap;

		CUser m_User;

	private:

		/*
		static bool __QCMP_STDCALLCONVENTION EnumAllWinStationsProc( TCHAR* StrName, Cmp_long_ptr lParam);
		bool EnumWinStation( TCHAR* StrName );
		bool EnumAllWinStations();
		bool m_bWinStationsEnumerated;
		*/
		__QCS_DECLARE_NONCOPYABLE( CSession );
	};

}//nsWin32


#endif//WINQL_OSSERV_SESSION_H_3
