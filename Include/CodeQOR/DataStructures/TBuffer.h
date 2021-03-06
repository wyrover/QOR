//TBuffer.h

// Copyright Querysoft Limited 2015
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

//Simple buffer template
//NOTE: Should not be used, deprecated in favour of std::vector

#ifndef CODEQOR_DATASTRUCTS_TBUFFER_H_1
#define CODEQOR_DATASTRUCTS_TBUFFER_H_1

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Traits/MemoryTraits.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
    //--------------------------------------------------------------------------------
    //A template for simple buffers, buffers of homogeneous POD types
    template< typename _t >
    class CTBuffer
    {
    public:

		//--------------------------------------------------------------------------------
		//A cursor for referencing buffer elements
		class CCursor
		{
			friend class CTBuffer< _t >;

		public:

			//--------------------------------------------------------------------------------
			CCursor( CTBuffer& Buffer ) : m_Buffer( Buffer ), m_ulIndex( 0 )
			{
			}

			//--------------------------------------------------------------------------------
			explicit CCursor( CTBuffer& Buffer, unsigned long ulIndex ) : m_Buffer( Buffer ), m_ulIndex( ulIndex )
			{
			}

			//--------------------------------------------------------------------------------
			CCursor( const CCursor& src ) : m_Buffer( src.m_Buffer ), m_ulIndex( src.m_ulIndex )
			{
			}

			//--------------------------------------------------------------------------------
			~CCursor()
			{
			}

			//--------------------------------------------------------------------------------
			CCursor& operator = ( const CCursor& src )
			{
				m_ulIndex = src.m_ulIndex;
				return *this;
			}

			//--------------------------------------------------------------------------------
			CCursor& operator += ( const CCursor& src )
			{
				m_ulIndex += src.m_ulIndex;
				return *this;
			}

			//--------------------------------------------------------------------------------
			CCursor& operator -= ( const CCursor& src )
			{
				m_ulIndex -= src.m_ulIndex;
				return *this;
			}

			//--------------------------------------------------------------------------------
			CCursor& operator ++ ( void )
			{
				m_ulIndex++;
				return *this;
			}

			//--------------------------------------------------------------------------------
			CCursor& operator -- ( void )
			{
				m_ulIndex--;
				return this;
			}

			//--------------------------------------------------------------------------------
			bool operator > ( const CCursor& cmp )
			{
				return ( m_ulIndex > cmp.m_ulIndex ) ? true : false;
			}

			//--------------------------------------------------------------------------------
			bool operator < ( const CCursor& cmp )
			{
				return ( m_ulIndex < cmp.m_ulIndex ) ? true : false;
			}

			//--------------------------------------------------------------------------------
			bool operator == ( const CCursor& cmp )
			{
				return ( ( cmp.m_Buffer.GetBuffer() == m_Buffer.GetBuffer() ) && ( cmp.m_ulIndex == m_ulIndex ) );
			}

			//--------------------------------------------------------------------------------
			bool operator != ( const CCursor& cmp )
			{
				return ( ( cmp.m_Buffer.GetBuffer() != m_Buffer.GetBuffer() ) || ( cmp.m_ulIndex != m_ulIndex ) );
			}

			//--------------------------------------------------------------------------------
			bool operator >= ( const CCursor& cmp )
			{
				return ( m_ulIndex >= cmp.m_ulIndex ) ? true : false;
			}

			//--------------------------------------------------------------------------------
			_t& operator *( void )
			{
				return m_Buffer[ m_ulIndex ];
			}

			//--------------------------------------------------------------------------------
			_t* operator ->( void )
			{
				return &m_Buffer[ m_ulIndex ];
			}

			//--------------------------------------------------------------------------------
			unsigned long Index( void )
			{
				return m_ulIndex;
			}

		protected:

			//--------------------------------------------------------------------------------
			void SetIndex( unsigned long ulIndex )
			{
				m_ulIndex = ulIndex;
			}

			CTBuffer& m_Buffer;
			unsigned long m_ulIndex;
			
		};



        //--------------------------------------------------------------------------------
        CTBuffer()
        {
            m_p = 0;
            m_uiAllocLen = 0;
            m_uiValid = 0;
        }

        //--------------------------------------------------------------------------------
        CTBuffer( const _t* cpData, unsigned int uiSrcLen )
        {
                m_p = 0;
                m_uiAllocLen = 0;
                m_uiValid = 0;
                SetSize( uiSrcLen );
                WriteBuffer( cpData, uiSrcLen );
        }

        //--------------------------------------------------------------------------------
        CTBuffer( const _t* cpData, unsigned int uiSrcLen, unsigned int uiInitialBufferSize )
        {
            m_p = 0;
            m_uiAllocLen = uiInitialBufferSize;
            m_uiValid = 0;
            if( uiSrcLen > m_uiAllocLen )
            {
				m_uiAllocLen = uiSrcLen;
            }
            SetSize( m_uiAllocLen );
            WriteBuffer( cpData, uiSrcLen );
        }

        //--------------------------------------------------------------------------------
        CTBuffer( const CTBuffer< _t >& Src )
        {
            m_p = 0;
            m_uiAllocLen = 0;
            m_uiValid = 0;
            SetSize( Src.Len() );
            WriteBuffer( Src.GetBuffer(), Src.Len() );
        }

        //--------------------------------------------------------------------------------
        CTBuffer& operator = ( const CTBuffer< _t >& Src )
        {
            SetSize( Src.Len() );
            WriteBuffer( Src.m_p, Src.Len() );
            return *this;
        }

        //--------------------------------------------------------------------------------
        unsigned int Len() const
        {
			return m_uiValid;
        }

        //--------------------------------------------------------------------------------
        //Two TBuffers are equal if they contain equal data
        bool operator == ( const CTBuffer< _t >& Src ) const
        {
            bool bResult = ( m_uiValid == Src.m_uiValid ) ? true : false;
            unsigned int uiCounter = 0;
            while( bResult == true && uiCounter < m_uiValid && uiCounter < Src.m_uiValid )
            {
                if( m_p[ uiCounter ] != Src.m_p[ uiCounter ] )
                {
					bResult = false;
					break;
                }
                uiCounter++;
            }
            return bResult;
        }

        //--------------------------------------------------------------------------------
        bool operator < ( const CTBuffer< _t >& Src ) const
        {
            bool bResult = false;
            unsigned int uiCounter = 0;
            unsigned int uiValid = m_uiValid;
            if( Src.m_uiValid < uiValid )
	        {
                uiValid = Src.m_uiValid;
            }
            while( bResult == false && uiCounter < uiValid && m_p[ uiCounter ] <= Src.m_p[ uiCounter ] )
            {
                if( m_p[ uiCounter ] < Src.m_p[ uiCounter ] )
                {
					bResult = true;
                }
                uiCounter++;
            }
            if( bResult == false && uiCounter >= uiValid && m_uiValid < Src.m_uiValid )
            {
                bResult = true;
            }
            return bResult;
        }

        //--------------------------------------------------------------------------------
        virtual ~CTBuffer()
        {
            Free();
        }

        //--------------------------------------------------------------------------------
        CTLRef< _t > operator()( void )
        {
            CTLRef< _t > ref( m_p, false );
            return ref;
        }

		//--------------------------------------------------------------------------------
		_t& operator [] ( unsigned long ulIndex )
		{
			if( ulIndex >= m_uiValid )
			{
				//throw "range_error";
				abort();
			}
			else
			{
				return m_p[ ulIndex ];
			}
		}

        //--------------------------------------------------------------------------------
        //The caller is responsible for freeing the returned pointer which is detached
        _t* Detach( void )
        {
            _t* p = m_p;
            m_p = 0;
            m_uiAllocLen = 0;
            m_uiValid = 0;
            return p;
        }

        //--------------------------------------------------------------------------------
        CTBuffer& Append( const _t* cpData, unsigned int uiSrcLen )
        {
            _t* pData = const_cast< _t* >( cpData );                    
            unsigned int uiCounter = 0;
            while( uiCounter < uiSrcLen && m_uiValid < m_uiAllocLen )
            {
				m_p[ m_uiValid++ ] = cpData[ uiCounter++ ];
            }
            return *this;
        }

        //--------------------------------------------------------------------------------
        bool ValidateBuffer( unsigned int uiSize )
        {
            bool bResult = false;
            if( uiSize <= m_uiAllocLen )
            {
                m_uiValid = uiSize;
                bResult = true;
            }
            return bResult;
        }

        //--------------------------------------------------------------------------------
        _t* GetBufferSetLength( unsigned int uiSize )
        {
            SetSize( uiSize );
			ValidateBuffer( uiSize );
            return m_p;
        }

        //--------------------------------------------------------------------------------
        _t* GetBuffer() const
        {
            return m_p;
        }

        //--------------------------------------------------------------------------------
		CCursor begin( void )
		{
			return CCursor( *this, 0 );
		}

		//--------------------------------------------------------------------------------
		CCursor end( void )
		{
			return CCursor( *this, m_uiValid ) ;
		}

		//--------------------------------------------------------------------------------
		unsigned int Capacity( void )
		{
			return m_uiAllocLen;
		}

    protected:

        _t* m_p;
        unsigned int m_uiAllocLen;
        unsigned int m_uiValid;                 

        
        //--------------------------------------------------------------------------------
        void WriteBuffer( const _t* cpData, unsigned int uiSrcLen )
        {
            unsigned int uiCounter = 0;
            while( uiCounter < uiSrcLen && m_uiValid < m_uiAllocLen )
            {
				m_p[ m_uiValid++ ] = cpData[ uiCounter++ ];
            }
        }

        //--------------------------------------------------------------------------------
        void Free()
        {
			if( m_p != 0 )
			{
				mem_traits< _t >::CTAllocator::Free( m_p, m_uiAllocLen );//delete [] m_p;
				m_p = 0;
			}
        }

        //--------------------------------------------------------------------------------
        void SetSize( unsigned int uiSize )
        {
            Free();
            m_uiAllocLen = uiSize;
            m_uiValid = 0;
            m_p = mem_traits< _t >::CTAllocator::Allocate( uiSize );
        }

	};

	typedef CTBuffer< byte > CByteBuffer;

}//nsCodeQOR

#endif//CODEQOR_DATASTRUCTS_TBUFFER_H_1
