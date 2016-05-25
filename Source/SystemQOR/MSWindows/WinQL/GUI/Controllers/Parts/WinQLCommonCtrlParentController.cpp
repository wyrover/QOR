//WinQLCommonCtrlParentController.cpp

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
#include "WinQL/GUI/Controllers/Parts/CommonCtrlParentController.h"
__QCMP_WARNING_POP
#include "WinQL/GUI/Window.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CCommonCtrlParentController );

	//--------------------------------------------------------------------------------
	CCommonCtrlParentController::CCommonCtrlParentController()
	{
		_WINQ_FCONTEXT( "CCommonCtrlParentController::CCommonCtrlParentController" );
	}

	//--------------------------------------------------------------------------------
	CCommonCtrlParentController::~CCommonCtrlParentController()
	{
		_WINQ_FCONTEXT( "CCommonCtrlParentController::~CCommonCtrlParentController" );
	}

	//--------------------------------------------------------------------------------
	bool CCommonCtrlParentController::ProcessMessage( COSWindow& Window, Cmp_long_ptr& lResult, unsigned int uMsg, Cmp_uint_ptr wParam, Cmp_long_ptr lParam )
	{
		_WINQ_FCONTEXT( "CCommonCtrlParentController::ProcessMessage" );

		bool bProcessed = false;

		switch ( uMsg )
		{
		case COSWindow::wmNotifyFormat:
			{
				COSWindow::refType WndFrom = COSWindow::FromHandle( CWindowHandle( 0, (void*)(wParam) ).Ref() );
				lResult = OnNotifyFormat( Window, WndFrom, lParam );
				bProcessed = true;
			}
			break;
		case COSWindow::wmNotify:
			{
				NotificationMessageHeader* pHdr = reinterpret_cast< NotificationMessageHeader* >( lParam );
				lResult = OnNotify( Window, wParam, pHdr );
				bProcessed = true;
			}
			break;
		case COSWindow::wmCommand:
			{					
				unsigned short wCode = HiWord( wParam );
				if( wCode > 1 )
				{
					unsigned short wCtrlID = LoWord( wParam );
					COSWindow::refType WndCtrl = COSWindow::FromHandle( CWindowHandle( 0, (void*)(lParam) ).Ref() );					
					OnCommand( Window, wCtrlID, wCode, WndCtrl );
					lResult = 0;
					bProcessed = true;
				}
			}
			break;
		}

		return bProcessed;
	}

	//--------------------------------------------------------------------------------
	long CCommonCtrlParentController::OnNotify( COSWindow& Window, Cmp_uint_ptr wParam, NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CCommonCtrlParentController::OnNotify" );
		long lResult = 0;
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CCommonCtrlParentController::OnNotifyFormat( COSWindow& Window, COSWindow::refType WndFrom, Cmp_long_ptr Command )
	{
		_WINQ_FCONTEXT( "CCommonCtrlParentController::OnNotifyFormat" );
		long lResult = 0;
#ifdef UNICODE
		lResult = COSWindow::nfrUnicode;
#else
		lResult = COSWindow::nfrANSI;
#endif
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CCommonCtrlParentController::OnCommand( COSWindow& Window, unsigned short wCtrlID, unsigned short wCode, COSWindow::refType Ctrl )
	{
		_WINQ_FCONTEXT( "CCommonCtrlParentController::OnCommand" );
	}

}//nsWin32

