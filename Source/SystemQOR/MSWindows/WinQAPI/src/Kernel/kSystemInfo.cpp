//kSystemInfo.cpp

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

#include "WinQAPI/Kernel32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"
#include "CodeQOR/Parameters/PChecks/StringChecks.h"

//------------------------------------------------------------------------------
namespace nsWinQAPI
{

	//--------------------------------------------------------------------------------
	BOOL CKernel32::DnsHostnameToComputerName( 
		CCheckParam< ::LPCTSTR, nsParamChecking::CStringCheck >::TType Hostname,
		CCheckParam< ::LPTSTR, nsParamChecking::CStringCheck >::TType ComputerName, 
		CCheckParam< ::LPDWORD, CNullPointerCheck >::TType pnSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::DnsHostnameToComputerName" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		bResult = ::DnsHostnameToComputerName( Hostname, ComputerName, pnSize );
#	else
		QOR_PP_UNREF( pnSize );
		QOR_PP_UNREF( ComputerName );
		QOR_PP_UNREF( Hostname );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "DnsHostnameToComputerName" ), _T( "Windows 2000" ), 0 ));
#	endif
		return bResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::EnumSystemFirmwareTables( DWORD FirmwareTableProviderSignature, void* pFirmwareTableBuffer, DWORD BufferSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::EnumSystemFirmwareTables" );
		UINT uiResult = 0;
#	ifdef __MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "EnumSystemFirmwareTables" ), 0 ));
#	else
		uiResult = ::EnumSystemFirmwareTables( FirmwareTableProviderSignature, pFirmwareTableBuffer, BufferSize );

		if( uiResult == 0 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "EnumSystemFirmwareTables" ), 0 ));
		}
#	endif
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	DWORD CKernel32::ExpandEnvironmentStrings( LPCTSTR lpSrc, LPTSTR lpDst, DWORD nSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::ExpandEnvironmentStrings" );
		DWORD dwResult = 0;
		dwResult = ::ExpandEnvironmentStrings( lpSrc, lpDst, nSize );
		if( dwResult == 0 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "ExpandEnvironmentStrings" ), 0 ));
		}
		return dwResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CKernel32::GetComputerName( LPTSTR lpBuffer, LPDWORD lpnSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetComputerName" );
		BOOL bResult = FALSE;
		bResult = ::GetComputerName( lpBuffer, lpnSize );
		if( lpBuffer != 0 && bResult == 0 )//Pass a null buffer if you're just querying the size needed
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "GetComputerName" ), 0 ));
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CKernel32::GetComputerNameEx( ::COMPUTER_NAME_FORMAT NameType, LPTSTR lpBuffer, LPDWORD lpnSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetComputerNameEx" );
		bool bResult = false;
#	if ( _WIN32_WINNT >= 0x0500 )
		bResult = ::GetComputerNameEx( NameType, lpBuffer, lpnSize ) ? true : false;
#	else
		QOR_PP_UNREF( lpnSize );
		QOR_PP_UNREF( lpBuffer );
		QOR_PP_UNREF( NameType );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "GetComputerNameEx" ), _T( "Windows 2000" ), 0 ));
#	endif
		return bResult;
	}

	//--------------------------------------------------------------------------------
	DWORD CKernel32::GetFirmwareEnvironmentVariable( LPCTSTR lpName, LPCTSTR lpGuid, void* pBuffer, DWORD nSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetFirmwareEnvironmentVariable" );
		DWORD dwResult = 0;
#	ifdef __MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "GetFirmwareEnvironmentVariable" ), 0 ));
#	else
		dwResult = ::GetFirmwareEnvironmentVariable( lpName, lpGuid, pBuffer, nSize );
		if( dwResult == 0 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "GetFirmwareEnvironmentVariable" ), 0 ));
		}
#	endif
		return dwResult;
	}

	//--------------------------------------------------------------------------------
	void CKernel32::GetNativeSystemInfo( ::LPSYSTEM_INFO lpSystemInfo )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetNativeSystemInfo" );
#	if ( _WIN32_WINNT >= 0x0501 )
		::GetNativeSystemInfo( lpSystemInfo );
#	else
		QOR_PP_UNREF( lpSystemInfo );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "GetNativeSystemInfo" ), _T( "Windows XP" ), 0 ));
#	endif
	}

	//--------------------------------------------------------------------------------
	BOOL CKernel32::GetProductInfo( DWORD dwOSMajorVersion, DWORD dwOSMinorVersion, DWORD dwSpMajorVersion, DWORD dwSpMinorVersion, PDWORD pdwReturnedProductType )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetProductInfo" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "GetProductInfo" ), 0 ));
#else
#	if ( _WIN32_WINNT >= 0x0600 )
		bResult = ::GetProductInfo( dwOSMajorVersion, dwOSMinorVersion, dwSpMajorVersion, dwSpMinorVersion, pdwReturnedProductType );
#	else
		QOR_PP_UNREF( pdwReturnedProductType );
		QOR_PP_UNREF( dwSpMinorVersion );
		QOR_PP_UNREF( dwSpMajorVersion );
		QOR_PP_UNREF( dwOSMinorVersion );
		QOR_PP_UNREF( dwOSMajorVersion );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "GetProductInfo" ), _T( "Windows Vista" ), 0 ));
#	endif
#endif
		return bResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::GetSystemDirectory( LPTSTR lpBuffer, UINT uSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetSystemDirectory" );
		UINT uiResult = 0;
		uiResult = ::GetSystemDirectory( lpBuffer, uSize );
		if( uiResult == 0 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "GetSystemDirectory" ), 0 ));
		}
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::GetSystemFirmwareTable( DWORD FirmwareTableProviderSignature, DWORD FirmwareTableID, void* pFirmwareTableBuffer, DWORD BufferSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetSystemFirmwareTable" );
		UINT uiResult = 0;
#ifdef	__MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "GetSystemFirmwareTable" ), 0 ));
#else
		uiResult = ::GetSystemFirmwareTable( FirmwareTableProviderSignature, FirmwareTableID, pFirmwareTableBuffer, BufferSize ); 
		if( uiResult == 0 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "GetSystemFirmwareTable" ), 0 ));
		}
#endif
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	void CKernel32::GetSystemInfo( ::LPSYSTEM_INFO lpSystemInfo )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetSystemInfo" );
		::GetSystemInfo( lpSystemInfo );
	}

	//------------------------------------------------------------------------------
	BOOL CKernel32::GetSystemRegistryQuota( PDWORD pdwQuotaAllowed, PDWORD pdwQuotaUsed )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetSystemRegistryQuota" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0501 )
		bResult = ::GetSystemRegistryQuota( pdwQuotaAllowed, pdwQuotaUsed );
#	else
		QOR_PP_UNREF( pdwQuotaUsed );
		QOR_PP_UNREF( pdwQuotaAllowed );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "GetSystemRegistryQuota" ), _T( "Windows XP Service Pack 1" ), 0 ));
#	endif
		return bResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::GetSystemWindowsDirectory( LPTSTR lpBuffer, UINT uSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetSystemWindowsDirectory" );
		UINT uiResult = 0;
		uiResult = ::GetSystemWindowsDirectory( lpBuffer, uSize );
		if( uiResult == 0 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "GetSystemWindowsDirectory" ), 0 ));
		}
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::GetSystemWow64Directory( LPTSTR lpBuffer, UINT uSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetSystemWow64Directory" );
		UINT uiResult = 0;
#	if( _WIN32_WINNT >= 0x0501 )
		uiResult = ::GetSystemWow64Directory( lpBuffer, uSize );
		if( uiResult == 0 )
		{
			__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "GetSystemWow64Directory" ), 0 ));
		}
#	else
		QOR_PP_UNREF( uSize );
		QOR_PP_UNREF( lpBuffer );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "GetSystemWow64Directory" ), _T( "Windows XP" ), 0 ));
#	endif
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	DWORD CKernel32::GetVersion(void)
	{
		_WINQ_SFCONTEXT( "CKernel32::GetVersion" );
		return ::GetVersion();
	}

	//--------------------------------------------------------------------------------
	BOOL CKernel32::GetVersionEx( ::LPOSVERSIONINFO lpVersionInfo )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetVersionEx" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
		bResult = ::GetVersionEx( lpVersionInfo );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::GetWindowsDirectoryA( CCheckParam< UINT, CNoCheck >::TType uSize, ::LPSTR pBuffer )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetWindowsDirectoryA" );
		CCheckReturn< UINT, CCheckNonZero< UINT > >::TType uiResult;
		uiResult = ::GetWindowsDirectoryA( pBuffer, uSize );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CKernel32::GetWindowsDirectoryW( CCheckParam< UINT, CNoCheck >::TType uSize, ::LPWSTR pBuffer )
	{
		_WINQ_SFCONTEXT( "CKernel32::GetWindowsDirectoryW" );
		CCheckReturn< UINT, CCheckNonZero< UINT > >::TType uiResult;
		uiResult = ::GetWindowsDirectoryW( pBuffer, uSize );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CKernel32::IsProcessorFeaturePresent( DWORD ProcessorFeature )
	{
		_WINQ_SFCONTEXT( "CKernel32::IsProcessorFeaturePresent" );
		return ::IsProcessorFeaturePresent( ProcessorFeature );
	}

	//--------------------------------------------------------------------------------
	//TODO: Could specialize buffer check for disallowed characters
	BOOL CKernel32::SetComputerName( CCheckParam< ::LPCTSTR, CNullPointerCheck >::TType pComputerName )
	{
		_WINQ_SFCONTEXT( "CKernel32::SetComputerName" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
		bResult = ::SetComputerName( pComputerName );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	//TODO: Could specialize buffer check for disallowed characters
	BOOL CKernel32::SetComputerNameEx( ::COMPUTER_NAME_FORMAT NameType, CCheckParam< ::LPCTSTR, CNullPointerCheck >::TType lpBuffer )
	{
		_WINQ_SFCONTEXT( "CKernel32::SetComputerNameEx" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		bResult = ::SetComputerNameEx( NameType, lpBuffer );
#	else
		QOR_PP_UNREF( lpBuffer );
		QOR_PP_UNREF( NameType );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "SetComputerNameEx" ), _T( "Windows 2000" ), 0 ));
#	endif
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CKernel32::SetFirmwareEnvironmentVariable( CCheckParam< ::LPCTSTR, CNullPointerCheck >::TType pName, LPCTSTR lpGuid, void* pBuffer, DWORD nSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::SetFirmwareEnvironmentVariable" );
		CCheckReturn< BOOL, CBoolCheck<> >::TType bResult;
#	ifdef __MINGW32__
		__WINQAPI_CONT_ERROR(( API_NOT_IN_MINGW32, _T( "SetFirmwareEnvironmentVariable" ), 0 ));
#	else
		bResult = ::SetFirmwareEnvironmentVariable( pName, lpGuid, pBuffer, nSize );
#	endif
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CKernel32::VerifyVersionInfo( CCheckParam< ::LPOSVERSIONINFOEX, CTRWPointerCheck< sizeof( ::OSVERSIONINFOEX ) > >::TType lpVersionInfo, DWORD dwTypeMask, DWORDLONG dwlConditionMask )
	{
		_WINQ_SFCONTEXT( "CKernel32::VerifyVersionInfo" );
		BOOL bResult = FALSE;
		bResult = ::VerifyVersionInfo( lpVersionInfo, dwTypeMask, dwlConditionMask );
		if( bResult == FALSE )
		{
			DWORD dwError = CKernel32::GetLastError();
			if( dwError != ERROR_OLD_WIN_VERSION )
			{
				__WINQAPI_CONT_ERROR(( GENERAL_API_ERROR, _T( "VerifyVersionInfo" ), 0 ));
			}
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	ULONGLONG CKernel32::VerSetConditionMask( ULONGLONG dwlConditionMask, DWORD dwTypeBitMask, BYTE dwConditionMask )
	{
		_WINQ_SFCONTEXT( "CKernel32::VerSetConditionMask" );
		ULONGLONG ullResult = 0;
#	if( _WIN32_WINNT >= 0x0500 )
		ullResult = ::VerSetConditionMask( dwlConditionMask, dwTypeBitMask, dwConditionMask );
#	else
		QOR_PP_UNREF( dwConditionMask );
		QOR_PP_UNREF( dwTypeBitMask );
		QOR_PP_UNREF( dwlConditionMask );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "VerSetConditionMask" ), _T( "Windows 2000" ), 0 ));
#	endif
		return ullResult;
	}

	//--------------------------------------------------------------------------------
	DWORD CKernel32::EnumerateLocalComputerNames( int NameType, unsigned long ulFlags, void* lpBuffer, unsigned int nSize )
	{
		_WINQ_SFCONTEXT( "CKernel32::EnumerateLocalComputerNames" );
		DWORD dwResult = 0;
#	if ( WINVER >= 0x0600 && NTDDI_VERSION >= NTDDI_VISTASP2 )
		dwResult = 0;//::EnumerateLocalComputerNames( NameType, ulFlags, lpBuffer, nSize );//Seems to require something else, maybe 64bit Compiler, maybe 7.1 SDK
#	else
		QOR_PP_UNREF( nSize );
		QOR_PP_UNREF( lpBuffer );
		QOR_PP_UNREF( ulFlags );
		QOR_PP_UNREF( NameType );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T( "EnumerateLocalComputerNames" ), _T( "Windows Vista Service Pack 2" ), 0 ));
#	endif
		return dwResult;
	}

}//nsWinQAPI

