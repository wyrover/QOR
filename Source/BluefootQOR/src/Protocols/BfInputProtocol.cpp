//BfInputProtocol.cpp

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

//Implementation of Bluefoot Input only bare streaming protocol class

#include "CompilerQOR.h"
#include "BluefootQOR/Protocols/BfInputProtocol.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	CBFInputProtocol::CBFInputProtocol() : CBFProtocol()
	{
	}

	//------------------------------------------------------------------------------
	CBFInputProtocol::~CBFInputProtocol()
	{
	}

	//------------------------------------------------------------------------------
	CBFInputProtocol::CBFInputProtocol( const CBFInputProtocol& src ) : CBFProtocol( src )
	{
	}

	//------------------------------------------------------------------------------
	CBFInputProtocol& CBFInputProtocol::operator = ( const CBFInputProtocol& src )
	{
		if( &src != this )
		{
			CBFProtocol::operator = ( src );
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	bool CBFInputProtocol::OnProtocolStateChange( void )
	{
		bool bResult = ( m_eState != m_eNextState );

		m_eState = m_eNextState;

		switch( m_eNextState )
		{
		case Stopped:
			bResult = false;
			break;
		case Reading:
			bResult = Read();
			break;
		case Writing:
			bResult = false;
			break;
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CBFInputProtocol::GetNextReadCount( void )
	{
		m_ulDataSize = 0;
	}

	//--------------------------------------------------------------------------------
	bool CBFInputProtocol::Read()
	{
		bool bResult = false;
		if( m_pInPipe )
		{
			unsigned long ulNumberOfUnitsPumped = 0;
			GetNextReadCount();
			if( m_ulDataSize > 0 )
			{				
				bResult = m_pInPipe->Pump( ulNumberOfUnitsPumped, m_ulDataSize );
			}
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CBFInputProtocol::OnConnectionError( void )
	{
		m_eNextState = Stopped;
	}

	//--------------------------------------------------------------------------------
	void CBFInputProtocol::OnConnected( void )
	{
		m_eNextState = Reading;
	}

	//--------------------------------------------------------------------------------
	void CBFInputProtocol::OnDisconnectionError( void )
	{
		m_eNextState = Stopped;
	}

	//--------------------------------------------------------------------------------
	void CBFInputProtocol::OnDisconnected( void )
	{
		m_eNextState = Stopped;
	}

	//--------------------------------------------------------------------------------
	void CBFInputProtocol::OnReadSuccess( unsigned long ulUnitsRead )
	{
		m_eNextState = Reading;
	}

	//--------------------------------------------------------------------------------
	void CBFInputProtocol::OnReadError( void )
	{
		m_eNextState = Stopped;
	}

}//nsBluefoot
