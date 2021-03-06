//WinQLBluetoothHost.cpp

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

#include "CodeQOR/ClassReg/ClassReg.h"
#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/Comms/Bluetooth/WinQLBluetoothHost.h"
#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterfaceClass.h"
#include "WinQL/System/WinQLSystem.h"
#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQL/Application/Threading/WinQLWait.h"
#include "WinQL/Application/Resources/WinQLResourceManager.h"
#include "WinQAPI/Kernel32.h"
#include "WinQAPI/BthProps.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CBluetoothHost::CBluetoothHostWindowClass );

	CBluetoothHost::CBluetoothHostWindowClass CBluetoothHost::s_WindowClass;

	//--------------------------------------------------------------------------------
	CBluetoothHost::CBluetoothHostWindowClass::CBluetoothHostWindowClass()
	{
		Preinitialise();
		SetOwnDC( true );
		SetHRedrawTrigger( true );
		SetVRedrawTrigger( true );
		m_hInstance = const_cast< ImageDOSHeader* >( &__ImageBase );
		Register();
	}

	//--------------------------------------------------------------------------------
	const TCHAR* CBluetoothHost::CBluetoothHostWindowClass::Name()
	{
		_WINQ_FCONTEXT( "CBluetoothHost::CBluetoothHostWindowClass::Name" );
		return _TXT( "WinQLBluetoothHostWindowClass" );
	};

	//--------------------------------------------------------------------------------
	CBluetoothHost::CBluetoothHostWindowClass::~CBluetoothHostWindowClass()
	{
	}

	__QOR_IMPLEMENT_OCLASS_LUID( CBluetoothHost );

	//--------------------------------------------------------------------------------
	CBluetoothHost::CBluetoothHost(): m_Library( CBthProps::Instance() ), m_pHostWindow( 0 ), m_DeviceChangeController( *this, 0, 0 ), m_AuthenticationSession( this ), m_ulMonitorThreadID( 0 ), m_pBluetoothHostMonitorThread( 0 ), m_ScanState( eInitial )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::CBluetoothHost" );
	}

	//--------------------------------------------------------------------------------
	CBluetoothHost::~CBluetoothHost()
	{
		_WINQ_FCONTEXT( "CBluetoothHost::~CBluetoothHost" );
		if( m_pBluetoothHostMonitorThread )
		{
			StopMonitoringRadios();
		}
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::AuthenticateDevice( COSWindow::refType Window, CBluetoothRemoteDevice::refType Device, CWString strPassKey )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::AuthenticateDevice" );

		if( !Device.IsNull() )
		{
			Device->Authenticate( Window, strPassKey );
		}
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::AuthenticateDeviceEx( COSWindow::refType ParentWindow, CBluetoothRemoteDevice::refType Device, BluetoothOutOfBandData* pbtOobData, CBluetoothRemoteDevice::Authentication_Requirements AuthentRequirements )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::AuthenticateDeviceEx" );

		if( !Device.IsNull() )
		{
			Device->AuthenticateEx( ParentWindow, pbtOobData, AuthentRequirements );
		}
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::EnableDiscovery( bool bEnabled )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::EnableDiscovery" );

		bool bResult = m_Library.BluetoothEnableDiscovery( 0, bEnabled ? TRUE : FALSE ) ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::EnableIncomingConnections( bool bEnabled )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::EnableIncomingConnections" );

		bool bResult = m_Library.BluetoothEnableIncomingConnections( 0, bEnabled ? TRUE : FALSE ) ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::EnumerateInstalledServices( CBluetoothRemoteDevice::refType Device )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::EnumerateInstalledServices" );
		if( !Device.IsNull() )
		{
			Device->EnumerateInstalledServices();
		}
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::IsConnectable( void )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::IsConnectable" );

		return m_Library.BluetoothIsConnectable( 0 ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::IsDiscoverable( void )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::IsDiscoverable" );

		return m_Library.BluetoothIsDiscoverable( 0 ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::IsVersionAvailable( unsigned char ucMajor, unsigned char ucMinor )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::IsVersionAvailable" );

		return m_Library.BluetoothIsVersionAvailable( ucMajor, ucMinor ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::SelectDevices( Select_Device_Params* pParams )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::SelectDevices" );

		return m_Library.BluetoothSelectDevices(
			reinterpret_cast< ::BLUETOOTH_SELECT_DEVICE_PARAMS* >( pParams ) ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::SelectDevicesFree( Select_Device_Params* pParams )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::SelectDevicesFree" );
		return m_Library.BluetoothSelectDevicesFree(
			reinterpret_cast< ::BLUETOOTH_SELECT_DEVICE_PARAMS* >( pParams ) ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::SetLocalServiceInfo( nsCodeQOR::mxGUID* pClassGuid, unsigned long ulInstance, const BluetoothLocalServiceInfo* pServiceInfoIn )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::SetLocalServiceInfo" );

		m_Library.BluetoothSetLocalServiceInfo(
			0,
			reinterpret_cast< const ::GUID* >( pClassGuid ),
			ulInstance,
			reinterpret_cast< const BLUETOOTH_LOCAL_SERVICE_INFO* >( pServiceInfoIn ) );
	}

	//--------------------------------------------------------------------------------
	CFindBluetoothRadioSession::refType CBluetoothHost::FindRadio( CBluetoothRadio::refType& Radio )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::FindRadio" );

		return CFindBluetoothRadioSession::refType( new CFindBluetoothRadioSession( Radio ), true );
	}

	//--------------------------------------------------------------------------------
	unsigned long CBluetoothHost::ScanForDevices( void )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::ScanForDevices" );
		
		switch( m_ScanState )
		{
		case eInitial:
		{
			m_Proto = CBluetoothRemoteDevice::Prototype();
			m_ScanState = eFirst;
			return 1;
		}
		break;
		case eFirst:
		{
			CFindBluetoothDeviceSession::SearchParams SearchParams;

			SearchParams.dwSize = sizeof( CFindBluetoothDeviceSession::SearchParams );
			SearchParams.cTimeoutMultiplier = 3;
			SearchParams.fIssueInquiry = 1;
			SearchParams.fReturnAuthenticated = 1;
			SearchParams.fReturnRemembered = 1;
			SearchParams.fReturnUnknown = 1;
			SearchParams.fReturnConnected = 1;
			SearchParams.hRadio = 0;

			m_FindDeviceSession = CFindBluetoothDeviceSession::refType( new CFindBluetoothDeviceSession( SearchParams, m_Proto->Ref() ), true );
			m_ScanState = eNext;
			return 1;
		}
		break;
		case eNext:
		{
			BluetoothAddr Address = m_Proto->GetInfo()->Address.ullLong;

			if( m_MapRemoteDevices.find( Address ) == m_MapRemoteDevices.end() )
			{
				m_MapRemoteDevices.insert( std::make_pair( Address, m_Proto ) );
			}

			m_Proto->EnumerateInstalledServices();

			ConnectRegisteredServiceClients( m_Proto );
		
			m_Proto = CBluetoothRemoteDevice::Prototype();

			if( !m_FindDeviceSession->Next( m_Proto->Ref() ) )
			{
				m_ScanState = eLast;
			}
			return 1;
		}
		break;
		case eLast:
		{
			m_Proto.Dispose();
			m_FindDeviceSession.Dispose();			
			m_ScanState = eInitial;
		}
		}

		return 0;
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::DisconnectRegisteredServiceClients( CBluetoothRemoteDevice::refType Device, CBluetoothClient* pClient )
	{
		if( !Device.IsNull() )
		{
			unsigned long ulCountServices = 0;
			Device->GetServices( ulCountServices );
			CBluetoothClient** ppServiceClients = Device->GetServiceClients();
			for( unsigned long ulService = 0; ulService < ulCountServices; ulService++ )
			{
				//Lookup pServiceUUID[ ulService ] in Client Registration
				if( ppServiceClients[ ulService ] == pClient )
				{
					ppServiceClients[ ulService ] = 0;
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::ConnectRegisteredServiceClients( CBluetoothRemoteDevice::refType Device )
	{
		if( !Device.IsNull() )
		{
			unsigned long ulCountServices = 0;
			nsCodeQOR::mxGUID* pServiceUUID = Device->GetServices( ulCountServices );
			CBluetoothClient** ppServiceClients = Device->GetServiceClients();
			for( unsigned long ulService = 0; ulService < ulCountServices; ulService++ )
			{
				//Lookup pServiceUUID[ ulService ] in Client Registration
				if( ppServiceClients[ ulService ] == 0 )
				{
					ServiceClientClassMapType::const_iterator it = m_MapServiceClients.find( pServiceUUID[ ulService ] );

					if( it != m_MapServiceClients.end() )
					{
						//
						CBluetoothClient* pClient = (*it).second;
						if( pClient )
						{
							ppServiceClients[ ulService ] = pClient;
							pClient->AttachDevice( Device );
						}
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::RegisterServiceClient( nsCodeQOR::mxGUID& ServiceUUID, CBluetoothClient* pClient )
	{
		m_MapServiceClients.insert( std::make_pair( ServiceUUID, pClient ) );

		AddrDeviceMapType::const_iterator it = m_MapRemoteDevices.begin();
		while( it != m_MapRemoteDevices.end() )
		{
			ConnectRegisteredServiceClients( (*it).second->Ref() );
			it++;
		}
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::UnregisterServiceClient( nsCodeQOR::mxGUID& ServiceUUID, CBluetoothClient* pClient )
	{
		ServiceClientClassMapType::iterator it_Clients = m_MapServiceClients.find( ServiceUUID );
		if( it_Clients != m_MapServiceClients.end() )
		{
			m_MapServiceClients.erase( it_Clients );
		}
		AddrDeviceMapType::const_iterator it_Devices = m_MapRemoteDevices.begin();
		while( it_Devices != m_MapRemoteDevices.end() )
		{
			DisconnectRegisteredServiceClients( (*it_Devices).second->Ref(), pClient );
			it_Devices++;
		}
	}

	//--------------------------------------------------------------------------------
	CBluetoothHost::AddrDeviceMapType& CBluetoothHost::Devices( void )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::Devices" );
		return m_MapRemoteDevices;
	}

	//--------------------------------------------------------------------------------
	CBluetoothHost::VecRadiosType& CBluetoothHost::Radios( void )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::Radios" );
		return m_VecRadios;
	}

	//--------------------------------------------------------------------------------
	unsigned long __QCMP_STDCALLCONVENTION CBluetoothHost::StaticMonitorThreadProc( void* pvHost )
	{
		unsigned long ulResult = (unsigned long)(-1 );
		CBluetoothHost* pHost = reinterpret_cast< CBluetoothHost* >( pvHost );

		if( pHost )
		{
			ulResult = pHost->InstanceMonitorThreadProc();
		}

		return ulResult;
	}

	//--------------------------------------------------------------------------------
	unsigned long CBluetoothHost::InstanceMonitorThreadProc()
	{
		unsigned long StyleEx = COSWindow::eWSExAppWindow;
		unsigned long Style = COSWindow::eWSOverlapped;
		m_pHostWindow = new COSWindow( &s_WindowClass, StyleEx, _TXT( "WinQLBluetoothHostWindow" ), Style, 0, 0,640, 480, 0, 0, ThisProcess(), 0 );

		if( m_pHostWindow )
		{
			m_BaseWindowController.DeviceChange.Configure( &m_DeviceChangeController );
			m_pHostWindow->Controller( &m_BaseWindowController );
		}

		if( m_VecRadios.size() == 0 )
		{
			EnumerateRadios();
		}

		for( VecRadiosType::iterator it = m_VecRadios.begin(); it != m_VecRadios.end(); it++ )
		{
			(*it)->EnableNotifications( m_pHostWindow->Handle()->AsHandle(), true );
		}

		CBluetoothHostMessageHandler MessageHandler( *this );
		MessageHandler.MessageLoop();

		delete m_pHostWindow;
		m_pHostWindow = 0;
		
		return 0;
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::StopMonitoringRadios()
	{
		_WINQ_FCONTEXT( "CBluetoothHost::StopMonitoringRadios" );
		CMessageHandler MessageHandler;
		MessageHandler.PostToThread( m_ulMonitorThreadID, COSWindow::wmQuit, 0, 0 );
		CWaitHelper WaitHelper;
		WaitHelper.WaitForSingleObject( m_pBluetoothHostMonitorThread->Handle(), Infinite );
		delete m_pBluetoothHostMonitorThread;
		m_pBluetoothHostMonitorThread = 0;
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::StartMonitoringRadios()
	{
		_WINQ_FCONTEXT( "CBluetoothHost::StartMonitoringRadios" );

		m_pBluetoothHostMonitorThread = new CThread( 0, 0, &StaticMonitorThreadProc, reinterpret_cast< void* >( this ), 0, &m_ulMonitorThreadID );
	}

	//--------------------------------------------------------------------------------
	void CBluetoothHost::EnumerateRadios( void )
	{
		_WINQ_FCONTEXT( "CBluetoothHost::EnumerateRadios" );
		CDeviceInterfaceClass::refType BluetoothRadios = CSystem::Instance().Devices( QOR_PP_SHARED_OBJECT_ACCESS ).InterfaceClassFromGUID( CDeviceManager::GUID_BTHPORT_DEVICE_INTERFACE );

		if( !BluetoothRadios.IsNull() )
		{
			CDeviceInterfaceClass::interface_iterator it = BluetoothRadios->Interfaces().begin();
			while( it != BluetoothRadios->Interfaces().end() )
			{
				CBluetoothRadio::refType BluetoothRadio = (*it).As< CBluetoothRadio >();

				if( !BluetoothRadio.IsNull() )
				{
					m_VecRadios.push_back( BluetoothRadio );

					if( BluetoothRadio->GetDeviceFile() )
					{
						m_MapRadioHandles.insert( std::make_pair( BluetoothRadio->GetDeviceFile()->Handle()->Use(), BluetoothRadio.operator CBluetoothRadio*() ) );
					}
				}
				it++;
			}
		}
	
	}

	//--------------------------------------------------------------------------------
	CBluetoothRadio::refType CBluetoothHost::RadioFromHandle( void* pRadioHandle )
	{
		CBluetoothRadio::refType Radio;

		HandleRadioMapType::const_iterator it = m_MapRadioHandles.find( pRadioHandle );
		if( it != m_MapRadioHandles.end() )
		{
			Radio.Attach( (*it).second );
		}
		return Radio;
	}

	//--------------------------------------------------------------------------------
	long CBluetoothHost::OnHCIEvent( BluetoothHCIEventInfo* pEventInfo, void* pRadioHandle )
	{		
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->bthAddress );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = (*it).second->Ref();

				if( !RemoteDevice.IsNull() )
				{
					switch( pEventInfo->connected )
					{
					case 0:		//Disconnect
						RemoteDevice->OnDisconnect();
						break;
					case 1:		//Connect
						RemoteDevice->OnConnect( static_cast< CBluetoothRemoteDevice::eConnectionType >( pEventInfo->connectionType ) );	//Connection type 1 == ACL, 2 == SCO
						break;
					}
				}
			}			
		}
		return 1;
	}

	//--------------------------------------------------------------------------------
	long CBluetoothHost::OnL2CAPEvent( BluetoothL2CAPEventInfo* pEventInfo, void* pRadioHandle )
	{
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->bthAddress );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = (*it).second->Ref();

				RemoteDevice->OnL2CAPEvent( pEventInfo, RadioFromHandle( pRadioHandle ) );
			}
		}
		return 1;
	}

	//--------------------------------------------------------------------------------
	long CBluetoothHost::OnDeviceInRange( BluetoothRadioInRange* pEventInfo, void* pRadioHandle )
	{
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->deviceInfo.address );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = (*it).second->Ref();

				RemoteDevice->OnInRange( pEventInfo->deviceInfo, pEventInfo->previousDeviceFlags, RadioFromHandle( pRadioHandle ) );
			}
			else
			{
				CBluetoothRemoteDevice::refType RemoteDevice( new CBluetoothRemoteDevice, true );

				m_MapRemoteDevices.insert( std::make_pair( pEventInfo->deviceInfo.address, RemoteDevice ) );
				RemoteDevice->OnInRange( pEventInfo->deviceInfo, pEventInfo->previousDeviceFlags, RadioFromHandle( pRadioHandle ) );
			}
		}
		return 1;	
	}

	//--------------------------------------------------------------------------------
	long CBluetoothHost::OnDeviceOutOfRange( BluetoothAddress* pEventInfo, void* pRadioHandle  )
	{
		if( pEventInfo )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pEventInfo->ullLong );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = (*it).second->Ref();

				RemoteDevice->OnOutOfRange();
			}
		}
		return 1;
	}

	//--------------------------------------------------------------------------------
	bool CBluetoothHost::OnAuthenticationRequest( CBluetoothRemoteDevice::Authentication_CallbackParams* pAuthCallbackParams )
	{
		bool bResult = false;
		if( pAuthCallbackParams )
		{
			AddrDeviceMapType::iterator it = m_MapRemoteDevices.find( pAuthCallbackParams->deviceInfo.Address.ullLong );
			if( it != m_MapRemoteDevices.end() )
			{
				CBluetoothRemoteDevice::refType RemoteDevice = (*it).second->Ref();

				bResult = RemoteDevice->OnAuthenticationRequest( pAuthCallbackParams, m_AuthenticationSession );
			}
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CBluetoothHost::CBluetoothDeviceChangeController );

	//--------------------------------------------------------------------------------
	CBluetoothHost::CBluetoothDeviceChangeController::CBluetoothDeviceChangeController( CBluetoothHost& Host, nsMammut::CModel* pModelItem, nsAppocrita::CController* pParent ) : CDeviceChangeController( pModelItem, pParent ), m_Host( Host )
	{
		_WINQ_FCONTEXT( "CBluetoothDeviceChangeController::CBluetoothDeviceChangeController" );
	}

	//--------------------------------------------------------------------------------
	CBluetoothHost::CBluetoothDeviceChangeController::~CBluetoothDeviceChangeController()
	{
		_WINQ_FCONTEXT( "CBluetoothDeviceChangeController::~CBluetoothDeviceChangeController" );
	}

	//--------------------------------------------------------------------------------
	long CBluetoothHost::CBluetoothDeviceChangeController::OnDBTCustomEvent( sDeviceBroadcastHeader* pDeviceBroadcastHeader )
	{
		_WINQ_FCONTEXT( "CBluetoothDeviceChangeController::OnDBTCustomEvent" );
		long lResult = 0;
		if( pDeviceBroadcastHeader && pDeviceBroadcastHeader->ulDeviceType == CNotificationFilter::eNotifyHandle )
		{
			sDeviceBroadcastHandle* pDeviceBroadcastHandle = reinterpret_cast< sDeviceBroadcastHandle* >( pDeviceBroadcastHeader );

			if( pDeviceBroadcastHandle )
			{
				void* pRadioHandle = pDeviceBroadcastHandle->DeviceHandle;

				if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_HCI_EVENT, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//HCI Event
					BluetoothHCIEventInfo* pData = reinterpret_cast< BluetoothHCIEventInfo* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnHCIEvent( pData, pRadioHandle );
				}
				else if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_L2CAP_EVENT, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//L2CAP Event
					BluetoothL2CAPEventInfo* pData = reinterpret_cast< BluetoothL2CAPEventInfo* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnL2CAPEvent( pData, pRadioHandle );
				}
				else if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_RADIO_IN_RANGE, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//In Range
					BluetoothRadioInRange* pData = reinterpret_cast< BluetoothRadioInRange* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnDeviceInRange( pData, pRadioHandle );
				}
				else if( memcmp( &pDeviceBroadcastHandle->EventGUID, &CBluetoothRadio::GUID_BLUETOOTH_RADIO_OUT_OF_RANGE, sizeof( nsCodeQOR::mxGUID ) ) == 0 )
				{
					//Out of Range
					BluetoothAddress* pData = reinterpret_cast< BluetoothAddress* >( pDeviceBroadcastHandle->data );
					lResult = m_Host.OnDeviceOutOfRange( pData, pRadioHandle );
				}
			}
		}
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CBluetoothHost::CBluetoothDeviceChangeController::OnDeviceChange( COSWindow& Window, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CBluetoothDeviceChangeController::OnDeviceChange" );

		switch( wParam )
		{
		case 0x0019://DBT_CONFIGCHANGECANCELLED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x0018://DBT_CONFIGCHANGED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8006://DBT_CUSTOMEVENT
			return OnDBTCustomEvent( reinterpret_cast< sDeviceBroadcastHeader* >( lParam ) );
			break;
		case 0x8000://DBT_DEVICEARRIVAL
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8001://DBT_DEVICEQUERYREMOVE
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8002://DBT_DEVICEQUERYREMOVEFAILED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8004://DBT_DEVICEREMOVECOMPLETE
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8003://DBT_DEVICEMOVEPENDING
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x8005://DBT_DEVICETYPESPECIFIC
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x0007://DBT_DEVNODES_CHANGED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0x0017://DBT_QUERYCHANGECONFIG
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		case 0xFFFF://DBT_USERDEFINED
			return Window.DefProc( COSWindow::wmDeviceChange, wParam, lParam );
			break;
		}
		return 0;
	}

}//nsWin32

