//WinQLThread.h

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

//WinQL Code Services Thread

#ifndef WINQL_CS_THREAD_H_3
#define WINQL_CS_THREAD_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Text/CodeString.h"
#include "CodeQOR/Threading/ThreadContext.h"
#include "WinQL/Definitions/Handles.h"
#include "WinQL/Definitions/Constants.h"
#include "WinQL/Definitions/Data.h"
#include "WinQL/Definitions/IO.h"
#include "WinQL/CodeServices/Locale/WinQLLocaleThreadData.h"
#include "WinQL/CodeServices/Handles/WinQLSyncHandle.h"
#include "WinQL/Application/Process/WinQLProcessHelper.h"
#include "WinQL/Application/Threading/WinQLThreadState.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	class __QOR_INTERFACE( __WINQL ) CThreadResourceManager;

	//--------------------------------------------------------------------------------
	typedef struct _NT_TIB
	{
		struct _EXCEPTION_REGISTRATION_RECORD* ExceptionList;
		void* StackBase;
		void* StackLimit;
		void* SubSystemTib;
#if defined(_MSC_EXTENSIONS)
		union {
			void* FiberData;
			unsigned long Version;
		};
#else
		void* FiberData;
#endif
		void* ArbitraryUserPointer;
		struct _NT_TIB *Self;
	} NT_TIB;
	typedef NT_TIB *PNT_TIB;

	class __QOR_INTERFACE( __WINQL ) CThread;

#ifdef __WINQL
	extern __QCMP_DECLARE_PERTHREAD CThread* t_pCurrentWin32Thread;//Per thread object pointer to track per thread data
#endif

	__QOR_INTERFACE( __WINQL ) CThread* GetCurrentWin32Thread( void );

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CThread : public nsCodeQOR::CThreadContextBase, public CThreadHelper
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CThread );

		__QCMP_STATIC_CONSTANT( long, Thread_Base_Priority_LowRT = 15 );
		__QCMP_STATIC_CONSTANT( long, Thread_Base_Priority_Max = 2 );
		__QCMP_STATIC_CONSTANT( long, Thread_Base_Priority_Min = (-2) );
		__QCMP_STATIC_CONSTANT( long, Thread_Base_Priority_Idle = (-15) );

		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Lowest = Thread_Base_Priority_Min );
		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Below_Normal = Thread_Priority_Lowest + 1 );
		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Normal = 0 );
		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Highest = Thread_Base_Priority_Max );
		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Above_Normal = Thread_Priority_Highest - 1 );
		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Error_Return = 0x7fffffff );
		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Time_Critical = Thread_Base_Priority_LowRT );
		__QCMP_STATIC_CONSTANT( long, Thread_Priority_Idle = Thread_Base_Priority_Idle );

		__QCMP_STATIC_CONSTANT( long, Thread_Mode_Background_Begin = 0x00010000 );
		__QCMP_STATIC_CONSTANT( long, Thread_Mode_Background_End = 0x00020000 );

		CThread();
		CThread( unsigned long dwDesiredAccess, bool bInheritHandle, unsigned long dwThreadId );
		CThread( void* hProcess, nsWin32::LPSECURITY_ATTRIBUTES lpThreadAttributes, Cmp_ulong_ptr dwStackSize, nsWin32::PTHREAD_START_ROUTINE lpStartAddress, void* lpParameter, unsigned long dwCreationFlags, unsigned long* lpThreadId );
		CThread( nsWin32::LPSECURITY_ATTRIBUTES lpThreadAttributes, Cmp_ulong_ptr dwStackSize, nsWin32::LPTHREAD_START_ROUTINE lpStartAddress, void* lpParameter, unsigned long dwCreationFlags, unsigned long* lpThreadId );
		virtual ~CThread();

		//--------------------------------------------------------------------------------
		virtual int& ProcessingThrow()
		{
			return m_ThreadData.ProcessingThrow();
		}

		//--------------------------------------------------------------------------------
		virtual void*& FrameInfoChain( void )
		{
			return m_ThreadData.FrameInfoChain();
		}

#if     ( __QCMP_COMPILER == __QCMP_MSVC || __QCMP_COMPILER == __QCMP_INTEL )
		//--------------------------------------------------------------------------------
		virtual nsCompiler::EH::ExceptData& CurrentException( void )
		{
			return m_ThreadData.CurrentException();
		}
#else
        virtual void* CurrentException( void )
        {
            return 0;
        }
#endif//( __QCMP_COMPILER == __QCMP_MSVC )

		static void Exit( unsigned long dwExitCode );
		static nsCodeQOR::CTCRef< CThread > GetCurrent( void );
		static unsigned long GetCurrentId( void );
		unsigned long GetProcessId( void );
		static bool IsAFiber( void );
		static void* ConvertToFiber( void* lpParameter );
		static void* ConvertToFiberEx( void* lpParameter, unsigned long dwFlags );
		static bool IsGUIThread( bool bConvert );
		//bool GetGUIInfo( nsWin32::LPGUITHREADINFO lpgui );
		bool GetExitCode( unsigned long* lpExitCode );
		unsigned long GetId( void );
		bool GetIOPendingFlag( int* lpIOIsPending );
		int GetPriority( void );
		bool GetPriorityBoost( int* pDisablePriorityBoost );
		bool GetTimes( nsWin32::LPFILETIME lpCreationTime, nsWin32::LPFILETIME lpExitTime, nsWin32::LPFILETIME lpKernelTime, nsWin32::LPFILETIME lpUserTime );
		unsigned long Resume( void );
		Cmp_ulong_ptr SetAffinityMask( Cmp_ulong_ptr dwThreadAffinityMask );
		unsigned long SetIdealProcessor( unsigned long dwIdealProcessor );
		bool SetPriority( int nPriority );
		bool SetPriorityBoost( bool bDisablePriorityBoost );
		unsigned long Suspend( void );
		bool Terminate( unsigned long dwExitCode );
		unsigned long Wow64Suspend( void );
		bool QueryCycleTime( Cmp_unsigned__int64* CycleTime );
		//TODO: Consider moving this to an IOThread sub class to avoid User32 dependency in base CThread
		bool AttachInput( CThread* pToThread, bool bAttach );
		bool GetContext( nsWin32::CONTEXT* lpContext );
		bool SetContext( const nsWin32::CONTEXT* lpContext );
		bool Wow64GetContext( nsWin32::PWOW64_CONTEXT lpContext );
		bool Wow64SetContext( const nsWin32::WOW64_CONTEXT* lpContext );
		bool GetSelectorEntry( unsigned long dwSelector, nsWin32::LPLDT_ENTRY lpSelectorEntry );
		bool GetUserNameT( TCHAR* lpBuffer, unsigned long* lpnSize );
		nsCodeQOR::CTCRef< CSyncHandle > Handle( void );
		void* CRTThreadData( void );
		bool SetCRTThreadData( void* pData );

		mxTCHAR* Name( void );

		static nsCodeQOR::CTCRef< CThread > Create( unsigned long ulCreationFlags, nsWin32::LPSECURITY_ATTRIBUTES pSecurityAttributes = 0, Cmp_ulong_ptr ulStackSize = 0 );		

		virtual unsigned long Run( void );

		//--------------------------------------------------------------------------------
		int& Errno()
		{
			return m_ThreadData.ErrorNumber();
		}

		//------------------------------------------------------------------------------
		CThreadState& Data( void )
		{
			return m_ThreadData;
		}

		//--------------------------------------------------------------------------------
		CThreadLocaleInfo*& LocaleInfoPtr()
		{
			return m_ThreadData.LocaleData().LocaleInfoPtr();
		}

		static nsCodeQOR::CThreadContextBase* GetCurrentImpl( void );
		static void SetCurrentImpl( nsCodeQOR::CThreadContextBase* pImpl );

		void UpdateLocale( CThreadLocaleInfo*& ptloci );		
		void UpdateMBCodePage( CMBCInfo*& ptmbci );
		CThreadLocaleInfo* UpdateLocaleInfo();
		CMBCInfo* UpdatetMBCInfo();

		nsCodeQOR::CThreadContextBase* m_pImpl;

		void AddRef( void );
		void Release( void );

		CThreadResourceManager& ResourceManager( void );

	protected:

		CThreadState m_ThreadData;
		CSyncHandle m_hThread;
		void* m_pCRTThreadData;
		mxTCHAR* m_Name;		

		CThreadResourceManager* m_pResourceManager;

		unsigned long InstanceThreadFunction( void );

	private:

		LPTHREAD_START_ROUTINE m_fpThreadFunction;
		void* m_pThreadFunctionParam;

		static unsigned long __QCMP_STDCALLCONVENTION StaticThreadFunction( void* vpThread );

		bool m_bWinQLThread;
		static unsigned long __QCMP_STDCALLCONVENTION StartRoutine( void* );
		unsigned long m_ulWinQLThreadRefCount;
		bool m_bCloseHandle;
		
	};


}//nsWin32

#endif//WINQL_CS_THREAD_H_3