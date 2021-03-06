//WinQLMenuController.cpp

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
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: stored in member for later use" )
#include "WinQL/GUI/Controllers/Parts/MenuController.h"
#include "WinQL/GUI/Window.h"
__QCMP_WARNING_POP
#include "WinQL/GUI/Menu.h"
#include "WinQL/System/WinQLSystem.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CMenuController );

	//--------------------------------------------------------------------------------
	CMenuController::CMenuController( nsMammut::CModel* pModelItem, nsAppocrita::CController* pParent ) : CBaseWindowPartController( pModelItem, pParent )
	{
		_WINQ_FCONTEXT( "CMenuController::CMenuController" );
	}

	//--------------------------------------------------------------------------------
	CMenuController::~CMenuController()
	{
		_WINQ_FCONTEXT( "CMenuController::~CMenuController" );
	}

	//--------------------------------------------------------------------------------
	bool CMenuController::ProcessMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CMenuController::ProcessMessage" );

		bool bProcessed = ProcessHook( Window, lResult, uMsg, wParam, lParam );

		switch ( uMsg )
		{
		case COSWindow::wmContextMenu:
			{
				COSWindow::refType refWnd = COSWindow::FromHandle( CWindowHandle( 0, (void*)(wParam) ).Ref() );
				unsigned short wXPos = LoWord( lParam );
				unsigned short wYPos = HiWord( lParam );
				OnContextMenu( Window, refWnd, wXPos, wYPos );
				bProcessed = true;
			}
			break;
		case COSWindow::wmInitMenu:
			{
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)(wParam) ).Ref() );
				OnInitMenu( Window, refMenu );
				lResult = 0;
				bProcessed = true;
			}
			break;
		case COSWindow::wmInitMenuPopup:
			{
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)( wParam ) ).Ref() );
				unsigned short wPos = LoWord( lParam );
				int bWindowMenu = static_cast< int >( HiWord( lParam ) );
				OnInitMenuPopup( Window, refMenu, wPos, bWindowMenu ? true : false );
				lResult = 0;
				bProcessed = true;
			}
			break;
#if		( WINVER >= 0x0500 )
		case COSWindow::wmUninitMenuPopup:
			{
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)(wParam) ).Ref() );
				unsigned short wDestroyedMenu = HiWord( lParam );
				OnDestroyedMenuPopup( Window, refMenu, wDestroyedMenu );
				bProcessed = true;
			}
			break;
#endif//( WINVER >= 0x0500 )
		case COSWindow::wmMenuSelect:
			{
				unsigned short wIndex = LoWord( wParam );
				unsigned short wFlags = HiWord( wParam );
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)( lParam ) ).Ref() );
				OnMenuSelect( Window, refMenu, wIndex, wFlags );
				lResult = 0;
				bProcessed = true;
			}
			break;
		case COSWindow::wmMenuChar:
			{
				unsigned short wCharCode = LoWord( wParam );
				unsigned short wMenuType = HiWord( wParam );
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)( lParam ) ).Ref() );
				lResult = OnMenuChar( Window, refMenu, wCharCode, wMenuType );
				bProcessed = true;
			}
			break;
		case COSWindow::wmNextMenu:
			{
				MDINextMenu* pNextMenu = reinterpret_cast< MDINextMenu* >( lParam );

				CMenu::refType refMenuIn = CMenu::FromHandle( CMenuHandle( 0, (void*)( pNextMenu->hmenuIn ) ).Ref() );
				CMenu::refType refMenuNext = CMenu::FromHandle( CMenuHandle( 0, (void*)( pNextMenu->hmenuNext ) ).Ref() );

				OnNextMenu( Window, wParam, refMenuIn, refMenuNext );
				bProcessed = true;
			}
			break;
#if		( WINVER >= 0x0500 )
		case COSWindow::wmMenuGetObject:
			{
				MenuGetObjectInfo* pMenuObjectInfo = reinterpret_cast< MenuGetObjectInfo* >( lParam );
				lResult = OnGetObject( Window, pMenuObjectInfo );
				bProcessed = true;
			}
			break;
		case COSWindow::wmMenuRButtonUp:
			{
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)( lParam ) ).Ref() );
				OnRButtonUp( Window, refMenu, wParam );
				bProcessed = true;
			}
			break;
		case COSWindow::wmMenuCommand:
			{
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)( lParam ) ).Ref() );

				unsigned short wItemID = static_cast< unsigned short >( -1 );
				int iIndex = 0;

				if( System().Information(QOR_PP_SHARED_OBJECT_ACCESS).IsWindows98orME() )
				{
					wItemID = LoWord( wParam );
					iIndex = static_cast< int >( HiWord( wParam ) );
				}
				else
				{
					iIndex = wParam;
				}

				OnMenuCommand( Window, refMenu, iIndex, wItemID );

				bProcessed = true;
			}
			break;
		case COSWindow::wmMenuDrag:
			{
				CMenu::refType refMenu = CMenu::FromHandle( CMenuHandle( 0, (void*)( lParam ) ).Ref() );
				lResult = OnMenuDrag( Window, refMenu, static_cast< unsigned short >( wParam ) );
				bProcessed = true;
			}
			break;
#endif//( WINVER >= 0x0500 )
		case COSWindow::wmCommand:
			{
				unsigned short wCode = HiWord( wParam );
					
				if( wCode == 0 )
				{
					unsigned short wMenuID = LoWord( wParam );						
					OnCommand( Window, wMenuID );
					lResult = 0;
					bProcessed = true;
				}
			}
			break;
		}

		return bProcessed;
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnContextMenu( COSWindow& Window, COSWindow::refType refWnd, unsigned short wXPos, unsigned short wYPos )
	{
		_WINQ_FCONTEXT( "CMenuController::OnContextMenu" );
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnInitMenu( COSWindow& Window, CMenu::refType refMenu )
	{
		_WINQ_FCONTEXT( "CMenuController::OnInitMenu" );
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnInitMenuPopup( COSWindow& Window, CMenu::refType refMenu, unsigned short wPos, bool bWindowMenu )
	{
		_WINQ_FCONTEXT( "CMenuController::OnInitMenuPopup" );
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnMenuSelect( COSWindow& Window, CMenu::refType Menu, unsigned short wIndex, unsigned short wFlags )
	{
		_WINQ_FCONTEXT( "CMenuController::OnMenuSelect" );
		if( !Menu.IsNull() )
		{
			
		}
	}

	//--------------------------------------------------------------------------------
	long CMenuController::OnMenuChar( COSWindow& Window, CMenu::refType refMenu, unsigned short wCharCode, unsigned short wMenuType )
	{
		_WINQ_FCONTEXT( "CMenuController::OnMenuChar" );
		long lResult = ( CMenu::_MNC_CLOSE << sizeof( unsigned short ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnNextMenu( COSWindow& Window, Cmp_uint_ptr wParam, CMenu::refType refMenuIn, CMenu::refType refMenuNext )
	{
		_WINQ_FCONTEXT( "CMenuController::OnNextMenu" );
	}

	//--------------------------------------------------------------------------------
	long CMenuController::OnGetObject( COSWindow& Window, MenuGetObjectInfo* pMenuObjectInfo )
	{
		_WINQ_FCONTEXT( "CMenuController::OnGetObject" );
		long lResult = COSWindow::mngoNoInterface;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnRButtonUp( COSWindow& Window, CMenu::refType refMenu, Cmp_uint_ptr wParam )
	{
		_WINQ_FCONTEXT( "CMenuController::OnRButtonUp" );
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnMenuCommand( COSWindow& Window, CMenu::refType refMenu, int iIndex, unsigned short wItemID )
	{
		_WINQ_FCONTEXT( "CMenuController::OnMenuCommand" );
	}

	//--------------------------------------------------------------------------------
	long CMenuController::OnMenuDrag( COSWindow& Window, CMenu::refType refMenu, unsigned short wParam )
	{
		_WINQ_FCONTEXT( "CMenuController::OnMenuDrag" );
		long lResult = CMenu::_MND_CONTINUE;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnDestroyedMenuPopup( COSWindow& Window, CMenu::refType refMenu, unsigned short wDestroyedMenu )
	{
		_WINQ_FCONTEXT( "CMenuController::OnDestroyedMenuPopup" );
	}

	//--------------------------------------------------------------------------------
	void CMenuController::OnCommand( COSWindow& Window, unsigned short wMenuID )
	{
		_WINQ_FCONTEXT( "CMenuController::OnCommand" );
	}

}//nsWin32

