//AppCommandQueue.h

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

//Application level Command Queue

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#ifndef APPOCRITAQOR_EXECUTIVE_COMMANDQUEUE_H_3
#define APPOCRITAQOR_EXECUTIVE_COMMANDQUEUE_H_3

#include "CompilerQOR.h"
#include <deque>
#include "CodeQOR/Macros/ClassIdentityMacros.h"
#include "CodeQOR/DataStructures/TLRef.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "AppocritaQOR/Executive/AppCommand.h"

//------------------------------------------------------------------------------
namespace nsAppocrita
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __APPOCRITA ) CCommandQueue
	{
	public:

		typedef nsCodeQOR::CTLRef< CCommandQueue > refType;

		__QOR_DECLARE_OCLASS_ID( CCommandQueue );

		CCommandQueue();
		virtual ~CCommandQueue();

		//------------------------------------------------------------------------------
		refType Ref( void )
		{
			return refType( this );
		}

		void PostCommand( CCommand::refType Command );
		CCommand::refType GetCommand( void );
		std::deque< CCommand::refType >::size_type GetQueueLength( void );
		
		unsigned int GetPriority( void );
		void SetPriority( unsigned int uiPriority );

	private:

		//TODO: Need a generic synchronization mechanism to protected the QueueData
		//This will probably end up being a Posum Mutex or Posum Critical Section

		std::deque< CCommand::refType > m_QueueData;
		unsigned int m_uiPriority;													// 1 - highest to 1000 lowest

		CCommandQueue( const CCommand& src );
		CCommandQueue& operator = ( const CCommandQueue& src );

	};

}//nsAppocrita

#endif//APPOCRITAQOR_EXECUTIVE_COMMAND_H_3