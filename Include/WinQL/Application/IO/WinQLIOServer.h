//WinQLIOServer.h

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

#ifndef WINQL_IO_SERVER_H_3
#define WINQL_IO_SERVER_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Data.h"
#include "WinQL/Application/ErrorSystem/WinQLErrorHandling.h"
#include "WinQL/Application/Threading/WinQLEvent.h"
#include "BluefootQOR/BfConnectionPool.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	//A generic single threaded server over any Async Read Write CBFPlug derived connections
	//Attach a connection pool to manage connections
	//Server is Asynchronous for connections and uses Async connectors
	//Run function is exclusive but not busy, i.e. it consumes 100% of 1 thread but not 100% of 1 core
	class __QOR_INTERFACE( __WINQL ) CIOServer
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CIOServer );

		CIOServer();
		virtual ~CIOServer();

		virtual void SetupConnection( nsBluefoot::CBFPlug::refPlugType& refConnector );		//override to set device specific properties for the Connector
		virtual nsBluefoot::CBFPlug::refPlugType CreateConnection( void );					//override to create new device specific pending client connections
		virtual bool OnListenResult( bool );												//override to custom process listen result 
		virtual bool Listen( void );														//override to customize Servers listen for new client connections
		virtual void Run( void );															//main loop
		virtual void Stop( void );															//call to break main loop on next event

		void SetConnectionPool( nsBluefoot::CBFConnectionPool::refType refConnectionPool );	//Attach a connection pool to allow the server to request new connections from a pool
		nsBluefoot::CBFConnectionPool::refType GetConnectionPool( void );

	protected:

		bool m_bStopping;																	//flag to break out of run loop
		CEvent m_ConnectEvent;																//Event for signalling connections
		OVERLAPPED m_Overlapped;															//Windows sync object for handling async connections
		CErrorHelper m_ErrorHelper;

		nsBluefoot::CBFPlug::refPlugType m_refPendingIOConnection;							//Precreated connection for the next client
		nsBluefoot::CBFConnectionPool::refType m_refConnectionPool;							//Connection pool from which to source connections
	};

}//nsWin32

#endif//WINQL_IO_SERVER_H_3
