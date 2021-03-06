//WinQLDateTimePicker.cpp

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
#include "WinQL/GUI/Windows/DateTimePicker.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CDateTimePickerClass );

	//--------------------------------------------------------------------------------
	CDateTimePickerClass::CDateTimePickerClass() : m_ComCtrl32( CCommonCtrl::CCDATE_CLASSES )
	{
		_WINQ_FCONTEXT( "CDateTimePickerClass::CDateTimePickerClass" );
	}

	//--------------------------------------------------------------------------------
	CDateTimePickerClass::~CDateTimePickerClass()
	{
		_WINQ_FCONTEXT( "CDateTimePickerClass::~CDateTimePickerClass" );
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerClass::Preregistered()
	{ 
		_WINQ_FCONTEXT( "CDateTimePickerClass::Preregistered" );
		return true; 
	}

	//--------------------------------------------------------------------------------
	const TCHAR* CDateTimePickerClass::Name()
	{ 
		_WINQ_FCONTEXT( "CDateTimePickerClass::Name" );
		return _TXT( "SysDateTimePick32" ); 
	}




	__QOR_IMPLEMENT_OCLASS_LUID( CDateTimePickerFactory );

	//--------------------------------------------------------------------------------
	CDateTimePickerFactory::CDateTimePickerFactory() : CWindowFactory()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::CDateTimePickerFactory" );
	}

	//--------------------------------------------------------------------------------
	CDateTimePicker* CDateTimePickerFactory::Create()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::Instance" );
		return new CDateTimePicker;//PreCreateWindow< CDateTimePicker, CDateTimePickerClass >();
	}

	//--------------------------------------------------------------------------------
	CDateTimePickerFactory::~CDateTimePickerFactory()
	{	
		_WINQ_FCONTEXT( "CDateTimePickerFactory::~CDateTimePickerFactory" );
	}
			
	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetUpDown()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetUpDown" );
		return GetStyleBits( DTS_UPDOWN );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetUpDown( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetUpDown" );
		SetStyleBits( DTS_UPDOWN, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetShowNone()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetShowNone" );
		return GetStyleBits( DTS_SHOWNONE );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetShowNone( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetShowNone" );
		SetStyleBits( DTS_SHOWNONE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetShortDateFormat()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetShortDateFormat" );
		return GetStyleBits( DTS_SHORTDATEFORMAT );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetShortDateFormat( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetShortDateFormat" );
		SetStyleBits( DTS_SHORTDATEFORMAT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetLongDateFormat()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetLongDateFormat" );
		return GetStyleBits( DTS_LONGDATEFORMAT );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetLongDateFormat( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetLongDateFormat" );
		SetStyleBits( DTS_LONGDATEFORMAT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetShortDateCenturyFormat()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetShortDateCenturyFormat" );
		bool bResult = false;
#if		( _WIN32_IE >= 0x500 )
		bResult = GetStyleBits( DTS_SHORTDATECENTURYFORMAT );
#endif//( _WIN32_IE >= 0x500 )
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetShortDateCenturyFormat( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetShortDateCenturyFormat" );
#if		( _WIN32_IE >= 0x500 )
		SetStyleBits( DTS_SHORTDATECENTURYFORMAT, bFlag );
#endif//( _WIN32_IE >= 0x500 )
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetTimeFormat()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetTimeFormat" );
		return GetStyleBits( DTS_TIMEFORMAT );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetTimeFormat( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetTimeFormat" );
		SetStyleBits( DTS_TIMEFORMAT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetAppCanParse()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetAppCanParse" );
		return GetStyleBits( DTS_APPCANPARSE );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetAppCanParse( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetAppCanParse" );
		SetStyleBits( DTS_APPCANPARSE, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePickerFactory::GetRightAlign()
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::GetRightAlign" );
		return GetStyleBits( DTS_RIGHTALIGN );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePickerFactory::SetRightAlign( bool bFlag )
	{
		_WINQ_FCONTEXT( "CDateTimePickerFactory::SetRightAlign" );
		SetStyleBits( DTS_RIGHTALIGN, bFlag );
	}



	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CDateTimePicker );

	//--------------------------------------------------------------------------------
	CDateTimePicker::CDateTimePicker() : CWinCtrlWindow()
	{				
		_WINQ_FCONTEXT( "CDateTimePicker::CDateTimePicker" );
	}

	//--------------------------------------------------------------------------------
	CDateTimePicker::~CDateTimePicker()
	{
		_WINQ_FCONTEXT( "CDateTimePicker::~CDateTimePicker" );
	}

	//--------------------------------------------------------------------------------
	long CDateTimePicker::OnNotify( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnNotify" );
		long lResult = 0;

		if( pHdr != 0 )
		{
			switch ( pHdr->m_uiCode )
			{
			case DTN_CLOSEUP:
				{
					OnCloseUp( pHdr );
				}
				break;
			case DTN_DATETIMECHANGE:
				{
					OnDateTimeChange( reinterpret_cast< LPNMDATETIMECHANGE >( pHdr ) );
					lResult = 0;
				}
				break;
			case DTN_DROPDOWN:
				{
					OnDropDown( pHdr );
				}
				break;
			case DTN_FORMAT:
				{
					OnFormat( reinterpret_cast< NMDATETIMEFORMAT* >( pHdr ) );
					lResult = 0;
				}
				break;
			case DTN_FORMATQUERY:
				{
					OnFormatQuery( reinterpret_cast< NMDATETIMEFORMATQUERY* >( pHdr ) );
					lResult = 0;
				}
				break;
			case DTN_USERSTRING:
				{
					OnUserString( reinterpret_cast< NMDATETIMESTRING* >( pHdr ) );
					lResult = 0;
				}
				break;
			case DTN_WMKEYDOWN:
				{
					OnKeyDown( reinterpret_cast< NMDATETIMEWMKEYDOWN* >( pHdr ) );
					lResult = 0;
				}
				break;
			case NM_KILLFOCUS:
				{
					OnKillFocus( pHdr );
				}
				break;
			case NM_SETFOCUS:
				{
					OnSetFocus( pHdr );
				}
				break;
			}
		}
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnCloseUp( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnCloseUp" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnDateTimeChange( LPNMDATETIMECHANGE pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnDateTimeChange" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnDropDown( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnDropDown" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnFormat( NMDATETIMEFORMAT* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnFormat" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnFormatQuery( NMDATETIMEFORMATQUERY* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnFormatQuery" );
		pHdr->szMax.cx = 100;
		pHdr->szMax.cy = 30;
	}			

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnUserString( NMDATETIMESTRING* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnUserString" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnKeyDown( NMDATETIMEWMKEYDOWN* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnKeyDown" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnKillFocus( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnKillFocus" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::OnSetFocus( NotificationMessageHeader* pHdr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::OnSetFocus" );
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::CloseMonthCal()
	{
		_WINQ_FCONTEXT( "CDateTimePicker::CloseMonthCal" );
#if		( NTDDI_VERSION >= NTDDI_VISTA )
		m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_CLOSEMONTHCAL, 0, 0 );
#endif//( NTDDI_VERSION >= NTDDI_VISTA )
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::GetInfo( DATETIMEPICKERINFO& Info )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetInfo" );
#if		( NTDDI_VERSION >= NTDDI_VISTA )
		m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETDATETIMEPICKERINFO, 0, reinterpret_cast< Cmp_long_ptr >( &Info ) );
#endif//( NTDDI_VERSION >= NTDDI_VISTA )
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::GetIdealSize( SIZE& IdealSize )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetIdealSize" );
#if		( NTDDI_VERSION >= NTDDI_VISTA )
		m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETIDEALSIZE, 0, reinterpret_cast< Cmp_long_ptr >( &IdealSize ) );
#endif//( NTDDI_VERSION >= NTDDI_VISTA )
	}

	//--------------------------------------------------------------------------------
	long CDateTimePicker::GetMonthCalColour( int iColour )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetMonthCalColour" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETMCCOLOR, static_cast< Cmp_uint_ptr >( iColour ), 0 );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	CFont::refType CDateTimePicker::GetMonthCalFont()
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetMonthCalFont" );
		
#if		( _WIN32_IE >= 0x0400 )
		CFontHandle Handle( 0, (void*)( m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETMCFONT, 0, 0 ) ) );
		return CFont::refType( CFont::FromHandle( CFontHandle::refType( &Handle, false ) ), false );
#else
		return CFont::refType( 0, false );
#endif//( _WIN32_IE >= 0x0400 )
	}

	//--------------------------------------------------------------------------------
	long CDateTimePicker::GetMonthCalStyle()
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetMonthCalStyle" );
		long lResult = 0;
#if		( NTDDI_VERSION >= NTDDI_VISTA )
		lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETMCSTYLE, 0, 0 );
#endif//( NTDDI_VERSION >= NTDDI_VISTA )
		return lResult;
	}

	//--------------------------------------------------------------------------------
	COSWindow::refType CDateTimePicker::GetMonthCal()
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetMonthCal" );
		CWindowHandle Handle( 0, (void*)( m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETMONTHCAL, 0, 0 ) ) );
		return COSWindow::refType( COSWindow::FromHandle( CWindowHandle::refType( &Handle, false ) ), false );
	}

	//--------------------------------------------------------------------------------
	long CDateTimePicker::GetRange( SystemTime* pTimeRange )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetRange" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETRANGE, 0, reinterpret_cast< Cmp_long_ptr >( pTimeRange ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CDateTimePicker::GetSystemTime( SystemTime& SysTime )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::GetSystemTime" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_GETSYSTEMTIME, 0, reinterpret_cast< Cmp_long_ptr >( &SysTime ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePicker::SetFormat( const TCHAR* strFormat )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::SetFormat" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_SETFORMAT, 0, reinterpret_cast< Cmp_long_ptr >( strFormat ) ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	long CDateTimePicker::SetMonthCalColour( int iColour, unsigned long clr )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::SetMonthCalColour" );
		long lResult = m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_SETMCCOLOR, static_cast< Cmp_uint_ptr >( iColour ), static_cast< Cmp_long_ptr >( clr ) );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	void CDateTimePicker::SetMonthCalFont( CFont& Font, bool bRedraw )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::SetMonthCalFont" );
#if		( _WIN32_IE >= 0x0400 )
		m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_SETMCFONT, reinterpret_cast< Cmp_uint_ptr >( Font.Handle()->Use() ), MakeLParam( bRedraw ? 1 : 0, 0 ) );
#endif//( _WIN32_IE >= 0x0400 )
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePicker::SetRange( unsigned long dwFlags, SystemTime* pTimeRange )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::SetRange" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_SETRANGE, static_cast< Cmp_uint_ptr >( dwFlags ), reinterpret_cast< Cmp_long_ptr >( pTimeRange ) ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CDateTimePicker::SetSystemTime( unsigned long dwFlags, SystemTime& Time )
	{
		_WINQ_FCONTEXT( "CDateTimePicker::SetSystemTime" );
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int) DTM_SETRANGE, static_cast< Cmp_uint_ptr >( dwFlags ), reinterpret_cast< Cmp_long_ptr >( &Time ) ) ? true : false );
		return bResult;
	}

}//nsWin32

