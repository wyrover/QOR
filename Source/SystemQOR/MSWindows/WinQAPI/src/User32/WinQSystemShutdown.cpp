//WinQSystemShutdown.cpp

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

//System Shutdwown functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	BOOL CUser32::ExitWindowsEx( UINT uFlags, DWORD dwReason )
	{
		_WINQ_FCONTEXT( "CUser32::ExitWindowsEx" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( ExitWindowsEx );
		bResult = Call< BOOL, UINT, DWORD >( pFunc, uFlags, dwReason );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::LockWorkStation(void)
	{
		_WINQ_FCONTEXT( "CUser32::LockWorkStation" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( LockWorkStation );
		bResult = Call< BOOL >( pFunc );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::ShutdownBlockReasonCreate( HWND hWnd, LPCWSTR pwszReason )
	{
		_WINQ_FCONTEXT( "CUser32::ShutdownBlockReasonCreate" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( ShutdownBlockReasonCreate );
		bResult = Call< BOOL, HWND, LPCWSTR >( pFunc, hWnd, pwszReason );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL WINAPI CUser32::ShutdownBlockReasonDestroy( HWND hWnd )
	{
		_WINQ_FCONTEXT( "CUser32::ShutdownBlockReasonDestroy" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( ShutdownBlockReasonDestroy );
		bResult = Call< BOOL, HWND >( pFunc, hWnd );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	BOOL WINAPI CUser32::ShutdownBlockReasonQuery( HWND hWnd, LPWSTR pwszBuff, DWORD* pcchBuff )
	{
		_WINQ_FCONTEXT( "CUser32::ShutdownBlockReasonQuery" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( ShutdownBlockReasonQuery );
		bResult = Call< BOOL, HWND, LPWSTR, DWORD* >( pFunc, hWnd, pwszBuff, pcchBuff );
		return bResult;
	}

}//nsWinQAPI
