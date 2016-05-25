//UTF16String.cpp

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

#include "CompilerQOR.h"
#include "CodeQOR/Text/UTF8String.h"
#include "CodeQOR/Text/UTF16String.h"
#include "CodeQOR/Text/UTF32String.h"

//------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	CUTF16Char CUTF16String::begin( void )
	{
		CUTF16Char it( m_String.GetBuffer() );
		m_String.ReleaseBuffer();
		return it;
	}

	//--------------------------------------------------------------------------------
	CUTF16Char CUTF16String::end( void )
	{
		CUTF16Char it( m_String.GetBuffer() + m_String.Len() );
		m_String.ReleaseBuffer();
		return it;
	}

	//--------------------------------------------------------------------------------
	void CUTF16String::CountChars()
	{
		m_bEncodingValidated = false;
		CUTF16Char it = begin();
		while( ++it != end() && !it.IsInvalid() )
		{
			m_usCharCount++;
		}
		if( !it.IsInvalid() )
		{
			m_bEncodingValidated = true;
		}
	}

	//--------------------------------------------------------------------------------
	CUTF16Char CUTF16String::CharAt( unsigned short usPos )
	{
		CUTF16Char Ch( m_String.GetBuffer() );
		m_String.ReleaseBuffer();
		while( usPos-- )
		{
			++Ch;
		}
		return Ch;
	}

    //--------------------------------------------------------------------------------
    CUTF16String::CUTF16String() : m_String()
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		m_usCharCount = 0;
		m_bEncodingValidated = true;
    }

	//--------------------------------------------------------------------------------
    CUTF16String::CUTF16String( const CChar16* cpString, unsigned short usSrcLen ) : m_String( cpString, usSrcLen )
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
    }

    //--------------------------------------------------------------------------------
    CUTF16String::CUTF16String( const CChar16* cpString, unsigned short usSrcLen, unsigned short usInitialBufferSize ) : m_String( cpString, usSrcLen, usInitialBufferSize )
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
    }

	//--------------------------------------------------------------------------------
	CUTF16String::CUTF16String( const CUTF16String& Src ) : m_String( Src.m_String ), m_usCharCount( Src.m_usCharCount ), m_bEncodingValidated( Src.m_bEncodingValidated )
	{
	}

	//--------------------------------------------------------------------------------
	CUTF16String::CUTF16String( const CUTF8String& Src )
	{
	}

	//--------------------------------------------------------------------------------
	CUTF16String::CUTF16String( const CUTF32String& Src )
	{
	}

    //--------------------------------------------------------------------------------
    CUTF16String::CUTF16String( nsCodeQOR::CTLRef< CChar16 > Src ) : m_String( Src )
    {
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
    }

	//--------------------------------------------------------------------------------
	CUTF16String::CUTF16String( CChar16 c ) : m_String( c )
	{
		m_String.SetCodePage( CCodePage::eUTF8 );
		CountChars();
	}

	//--------------------------------------------------------------------------------
	CUTF16String::CUTF16String( CTString< CChar16, CDefaultSource >::ref_type Src ) : m_String( Src )
	{
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF16String() );
		}
	}

    //--------------------------------------------------------------------------------
    CUTF16String::CUTF16String( const CTString< CChar16, CDefaultSource >& Src ) : m_String( Src )
    {
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF16String() );
		}
    }

	//--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::operator = ( const CUTF16String& Src )
	{
		if( &Src != this )
		{
			m_String = Src.m_String;
			m_usCharCount = Src.m_usCharCount;
			m_bEncodingValidated = Src.m_bEncodingValidated;
		}
		return *this;
	}

    //--------------------------------------------------------------------------------
    CUTF16String& CUTF16String::operator = ( const CTString< CChar16, CDefaultSource >& Src )
    {
		m_String = Src;
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF16String() );
		}
        return *this;
    }

	//--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::operator = ( CTString< CChar16, CDefaultSource >::ref_type Src )
	{
		m_String = Src;
		if( GetCodePage() != CCodePage::eUTF8 )
		{
			operator = ( CUTF32String( *this ).ToUTF16String() );
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::operator = ( CChar16 c )
	{
		operator = ( CTString< CChar16, CDefaultSource >( c ) );
		CountChars();
		return *this;
	}
		
	//--------------------------------------------------------------------------------
	unsigned short CUTF16String::GetCodePage() const
	{
		return m_String.GetCodePage();
	}

    //--------------------------------------------------------------------------------
	//Returns UTF-16 character count
    unsigned short CUTF16String::Length() const
    {
		return m_usCharCount;
    }

	//--------------------------------------------------------------------------------
	bool CUTF16String::IsEmpty( void ) const
	{
		return m_String.IsEmpty();
	}

    //--------------------------------------------------------------------------------
    //Two Strings are equal if they contain equal data
    bool CUTF16String::operator == ( const CTString< CChar16, CDefaultSource >& Src ) const
    {
		return m_String == Src;
    }

    //--------------------------------------------------------------------------------
    bool CUTF16String::operator < ( const CTString< CChar16, CDefaultSource >& Cmp ) const
    {
		return m_String < Cmp;
    }

    //--------------------------------------------------------------------------------
    CUTF16String::~CUTF16String()
    {
    }

	//--------------------------------------------------------------------------------
	CUTF16Char CUTF16String::At( unsigned short usPos )
	{
		CUTF16Char it = begin();
		it += usPos;
		return it;
	}

	//--------------------------------------------------------------------------------
	bool CUTF16String::ValidateReference( CUTF16Char Ch )
	{
		if( Ch.IsNull() )
		{
			return false;
		}

		CChar16* pBuffer = m_String.GetBuffer();
		bool bResult = ( Ch.ptr() >= pBuffer && Ch.ptr() < ( pBuffer + m_String.Len() ) && !Ch.IsInvalid() );
		m_String.ReleaseBuffer();
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CUTF16String::Set( unsigned short usPos, CUTF16Char ch )
	{
		bool bResult = false;
		CUTF16Char Ref = CharAt( usPos );
		if( ValidateReference( Ref ) )
		{
			short sShift = Ref.Len() - ch.Len();

			if( sShift > 0 )
			{
				m_String.Remove( static_cast< unsigned short >( Ref.ptr() - m_String.GetBuffer() ), sShift );	
				m_String.ReleaseBuffer();
			}		
			else if( sShift < 0 )
			{
				CUTF16String strInsert( const_cast< CChar16* >( ch.ptr() ), static_cast< unsigned short >( 0 - sShift ) );
			}
			memcpy( Ref.ptr(), ch.ptr(), Ref.Len() - sShift );
			bResult = true;
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::Insert(  unsigned short usPos, CUTF16String& Src )
	{
		if( usPos > m_usCharCount )
		{
			usPos = m_usCharCount;
		}
		CUTF16Char Ref = CharAt( usPos );
		m_String.Insert( static_cast< unsigned short >( Ref.ptr() - m_String.GetBuffer() ), Src.m_String );
		m_String.ReleaseBuffer();
		CountChars();
		return *this;
	}

	//--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::Remove( unsigned short usPos, unsigned short usCount )
	{
		CUTF16Char Begin = CharAt( usPos );
		CUTF16Char End = CharAt( usPos + usCount );

		m_String.Remove( static_cast< unsigned short >( Begin.ptr() - m_String.GetBuffer() ), static_cast< unsigned short >( End.ptr() - Begin.ptr() ) );
		m_String.ReleaseBuffer();
		CountChars();
		return *this;
	}

	//--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::Clear( void )
	{
		m_String.Clear();
		m_usCharCount = 0;
		m_bEncodingValidated = true;
		return *this;
	}

    //--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::Append( CChar16 ch )
	{
		return Append( const_cast< const CChar16* >( &ch ), 1 );
	}

	//--------------------------------------------------------------------------------
    CUTF16String& CUTF16String::Append( const CChar16* cpString, unsigned short usSrcLen )
    {
		m_String.Append( cpString, usSrcLen );
		CountChars();
        return *this;
    }

	//--------------------------------------------------------------------------------
	CUTF16String& CUTF16String::Append( const CUTF16String& Str )
	{
		return Append( Str.m_String, Str.m_String.Len() );
	}

	//--------------------------------------------------------------------------------
	CUTF16String CUTF16String::Left( unsigned short usLen )
	{
		CUTF16Char Pos = CharAt( usLen );
		CUTF16String Result( m_String.Left( static_cast< unsigned short >( Pos.ptr() - m_String.GetBuffer() ) ) );
		m_String.ReleaseBuffer();
		return Result;
	}

	//--------------------------------------------------------------------------------
	CUTF16String CUTF16String::Right( unsigned short usLen )
	{
		CUTF16Char Pos = CharAt( m_usCharCount - usLen );
		CUTF16Char End = --end();
		return CUTF16String( m_String.Right( static_cast< unsigned short >( End.ptr() - Pos.ptr() ) ) );
	}

	//--------------------------------------------------------------------------------
	CUTF16String CUTF16String::Mid( unsigned short usPos, short usLen )
	{
		CUTF16Char Begin = CharAt( usPos );
		CUTF16Char End( Begin );
		End += usLen;
		return CUTF16String( m_String.Mid( static_cast< unsigned short >( Begin.ptr() - m_String.GetBuffer() ), static_cast< unsigned short >( End.ptr() - Begin.ptr() ) ) );
	}

	//--------------------------------------------------------------------------------
	CUTF16String CUTF16String::TrimLeft()
	{
		CTrimLeftFunctor F;
		return ProcessByChar( F, 0 );
	}

	//--------------------------------------------------------------------------------
	CUTF16String CUTF16String::TrimRight()
	{		
		CTrimRightFunctor F;
		return ReverseProcessByChar( F, m_usCharCount );
	}


	//--------------------------------------------------------------------------------
	//Process the string through a functor one character at a time
	CUTF16String CUTF16String::ProcessByChar( CCharProcessorFunctor& ProcessFunctor, unsigned short usPos )
	{
		CUTF16String strResult;
		CUTF16Char Pos = CharAt( usPos );
		while( Pos.ptr() != end() && ProcessFunctor( strResult, Pos ) == eProcessResultMore )
		{
			++Pos;
		}
		return strResult;
	}

	//--------------------------------------------------------------------------------
	//Process the string through a functor one character at a time in reverse
	CUTF16String CUTF16String::ReverseProcessByChar( CCharProcessorFunctor& ProcessFunctor, unsigned short usPos )
	{
		CUTF16String strResult;
		CUTF16Char Pos = CharAt( usPos );
		while( Pos.ptr() >= begin() && ProcessFunctor( strResult, Pos ) == eProcessResultMore )
		{
			--Pos;
		}
		return strResult;
	}

	//--------------------------------------------------------------------------------
	//Process the string through a functor to find the beginning and end of substrings and then process each substring through a second functor
	//This can be used as the basis for tokenizing a string, the beginning of language parsing.
	void CUTF16String::ProcessForSubString( CCharProcessorFunctor& CharFunctor, CStringProcessorFunctor& StringFunctor, unsigned short usPos )
	{
		CUTF16String strResult;
		CUTF16Char Pos = CharAt( usPos );
		do
		{				
			strResult.Clear();
			while( Pos.ptr() != end() && CharFunctor( strResult, Pos ) != eProcessResultBegin )
			{
				++Pos;
			}
			
			while( Pos.ptr() != end() && CharFunctor( strResult, Pos ) == eProcessResultMore )
			{
			}
		}while( StringFunctor( strResult ) != eProcessResultEnd );
	}

	//--------------------------------------------------------------------------------
	//Reserve memory for the string in advance if you plan to make many small appends
	void CUTF16String::Reserve( unsigned short usCharCount )
	{
		m_String.Reserve( usCharCount * eUTF16MaxBytes );
	}

	//--------------------------------------------------------------------------------
	unsigned short CUTF16String::BufferByteCount( void )
	{
		return m_String.Len();
	}

	//--------------------------------------------------------------------------------
	CUTF32String CUTF16String::ToUTF32String( void )
	{
		return CUTF32String( *this );
	}

	//--------------------------------------------------------------------------------
	CUTF8String CUTF16String::ToUTF8String( void )
	{
		return CUTF8String( *this );
	}

}//nsCodeQOR
