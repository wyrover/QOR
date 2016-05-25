//WinQLHandle.cpp

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
#include "WinQL/CodeServices/Handles/WinQLHandle.h"
#include "WinQAPI/Kernel32.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	using namespace nsWinQAPI;

	__QOR_IMPLEMENT_OCLASS_LUID( CHandle );

	//--------------------------------------------------------------------------------
	CHandle::CHandle()
	{
		_WINQ_FCONTEXT( "CHandle::CHandle" );
		m_h = (void*)(-1);
		m_pObject = 0;
	}
	
	//--------------------------------------------------------------------------------
	CHandle::CHandle( void* h )
	{
		_WINQ_FCONTEXT( "CHandle::CHandle" );
		m_h = h;
		m_pObject = 0;
	}

	//--------------------------------------------------------------------------------
	CHandle::CHandle( const CHandle& src )
	{
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CHandle& CHandle::operator = ( const CHandle& src )
	{
		if( &src != this )
		{
			m_h = src.m_h;
			m_pObject = src.m_pObject;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	CHandle::~CHandle()
	{
		_WINQ_FCONTEXT( "CHandle::~CHandle" );
	}

	//--------------------------------------------------------------------------------
	void CHandle::Close()
	{
		_WINQ_FCONTEXT( "CHandle::Close" );
		__QOR_PROTECT
		{
			if( m_h && m_h != (void*)(0xFFFFFFFF) )
			{
				CKernel32::CloseHandle( m_h );
				m_h = 0;
			}
		}__QOR_ENDPROTECT
	}

	//--------------------------------------------------------------------------------
	bool CHandle::IsNull( void ) const
	{
		_WINQ_FCONTEXT( "CHandle::IsNull" );
		return ( m_h == 0 ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CHandle::IsInvalid( void )
	{
		_WINQ_FCONTEXT( "CHandle::IsNull" );
		return ( m_h == (void*)(0xFFFFFFFF) ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	void* CHandle::Use( void ) const
	{
		_WINQ_FCONTEXT( "CHandle::Use" );
		return m_h;
	}

	//--------------------------------------------------------------------------------
	bool CHandle::Attach( void* pObj )
	{
		_WINQ_FCONTEXT( "CHandle::Attach" );
		bool bResult = false;
		if( m_pObject == 0 )
		{
			m_pObject = pObj;
			bResult = true;
		}
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void* CHandle::Detach( void )
	{
		_WINQ_FCONTEXT( "CHandle::Detach" );
		void* pResult = m_pObject;
		m_pObject = 0;
		return pResult;
	}

	//--------------------------------------------------------------------------------
	void* CHandle::Object() const
	{
		_WINQ_FCONTEXT( "CHandle::Object" );
		void* pResult = m_pObject;
		return pResult;
	}

	//--------------------------------------------------------------------------------
	bool CHandle::Duplicate( void* hSourceProcessHandle, void* hTargetProcessHandle, void** lpTargetHandle, unsigned long dwDesiredAccess, bool bInheritHandle, unsigned long dwOptions )
	{
		_WINQ_FCONTEXT( "CHandle::Duplicate" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::DuplicateHandle( hSourceProcessHandle, m_h, hTargetProcessHandle, lpTargetHandle, dwDesiredAccess, bInheritHandle ? TRUE : FALSE, dwOptions ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CHandle::GetInformation( unsigned long* lpdwFlags )
	{
		_WINQ_FCONTEXT( "CHandle::GetInformation" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::GetHandleInformation( m_h, lpdwFlags ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CHandle::SetInformation( unsigned long dwMask, unsigned long dwFlags )
	{
		_WINQ_FCONTEXT( "CHandle::SetInformation" );
		bool bResult = false;
		__QOR_PROTECT
		{
			bResult = CKernel32::SetHandleInformation( m_h, dwMask, dwFlags ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CHandle::Drop( void )
	{
		_WINQ_FCONTEXT( "CHandle::Drop" );
		m_h = 0;
	}

}//nsWin32