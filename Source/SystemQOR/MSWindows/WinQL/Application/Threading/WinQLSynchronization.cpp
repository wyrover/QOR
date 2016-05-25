//WinQLSynchronization.cpp

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

#include "WinQL/Application/ErrorSystem/WinQLError.h"
#include "WinQL/Application/Threading/WinQLSynchronization.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;
		
	//--Interlocked Helper------------------------------------------------------------

	// {6209458F-09D3-4069-B758-3E1F36B0C247}
	__QOR_IMPLEMENT_OCLASS_GUID( CInterlockedHelper, 0x6209458f, 0x9d3, 0x4069, 0xb7, 0x58, 0x3e, 0x1f, 0x36, 0xb0, 0xc2, 0x47 )

	//--------------------------------------------------------------------------------
	CInterlockedHelper::CInterlockedHelper()
	{
		_WINQ_FCONTEXT( "CInterlockedHelper::CInterlockedHelper" );
	}

	//--------------------------------------------------------------------------------
	CInterlockedHelper::~CInterlockedHelper()
	{
		_WINQ_FCONTEXT( "CInterlockedHelper::~CInterlockedHelper" );
	}

	//--------------------------------------------------------------------------------		
	long CInterlockedHelper::Increment( long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::Increment" );
		return CKernel32::InterlockedIncrement( Addend );
	}

#ifndef __MINGW32__
	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::CompareExchange64( Cmp_long_long volatile* Destination, Cmp_long_long Exchange, Cmp_long_long Comperand )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::CompareExchange64" );
		return CKernel32::InterlockedCompareExchange64( Destination, Exchange, Comperand );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::CompareExchangeAcquire( long volatile* Destination, long Exchange, long Comperand )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::CompareExchangeAcquire" );
		return CKernel32::InterlockedCompareExchangeAcquire( Destination, Exchange, Comperand );
	}

	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::CompareExchangeAcquire64( Cmp_long_long volatile* Destination, Cmp_long_long Exchange, Cmp_long_long Comperand )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::CompareExchangeAcquire64" );
		return CKernel32::InterlockedCompareExchangeAcquire64( Destination, Exchange, Comperand );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::CompareExchangeRelease( long volatile* Destination, long Exchange, long Comperand )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::CompareExchangeRelease" );
		return CKernel32::InterlockedCompareExchangeRelease( Destination, Exchange, Comperand );
	}

	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::CompareExchangeRelease64( Cmp_long_long volatile* Destination, Cmp_long_long Exchange, Cmp_long_long Comperand )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::CompareExchangeRelease64" );
		return CKernel32::InterlockedCompareExchangeRelease64( Destination, Exchange, Comperand );
	}

	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::Decrement64( Cmp_long_long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::Decrement64" );
		return CKernel32::InterlockedDecrement64( Addend );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::DecrementAcquire( long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::DecrementAcquire" );
		return CKernel32::InterlockedDecrementAcquire( Addend );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::DecrementRelease( long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::DecrementRelease" );
		return CKernel32::InterlockedDecrementRelease( Addend );
	}

	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::Exchange64( Cmp_long_long volatile* Target, Cmp_long_long Value )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::Exchange64" );
		return CKernel32::InterlockedExchange64( Target, Value );
	}

	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::ExchangeAcquire64( Cmp_long_long volatile Target, Cmp_long_long Value )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::ExchangeAcquire64" );
		return CKernel32::InterlockedExchangeAcquire64( Target, Value );
	}

	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::ExchangeAdd64( Cmp_long_long volatile* Addend, Cmp_long_long Value )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::ExchangeAdd64" );
		return CKernel32::InterlockedExchangeAdd64( Addend, Value );
	}

	//--------------------------------------------------------------------------------
	Cmp_long_long CInterlockedHelper::Increment64( Cmp_long_long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::Increment64" );
		return CKernel32::InterlockedIncrement64( Addend );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::IncrementAcquire( long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::IncrementAcquire" );
		return CKernel32::InterlockedIncrementAcquire( Addend );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::IncrementRelease( long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::IncrementRelease" );
		return CKernel32::InterlockedIncrementRelease( Addend );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::CompareExchange( long volatile* Destination, long Exchange, long Comperand )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::CompareExchange" );
		return CKernel32::InterlockedCompareExchange( Destination, Exchange, Comperand );
	}

	//--------------------------------------------------------------------------------
	void* CInterlockedHelper::CompareExchangePointer( void* volatile* Destination, void* Exchange, void* Comperand )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::CompareExchangePointer" );
		return CKernel32::mxInterlockedCompareExchangePointer( Destination, Exchange, Comperand );
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::ExchangeAdd( long volatile* Addend, long Value )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::ExchangeAdd" );
		return CKernel32::InterlockedExchangeAdd( Addend, Value );
	}
#endif//!__MINGW32__
	//--------------------------------------------------------------------------------
	long CInterlockedHelper::Decrement( long volatile* Addend )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::Decrement" );
		LONG lResult = 0;
		__QOR_PROTECT
		{
			lResult = CKernel32::InterlockedDecrement( Addend );
		}__QOR_ENDPROTECT
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CInterlockedHelper::Exchange( long volatile* Target, long Value )
	{
		_WINQ_SFCONTEXT( "CInterlockedHelper::Exchange" );
		LONG lResult = 0;
		__QOR_PROTECT
		{
			lResult = CKernel32::InterlockedExchange( Target, Value );
		}__QOR_ENDPROTECT
		return lResult;
	}


	//--shared long

	//--------------------------------------------------------------------------------
	shared_long::shared_long() 
	{ 
		CKernel32::InterlockedExchange( &m, 0 ); 
	}

	//--------------------------------------------------------------------------------
	shared_long::shared_long( const shared_long& x ) 
	{ 
		CKernel32::InterlockedExchange( &m, x.m ); 
	}

	//--------------------------------------------------------------------------------
	shared_long::shared_long( long& x ) 
	{ 
		CKernel32::InterlockedExchange( &m, x ); 
	}	
		
	//--------------------------------------------------------------------------------
	shared_long::shared_long( const long x ) 
	{ 
		CKernel32::InterlockedExchange( &m, x ); 
	}
		
	//--------------------------------------------------------------------------------
	shared_long shared_long::operator+() const //unary plus
	{ 
		return *this; 
	}
		
	//--------------------------------------------------------------------------------
	shared_long shared_long::operator-() const //unary minus
	{ 
		volatile long s = 0;
		CKernel32::InterlockedExchange( &s, m );
		s = -s;
		return shared_long(s);
	}

	//--------------------------------------------------------------------------------
	void shared_long::operator= ( const shared_long&  x ) 
	{ 
		opAssign( x ); 
	}

	//--------------------------------------------------------------------------------
	void shared_long::operator= ( volatile const long& x ) 
	{
		opAssign( x ); 
	}

	//--------------------------------------------------------------------------------
	void shared_long::operator+= ( const shared_long& x ) 
	{ 
		opPlusAssign( x ); 
	}

	//--------------------------------------------------------------------------------
	void shared_long::operator-= ( const shared_long& x ) 
	{ 
		opMinusAssign( x ); 
	}

	//--------------------------------------------------------------------------------
	void shared_long::operator*= ( const shared_long& x ) 
	{ 
		opStarAssign( x ); 
	}

	//--------------------------------------------------------------------------------
	void shared_long::operator/= ( const shared_long& x ) 
	{ 
		opDivAssign( x ); 
	}

	//--------------------------------------------------------------------------------
	shared_long::operator volatile long&() 
	{ 
		return ToPrimitive(); 
	} 

	//--------------------------------------------------------------------------------
	void shared_long::operator %= ( const shared_long& x ) 
	{ 
		opModAssign( x ); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::opPreInc() 
	{ 
		return shared_long( CKernel32::InterlockedIncrement( &m ) ); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::opPreDec() 
	{ 
		return shared_long( CKernel32::InterlockedDecrement( &m ) ); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::opPostInc() 
	{ 
		return shared_long( CKernel32::InterlockedIncrement( &m ) ); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::opPostDec() 
	{ 
		return shared_long( CKernel32::InterlockedDecrement( &m ) ); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::operator++ () 
	{ 
		return opPostInc(); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::operator++ ( int ) 
	{ 
		return opPreInc(); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::operator-- () 
	{ 
		return opPostDec(); 
	}

	//--------------------------------------------------------------------------------
	shared_long shared_long::operator-- ( int ) 
	{ 
		return opPreDec(); 
	}

	//--------------------------------------------------------------------------------
	int shared_long::Compare( const shared_long& x ) const 
	{ 
		volatile long s1 = 0;
		volatile long s2 = 0;
		CKernel32::InterlockedExchange( &s1, m );
		CKernel32::InterlockedExchange( &s2, x.m );
		return ( s1 - s2 );
	}   

	//--------------------------------------------------------------------------------
	void shared_long::Reset()
	{ 
		CKernel32::InterlockedExchange( &m, 0 ); 
	}

	//non member operators - implemented in terms of member functions

	//--------------------------------------------------------------------------------
	shared_long operator % ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		shared_long ret( x0 );
		ret %= x1; return ret; 
	} 

	//--------------------------------------------------------------------------------
	shared_long operator + ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		shared_long ret( x0 );
		ret += x1;
		return ret; 
	} 

	//--------------------------------------------------------------------------------
	shared_long operator - ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		shared_long ret( x0 );
		ret -= x1;
		return ret; 
	} 

	//--------------------------------------------------------------------------------
	shared_long operator * ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		shared_long ret( x0 );
		ret *= x1;
		return ret;
	} 

	//--------------------------------------------------------------------------------
	shared_long operator / ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		shared_long ret( x0 );
		ret /= x1;
		return ret;
	} 

	//--------------------------------------------------------------------------------
	bool operator > ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		return x0.Compare( x1 ) > 0; 
	} 

	//--------------------------------------------------------------------------------
	bool operator < ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		return x0.Compare( x1 ) < 0; 
	} 

	//--------------------------------------------------------------------------------
	bool operator >= ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		return x0.Compare( x1 ) >= 0; 
	} 

	//--------------------------------------------------------------------------------
	bool operator <= ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		return x0.Compare( x1 ) <= 0; 
	} 

	//--------------------------------------------------------------------------------
	bool operator == ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		return x0.Compare( x1 ) == 0; 
	} 

	//--------------------------------------------------------------------------------
	bool operator != ( const shared_long& x0, const shared_long& x1 ) 
	{ 
		return x0.Compare( x1 ) != 0; 
	} 

	//protected:

	//--------------------------------------------------------------------------------
	void shared_long::opModAssign( const shared_long& x ) 
	{ 
		//equivalent of m %= x.m; m = ( m % x.m )
		volatile long s1 = 0;
		volatile long s2 = 0;
		CKernel32::InterlockedExchange( &s1, x.m );			
		CKernel32::InterlockedExchange( &s2, m );
		s2 %= s1;
		opAssign( s2 );			
	}

	//--------------------------------------------------------------------------------
	void shared_long::opAssign( const shared_long& x ) 
	{ 
		CKernel32::InterlockedExchange( &m, x.m ); 
	}

	//--------------------------------------------------------------------------------
	void shared_long::opAssign( const long& x ) 
	{ 
		CKernel32::InterlockedExchange( &m, x ); 
	}

	//--------------------------------------------------------------------------------
	void shared_long::opPlusAssign( const shared_long& x ) 
	{ 
		CKernel32::InterlockedExchangeAdd( &m, x.m );			
	}

	//--------------------------------------------------------------------------------
	void shared_long::opMinusAssign( const shared_long& x ) 
	{ 
		volatile long s1 = 0;
		volatile long s2 = 0;
		CKernel32::InterlockedExchange( &s1, x.m );
		s1 = -s1;
		CKernel32::InterlockedExchangeAdd( &m, s2 );//m -= x.m;
	}

	//--------------------------------------------------------------------------------
	void shared_long::opStarAssign( const shared_long& x ) 
	{ 
		volatile long s1 = 0;
		volatile long s2 = 0;
		CKernel32::InterlockedExchange( &s1, x.m );
		CKernel32::InterlockedExchange( &s2, m );
		s2 *= s1;
		CKernel32::InterlockedExchange( &m, s2 );//m *= x.m;
	}

	//--------------------------------------------------------------------------------
	void shared_long::opDivAssign( const shared_long& x ) 
	{ 
		volatile long s1 = 0;
		volatile long s2 = 0;
		CKernel32::InterlockedExchange( &s1, x.m );
		CKernel32::InterlockedExchange( &s2, m );
		s2 /= s1;
		CKernel32::InterlockedExchange( &m, s2 );//m /= x.m;
	}

	//--------------------------------------------------------------------------------
	volatile const long& shared_long::ToPrimitive() const 
	{ 
		return m; 
	}

	//--------------------------------------------------------------------------------
	volatile long& shared_long::ToPrimitive() 
	{ 
		return m; 
	}

}//nsWin32