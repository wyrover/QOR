//WinQLHotKey.cpp

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

#include "CompilerQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usafe: stored in member for later use" );
#include "WinQL/GUI/Windows/HotKey.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CHotKeyClass );

	//--------------------------------------------------------------------------------
	CHotKeyClass::CHotKeyClass() : m_ComCtrl32( CCommonCtrl::CCHOTKEY_CLASS )
	{
		_WINQ_FCONTEXT( "CHotKeyClass::CHotKeyClass" );
	}

	//--------------------------------------------------------------------------------
	CHotKeyClass::~CHotKeyClass()
	{
		_WINQ_FCONTEXT( "CHotKeyClass::~CHotKeyClass" );
	}

	//--------------------------------------------------------------------------------
	bool CHotKeyClass::Preregistered()
	{ 
		_WINQ_FCONTEXT( "CHotKeyClass::Preregistered" );
		return true; 
	}

	//--------------------------------------------------------------------------------
	const TCHAR* CHotKeyClass::Name()
	{ 
		_WINQ_FCONTEXT( "CHotKeyClass::Name" );
		return _TXT( "msctls_hotkey32" ); 
	}






	__QOR_IMPLEMENT_OCLASS_LUID( CHotKeyFactory );

	//--------------------------------------------------------------------------------
	CHotKeyFactory::CHotKeyFactory() : CWindowFactory()
	{
		_WINQ_FCONTEXT( "CHotKeyFactory::CHotKeyFactory" );
	}

	//--------------------------------------------------------------------------------
	CHotKeyFactory::~CHotKeyFactory()
	{
		_WINQ_FCONTEXT( "CHotKeyFactory::~CHotKeyFactory" );
	}

	//--------------------------------------------------------------------------------
	CWindowHotKey* CHotKeyFactory::Create()
	{
		_WINQ_FCONTEXT( "CHotKeyFactory::Instance" );
		return new CWindowHotKey;//PreCreateWindow< CWindowHotKey, CHotKeyClass >();
	}





	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CWindowHotKey );

	//--------------------------------------------------------------------------------
	CWindowHotKey::CWindowHotKey() : CWinCtrlWindow()
	{	
		_WINQ_FCONTEXT( "CWindowHotKey::CWindowHotKey" );
	}

	//--------------------------------------------------------------------------------
	CWindowHotKey::~CWindowHotKey()
	{
		_WINQ_FCONTEXT( "CWindowHotKey::~CWindowHotKey" );
	}

	//--------------------------------------------------------------------------------
	void CWindowHotKey::OnCommand( unsigned short wCtrlID, unsigned short wCode )
	{
		_WINQ_FCONTEXT( "CWindowHotKey::OnCommand" );
		switch ( wCode )
		{
		case EN_CHANGE:
			{
				OnChange();
			}
			break;

		default:
			{
				OnUnknownCommand( wCode );
			}
			break;
		}
	}

	//--------------------------------------------------------------------------------
	void CWindowHotKey::OnChange()
	{
		_WINQ_FCONTEXT( "CWindowHotKey::OnChange" );
	}

	//--------------------------------------------------------------------------------
	void CWindowHotKey::OnUnknownCommand( unsigned short wCode )
	{
		_WINQ_FCONTEXT( "CWindowHotKey::OnUnknownCommand" );
	}

	//--------------------------------------------------------------------------------
	long CWindowHotKey::GetHotKey()
	{
		_WINQ_FCONTEXT( "CWindowHotKey::GetHotKey" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) HKM_GETHOTKEY, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CWindowHotKey::SetHotKey( unsigned long dwHotKey )
	{
		_WINQ_FCONTEXT( "CWindowHotKey::SetHotKey" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) HKM_SETHOTKEY, static_cast< Cmp_uint_ptr >( dwHotKey ), 0 );
	}

	//--------------------------------------------------------------------------------
	void CWindowHotKey::SetRules( unsigned long dwInvalid, unsigned short wDefault )
	{
		_WINQ_FCONTEXT( "CWindowHotKey::SetRules" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) HKM_SETRULES, static_cast< Cmp_uint_ptr >( dwInvalid ), MakeLParam( wDefault, 0 ) );
	}

}//nsWin32
