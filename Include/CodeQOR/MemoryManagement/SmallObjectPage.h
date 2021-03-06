//SmallObjectPage.h

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

// A scalable page for a SmallObjectBucket

#ifndef CODEQOR_MEMMAN_SMALLOBJECTPAGE_H_2
#define CODEQOR_MEMMAN_SMALLOBJECTPAGE_H_2

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __CODEQOR ) CSmallObjectPage
	{
	public:

		__QCMP_STATIC_CONSTANT( int, siWordBits = sizeof( Cmp_uint_ptr ) * 8 );	//The bits in a pointer sized word

		CSmallObjectPage( Cmp_uint_ptr uiUnitSize, Cmp_uint_ptr uiMapWordCount = 1 );
		CSmallObjectPage( const CSmallObjectPage& src );
		~CSmallObjectPage();

		void* Allocate( Cmp_uint_ptr uiUnitSize );								//Allocate uiUnitSize bytes in this page
		bool IsEmpty( void );													//Is this page empty
		bool Free( void* pElement, Cmp_uint_ptr uiUnitSize );					//Free the element with address pElement
		bool IsFull( void );													//Is this page full
		void Analyse( void(*pTrace)( char* ) );

		//--------------------------------------------------------------------------------
		byte* Memory( void ){ return m_pMemory; }

	protected:

		void Use( Cmp_uint_ptr uiWordIndex, Cmp_uint_ptr uiBitIndex );			//Mark bit as used
		void Deallocate( Cmp_uint_ptr uiWordIndex, Cmp_uint_ptr uiBitIndex );	//Mark bit as unused
		bool InUse( Cmp_uint_ptr uiWordIndex, Cmp_uint_ptr uiBitIndex );		//Check for usage in bit mask
			
		Cmp_uint_ptr* m_pMap;													//Bitwise map of allocation usage in this page
		byte* m_pMemory;														//Address of memory mapped by this page
		Cmp_uint_ptr m_uiMapWords;												//Number of words in the map
		Cmp_uint_ptr m_uiUnitSize;												//Max Size of allocation units

	private:
											
		CSmallObjectPage& operator = ( const CSmallObjectPage& src );			//Assignment is not implemented
	};

}//nsCodeQOR

#endif//CODEQOR_MEMMAN_SMALLOBJECTPAGE_H_2
