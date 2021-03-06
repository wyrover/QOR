//WinQLPrivateNamespace.cpp

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
#include "WinQL/Application/Threading/WinQLPrivateNamespace.h"
#include "WinQAPI/Kernel32.h"

//------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CPrivateNamespace );

	//--------------------------------------------------------------------------------
	CPrivateNamespace::CPrivateNamespace( nsWin32::LPSECURITY_ATTRIBUTES lpPrivateNamespaceAttributes, void* lpBoundaryDescriptor, const TCHAR* lpAliasPrefix, unsigned char* pbResult )
	{
		_WINQ_FCONTEXT( "CPrivateNamespace::CPrivateNamespace" );
		__QOR_PROTECT
		{
			m_pResult = pbResult;
			m_Flags = 0;
			m_Handle = CKernel32::CreatePrivateNamespace( reinterpret_cast< ::LPSECURITY_ATTRIBUTES >( lpPrivateNamespaceAttributes ), lpBoundaryDescriptor, lpAliasPrefix );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	CPrivateNamespace::CPrivateNamespace( CBoundaryDescriptor& BoundaryDescriptor, const TCHAR* lpAliasPrefix, unsigned char* pbResult )
	{
		_WINQ_FCONTEXT( "CPrivateNamespace::CPrivateNamespace" );
		__QOR_PROTECT
		{
			m_pResult = pbResult;
			m_Flags = 0;
			m_Handle = CKernel32::OpenPrivateNamespace( BoundaryDescriptor.Handle().operator nsWin32::CSyncHandle *(), lpAliasPrefix );
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	void CPrivateNamespace::Close( unsigned long Flags )
	{
		_WINQ_FCONTEXT( "CPrivateNamespace::Close" );
		__QOR_PROTECT
		{
			m_Flags = Flags;
			delete this;
		}__QOR_ENDPROTECT
	}		

	//--------------------------------------------------------------------------------
	//NOTE: Do not call directly or by deleting the object, call Close instead
	CPrivateNamespace::~CPrivateNamespace()
	{
		_WINQ_FCONTEXT( "CPrivateNamespace::~CPrivateNamespace" );
		__QOR_PROTECT
		{
			BOOLEAN bResult = CKernel32::ClosePrivateNamespace( m_Handle.Use(), m_Flags );
			if( m_pResult != 0 )
			{
				*m_pResult = bResult;
			}
		}__QOR_ENDPROTECT
	}

}//nsWin32
