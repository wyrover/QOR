//Session.cpp

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

#include "WinQAPI/AdvAPI32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	__QOR_IMPLEMENT_OCLASS_GUID( CAdvAPI32, 0x97b10525, 0xb2ff, 0x42eb, 0x8d, 0x7c, 0xb0, 0xc, 0x92, 0x40, 0x81, 0x29 );

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::AbortSystemShutdownA( LPSTR lpMachineName )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::AbortSystemShutdownA" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( AbortSystemShutdownA );
		bResult = Call< BOOL, LPSTR >( pFunc, lpMachineName );
#	else
		QOR_PP_UNREF( lpMachineName );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("AbortSystemShutdownA"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::AbortSystemShutdownW( LPWSTR lpMachineName )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::AbortSystemShutdownW" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( AbortSystemShutdownW );
		bResult = Call< BOOL, LPWSTR >( pFunc, lpMachineName );
#	else
		QOR_PP_UNREF( lpMachineName );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("AbortSystemShutdownW"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	DWORD CAdvAPI32::InitiateShutdownA( LPSTR lpMachineName, LPSTR lpMessage, DWORD dwGracePeriod, DWORD dwShutdownFlags, DWORD dwReason )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::InitiateShutdown" );
		CCheckReturn< DWORD, CTSuccessCheck< DWORD > >::TType dwResult;
	#	if ( _WIN32_WINNT >= 0x0600 )
			_WINQ_USESAPI( InitiateShutdownA );
			dwResult = Call< DWORD, LPSTR, LPSTR, DWORD, DWORD, DWORD >( pFunc, lpMachineName, lpMessage, dwGracePeriod, dwShutdownFlags, dwReason );
	#	else
			QOR_PP_UNREF5( lpMachineName, lpMessage, dwGracePeriod, dwShutdownFlags, dwReason );
			__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("InitiateShutdownA"), _T( "Windows Vista" ), 0 ));
	#	endif
		return dwResult;
	}

	//------------------------------------------------------------------------------
	DWORD CAdvAPI32::InitiateShutdownW( LPWSTR lpMachineName, LPWSTR lpMessage, DWORD dwGracePeriod, DWORD dwShutdownFlags, DWORD dwReason )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::InitiateShutdownW" );
		CCheckReturn< DWORD, CTSuccessCheck< DWORD > >::TType dwResult;
#	if ( _WIN32_WINNT >= 0x0600 )
		_WINQ_USESAPI( InitiateShutdownW );
		dwResult = Call< DWORD, LPWSTR, LPWSTR, DWORD, DWORD, DWORD >( pFunc, lpMachineName, lpMessage, dwGracePeriod, dwShutdownFlags, dwReason );
#	else
		QOR_PP_UNREF5( lpMachineName, lpMessage, dwGracePeriod, dwShutdownFlags, dwReason );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("InitiateShutdownW"), _T( "Windows Vista" ), 0 ));
#	endif
		return dwResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::InitiateSystemShutdownA( LPSTR lpMachineName, LPSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::InitiateSystemShutdownA" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( InitiateSystemShutdownA );
		bResult = Call< BOOL, LPSTR, LPSTR, DWORD, BOOL, BOOL >( pFunc, lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown );
#	else
		QOR_PP_UNREF5( lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("InitiateSystemShutdownA"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::InitiateSystemShutdownW( LPWSTR lpMachineName, LPWSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::InitiateSystemShutdownW" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( InitiateSystemShutdownW );
		bResult = Call< BOOL, LPWSTR, LPWSTR, DWORD, BOOL, BOOL >( pFunc, lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown );
#	else
		QOR_PP_UNREF5( lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("InitiateSystemShutdownW"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::InitiateSystemShutdownExA( LPSTR lpMachineName, LPSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown, DWORD dwReason )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::InitiateSystemShutdownExA" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( InitiateSystemShutdownExA );
		bResult = Call< BOOL, LPSTR, LPSTR, DWORD, BOOL, BOOL, DWORD >( pFunc, lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown, dwReason );
#	else
		QOR_PP_UNREF6( lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown, dwReason );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("InitiateSystemShutdownExA"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::InitiateSystemShutdownExW( LPWSTR lpMachineName, LPWSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown, DWORD dwReason )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::InitiateSystemShutdownExW" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( InitiateSystemShutdownExW );
		bResult = Call< BOOL, LPWSTR, LPWSTR, DWORD, BOOL, BOOL, DWORD >( pFunc, lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown, dwReason );
#	else
		QOR_PP_UNREF6( lpMachineName, lpMessage, dwTimeout, bForceAppsClosed, bRebootAfterShutdown, dwReason );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("InitiateSystemShutdownExW"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::GetUserNameA( LPSTR lpBuffer, LPDWORD lpnSize )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::GetUserNameA" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( GetUserNameA );
		bResult = Call< BOOL, LPSTR, LPDWORD >( pFunc, lpBuffer, lpnSize );
#	else
		QOR_PP_UNREF2( lpBuffer, lpnSize );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("GetUserNameA"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::GetUserNameW( LPWSTR lpBuffer, LPDWORD lpnSize )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::GetUserNameW" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0500 )
		_WINQ_USESAPI( GetUserNameW );
		bResult = Call< BOOL, LPWSTR, LPDWORD >( pFunc, lpBuffer, lpnSize );
#	else
		QOR_PP_UNREF2( lpBuffer, lpnSize );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("GetUserNameW"), _T( "Windows 2000 Professional" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::LogonUserA( LPSTR lpszUsername, LPSTR lpszDomain, LPSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PHANDLE phToken )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LogonUserA" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0501 )
		_WINQ_USESAPI( LogonUserA );
		bResult = Call< BOOL, LPSTR, LPSTR, LPSTR, DWORD, DWORD, PHANDLE >( pFunc, lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken );
#	else
		QOR_PP_UNREF6( lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LogonUserA"), _T( "Windows XP" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::LogonUserW( LPWSTR lpszUsername, LPWSTR lpszDomain, LPWSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PHANDLE phToken )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LogonUserW" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0501 )
		_WINQ_USESAPI( LogonUserW );
		bResult = Call< BOOL, LPWSTR, LPWSTR, LPWSTR, DWORD, DWORD, PHANDLE >( pFunc, lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken );
#	else
		QOR_PP_UNREF6( lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LogonUserW"), _T( "Windows XP" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::LogonUserExA( LPSTR lpszUsername, LPSTR lpszDomain, LPSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PHANDLE phToken, PSID* ppLogonSid, PVOID* ppProfileBuffer, LPDWORD pdwProfileLength, PQUOTA_LIMITS pQuotaLimits )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LogonUserExA" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0501 )
		_WINQ_USESAPI( LogonUserExA );
		bResult = Call< BOOL, LPSTR, LPSTR, LPSTR, DWORD, DWORD, PHANDLE, PSID*, PVOID*, LPDWORD, PQUOTA_LIMITS >( pFunc, lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits );
#	else
		QOR_PP_UNREF10( lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LogonUserExA"), _T( "Windows XP" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::LogonUserExW( LPWSTR lpszUsername, LPWSTR lpszDomain, LPWSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PHANDLE phToken, PSID* ppLogonSid, PVOID* ppProfileBuffer, LPDWORD pdwProfileLength, ::PQUOTA_LIMITS pQuotaLimits )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LogonUserExW" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( LogonUserExW );
#	if ( _WIN32_WINNT >= 0x0501 )
		bResult = Call< BOOL, LPWSTR, LPWSTR, LPWSTR, DWORD, DWORD, PHANDLE, PSID*, PVOID*, LPDWORD, ::PQUOTA_LIMITS >( pFunc, lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits );
#	else
		QOR_PP_UNREF10( lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LogonUserExW"), _T( "Windows XP" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	BOOL CAdvAPI32::LogonUserExExW( LPWSTR lpszUsername, LPWSTR lpszDomain, LPWSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PTOKEN_GROUPS pTokenGroups, PHANDLE phToken, PSID* ppLogonSid, PVOID* ppProfileBuffer, LPDWORD pdwProfileLength, ::PQUOTA_LIMITS pQuotaLimits )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::LogonUserExExW" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
#	if ( _WIN32_WINNT >= 0x0600 )
		_WINQ_USESAPI( LogonUserExExW );
		bResult = Call< BOOL, LPWSTR, LPWSTR, LPWSTR, DWORD, DWORD, PTOKEN_GROUPS, PHANDLE, PSID*, PVOID*, LPDWORD, ::PQUOTA_LIMITS >( pFunc, lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, pTokenGroups, phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits );
#	else
		QOR_PP_UNREF11( lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, pTokenGroups, phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("LogonUserExExW"), _T( "Windows Vista" ), 0 ));
#	endif
		return bResult;
	}

	//------------------------------------------------------------------------------
	DWORD CAdvAPI32::MSChapSrvChangePassword( PWSTR ServerName, PWSTR UserName, BOOLEAN LmOldPresent, ::PLM_OWF_PASSWORD LmOldOwfPassword, ::PLM_OWF_PASSWORD LmNewOwfPassword, ::PNT_OWF_PASSWORD NtOldOwfPassword, ::PNT_OWF_PASSWORD NtNewOwfPassword )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::MSChapSrvChangePassword" );
		CCheckReturn< DWORD, CTSuccessCheck< DWORD > >::TType dwResult;
#	if ( _WIN32_WINNT >= 0x0501 )
		_WINQ_USESAPI( MSChapSrvChangePassword );
		dwResult = Call< DWORD, PWSTR, PWSTR, BOOLEAN, ::PLM_OWF_PASSWORD, ::PLM_OWF_PASSWORD, ::PNT_OWF_PASSWORD, ::PNT_OWF_PASSWORD >( pFunc, ServerName, UserName, LmOldPresent, LmOldOwfPassword, LmNewOwfPassword, NtOldOwfPassword, NtNewOwfPassword );
#	else
		__QCMP_UNREF( ServerName );
		__QCMP_UNREF( UserName );
		__QCMP_UNREF( LmOldPresent );
		__QCMP_UNREF( LmOldOwfPassword );
		__QCMP_UNREF( LmNewOwfPassword );
		__QCMP_UNREF( NtOldOwfPassword );
		__QCMP_UNREF( NtNewOwfPassword );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("MSChapSrvChangePassword"), _T( "Windows XP" ), 0 ));
#	endif
		return dwResult;
	}

	//------------------------------------------------------------------------------
	DWORD CAdvAPI32::MSChapSrvChangePassword2( PWSTR ServerName, PWSTR UserName, ::PSAMPR_ENCRYPTED_USER_PASSWORD NewPasswordEncryptedWithOldNt, ::PENCRYPTED_NT_OWF_PASSWORD OldNtOwfPasswordEncryptedWithNewNt, BOOLEAN LmPresent, ::PSAMPR_ENCRYPTED_USER_PASSWORD NewPasswordEncryptedWithOldLm, ::PENCRYPTED_LM_OWF_PASSWORD OldLmOwfPasswordEncryptedWithNewLmOrNt )
	{
		_WINQ_FCONTEXT( "CAdvAPI32::MSChapSrvChangePassword2" );
		CCheckReturn< DWORD, CTSuccessCheck< DWORD > >::TType dwResult;
#	if ( _WIN32_WINNT >= 0x0501 )
		_WINQ_USESAPI( MSChapSrvChangePassword );
		dwResult = Call< DWORD, PWSTR, PWSTR, ::PSAMPR_ENCRYPTED_USER_PASSWORD, ::PENCRYPTED_NT_OWF_PASSWORD, BOOLEAN, ::PSAMPR_ENCRYPTED_USER_PASSWORD, ::PENCRYPTED_LM_OWF_PASSWORD >( pFunc, ServerName, UserName, NewPasswordEncryptedWithOldNt, OldNtOwfPasswordEncryptedWithNewNt, LmPresent, NewPasswordEncryptedWithOldLm, OldLmOwfPasswordEncryptedWithNewLmOrNt );
#	else
		__QCMP_UNREF( ServerName );
		__QCMP_UNREF( UserName );
		__QCMP_UNREF( NewPasswordEncryptedWithOldNt );
		__QCMP_UNREF( OldNtOwfPasswordEncryptedWithNewNt );
		__QCMP_UNREF( LmPresent );
		__QCMP_UNREF( NewPasswordEncryptedWithOldLm );
		__QCMP_UNREF( OldLmOwfPasswordEncryptedWithNewLmOrNt );
		__WINQAPI_CONT_ERROR(( API_REQUIRES_VERSION, _T("MSChapSrvChangePassword2"), _T( "Windows XP" ), 0 ));
#	endif
		return dwResult;
	}

}//nsWinQAPI

