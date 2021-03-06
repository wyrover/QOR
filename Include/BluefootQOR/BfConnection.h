//BfConnection.h

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

#ifndef BLUEFOOT_CONNECTION_H_3
#define BLUEFOOT_CONNECTION_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "BfSource.h"
#include "BfSink.h"
#include "BfPlug.h"

//--------------------------------------------------------------------------------
namespace nsBluefoot
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CBFConnectionPool;

	//--------------------------------------------------------------------------------
	template< class TPlug, class TSource, class TSink >
	class CTBFConnection : public TPlug
	{
	public:

		typedef TPlug plugType;
		typedef TSource sourceType;
		typedef TSink sinkType;

		//--------------------------------------------------------------------------------
		CTBFConnection( CBFConnectionPool* pPool = 0 ) : TPlug( pPool )
		,	m_Source( this )
		,	m_Sink( this )
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CTBFConnection()
		{
		}

		//Connection interface
		//--------------------------------------------------------------------------------
		virtual CBFSource* GetSource( void )
		{
			return &m_Source;
		}

		//--------------------------------------------------------------------------------
		virtual CBFSink* GetSink( void )
		{
			return &m_Sink;
		}

		//--------------------------------------------------------------------------------
		virtual bool CanRead( void ) const
		{
			return false;
		}

		//--------------------------------------------------------------------------------
		virtual bool CanWrite( void ) const
		{
			return false;
		}

		//--------------------------------------------------------------------------------
		virtual const bool AsyncConnection( void ) const
		{
			return false;
		}

	protected:

		TSource m_Source;
		TSink m_Sink;
	};


	//--------------------------------------------------------------------------------
	//Adds read capability to a Connection by attaching a Source
	template< class TPlug, class TSource >
	class CTBFReadOnlyConnection : public CTBFConnection< TPlug, TSource, CNULLSink >
	{
	public:

		//--------------------------------------------------------------------------------
		CTBFReadOnlyConnection( CBFConnectionPool* pPool = 0 ) : CTBFConnection< TPlug, TSource, CNULLSink >( pPool )
		{			
		}

		//--------------------------------------------------------------------------------
		virtual ~CTBFReadOnlyConnection()
		{
		}

		//--------------------------------------------------------------------------------
		virtual bool CanRead( void ) const
		{
			return true;
		}
	};

	//--------------------------------------------------------------------------------
	template< class TPlug, class TSink >
	class CTBFWriteOnlyConnection : public CTBFConnection< TPlug, CNULLSource, TSink >
	{
	public:

		//--------------------------------------------------------------------------------
		CTBFWriteOnlyConnection( CBFConnectionPool* pPool = 0 ) : CTBFConnection< TPlug, CNULLSource, TSink >( pPool )
		{			
		}

		//--------------------------------------------------------------------------------
		virtual ~CTBFWriteOnlyConnection()
		{
		}

		//--------------------------------------------------------------------------------
		virtual bool CanWrite( void ) const
		{
			return true;
		}
	};

	//--------------------------------------------------------------------------------
	//A Read|Write connection add Source and Sink to a base CBFPlug
	template< class TPlug, class TSource, class TSink >
	class CTBFReadWriteConnection : public CTBFConnection< TPlug, TSource, TSink >
	{
	public:

		//--------------------------------------------------------------------------------
		CTBFReadWriteConnection( CBFConnectionPool* pPool = 0 ) : CTBFConnection< TPlug, TSource, TSink >( pPool )
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CTBFReadWriteConnection()
		{
		}

		//--------------------------------------------------------------------------------
		virtual bool CanRead( void ) const
		{
			return true;
		}

		//--------------------------------------------------------------------------------
		virtual bool CanWrite( void ) const
		{
			return true;
		}
	};

	//--------------------------------------------------------------------------------
	//CRTP wrapper which turns a TConnection into an Asynchronous Connection which 
	//will be called back when Read or Writes complete
	template< class TConnection, class TAsyncHandler >
	class CBFAsyncConnection : public TConnection, public TAsyncHandler
	{
		friend TAsyncHandler;

	public:

		//--------------------------------------------------------------------------------
		CBFAsyncConnection( CBFConnectionPool* pPool = 0 ) : TConnection( pPool )
		{		
			SetSyncObject( &m_Overlapped );															//Use the internal SyncObject by default. This may get changed by Server/Connection Manager		
		}

		//--------------------------------------------------------------------------------
		virtual ~CBFAsyncConnection()
		{			
		}

		//--------------------------------------------------------------------------------
		virtual void OnConnected( void )
		{
			_WINQ_FCONTEXT( "CBFAsyncConnection::OnConnected" );
			TConnection::SetSyncObject( &m_Overlapped );											//Once connected always use the internal SyncObject for IO
			TConnection::OnConnected();
		}

		//--------------------------------------------------------------------------------
		virtual const bool AsyncConnection( void ) const
		{
			return true;
		}

	protected:

		//--------------------------------------------------------------------------------
		virtual void OnWriteCompleted( unsigned long ulError, unsigned long ulCountBytesWritten )
		{	
			if( ulError == 0 )
			{
				CBFSink* pSink = GetSink();
				if( pSink )
				{
					pSink->OnWriteSuccess();
				}
			}

			if( Protocol() )
			{
				if( ulError == 0 )
				{
					Protocol()->OnWriteSuccess();
				}
				else
				{
					Protocol()->OnWriteError();
				}
			}
		}
			
		//--------------------------------------------------------------------------------
		virtual void OnReadCompleted( unsigned long ulError, unsigned long ulCountBytesRead )
		{
			if( ulError == 0 )
			{
				CBFSource* pSource = GetSource();
				if( pSource )
				{
					pSource->OnReadSuccess( ulCountBytesRead );
				}
			}

			if( Protocol() )
			{
				if( ulError == 0 )
				{
					Protocol()->OnReadSuccess( ulCountBytesRead );
				}
				else
				{
					Protocol()->OnReadError();
				}
			}
		}
	};

}//nsBluefoot

#endif//BLUEFOOT_CONNECTION_H_3
