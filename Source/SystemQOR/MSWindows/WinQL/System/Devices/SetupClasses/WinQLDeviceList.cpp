//WinQLDeviceList.cpp

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

#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceInstance.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceList.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/GUI/Window.h"
#include "WinQL/System/WinQLSystem.h"
#include "WinQL/Application/Resources/WinQLResourceManager.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/SetupAPI.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceList )

	//--------------------------------------------------------------------------------
	CDeviceList::CDeviceList( nsCodeQOR::mxGUID* pGuid, COSWindow* pWindow, const mxTCHAR* szMachineName ) : m_InfoSet( new CDeviceInfoSet( pGuid, pWindow, szMachineName ) )
	, m_Library( CSetupAPI::Instance() )
	{
		_WINQ_FCONTEXT( "CDeviceList::CDeviceList" );

		unsigned int uiIndex = 0;
		do
		{	
		}while( !EnumDevice( uiIndex, pGuid ) );		
	}

	//--------------------------------------------------------------------------------
	bool CDeviceList::EnumDevice( unsigned int& uiIndex, nsCodeQOR::mxGUID* pGuid )
	{
		_WINQ_FCONTEXT( "CDeviceList::EnumDevice" );
		bool bEnumerated = false;
		unsigned long ulError = 0;
		unsigned long ulResult = (unsigned long)(-1);
		SP_DevInfo_Data DevInfo;
		DevInfo.cbSize = sizeof( ::SP_DEVINFO_DATA );
		DevInfo.ClassGuid = *pGuid;
		DevInfo.DevInst = 0;
		DevInfo.Reserved = 0;
		if( m_Library.SetupDiEnumDeviceInfo( reinterpret_cast< ::HDEVINFO >( m_InfoSet->Handle().Use() ), uiIndex, reinterpret_cast< ::PSP_DEVINFO_DATA >( &DevInfo ) ) )
		{
			ulResult = DevInfo.DevInst;
			if( ulResult > 0 && ulResult != (unsigned long)(-1) )
			{
				if( AddDevice( DevInfo, uiIndex ) )
				{
					uiIndex++;
				}
				else
				{
					ulError = ::GetLastError();
					bEnumerated = true;
				}
			}
			else
			{
				ulError = ::GetLastError();
				bEnumerated = true;
			}
		}
		else
		{
			ulError = ::GetLastError();
			bEnumerated = true;
		}
		return bEnumerated;
	}

	//--------------------------------------------------------------------------------
	bool CDeviceList::AddDevice( SP_DevInfo_Data& DevInfo, unsigned int uiIndex )
	{
		_WINQ_FCONTEXT( "CDeviceList::AddDevice" );
		CTString strDeviceID;
		if( m_Library.CM_Get_Device_ID_Ex( static_cast< ::DEVINST >( DevInfo.DevInst ), strDeviceID.GetBufferSetLength( MaxDeviceIDLen + 1), MaxDeviceIDLen, 0, 0 ) != CR_SUCCESS )
		{
			return false;
		}
		else
		{
			strDeviceID.ValidateBuffer();
			//Get the device instance ID and device data and add it to the model
			CTString strDeviceInstance;
			unsigned long ulInstanceSize = 0;
			m_Library.SetupDiGetDeviceInstanceId( reinterpret_cast< ::HDEVINFO >( m_InfoSet->Handle().Use() ), reinterpret_cast< ::PSP_DEVINFO_DATA >( &DevInfo ), 0, 0, &ulInstanceSize );
			if( ulInstanceSize > 0 )
			{							
				m_Library.SetupDiGetDeviceInstanceId( m_InfoSet->Handle().Use() , reinterpret_cast< ::PSP_DEVINFO_DATA >( &DevInfo ), 
					strDeviceInstance.GetBufferSetLength( static_cast< unsigned short >( ulInstanceSize + 1 ) ), ulInstanceSize, &ulInstanceSize );
				strDeviceInstance.ValidateBuffer( static_cast< unsigned short >( ulInstanceSize ) );
			}
			else
			{
				return false;
			}

			CDeviceInstance* pInstance = new CDeviceInstance( strDeviceID, m_InfoSet, DevInfo, uiIndex );	
		
		}
						
		return true;
	}

	//--------------------------------------------------------------------------------
	CDeviceList::CDeviceList( const CDeviceList& src ) : m_InfoSet( 0 )
	, m_Library( CSetupAPI::Instance() )
	{
		_WINQ_FCONTEXT( "CDeviceList::CDeviceList" );
	}

	//--------------------------------------------------------------------------------
	CDeviceList::~CDeviceList()
	{
		_WINQ_FCONTEXT( "CDeviceList::~CDeviceList" );
	}

	//--------------------------------------------------------------------------------
	unsigned long CDeviceList::Size()
	{
		_WINQ_FCONTEXT( "CDeviceList::Size" );
		return 0;//TODO:
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< CDeviceInstance > CDeviceList::operator[]( unsigned long ulIndex )
	{
		_WINQ_FCONTEXT( "CDeviceList::operator[]" );
		nsCodeQOR::CTLRef< CDeviceInstance > RefResult;
		/*
		CDeviceListModel& Model( m_pModel->As< CDeviceListModel >() );
		if( ulIndex < Model.m_Instances.Value().size() )
		{
			nsCodeQOR::CTLRef< CDeviceInstance > Result( &( Model.m_Instances.Value().at( ulIndex )->As< CDeviceInstance >() ), false );
			RefResult = Result;
		}
		*/
		return RefResult;
	}

}//nsWin32