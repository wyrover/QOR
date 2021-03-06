//WinQLDeviceSetupClass.cpp

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
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/CodeServices/Text/WinString.h"
#include "WinQL/System/Devices/SetupClasses/WinQLDeviceSetupClass.h"
//#include "WinQL/Devices/SetupClasses/DeviceList.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/GUI/Window.h"
#include "WinQL/System/WinQLSystem.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/SetupAPI.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceSetupClass );

	//--------------------------------------------------------------------------------
	CDeviceSetupClass::CDeviceSetupClass( nsCodeQOR::mxGUID GUID, const CTString& strMachineName ) : m_Library( CSetupAPI::Instance() )
	, m_GUID( GUID )
	, m_strMachine( strMachineName )
	, m_bInstancesEnumerated( false )
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::CDeviceSetupClass" );
	}

	//--------------------------------------------------------------------------------
	CDeviceSetupClass::CDeviceSetupClass( const CDeviceSetupClass& src ) : m_Library( CSetupAPI::Instance() )
	, m_GUID( src.m_GUID )
	, m_strMachine( src.m_strMachine )
	, m_bInstancesEnumerated( src.m_bInstancesEnumerated )
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::CDeviceSetupClass" );
	}

	//--------------------------------------------------------------------------------
	CDeviceSetupClass::~CDeviceSetupClass()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::~CDeviceSetupClass" );
	}

	//--------------------------------------------------------------------------------
	CTString CDeviceSetupClass::Name()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::Name" );
		CTString strName;
		unsigned long ulLength = 0;
		m_Library.SetupDiClassNameFromGuidEx( reinterpret_cast< const ::GUID* >( &m_GUID ),
			strName.GetBufferSetLength( MaxNameLength ), MaxNameLength, &ulLength, m_strMachine, 0 );
		strName.ValidateBuffer( static_cast< unsigned short >( ulLength ) );
		return strName;
	}

	//--------------------------------------------------------------------------------
	bool CDeviceSetupClass::IsLocal()
	{
		return ( m_strMachine.IsEmpty() ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CDeviceSetupClass::IsRemote()
	{
		return ( m_strMachine.IsEmpty() ) ? false : true;
	}

	//--------------------------------------------------------------------------------
	CTString CDeviceSetupClass::Description()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::Description" );
		CTString strDescription;
		unsigned long ulLength = 0;
		if( IsRemote() )
		{
			m_Library.SetupDiGetClassDescriptionEx( reinterpret_cast< const ::GUID* >( &m_GUID ), 0, 0, &ulLength, m_strMachine, 0 );
			if( ulLength > 0 )
			{
				m_Library.SetupDiGetClassDescriptionEx( reinterpret_cast< const ::GUID* >( &m_GUID ),
					strDescription.GetBufferSetLength( static_cast< unsigned short >( ulLength + 1 ) ), ulLength, &ulLength, m_strMachine, 0);
				strDescription.ValidateBuffer( static_cast< unsigned short >( ulLength ) );
			}
		}
		else
		{
			m_Library.SetupDiGetClassDescription( reinterpret_cast< const ::GUID* >( &m_GUID ), 0, 0, &ulLength );
			if( ulLength > 0 )
			{
				m_Library.SetupDiGetClassDescription( reinterpret_cast< const ::GUID* >( &m_GUID ),
					strDescription.GetBufferSetLength( static_cast< unsigned short >( ulLength + 1 ) ), ulLength, &ulLength );
				strDescription.ValidateBuffer( static_cast< unsigned short >( ulLength ) );
			}
		}
		return strDescription;
	}
			
	/*
	//--------------------------------------------------------------------------------
	CDeviceList& CDeviceSetupClass::DeviceList()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::DeviceList" );
		if( m_DeviceList.IsNull() )
		{
			m_DeviceList.Configure( new CDeviceList( m_pGUID, 0, m_szMachine ), true );
		}

		return m_DeviceList();
	}
	*/

	//--------------------------------------------------------------------------------
	CString< byte > CDeviceSetupClass::GetProperty( CDeviceSetupClass::eProperty Property )
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::GetProperty" );
		CString< byte > Buffer;
		unsigned long ulRegDataType = 0;
		unsigned long ulRequiredSize = 0;
		m_Library.SetupDiGetClassRegistryProperty( 
			reinterpret_cast< const ::GUID* >( &m_GUID ), static_cast< unsigned long >( Property ), &ulRegDataType, 0, 0, &ulRequiredSize, m_strMachine.GetNullableBuffer() );
		m_strMachine.ReleaseBuffer();

		if( ulRequiredSize )
		{
			m_Library.SetupDiGetClassRegistryProperty( 
				reinterpret_cast< const ::GUID* >( &m_GUID ), static_cast< unsigned long >( Property ), &ulRegDataType, 
				Buffer.GetBufferSetLength( static_cast< unsigned short >( ulRequiredSize ) ), ulRequiredSize, &ulRequiredSize, m_strMachine.GetNullableBuffer() );
			m_strMachine.ReleaseBuffer();
			Buffer.ValidateBuffer( static_cast< unsigned short >( ulRequiredSize ) );
		}

		return Buffer;
	}

	//--------------------------------------------------------------------------------
	unsigned long CDeviceSetupClass::GetCharacteristics()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::GetCharacteristics" );
		unsigned long ulCharacteristics = 0;
		CString< byte > Buffer = GetProperty( Characteristics );
		if( !Buffer.IsEmpty() )
		{
			ulCharacteristics = *( reinterpret_cast< unsigned long* >( Buffer.GetBuffer() ) );
			Buffer.ReleaseBuffer();
		}
		//FILE_AUTOGENERATED_DEVICE_NAME
		//FILE_CHARACTERISTIC_PNP_DEVICE
		//FILE_CHARACTERISTIC_TS_DEVICE
		//FILE_CHARACTERISTIC_WEBDAV_DEVICE
		//FILE_DEVICE_IS_MOUNTED 
		//FILE_DEVICE_SECURE_OPEN
		//FILE_FLOPPY_DISKETTE
		//FILE_READ_ONLY_DEVICE
		//FILE_REMOTE_DEVICE
		//FILE_REMOVABLE_MEDIA
		//FILE_VIRTUAL_VOLUME
		//FILE_WRITE_ONCE_MEDIA
		//DEVICE_OBJECT
		return ulCharacteristics;
	}

	//--------------------------------------------------------------------------------
	unsigned long CDeviceSetupClass::GetDeviceType()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::GetDeviceType" );
		unsigned long ulDevType = 0;
		CString< byte > Buffer = GetProperty( DevType );
		if( !Buffer.IsEmpty() )
		{
			ulDevType = *( reinterpret_cast< unsigned long* >( Buffer.GetBuffer() ) );
			Buffer.ReleaseBuffer();
		}
		return ulDevType;
		/*
		#define FILE_DEVICE_8042_PORT           0x00000027
#define FILE_DEVICE_ACPI                0x00000032
#define FILE_DEVICE_BATTERY             0x00000029
#define FILE_DEVICE_BEEP                0x00000001
#define FILE_DEVICE_BUS_EXTENDER        0x0000002a
#define FILE_DEVICE_CD_ROM              0x00000002
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003
#define FILE_DEVICE_CHANGER             0x00000030
#define FILE_DEVICE_CONTROLLER          0x00000004
#define FILE_DEVICE_DATALINK            0x00000005
#define FILE_DEVICE_DFS                 0x00000006
#define FILE_DEVICE_DFS_FILE_SYSTEM     0x00000035
#define FILE_DEVICE_DFS_VOLUME          0x00000036
#define FILE_DEVICE_DISK                0x00000007
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008
#define FILE_DEVICE_DVD                 0x00000033
#define FILE_DEVICE_FILE_SYSTEM         0x00000009
#define FILE_DEVICE_FIPS                0x0000003a
#define FILE_DEVICE_FULLSCREEN_VIDEO    0x00000034
#define FILE_DEVICE_INPORT_PORT         0x0000000a
#define FILE_DEVICE_KEYBOARD            0x0000000b
#define FILE_DEVICE_KS                  0x0000002f
#define FILE_DEVICE_KSEC                0x00000039
#define FILE_DEVICE_MAILSLOT            0x0000000c
#define FILE_DEVICE_MASS_STORAGE        0x0000002d
#define FILE_DEVICE_MIDI_IN             0x0000000d
#define FILE_DEVICE_MIDI_OUT            0x0000000e
#define FILE_DEVICE_MODEM               0x0000002b
#define FILE_DEVICE_MOUSE               0x0000000f
#define FILE_DEVICE_MULTI_UNC_PROVIDER  0x00000010
#define FILE_DEVICE_NAMED_PIPE          0x00000011
#define FILE_DEVICE_NETWORK             0x00000012
#define FILE_DEVICE_NETWORK_BROWSER     0x00000013
#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014
#define FILE_DEVICE_NETWORK_REDIRECTOR  0x00000028
#define FILE_DEVICE_NULL                0x00000015
#define FILE_DEVICE_PARALLEL_PORT       0x00000016
#define FILE_DEVICE_PHYSICAL_NETCARD    0x00000017
#define FILE_DEVICE_PRINTER             0x00000018
#define FILE_DEVICE_SCANNER             0x00000019
#define FILE_DEVICE_SCREEN              0x0000001c
#define FILE_DEVICE_SERENUM             0x00000037
#define FILE_DEVICE_SERIAL_MOUSE_PORT   0x0000001a
#define FILE_DEVICE_SERIAL_PORT         0x0000001b
#define FILE_DEVICE_SMARTCARD           0x00000031
#define FILE_DEVICE_SMB                 0x0000002e
#define FILE_DEVICE_SOUND               0x0000001d
#define FILE_DEVICE_STREAMS             0x0000001e
#define FILE_DEVICE_TAPE                0x0000001f
#define FILE_DEVICE_TAPE_FILE_SYSTEM    0x00000020
#define FILE_DEVICE_TERMSRV             0x00000038
#define FILE_DEVICE_TRANSPORT           0x00000021
#define FILE_DEVICE_UNKNOWN             0x00000022
#define FILE_DEVICE_VDM                 0x0000002c
#define FILE_DEVICE_VIDEO               0x00000023
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_WAVE_IN             0x00000025
#define FILE_DEVICE_WAVE_OUT            0x00000026
		*/
	}

	//--------------------------------------------------------------------------------
	bool CDeviceSetupClass::GetExclusiveAccessAvailable()
	{
		_WINQ_FCONTEXT( "CDeviceClass::GetExclusiveAccessAvailable" );
		CString< byte > Buffer = GetProperty( Exclusive );
		unsigned long ulResult = 0;
		if( !Buffer.IsEmpty() )
		{
			ulResult = *( reinterpret_cast< unsigned long* >( Buffer.GetBuffer() ) );
			Buffer.ReleaseBuffer();
		}
		return ulResult == 1 ? true : false;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< nsCodeQOR::CTArray< CTString, CPolicy > > CDeviceSetupClass::GetLowerFilters()
	{
		_WINQ_FCONTEXT( "CDeviceClass::GetUpperFilters" );

		nsCodeQOR::CTArray< CTString, CPolicy >* pArrayOfStrings = 0;

		//TODO:

		nsCodeQOR::CTLRef< nsCodeQOR::CTArray< CTString, CPolicy > > Result( pArrayOfStrings, true );
		return Result;
	}

	//--------------------------------------------------------------------------------
	SECURITY_DESCRIPTOR CDeviceSetupClass::GetSecurity()
	{
		_WINQ_FCONTEXT( "CDeviceClass::GetSecurity" );
		CString< byte > Buffer = GetProperty( Security );
		SECURITY_DESCRIPTOR Result = *( reinterpret_cast< SECURITY_DESCRIPTOR* >( Buffer.GetBuffer() ) );
		Buffer.ReleaseBuffer();
		return Result;
	}

	//--------------------------------------------------------------------------------
	CTString CDeviceSetupClass::GetSecurity_SDS()
	{
		_WINQ_FCONTEXT( "CDeviceClass::GetSecurity_SDS" );
		
		CTString strSecuritySDS;
		CString< byte > Buffer = GetProperty( Security_SDS );
		if( !Buffer.IsEmpty() )
		{
			memcpy( strSecuritySDS.GetBufferSetLength( Buffer.Len() / sizeof( mxTCHAR ) ), Buffer.GetNullableBuffer(), Buffer.Len() );
			Buffer.ReleaseBuffer();
			strSecuritySDS.ValidateBuffer( Buffer.Len() / sizeof( mxTCHAR ) );
		}		

		return strSecuritySDS;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< nsCodeQOR::CTArray< CTString, CPolicy > > CDeviceSetupClass::GetUpperFilters()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::GetUpperFilters" );

		nsCodeQOR::CTArray< CTString, CPolicy >* pArrayOfStrings = 0;

		//TODO:

		nsCodeQOR::CTLRef< nsCodeQOR::CTArray< CTString, CPolicy > > Result( pArrayOfStrings, true );
		return Result;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< nsCodeQOR::CTArray< nsCodeQOR::__mxGUID, CPolicy > > CDeviceSetupClass::GetGUIDsFromName()
	{
		_WINQ_FCONTEXT( "CDeviceSetupClass::GetGUIDsFromName" );

		nsCodeQOR::CTArray< nsCodeQOR::__mxGUID >* pArrayOfGUIDs = 0;
		unsigned long ulRequiredSize;

		if( IsRemote() )
		{
			m_Library.SetupDiClassGuidsFromNameEx( Name(), 0, 0, &ulRequiredSize, m_strMachine, 0 ); 

			if( ulRequiredSize != 0 )
			{
				pArrayOfGUIDs = new nsCodeQOR::CTArray< nsCodeQOR::__mxGUID >;
				pArrayOfGUIDs->SetCapacity( ulRequiredSize );

				m_Library.SetupDiClassGuidsFromNameEx( Name(), reinterpret_cast< ::LPGUID >( pArrayOfGUIDs->GetAddressOfData() ), ulRequiredSize, &ulRequiredSize, m_strMachine, 0 );
				pArrayOfGUIDs->Validate( ulRequiredSize );
			}
		}
		else
		{
			m_Library.SetupDiClassGuidsFromName( Name(), 0, 0, &ulRequiredSize ); 

			if( ulRequiredSize != 0 )
			{
				pArrayOfGUIDs = new nsCodeQOR::CTArray< nsCodeQOR::__mxGUID >;
				pArrayOfGUIDs->SetCapacity( ulRequiredSize );

				m_Library.SetupDiClassGuidsFromName( Name(), reinterpret_cast< ::LPGUID >( pArrayOfGUIDs->GetAddressOfData() ), ulRequiredSize, &ulRequiredSize );
				pArrayOfGUIDs->Validate( ulRequiredSize );
			}
		}
		nsCodeQOR::CTLRef< nsCodeQOR::CTArray< nsCodeQOR::__mxGUID > > Result( pArrayOfGUIDs, true );
		return Result;
	}

	//--------------------------------------------------------------------------------
	std::vector< CDeviceInstance::refType >& CDeviceSetupClass::GetInstances()
	{
		if( !m_bInstancesEnumerated )
		{
			EnumerateInstances();
			m_bInstancesEnumerated = true;
		}
		return m_Instances;
	}

	//--------------------------------------------------------------------------------
	unsigned int CDeviceSetupClass::EnumerateInstances( void )
	{		
		unsigned int uiIndex = m_Instances.size();
		if( !m_bInstancesEnumerated )
		{
			CDeviceInfoSet InfoSet( m_GUID, static_cast< int >( DIGCF_ALLCLASSES ) );	
			nsCodeQOR::mxGUID nullGUID = { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };			
			SP_DevInfo_Data DevInfo;
			do
			{
				unsigned long ulError = 0;
				unsigned long ulResult = (unsigned long)(-1);
				DevInfo.cbSize = sizeof( ::SP_DEVINFO_DATA );
				DevInfo.ClassGuid = nullGUID;
				DevInfo.DevInst = 0;
				DevInfo.Reserved = 0;

				if( m_Library.SetupDiEnumDeviceInfo( reinterpret_cast< ::HDEVINFO >( InfoSet.Handle().Use() ), uiIndex, reinterpret_cast< ::PSP_DEVINFO_DATA >( &DevInfo ) ) )
				{
					ulResult = DevInfo.DevInst;
					if( ulResult > 0 && ulResult != (unsigned long)(-1) )
					{
						CTString strDeviceID;
						if( m_Library.CM_Get_Device_ID_Ex( static_cast< ::DEVINST >( DevInfo.DevInst ), strDeviceID.GetBufferSetLength( MaxDeviceIDLen + 1), MaxDeviceIDLen, 0, 0 ) != CR_SUCCESS )
						{
							ulError = ::GetLastError();
						}
						else
						{
							strDeviceID.ValidateBuffer();
							//Get the device instance ID and device data and add it to the global instance map
							CTString strDeviceInstance;
							unsigned long ulInstanceSize = 0;
							m_Library.SetupDiGetDeviceInstanceId( reinterpret_cast< ::HDEVINFO >( InfoSet.Handle().Use() ), reinterpret_cast< ::PSP_DEVINFO_DATA >( &DevInfo ), 0, 0, &ulInstanceSize );
							if( ulInstanceSize > 0 )
							{							
								m_Library.SetupDiGetDeviceInstanceId( InfoSet.Handle().Use(), reinterpret_cast< ::PSP_DEVINFO_DATA >( &DevInfo ), 
									strDeviceInstance.GetBufferSetLength( static_cast< unsigned short >( ulInstanceSize + 1 ) ), ulInstanceSize, &ulInstanceSize );
								strDeviceInstance.ValidateBuffer( static_cast< unsigned short >( ulInstanceSize ) );
							}
							else
							{
								ulError = ::GetLastError();
							}

							CDeviceInstance* pDeviceInstance = CSystem::Instance().Devices(QOR_PP_SHARED_OBJECT_ACCESS).DeviceFromID( strDeviceInstance );
						
							if( pDeviceInstance == 0 )
							{
								pDeviceInstance = new CDeviceInstance( strDeviceID, DevInfo );
							}
							/*
							else
							{
								pDeviceInstance->AttachInfoSet( &InfoSet, uiIndex );
							}
							*/
							m_Instances.push_back( pDeviceInstance->Ref() );
						}
						
						uiIndex++;
					}
					else
					{
						ulError = ::GetLastError();
						m_bInstancesEnumerated = true;
					}
				}
				else
				{
					ulError = ::GetLastError();
					m_bInstancesEnumerated = true;
				}
			}while( !m_bInstancesEnumerated );
		}
		return uiIndex;
	}

}//nsWin32
