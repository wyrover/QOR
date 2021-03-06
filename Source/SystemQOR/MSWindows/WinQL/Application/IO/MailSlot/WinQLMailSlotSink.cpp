//WinQLMailSlotSink.cpp

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

#include "WinQL/Application/IO/MailSlot/WinQLMailSlotSink.h"
#include "WinQL/Application/IO/MailSlot/WinQLMailSlotConnector.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	__QOR_IMPLEMENT_OCLASS_LUID( CMailSlotSink );

	//--------------------------------------------------------------------------------
	CMailSlotSink::CMailSlotSink(  CMailSlotConnector* pPipeConnector ) : CIOSink( pPipeConnector )
	{
		_WINQ_FCONTEXT( "CMailSlotSink::CMailSlotSink" );
	}

	//--------------------------------------------------------------------------------
	CMailSlotSink::~CMailSlotSink()
	{
		_WINQ_FCONTEXT( "CMailSlotSink::~CMailSlotSink" );
	}

	//--------------------------------------------------------------------------------
	bool CMailSlotSink::Write( unsigned long& ulNumberOfBytesWritten, unsigned long ulNumberOfBytesToWrite )
	{
		_WINQ_FCONTEXT( "CMailSlotSink::Write" );
		bool bResult = false;
		CMailSlotConnector* pMailSlotConnector = dynamic_cast< CMailSlotConnector* >( m_pIOSinkConnector );
		if( pMailSlotConnector )
		{			
			if( pMailSlotConnector->AsyncConnection() )
			{
				byte* pBuffer = GetSource()->GetBuffer()->ReadRequest( ulNumberOfBytesToWrite );

				if( pBuffer )
				{
					unsigned long ulUnitSize = GetSource()->GetBuffer()->GetUnitSize();
					bResult = pMailSlotConnector->MailSlot().Write( (const void*)(pBuffer), ulNumberOfBytesToWrite * ulUnitSize, 
						reinterpret_cast< OVERLAPPED* >( pMailSlotConnector->GetSyncObject() ), (LPOVERLAPPED_COMPLETION_ROUTINE)(&COverlappedHandler::OnOverlappedWriteCompleted) );
				}
				ulNumberOfBytesWritten = 0;

				if( !bResult && pMailSlotConnector->Protocol() )
				{
					pMailSlotConnector->Protocol()->OnWriteError();
				}

			}
			else
			{
				byte* pBuffer = GetSource()->GetBuffer()->ReadRequest( ulNumberOfBytesToWrite );

				if( pBuffer )
				{
					unsigned long ulUnitSize = GetSource()->GetBuffer()->GetUnitSize();
					bResult = pMailSlotConnector->MailSlot().Write( (const void*)(pBuffer), ulNumberOfBytesToWrite * ulUnitSize, ulNumberOfBytesWritten, 0 );
					if( bResult && ( ulNumberOfBytesWritten > 0 ) )
					{
						ulNumberOfBytesWritten  /= m_pBuffer->GetUnitSize();
					}
					GetSource()->GetBuffer()->ReadAcknowledge( ulNumberOfBytesWritten );
				}

				if( pMailSlotConnector->Protocol() )
				{
					if( bResult )
					{
						pMailSlotConnector->Protocol()->OnWriteSuccess();
					}
					else
					{
						pMailSlotConnector->Protocol()->OnWriteError();
					}
				}
			}
		}
		return bResult;
	}

}//nsWin32


