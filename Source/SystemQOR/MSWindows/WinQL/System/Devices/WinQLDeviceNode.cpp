//WinQLDeviceNode.cpp

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
#include "WinQL/System/WinQLSystem.h"
#include "WinQL/System/Devices/WinQLDeviceNode.h"
#include "WinQL/System/Devices/WinQLConfigManSession.h"
#include "WinQL/System/Devices/Instances/WinQLDeviceInstance.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CDeviceNode );

	//--------------------------------------------------------------------------------
	CDeviceNode::CDeviceNode( unsigned long ulDevInst, CConfigurationManagementSession& Session ) : m_DevInst( ulDevInst), m_Session( Session ), m_bChildrenEnumerated( false ), m_pInstance( 0 )
	{
		_WINQ_FCONTEXT( "CDeviceNode::CDeviceNode" );
	}

	//--------------------------------------------------------------------------------
	CDeviceNode::CDeviceNode( const CDeviceNode& src ) : m_DevInst( src.m_DevInst ), m_Session( src.m_Session ), m_bChildrenEnumerated( src.m_bChildrenEnumerated ), m_pInstance( src.m_pInstance )
	{
		_WINQ_FCONTEXT( "CDeviceNode::CDeviceNode" );
	}

	//--------------------------------------------------------------------------------
	CDeviceNode::~CDeviceNode()
	{
		_WINQ_FCONTEXT( "CDeviceNode::~CDeviceNode" );

		for( std::vector< CDeviceNode* >::iterator it = m_VecChildren.begin(); it != m_VecChildren.end(); ++it )
		{
			CDeviceNode* pNode = *it;
			delete pNode;
		}
	}

	//--------------------------------------------------------------------------------
	std::vector< CDeviceNode* >& CDeviceNode::GetChildren( void )
	{
		_WINQ_FCONTEXT( "CDeviceNode::GetChildren" );
		if( !m_bChildrenEnumerated )
		{
			EnumerateChildren();
		}
		return m_VecChildren;
	}

	//--------------------------------------------------------------------------------
	void CDeviceNode::EnumerateChildren()
	{
		_WINQ_FCONTEXT( "CDeviceNode::EnumerateChildren" );
		unsigned long ulChildDevInst = m_Session.GetFirstDevNodeChild( m_DevInst );

		while( ulChildDevInst != 0 )
		{
			m_VecChildren.push_back( new CDeviceNode( ulChildDevInst, m_Session ) );
			ulChildDevInst = m_Session.GetDevNodeSibling( ulChildDevInst );
		}
	}

	//--------------------------------------------------------------------------------
	nsCodeQOR::CTLRef< CDeviceInstance > CDeviceNode::GetInstance()
	{
		_WINQ_FCONTEXT( "CDeviceNode::GetInstance" );
		CTString strDeviceInstance = m_Session.GetDeviceInstanceID( m_DevInst );
		m_pInstance = CSystem::Instance().Devices( QOR_PP_SHARED_OBJECT_ACCESS ).DeviceFromID( strDeviceInstance );

		if( m_pInstance == 0 )
		{
			CTString strEnumerator = m_Session.GetDevNodeEnumerator( m_DevInst );

			CDeviceEnumerator::refType Enumerator = CSystem::Instance().Devices( QOR_PP_SHARED_OBJECT_ACCESS ).EnumeratorFromName( strEnumerator.Ref() );

			if( !Enumerator.IsNull() )
			{
				Enumerator->Enumerate();
				m_pInstance = CSystem::Instance().Devices( QOR_PP_SHARED_OBJECT_ACCESS ).DeviceFromID( strDeviceInstance );
			}
		}

		return nsCodeQOR::CTLRef< CDeviceInstance >( m_pInstance, false );		
	}

	//--------------------------------------------------------------------------------
	CTString CDeviceNode::GetDescription()
	{
		_WINQ_FCONTEXT( "CDeviceNode::GetDescription" );
		CTString strDescription = m_Session.GetDevNodeDescription( m_DevInst );
		if( strDescription.IsEmpty() && GetInstance() != 0 )
		{
			strDescription = GetInstance()->GetDisplayName();
		}
		else if( strDescription.IsEmpty() )
		{
			strDescription = m_Session.GetDeviceInstanceID( m_DevInst );
		}
		return strDescription;
	}

}//nsWin32
