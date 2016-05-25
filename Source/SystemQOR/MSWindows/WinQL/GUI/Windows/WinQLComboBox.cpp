//WinQLComboBox.cpp

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
#include "WinQL/GUI/Windows/ComboBox.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{

	__QOR_IMPLEMENT_OCLASS_LUID( CComboBoxClass );

	//--------------------------------------------------------------------------------
	CComboBoxClass::CComboBoxClass()
	{
		_WINQ_FCONTEXT( "CComboBoxClass::CComboBoxClass" );
	}

	//--------------------------------------------------------------------------------
	CComboBoxClass::~CComboBoxClass()
	{
		_WINQ_FCONTEXT( "CComboBoxClass::~CComboBoxClass" );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxClass::Preregistered()
	{ 
		_WINQ_FCONTEXT( "CComboBoxClass::Preregistered" );
		return true; 
	}

	//--------------------------------------------------------------------------------
	const TCHAR* CComboBoxClass::Name()
	{ 
		_WINQ_FCONTEXT( "CComboBoxClass::Name" );
		return _TXT( "COMBOBOX" ); 
	}


	__QOR_IMPLEMENT_OCLASS_LUID( CComboBox );

	//--------------------------------------------------------------------------------
	void CComboBox::OnCommand( unsigned short wCtrlID, unsigned short wCode )
	{
		_WINQ_FCONTEXT( "CComboBoxClass::OnCommand" );

		switch ( wCode )
		{
		case CBN_ERRSPACE:
			{
				OnErrSpace();
			}
			break;
		case CBN_SELCHANGE:
			{
				OnSelChange();
			}
			break;
		case CBN_DBLCLK:
			{
				OnDblClick();
			}
			break;
		case CBN_SETFOCUS:
			{
				OnSetFocus();
			}
			break;
		case CBN_KILLFOCUS:
			{
				OnKillFocus();
			}
			break;
		case CBN_EDITCHANGE:
			{
				OnEditChange();
			}
			break;
		case CBN_EDITUPDATE:
			{
				OnEditUpdate();
			}
			break;
		case CBN_DROPDOWN:
			{
				OnDropDown();
			}
			break;
		case CBN_CLOSEUP:
			{
				OnCloseUp();
			}
			break;
		case CBN_SELENDOK:
			{
				OnSelEndOK();
			}
			break;
		case CBN_SELENDCANCEL:
			{
				OnSelEndCancel();
			}
			break;
		}
	}


	__QOR_IMPLEMENT_OCLASS_LUID( CComboBoxFactory );

	//--------------------------------------------------------------------------------
	CComboBoxFactory::CComboBoxFactory() : CWindowFactory()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::CComboBoxFactory" );
	}

	//--------------------------------------------------------------------------------
	CComboBox* CComboBoxFactory::Create()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::Instance" );
		return new CComboBox;//PreCreateWindow< CComboBox, CComboBoxClass >();
	}

	//--------------------------------------------------------------------------------
	CComboBoxFactory::~CComboBoxFactory()
	{				
		_WINQ_FCONTEXT( "CComboBoxFactory::~CComboBoxFactory" );
	}


	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetAutoHScroll()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetAutoScroll" );
		return GetStyleBits( CBS_AUTOHSCROLL );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetAutoHScroll( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetAutoScroll" );
		SetStyleBits( CBS_AUTOHSCROLL, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetSimple()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetSimple" );
		return GetStyleBits( CBS_SIMPLE );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetSimple( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetSimple" );
		SetStyleBits( CBS_SIMPLE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetDropDown()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetDropDown" );
		return GetStyleBits( CBS_DROPDOWN );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetDropDown( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetDropDown" );
		SetStyleBits( CBS_DROPDOWN, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetDropDownList()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetDropDownList" );
		return GetStyleBits( CBS_DROPDOWNLIST );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetDropDownList( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetDropDownList" );
		SetStyleBits( CBS_DROPDOWNLIST, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetOwnerDrawFixed()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetOwnerDrawFixed" );
		return GetStyleBits( CBS_OWNERDRAWFIXED );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetOwnerDrawFixed( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetOwnerDrawFixed" );
		SetStyleBits( CBS_OWNERDRAWFIXED, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetOwnerDrawVariable()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetOwnerDrawVariable" );
		return GetStyleBits( CBS_OWNERDRAWVARIABLE );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetOwnerDrawVariable( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetOwnerDrawVariable" );
		SetStyleBits( CBS_OWNERDRAWVARIABLE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetOEMConvert()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetOEMConvert" );
		return GetStyleBits( CBS_OEMCONVERT );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetOEMConvert( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetOEMConvert" );
		SetStyleBits( CBS_OEMCONVERT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetSort()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetSort" );
		return GetStyleBits( CBS_SORT );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetSort( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetSort" );
		SetStyleBits( CBS_SORT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetHasStrings()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetHasStrings" );
		return GetStyleBits( CBS_HASSTRINGS );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetHasStrings( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetHasStrings" );
		SetStyleBits( CBS_HASSTRINGS, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetNoIntegralHeight()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetNoIntegralHeight" );
		return GetStyleBits( CBS_NOINTEGRALHEIGHT );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetNoIntegralHeight( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetNoIntegralHeight" );
		SetStyleBits( CBS_NOINTEGRALHEIGHT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetDisableNoScroll()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetNoIntegralHeight" );
		return GetStyleBits( CBS_DISABLENOSCROLL );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetDisableNoScroll( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetDisableNoScroll" );
		SetStyleBits( CBS_DISABLENOSCROLL, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetUpperCase()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetUpperCase" );
		return GetStyleBits( CBS_UPPERCASE );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetUpperCase( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetUpperCase" );
		SetStyleBits( CBS_UPPERCASE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CComboBoxFactory::GetLowerCase()
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::GetLowerCase" );
		return GetStyleBits( CBS_LOWERCASE );
	}

	//--------------------------------------------------------------------------------
	void CComboBoxFactory::SetLowerCase( bool bFlag )
	{
		_WINQ_FCONTEXT( "CComboBoxFactory::SetLowerCase" );
		SetStyleBits( CBS_LOWERCASE, bFlag );
	}




	//--------------------------------------------------------------------------------
	CComboBox::CComboBox() : CWinCtrlWindow()
	{	
		_WINQ_FCONTEXT( "CComboBox::CComboBox" );
	}

	//--------------------------------------------------------------------------------
	CComboBox::~CComboBox()
	{
		_WINQ_FCONTEXT( "CComboBox::~CComboBox" );
	}

	//--------------------------------------------------------------------------------
	long CComboBox::AddString( const TCHAR* strItem )
	{
		_WINQ_FCONTEXT( "CComboBox::AddString" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_ADDSTRING, 0, reinterpret_cast< Cmp_long_ptr >( strItem ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::DeleteString( Cmp_uint_ptr Index )
	{
		_WINQ_FCONTEXT( "CComboBox::DeleteString" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_DELETESTRING, Index, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::Dir( Cmp_uint_ptr Flags, const TCHAR* strPath )
	{
		_WINQ_FCONTEXT( "CComboBox::Dir" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_DIR, Flags, reinterpret_cast< Cmp_long_ptr >( strPath ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::FindString( Cmp_uint_ptr Index, const TCHAR* strSearch )
	{
		_WINQ_FCONTEXT( "CComboBox::FindString" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_FINDSTRING, Index, reinterpret_cast< Cmp_long_ptr >( strSearch ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::FindStringExact( Cmp_uint_ptr Index, const TCHAR* strSearch )
	{
		_WINQ_FCONTEXT( "CComboBox::FindStringExact" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_FINDSTRINGEXACT, Index, reinterpret_cast< Cmp_long_ptr >( strSearch ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetInfo( COMBOBOXINFO& Info )
	{
		_WINQ_FCONTEXT( "CComboBox::GetInfo" );
		long lResult = 0;
#if		( _WIN32_WINNT >= 0x0501 )
		lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETCOMBOBOXINFO, 0, reinterpret_cast< Cmp_long_ptr >( &Info ) );
#endif//( _WIN32_WINNT >= 0x0501 )
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetCount()
	{
		_WINQ_FCONTEXT( "CComboBox::GetCount" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETCOUNT, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetCueBanner( wchar_t* wstrBuffer, Cmp_long_ptr lBufferCount )
	{
		_WINQ_FCONTEXT( "CComboBox::GetCueBanner" );
		long lResult = 0;//m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETCUEBANNER, reinterpret_cast< Cmp_uint_ptr >( wstrBuffer ), lBufferCount );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetCurSel()
	{
		_WINQ_FCONTEXT( "CComboBox::GetCurSel" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETCURSEL, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetDroppedControlRect( CRectangle& rcCtrl )
	{
		_WINQ_FCONTEXT( "CComboBox::GetDroppedControlRect" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETDROPPEDCONTROLRECT, 0, reinterpret_cast< Cmp_long_ptr >( &rcCtrl ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CComboBox::GetDroppedState()
	{
		_WINQ_FCONTEXT( "CComboBox::GetDroppedState" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int)CB_GETDROPPEDSTATE, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetDroppedWidth()
	{
		_WINQ_FCONTEXT( "CComboBox::GetDroppedWidth" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETDROPPEDWIDTH, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetEditSel( unsigned long& dwBeginSel, unsigned long& dwEndSel )
	{
		_WINQ_FCONTEXT( "CComboBox::GetEditSel" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETEDITSEL, reinterpret_cast< Cmp_uint_ptr >( &dwBeginSel ), reinterpret_cast< Cmp_long_ptr >( &dwEndSel ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CComboBox::GetExtendedUI()
	{
		_WINQ_FCONTEXT( "CComboBox::GetExtendedUI" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETEXTENDEDUI, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetHorizontalExtent()
	{
		_WINQ_FCONTEXT( "CComboBox::GetHorizontalExtent" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETHORIZONTALEXTENT, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetItemData( Cmp_uint_ptr Index )
	{
		_WINQ_FCONTEXT( "CComboBox::GetItemData" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETITEMDATA, Index, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetItemHeight( Cmp_uint_ptr Index )
	{
		_WINQ_FCONTEXT( "CComboBox::GetItemHeight" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETITEMHEIGHT, Index, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetText( Cmp_uint_ptr Index, wchar_t* wstrBuffer )
	{
		_WINQ_FCONTEXT( "CComboBox::GetText" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETLBTEXT, Index, reinterpret_cast< Cmp_long_ptr >( wstrBuffer ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetTextLength( Cmp_uint_ptr Index )
	{
		_WINQ_FCONTEXT( "CComboBox::GetTextLength" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETLBTEXTLEN, Index, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetLocale()
	{
		_WINQ_FCONTEXT( "CComboBox::GetLocale" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETLOCALE, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetMinVisible()
	{
		_WINQ_FCONTEXT( "CComboBox::GetMinVisible" );
		long lResult = 0;//m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETMINVISIBLE, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::GetTopIndex()
	{
		_WINQ_FCONTEXT( "CComboBox::GetTopIndex" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_GETTOPINDEX, 0, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::InitStorage( Cmp_uint_ptr ItemCount, long lBytes )
	{
		_WINQ_FCONTEXT( "CComboBox::InitStorage" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_INITSTORAGE, ItemCount, static_cast< Cmp_long_ptr >( lBytes ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::InsertString( Cmp_uint_ptr Index, const char* strItem )
	{
		_WINQ_FCONTEXT( "CComboBox::InsertString" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_INSERTSTRING, Index, reinterpret_cast< Cmp_long_ptr >( strItem ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CComboBox::LimitText( Cmp_uint_ptr CharCount )
	{
		_WINQ_FCONTEXT( "CComboBox::LimitText" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_LIMITTEXT, CharCount, 0 );
	}

	//--------------------------------------------------------------------------------
	void CComboBox::ResetContent()
	{
		_WINQ_FCONTEXT( "CComboBox::ResetContent" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_RESETCONTENT, 0, 0 );
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SelectString( Cmp_uint_ptr Index, const TCHAR* strSearch )
	{
		_WINQ_FCONTEXT( "CComboBox::SelectString" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SELECTSTRING, Index, reinterpret_cast< Cmp_long_ptr >( strSearch ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetCueBanner( wchar_t* strCue )
	{
		_WINQ_FCONTEXT( "CComboBox::SetCueBanner" );
		long lResult = 0;//m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETCUEBANNER, 0, reinterpret_cast< Cmp_long_ptr >( strCue ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetCurSel( Cmp_uint_ptr Index )
	{
		_WINQ_FCONTEXT( "CComboBox::SetCurSel" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETCURSEL, Index, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetDroppedWidth( Cmp_uint_ptr PixelWidth )
	{
		_WINQ_FCONTEXT( "CComboBox::SetDroppedWidth" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETDROPPEDWIDTH, PixelWidth, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetEditSel( unsigned short wSelBegin, unsigned short wSelEnd )
	{
		_WINQ_FCONTEXT( "CComboBox::SetEditSel" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETEDITSEL, 0, MakeLParam( wSelBegin, wSelEnd ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetExtendedUI( bool bExtended )
	{
		_WINQ_FCONTEXT( "CComboBox::SetExtendedUI" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETEXTENDEDUI, static_cast< Cmp_uint_ptr >( bExtended ? 1 : 0 ), 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetHorizontalExtent( Cmp_uint_ptr PixelWidth )
	{
		_WINQ_FCONTEXT( "CComboBox::SetHorizontalExtent" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETHORIZONTALEXTENT, PixelWidth, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetItemData( Cmp_uint_ptr Index, Cmp_long_ptr lItemData )
	{
		_WINQ_FCONTEXT( "CComboBox::SetItemData" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETITEMDATA, Index, lItemData );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetItemHeight( Cmp_uint_ptr Index, long lPixelHeight )
	{
		_WINQ_FCONTEXT( "CComboBox::SetItemHeight" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETITEMHEIGHT, Index, static_cast< Cmp_long_ptr >( lPixelHeight ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetLocale( Cmp_uint_ptr LocaleID )
	{
		_WINQ_FCONTEXT( "CComboBox::SetLocale" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETLOCALE, LocaleID, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CComboBox::SetMinvisible( Cmp_uint_ptr MinVisible )
	{
		_WINQ_FCONTEXT( "CComboBox::SetMinvisible" );
		bool bResult = false;//( m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETMINVISIBLE, MinVisible, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CComboBox::SetTopIndex( Cmp_uint_ptr TopIndex )
	{
		_WINQ_FCONTEXT( "CComboBox::SetTopIndex" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SETTOPINDEX, TopIndex, 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CComboBox::ShowDropDown( bool bShow )
	{
		_WINQ_FCONTEXT( "CComboBox::ShowDropDown" );
		m_Win32MsgHandler.Send( Ref(), (unsigned int) CB_SHOWDROPDOWN, static_cast< Cmp_uint_ptr >( bShow ? 1 : 0 ), 0 );
	}


}//nsWin32
