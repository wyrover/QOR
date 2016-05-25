//WinQRawInput.cpp

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

//Raw Input functions

#include "WinQAPI/User32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/ReturnCheck.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	LRESULT CUser32::DefRawInputProc( PRAWINPUT* paRawInput, INT nInput, UINT cbSizeHeader )
	{
		_WINQ_FCONTEXT( "CUser32::DefRawInputProc" );
		CCheckReturn< LRESULT, CSuccessCheck<> >::TType Result;
		_WINQ_USESAPI( DefRawInputProc );
		Result = Call< LRESULT, PRAWINPUT*, INT, UINT >( pFunc, paRawInput, nInput, cbSizeHeader );
		return Result;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::GetRawInputBuffer( PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader )
	{
		_WINQ_FCONTEXT( "CUser32::GetRawInputBuffer" );
		CCheckReturn< UINT, CTCheckFailureValue< UINT, (UINT)-1 > >::TType uiResult;
		_WINQ_USESAPI( GetRawInputBuffer );
		uiResult = Call< UINT, PRAWINPUT, PUINT, UINT >( pFunc, pData, pcbSize, cbSizeHeader );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::GetRawInputData( HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader )
	{
		_WINQ_FCONTEXT( "CUser32::GetRawInputData" );
		CCheckReturn< UINT, CTCheckFailureValue< UINT, (UINT)-1 > >::TType uiResult;
		_WINQ_USESAPI( GetRawInputData );
		uiResult = Call< UINT, HRAWINPUT, UINT, LPVOID, PUINT, UINT >( pFunc, hRawInput, uiCommand, pData, pcbSize, cbSizeHeader );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::GetRawInputDeviceInfo( HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize )
	{
		_WINQ_FCONTEXT( "CUser32::GetRawInputDeviceInfo" );
		CCheckReturn< UINT, CTCheckNotLess< UINT, 1 > >::TType uiResult;
		_WINQ_USESAPI( GetRawInputDeviceInfo );
		uiResult = Call< UINT, HANDLE, UINT, LPVOID, PUINT >( pFunc, hDevice, uiCommand, pData, pcbSize );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::GetRawInputDeviceList( PRAWINPUTDEVICELIST pRawInputDeviceList, PUINT puiNumDevices, UINT cbSize )
	{
		_WINQ_FCONTEXT( "CUser32::GetRawInputDeviceList" );
		CCheckReturn< UINT, CTCheckFailureValue< UINT, (UINT)-1 > >::TType uiResult;
		_WINQ_USESAPI( GetRawInputDeviceList );
		uiResult = Call< UINT, PRAWINPUTDEVICELIST, PUINT, UINT >( pFunc, pRawInputDeviceList, puiNumDevices, cbSize );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	UINT CUser32::GetRegisteredRawInputDevices( PRAWINPUTDEVICE pRawInputDevices, PUINT puiNumDevices, UINT cbSize )
	{
		_WINQ_FCONTEXT( "CUser32::GetRegisteredRawInputDevices" );
		CCheckReturn< UINT, CTCheckFailureValue< UINT, (UINT)-1 > >::TType uiResult;
		_WINQ_USESAPI( GetRegisteredRawInputDevices );
		uiResult = Call< UINT, PRAWINPUTDEVICE, PUINT, UINT >( pFunc, pRawInputDevices, puiNumDevices, cbSize );
		return uiResult;
	}

	//--------------------------------------------------------------------------------
	BOOL CUser32::RegisterRawInputDevices( PCRAWINPUTDEVICE pRawInputDevices, UINT uiNumDevices, UINT cbSize )
	{
		_WINQ_FCONTEXT( "CUser32::RegisterRawInputDevices" );
		CCheckReturn< BOOL, CBoolCheck< > >::TType bResult;
		_WINQ_USESAPI( RegisterRawInputDevices );
		bResult = Call< BOOL, PCRAWINPUTDEVICE, UINT, UINT >( pFunc, pRawInputDevices, uiNumDevices, cbSize );
		return bResult;
	}

}//nsWinQAPI
