//WinQLDeviceInterface.cpp

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
#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterface.h"
#include "WinQL/System/Devices/Interfaces/WinQLDeviceInterfaceClass.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceInstance.h"
#include "WinQL/System/Devices/WinQLIODevice.h"
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
	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceInterface );
	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceInterface::CDeviceSession );

	//--------------------------------------------------------------------------------
	CDeviceInterface::CDeviceInterface() : m_pInstance( 0 )
	,	m_pClass( 0 )
	,	m_ulIndex( (unsigned long)(-1) )
	,	m_pDeviceFile( 0 )
	,	m_ulUsageCount( 0 )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::CDeviceInterface" );
	}

	//--------------------------------------------------------------------------------
	CDeviceInterface::CDeviceInterface( CDeviceHandle& hExisting ) : m_pInstance( 0 )
	,	m_pClass( 0 )
	,	m_ulIndex( (unsigned long)(-1) )
	,	m_pDeviceFile( 0 )
	,	m_ulUsageCount( 0 )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::CDeviceInterface" );

		m_pDeviceFile = new CIODeviceFile( hExisting );
	}

	//--------------------------------------------------------------------------------
	CDeviceInterface::CDeviceInterface( const CDeviceInterface& src ) : m_pInstance( src.m_pInstance )
	,	m_pClass( src.m_pClass )
	,	m_ulIndex( src.m_ulIndex )
	,	m_pDeviceFile( src.m_pDeviceFile )
	,	m_ulUsageCount( src.m_ulUsageCount )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::CDeviceInterface" );
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CDeviceInterface& CDeviceInterface::operator = ( const CDeviceInterface& src )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::operator =" );

		if( &src != this )
		{
			m_bActive = src.m_bActive;
			m_bDefault = src.m_bDefault;
			m_bRemoved = src.m_bRemoved;
			m_pInstance = src.m_pInstance;
			m_pClass = src.m_pClass;
			m_ulIndex = src.m_ulIndex;
			m_strPath = src.m_strPath;
			m_pDeviceFile = src.m_pDeviceFile;
			m_ulUsageCount = src.m_ulUsageCount;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CDeviceInterface::~CDeviceInterface()
	{
		_WINQ_FCONTEXT( "CDeviceInterface::~CDeviceInterface" );
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterface::SetClass( CDeviceInterfaceClass* pClass, unsigned long ulClassIndex )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::SetClass" );
		m_pClass = pClass;
		m_ulIndex = ulClassIndex;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< CDeviceInterfaceClass > CDeviceInterface::GetClass()
	{
		_WINQ_FCONTEXT( "CDeviceInterface::GetClass" );
		nsCodeQOR::CTLRef< CDeviceInterfaceClass > Ref( m_pClass, false );
		return Ref;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterface::SetInstance( CDeviceInstance* pInstance )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::SetInstance" );
		m_pInstance = pInstance;
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< CDeviceInstance > CDeviceInterface::GetInstance()
	{
		_WINQ_FCONTEXT( "CDeviceInterface::GetInstance" );
		nsCodeQOR::CTLRef< CDeviceInstance > Ref( m_pInstance, false );
		return Ref;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterface::SetActive( bool bActive )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::SetActive" );
		m_bActive = bActive;
	}
	//--------------------------------------------------------------------------------
	bool CDeviceInterface::GetActive( void )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::GetActive" );
		return m_bActive;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterface::SetDefault( bool bDefault )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::SetDefault" );
		m_bDefault = bDefault;
	}
	//--------------------------------------------------------------------------------
	bool CDeviceInterface::GetDefault( void )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::GetDefault" );
		return m_bDefault;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterface::SetRemoved( bool bRemoved )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::SetRemoved" );
		m_bRemoved = bRemoved;
	}
	//--------------------------------------------------------------------------------
	bool CDeviceInterface::GetRemoved( void )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::GetRemoved" );
		return m_bRemoved;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterface::SetPath( const mxTCHAR* szPath )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::SetPath" );
		nsCodeQOR::CTLRef< mxTCHAR > RefPath( szPath, false );
		m_strPath = CTString( RefPath );
	}

	//--------------------------------------------------------------------------------
	CTString& CDeviceInterface::GetPath()
	{
		return m_strPath;
	}

	//--------------------------------------------------------------------------------
	CIODeviceFile& CDeviceInterface::Open( unsigned long ulAccessRequired, unsigned long ulShareMode, unsigned long ulAttributes )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::Open" );
		if( m_pDeviceFile == 0 )
		{
			m_pDeviceFile = new CIODeviceFile( m_strPath.GetBuffer(), ulAccessRequired, ulShareMode, ulAttributes );
			m_strPath.ReleaseBuffer();
		}

		++m_ulUsageCount;
		return *m_pDeviceFile;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterface::Close( void )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::Close" );
		--m_ulUsageCount;
		if( m_ulUsageCount <= 0 && m_pDeviceFile != 0 )
		{
			delete m_pDeviceFile;
			m_pDeviceFile = 0;
		}
	}

	//--------------------------------------------------------------------------------
	CIODeviceFile* CDeviceInterface::GetDeviceFile( void )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::GetDeviceFile" );
		return m_pDeviceFile;
	}


	//--------------------------------------------------------------------------------
	CDeviceInterface::CDeviceSession::CDeviceSession( CDeviceInterface& Interface, unsigned long ulAccessRequired, unsigned long ulShareMode, unsigned long ulAttributes ) : m_Interface( Interface )
	{
		_WINQ_FCONTEXT( "CDeviceInterface::CDeviceSession::CDeviceSession" );
		m_Interface.Open( ulAccessRequired, ulShareMode, ulAttributes );
	}

	//--------------------------------------------------------------------------------
	CDeviceInterface::CDeviceSession::~CDeviceSession()
	{
		_WINQ_FCONTEXT( "CDeviceInterface::CDeviceSession::~CDeviceSession" );
		m_Interface.Close();
	}



/*
	//--------------------------------------------------------------------------------
	CIODeviceFile& CDeviceInterfaceInstanceController::Open( unsigned long ulAccessRequired, unsigned long ulShareMode, unsigned long ulAttributes )
	{
		_WINQ_FCONTEXT( "CDeviceInterfaceInstanceController::Open" );

		nsMammut::CModel::refType RefBaseModel( GetModel(), false );

		nsCodeQOR::CTLRef< CDeviceInterfaceInstanceModel > RefModel( RefBaseModel.As< CDeviceInterfaceInstanceModel >(), false );
		CIODeviceFile* pDeviceFile = 0;

		if( !RefModel.IsNull() )
		{	
			pDeviceFile = RefModel->m_pDeviceFile;

			if( pDeviceFile == 0 )
			{
				RefModel->m_pDeviceFile.Set( new CIODeviceFile( RefModel->m_Path.Value(), ulAccessRequired, ulShareMode, ulAttributes ) );
				RefModel->m_ulUsageCount.Set( RefModel->m_ulUsageCount + 1 );
			}
		}

		return *pDeviceFile;
	}

	//--------------------------------------------------------------------------------
	void CDeviceInterfaceInstanceController::Close( void )
	{
		_WINQ_FCONTEXT( "CDeviceInterfaceInstanceController::Close" );

		nsMammut::CModel::refType RefBaseModel( GetModel(), false );

		nsCodeQOR::CTLRef< CDeviceInterfaceInstanceModel > RefModel( RefBaseModel.As< CDeviceInterfaceInstanceModel >(), false );

		if( !RefModel.IsNull() )
		{
			RefModel->m_ulUsageCount.Set( RefModel->m_ulUsageCount - 1 );

			CIODeviceFile* pDeviceFile = RefModel->m_pDeviceFile.Value();
			if( RefModel->m_ulUsageCount.Value() <= 0 && pDeviceFile != 0 )
			{
				RefModel->m_pDeviceFile.Set( 0 );
				delete pDeviceFile;
			}
		}
	}
*/


}//nsWin32
