//SEH.h

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

//Header for Structured Exception Support

#ifndef WINCMPSUPVC_EXCEPT_SEH_H_1
#define WINCMPSUPVC_EXCEPT_SEH_H_1

#include "SystemQOR.h"
#include "CodeQOR/ErrorSystem/IExceptionFrame.h"
#include "WinQL/Application/ErrorSystem/WinQLSEH.h"

extern __QCMP_NORETURN void RaiseException( const void* prec );

//--------------------------------------------------------------------------------
namespace nsCompiler
{
	//--------------------------------------------------------------------------------
	class CExceptionFrame : public nsCodeQOR::IExceptionFrame
	{
	public:

		//--------------------------------------------------------------------------------
		CExceptionFrame(void * Handler): m_pNext( reinterpret_cast< CExceptionFrame* >( GetCurrent() ) ), m_FrameHandler( Handler )
		{
		}	

		//--------------------------------------------------------------------------------
		inline CExceptionFrame* Next()
		{ 
			return m_pNext; 
		}

		//--------------------------------------------------------------------------------
		inline void* Handler() const
		{ 
			return m_FrameHandler; 
		}

		//--------------------------------------------------------------------------------
		inline void Remove()
		{ 
			this->m_pNext->SetCurrent(); 
		}

		static __QCMP_NORETURN void RaiseException( const void* prec );

		void __stdcall UnwindNestedFrames( nsWin32::EXCEPTION_RECORD* pExcept );

	private:

		CExceptionFrame* m_pNext;
		void* m_FrameHandler;

		// Not to be implemented
		CExceptionFrame( const CExceptionFrame& );
		CExceptionFrame& operator = ( const CExceptionFrame& );
	};

	//--------------------------------------------------------------------------------
	namespace SEH
	{
		extern const unsigned int EH_NONCONTINUABLE;
		extern const unsigned int EH_UNWINDING;
		extern const unsigned int EH_EXIT_UNWIND;
		extern const unsigned int EH_STACK_INVALID;
        extern const unsigned int EH_NESTED_CALL;
		extern const unsigned int EH_UNKNOWN1;
		extern const unsigned int EH_UNKNOWN2;
		extern const unsigned int EH_UNKNOWN3;
		
		typedef nsWin32::CONTEXT Context;

		//--------------------------------------------------------------------------------
		class ExceptionRecord : public nsWin32::EXCEPTION_RECORD
		{
		public:

			int IsUnwinding() const 
			{
				return ( ExceptionFlags & ( EH_UNWINDING | EH_EXIT_UNWIND ) ) != 0; 
			}
		};

		//--------------------------------------------------------------------------------
		struct ScopeTableEntry
		{	
			unsigned int previousTryLevel;
			unsigned int ( *lpfnFilter )();
			unsigned int ( *lpfnHandler )();			
		};

		//--------------------------------------------------------------------------------
		class ExceptionFrame : public CExceptionFrame
		{
		public:

			//--------------------------------------------------------------------------------
			void* EBP() const 
			{
				return ( void* )&m_ebp; 
			}

			//--------------------------------------------------------------------------------
			const ScopeTableEntry& CurrentEntry() const ;

			//--------------------------------------------------------------------------------
			const ScopeTableEntry& Entry(int level) const ;

			//--------------------------------------------------------------------------------
			int TryLevel() const 
			{
				return m_TryLevel; 
			}

			//--------------------------------------------------------------------------------
			void SetTryLevel( int val ) 
			{
				m_TryLevel = val; 
			}

			//--------------------------------------------------------------------------------
			nsWin32::EXCEPTION_POINTERS* GetExceptionPointers() const 
			{
				return *( ( nsWin32::EXCEPTION_POINTERS** )this - 1 ); 
			}

			//--------------------------------------------------------------------------------
			void SetExceptionPointers( nsWin32::EXCEPTION_POINTERS* val ) const 
			{
				*( ( nsWin32::EXCEPTION_POINTERS** )this - 1) = val; 
			}

		private:

			ScopeTableEntry* m_pScopeTable;
			int m_TryLevel;
			void* m_ebp;			

			//Not to be implemented			
			ExceptionFrame();
			ExceptionFrame( const ExceptionFrame& );
			ExceptionFrame& operator = ( const ExceptionFrame& );
		};


		//--------------------------------------------------------------------------------
		class UnwindFrame : public CExceptionFrame
		{
		public:

			//--------------------------------------------------------------------------------
			UnwindFrame( void* pHandler, int tryLevel, SEH::ExceptionFrame* pOriginalFrame ): CExceptionFrame( pHandler ), m_TryLevel( tryLevel ), m_pOriginalFrame( pOriginalFrame )
			{
			}

			//--------------------------------------------------------------------------------
			int TryLevel() const 
			{ 
				return m_TryLevel; 
			}

			//--------------------------------------------------------------------------------
			void SetTryLevel( int val ) 
			{ 
				m_TryLevel = val; 
			}

			//--------------------------------------------------------------------------------
			const SEH::ExceptionFrame* OriginalFrame() const 
			{ 
				return m_pOriginalFrame; 
			}

		private:

			int m_TryLevel;
			SEH::ExceptionFrame* m_pOriginalFrame;

			UnwindFrame( const UnwindFrame& );
			UnwindFrame& operator = ( const UnwindFrame& );
		};

	}//SEH

}//nsCompiler

#endif//WINCMPSUPVC_EXCEPT_SEH_H_1
