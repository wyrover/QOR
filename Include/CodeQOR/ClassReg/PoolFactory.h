//PoolFactory.h

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

//A class registry based factory for pool based allocation

#ifndef CODEQOR_POOLFACTORY_H_3
#define CODEQOR_POOLFACTORY_H_3

#include "CodeQOR/ClassReg/ClassReg.h"
#include "CodeQOR/Modules/ProcessBase.h"
#include "CodeQOR/Traits/MemoryTraits.h"

//------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	template< class T, class TPolicy >
	class CTPoolFactory : public CTClassRegEntry< T >
	{

	public:

		typedef typename TPolicy::TThreadSyncSinglePrimitive sectionType;

		//--------------------------------------------------------------------------------
		CTPoolFactory() : CTClassRegEntry()
		{
			m_uiCacheSize = 0;
		}

		//--------------------------------------------------------------------------------
		virtual ~CTPoolFactory()
		{
		}

		//--------------------------------------------------------------------------------
		T* Create( void )
		{
			return mem_traits< T >::CTAllocator::Allocate();
		}

		//--------------------------------------------------------------------------------
		virtual void Dispose( T* pT )
		{
			return mem_traits< T >::CTAllocator::Free( pT );
		}

		//--------------------------------------------------------------------------------
		void SetPoolTargetSize( unsigned int uiSize )
		{
			m_uiCacheSize = uiSize;
		}

		//--------------------------------------------------------------------------------
		virtual void* Instance( void )
		{
			T* pT = 0;
			TPolicy::TThreadSyncSingleLock Lock( m_Section );
			if( m_FreeList.GetCount() > 0 )
			{
				pT = m_FreeList.Dock();					
			}
			else if( m_uiInUse < m_uiCacheSize )
			{
				pT = Create();
			}
			else
			{
				return 0;
			}

			Use( pT );

			return pT;
		}

		//--------------------------------------------------------------------------------
		virtual void Release( void* pInstance )
		{
			T* pT = reinterpret_cast< T* >( pInstance );
			if( pT )
			{
				TPolicy::TThreadSyncSingleLock Lock( m_Section );
				Unuse( pT );
				if( m_FreeList.GetCount() + m_uiInUse > m_uiCacheSize )
				{
					Dispose( pT );
				}
				else
				{
					m_FreeList.Insert( 1, pT );
				}				
			}
		}

	protected:

		//--------------------------------------------------------------------------------
		void Use( T* pT )
		{
			m_InUseList.Append( pT );
			m_uiInUse++;
		}

		//--------------------------------------------------------------------------------
		void Unuse( T* pT )
		{
			unsigned long ulIndex = m_InUseList.Find( pT );
			m_InUseList.RemoveAt( ulIndex );
			m_uiInUse--;
		}

		nsCodeQOR::CTLinkedList< T > m_FreeList;
		nsCodeQOR::CTIndexedArray< T*, TPolicy > m_InUseList;
		unsigned int m_uiInUse;
		unsigned int m_uiCacheSize;		

	private:

		sectionType m_Section;

		CTPoolFactory( const CTPoolFactory& );
		CTPoolFactory& operator = ( const CTPoolFactory& );

	};

}//nsCodeQOR

#endif//CODEQOR_POOLFACTORY_H_3