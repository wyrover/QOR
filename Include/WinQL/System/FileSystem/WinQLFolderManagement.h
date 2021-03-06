//WinQLFolderManagement.h

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

#ifndef WINQL_FILESYSTEM_FOLDERMANAGEMENT_H_2
#define WINQL_FILESYSTEM_FOLDERMANAGEMENT_H_2

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/IO.h"
#include "WinQL/CodeServices/Handles/WinQLRAIISessionHandle.h"
#include "WinQL/CodeServices/Text/WinString.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	//Stateless helper for Directory functions
	class __QOR_INTERFACE( __WINQL ) CDirectoryHelper
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDirectoryHelper );

		CDirectoryHelper();
		CDirectoryHelper( const CDirectoryHelper& );
		CDirectoryHelper& operator = ( const CDirectoryHelper& );
		~CDirectoryHelper();
		bool Create( const TCHAR* lpPathName, nsWin32::LPSECURITY_ATTRIBUTES lpSecurityAttributes );
		bool Create( const TCHAR* lpTemplateDirectory, const TCHAR* lpNewDirectory, nsWin32::LPSECURITY_ATTRIBUTES lpSecurityAttributes );
		bool CreateTransacted( const TCHAR* lpTemplateDirectory, const TCHAR* lpNewDirectory, nsWin32::LPSECURITY_ATTRIBUTES lpSecurityAttributes, void* hTransaction );

		//TODO: integrate this with WinQL objects
		bool ReadChangesW( void* hDirectory, void* lpBuffer, unsigned long nBufferLength, bool bWatchSubtree, unsigned long dwNotifyFilter, unsigned long* lpBytesReturned, nsWin32::LPOVERLAPPED lpOverlapped, nsWin32::LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine );
		unsigned long GetCurrent( CTStringRef strDirectory );
		bool Remove( const TCHAR* lpPathName );
		bool RemoveTransacted( const TCHAR* lpPathName, void* hTransaction );
		bool SetCurrent( const TCHAR* lpPathName );
	};

	//--------------------------------------------------------------------------------
	//Session class for Directory Change Notifications
	class __QOR_INTERFACE( __WINQL ) CChangeNotification
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CChangeNotification );

		CChangeNotification( const TCHAR* lpPathName, bool bWatchSubtree, unsigned long dwNotifyFilter );
		virtual ~CChangeNotification();
		bool Next( void );

	protected:

		CRAIISessionHandle m_Handle;

	private:

		CChangeNotification();
		CChangeNotification( const CChangeNotification& );
		CChangeNotification& operator = ( const CChangeNotification& );
	};

}//nsWin32

#endif//WINQL_FILESYSTEM_FOLDERMANAGEMENT_H_2
