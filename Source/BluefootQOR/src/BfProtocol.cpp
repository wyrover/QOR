//BfProtocol.cpp

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

//Implementation of Bluefoot protocol class

#include "CompilerQOR.h"
#include "BluefootQOR/BfProtocol.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	CBFProtocol::CBFProtocol() : m_eState( Stopped )
	,	m_eNextState( Stopped )
	,	m_ulDataSize( 0 )
	,	m_pInPipe( 0 )
	,	m_pOutPipe( 0 )
	{
	}

	//------------------------------------------------------------------------------
	CBFProtocol::~CBFProtocol()
	{
	}

	//------------------------------------------------------------------------------
	CBFProtocol::CBFProtocol(const CBFProtocol& src)
	{
		*this = src;
	}

	//------------------------------------------------------------------------------
	CBFProtocol& CBFProtocol::operator = ( const CBFProtocol& src )
	{
		if( &src != this )
		{
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	void CBFProtocol::SetOutPipe( CBFPipeline* pOutPipe )
	{
		m_pOutPipe = pOutPipe;
	}

	//------------------------------------------------------------------------------
	CBFPipeline* CBFProtocol::GetOutPipe( void )
	{
		return m_pOutPipe;
	}

	//------------------------------------------------------------------------------
	void CBFProtocol::SetInPipe( CBFPipeline* pInPipe )
	{
		m_pInPipe = pInPipe;
	}

	//------------------------------------------------------------------------------
	CBFPipeline* CBFProtocol::GetInPipe( void )
	{
		return m_pInPipe;
	}

	//------------------------------------------------------------------------------
	void CBFProtocol::Run( void )
	{
		while( OnProtocolStateChange() )
		{
		}
	}

	//------------------------------------------------------------------------------
	bool CBFProtocol::OnProtocolStateChange( void )
	{
		bool bResult = ( m_eState != m_eNextState );

		m_eState = m_eNextState;

		switch( m_eNextState )
		{
		case Stopped:
			break;
		case Reading:
			bResult = Read();
			break;
		case Writing:
			bResult = Write();
			break;
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::GetNextReadCount( void )
	{
		//_WINQ_FCONTEXT( "CIOProtocol::GetNextReadCount" );
		m_ulDataSize = 0;
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::GetNextWriteCount( void )
	{
		//_WINQ_FCONTEXT( "CIOProtocol::GetNextWriteCount" );
		m_ulDataSize = 0;
	}

	//--------------------------------------------------------------------------------
	bool CBFProtocol::Read()
	{
		//_WINQ_FCONTEXT( "CIOProtocol::Read" );
		bool bResult = false;
		GetNextReadCount();
		if( m_ulDataSize > 0 )
		{
			unsigned long ulNumberOfUnitsPumped = 0;
			bResult = m_pInPipe->Pump( m_ulDataSize, ulNumberOfUnitsPumped );
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CBFProtocol::Write()
	{
		bool bResult = false;
		GetNextWriteCount();
		if( m_ulDataSize > 0 )
		{
			unsigned long ulWritten = 0;
			bResult = m_pOutPipe->Pump( m_ulDataSize, ulWritten );
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnConnectionError( void )
	{
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnConnected( void )
	{
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnDisconnectionError( void )
	{
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnDisconnected( void )
	{
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnReadSuccess( unsigned long ulUnitsRead )
	{
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnReadError( void )
	{
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnWriteSuccess( void )
	{
	}

	//--------------------------------------------------------------------------------
	void CBFProtocol::OnWriteError( void )
	{
	}

}//nsBluefoot

