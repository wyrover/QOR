//WinQLDragListBox.cpp

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
#include "WinQL/GUI/Windows/DragListBox.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CDragListBoxFactory );

	//--------------------------------------------------------------------------------
	CDragListBoxFactory::CDragListBoxFactory() : CListBoxFactory()
	{
		_WINQ_FCONTEXT( "CDragListBoxFactory::CDragListBoxFactory" );
	}

	//--------------------------------------------------------------------------------
	CDragListBoxFactory::~CDragListBoxFactory()
	{	
		_WINQ_FCONTEXT( "CDragListBoxFactory::~CDragListBoxFactory" );
	}

	//--------------------------------------------------------------------------------
	CListBox* CDragListBoxFactory::Create()
	{
		_WINQ_FCONTEXT( "CDragListBoxFactory::Instance" );
		return new CListBox;//PreCreateWindow< CDragListBox, CListBoxClass >();
	}




	__QOR_IMPLEMENT_OCLASS_LUID( CDragListBox );

	//--------------------------------------------------------------------------------
	CDragListBox::CDragListBox() : CListBox()
	{	
		_WINQ_FCONTEXT( "CDragListBox::CDragListBox" );
		m_uiDLMessage = 0;
	}

	//--------------------------------------------------------------------------------
	CDragListBox::~CDragListBox()
	{
		_WINQ_FCONTEXT( "CDragListBox::~CDragListBox" );
	}

	//--------------------------------------------------------------------------------
	void CDragListBox::Create( const TCHAR* lpWindowName, InstanceHandle hInstance, unsigned long dwStyle, unsigned long dwExStyle, int x, int y, int nWidth, int nHeight, CWindowHandle::refType hWndParent, CMenuHandle::refType hMenu )
	{
		_WINQ_FCONTEXT( "CDragListBox::Create" );

		CListBox::Create( lpWindowName, hInstance, dwStyle, dwExStyle, x, y, nWidth, nHeight, hWndParent, hMenu );
		m_ComCtrl32.MakeDragList( Ref() );
		m_uiDLMessage = m_Win32MsgHandler.RegisterWindowMessageT( _TXT( "commctrl_DragListMsg" ) );
	}

	//--------------------------------------------------------------------------------
	bool CDragListBox::OnDLMessage( long& lResult, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CDragListBox::OnDLMessage" );

		bool bProcessed = false;
		DRAGLISTINFO* pDragListInfo = reinterpret_cast< DRAGLISTINFO* >( lParam );

		if( pDragListInfo != 0 )
		{			
			COSWindow::refType Window = COSWindow::FromHandle( CWindowHandle( 0, pDragListInfo->phWnd ).Ref() );

			switch ( pDragListInfo->uNotification )
			{
			case DL_BEGINDRAG:
				{
					lResult = OnBeginDrag( Window, pDragListInfo->ptCursor );
					bProcessed = true;
				}
				break;
			case DL_DRAGGING:
				{
					lResult = OnDragging( Window, pDragListInfo->ptCursor );
					bProcessed = true;
				}
				break;
			case DL_DROPPED:
				{
					OnDropped( Window, pDragListInfo->ptCursor );
					bProcessed = true;
				}
				break;
			case DL_CANCELDRAG:
				{
					OnCancelDrag( Window, pDragListInfo->ptCursor );
					bProcessed = true;
				}
				break;

			}
		}
		return bProcessed;
	}

	//--------------------------------------------------------------------------------
	void CDragListBox::OnCancelDrag( COSWindow::refType Window, nsWin32::POINT ptCursor )
	{
		_WINQ_FCONTEXT( "CDragListBox::OnCancelDrag" );
	}

	//--------------------------------------------------------------------------------
	void CDragListBox::OnDropped( COSWindow::refType Window, nsWin32::POINT ptCursor )
	{
		_WINQ_FCONTEXT( "CDragListBox::OnDropped" );
	}

	//--------------------------------------------------------------------------------
	long CDragListBox::OnDragging( COSWindow::refType Window, nsWin32::POINT ptCursor )
	{
		_WINQ_FCONTEXT( "CDragListBox::OnDragging" );

		long lResult = DL_STOPCURSOR;

		int iItem = m_ComCtrl32.LBItemFromPt( Window, ptCursor, 1 );

		if( iItem != -1 )
		{
			m_ComCtrl32.DrawInsert( GetParent()->Ref(), Window, iItem );
		}

		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDragListBox::OnBeginDrag( COSWindow::refType Window, nsWin32::POINT ptCursor )
	{
		_WINQ_FCONTEXT( "CDragListBox::OnBeginDrag" );
		long lResult = static_cast< long >( 1 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	unsigned int CDragListBox::DLMessageID()
	{
		_WINQ_FCONTEXT( "CDragListBox::DLMessageID" );
		return m_uiDLMessage;
	}

}//nsWin32

