//WinQLThemeData.cpp

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
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usafe: stored in member for later use" );
#include "WinQL/GUI/Theme/ThemeData.h"
__QCMP_WARNING_POP
#include "WinQAPI/User32.h"
#include "WinQAPI/UxTheme.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QCMP_DECLARE_PERTHREAD CThemeHandleMap* p_tThemeHandleMap = 0;

	__QOR_IMPLEMENT_OCLASS_LUID( CThemeAPI );

	//--------------------------------------------------------------------------------
	void CThemeData::Uninit()
	{
		_WINQ_FCONTEXT( "CThemeData::Uninit" );

		CThemeHandleMap* pMap = p_tThemeHandleMap;

		if( pMap && !( m_Handle.IsNull() ) )
		{
			pMap->Remove( m_Handle.Ref() );
		}
	}

	//--------------------------------------------------------------------------------
	void CThemeData::Init()
	{
		_WINQ_FCONTEXT( "CThemeData::Init" );

		CThemeHandleMap* pMap = p_tThemeHandleMap;

		if( pMap == 0 )
		{
			pMap = new CThemeHandleMap;
		}

		if( !( m_Handle.IsNull() ) )
		{
			pMap->Add( m_Handle.Ref(), this );
		}

		if( p_tThemeHandleMap == 0 )
		{
			p_tThemeHandleMap = pMap;
		}
	}

	//--------------------------------------------------------------------------------
	CThemeAPI::CThemeAPI() : m_UXTheme( nsWinQAPI::CUXTheme::Instance() )
	{
		_WINQ_FCONTEXT( "CThemeAPI::CThemeAPI" );
	}

	//--------------------------------------------------------------------------------
	CThemeAPI::~CThemeAPI()
	{
		_WINQ_FCONTEXT( "CThemeAPI::~CThemeAPI" );
	}

	//--------------------------------------------------------------------------------
	CThemeAPI& CThemeAPI::operator = ( CThemeAPI& src )
	{
		_WINQ_FCONTEXT( "CThemeAPI::operator =" );
		return *this;
	}

	//--------------------------------------------------------------------------------
	long CThemeAPI::Enable( bool bEnable )
	{
		_WINQ_FCONTEXT( "CThemeAPI::Enable" );
		long lResult = m_UXTheme.EnableTheming( bEnable ? TRUE : FALSE );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	long CThemeAPI::GetCurrentName( wchar_t* pszThemeFileName, int dwMaxNameChars, wchar_t* pszColorBuff, int cchMaxColorChars, wchar_t* pszSizeBuff, int cchMaxSizeChars )
	{
		_WINQ_FCONTEXT( "CThemeAPI::GetCurrentName" );
		long lResult = m_UXTheme.GetCurrentThemeName( pszThemeFileName, dwMaxNameChars, pszColorBuff, cchMaxColorChars, pszSizeBuff, cchMaxSizeChars );
		return lResult;
	}

	//--------------------------------------------------------------------------------
	unsigned long CThemeAPI::GetAppProperties()
	{
		_WINQ_FCONTEXT( "CThemeAPI::GetAppProperties" );
		unsigned long ulResult = m_UXTheme.GetThemeAppProperties();
		return ulResult;
	}

	//--------------------------------------------------------------------------------
	void CThemeAPI::SetAppProperties( unsigned long ulFlags )
	{
		_WINQ_FCONTEXT( "CThemeAPI::SetAppProperties" );
		m_UXTheme.SetThemeAppProperties( ulFlags );
	}

	//--------------------------------------------------------------------------------
	long CThemeAPI::GetDocumentationProperty( const wchar_t* pszThemeName, const wchar_t* pszPropertyName, wchar_t* pszValueBuff, int cchMaxValChars )
	{
		_WINQ_FCONTEXT( "CThemeAPI::GetDocumentationProperty" );
		return m_UXTheme.GetThemeDocumentationProperty( pszThemeName, pszPropertyName, pszValueBuff, cchMaxValChars );
	}

	//--------------------------------------------------------------------------------
	CThemeData::refType CThemeAPI::GetWindowTheme( COSWindow::refType Wnd )
	{
		_WINQ_FCONTEXT( "CThemeAPI::GetWindowTheme" );
		return CThemeData::FromHandle( CThemeHandle( 0, (void*)(m_UXTheme.GetWindowTheme( reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ) )) ).Ref() );
	}

	//--------------------------------------------------------------------------------
	bool CThemeAPI::IsAppThemed()
	{
		_WINQ_FCONTEXT( "CThemeAPI::IsAppThemed" );
		bool bResult = m_UXTheme.IsAppThemed() ? true : false;
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CThemeAPI::IsCompositionActive()
	{
		_WINQ_FCONTEXT( "CThemeAPI::IsCompositionActive" );
		return m_UXTheme.IsCompositionActive() ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CThemeAPI::IsThemeActive()
	{
		_WINQ_FCONTEXT( "CThemeAPI::IsThemeActive" );
		return m_UXTheme.IsThemeActive() ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CThemeAPI::IsDialogTextureEnabled( COSWindow::refType Wnd )
	{
		return m_UXTheme.IsThemeDialogTextureEnabled( 
			reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ) ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	long CThemeAPI::SetWindowTheme( COSWindow::refType Wnd, const wchar_t* pszSubAppName, const wchar_t* pszSubIdList )
	{
		return m_UXTheme.SetWindowTheme( 
			reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ), 
			pszSubAppName, pszSubIdList );
	}

	//--------------------------------------------------------------------------------
	long CThemeAPI::SetWindowAttribute( COSWindow::refType Wnd, nsWin32::WINDOWTHEMEATTRIBUTETYPE eAttribute, void* pvAttribute, unsigned long cbAttribute )
	{
		return m_UXTheme.SetWindowThemeAttribute( 
			reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ), 
			static_cast< ::WINDOWTHEMEATTRIBUTETYPE >( eAttribute ), 
			pvAttribute, cbAttribute );
	}

	//--------------------------------------------------------------------------------
	long CThemeAPI::SetWindowNonClientAttributes( COSWindow::refType Wnd, unsigned long dwMask, unsigned long dwAttributes )
	{
		return m_UXTheme.SetWindowThemeNonClientAttributes( 
			reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ), 
			dwMask, dwAttributes );
	}

	//--------------------------------------------------------------------------------





	__QOR_IMPLEMENT_OCLASS_LUID( CThemeData );

	__QCMP_WARNING_PUSH
	__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usafe: stored in member for later use" );
	//--------------------------------------------------------------------------------
	CThemeData::CThemeData( COSWindow::refType Wnd, const wchar_t* pszClassList ) : m_UXTheme( nsWinQAPI::CUXTheme::Instance() )
	,	m_Handle( this, 0 )
	{
		m_Handle = ( m_UXTheme.OpenThemeData( reinterpret_cast< HWND >( Wnd->Handle()->Use() ), pszClassList ) );
		Init();
	}

	//--------------------------------------------------------------------------------
	CThemeData::CThemeData( COSWindow::refType Wnd, const wchar_t* pszClassIdList, unsigned long dwFlags ) : m_UXTheme( nsWinQAPI::CUXTheme::Instance() )
	,	m_Handle( this, 0 )
	{
		m_Handle = ( m_UXTheme.OpenThemeDataEx( reinterpret_cast< HWND >( Wnd->Handle()->Use() ), pszClassIdList, dwFlags ) );
		Init();
	}

	//--------------------------------------------------------------------------------
	CThemeData::CThemeData( CThemeHandle::refType hTheme ) : m_UXTheme( nsWinQAPI::CUXTheme::Instance() )
	,	m_Handle( this, hTheme->AsHandle().ptr() )
	{
		Init();
	}

	__QCMP_WARNING_POP

	//--------------------------------------------------------------------------------
	CThemeData::~CThemeData()
	{
		m_UXTheme.CloseThemeData( m_Handle.Use() );
		Uninit();
	}

	//--------------------------------------------------------------------------------
	CThemeData& CThemeData::operator = ( CThemeData& src )
	{
		m_Handle = src.Handle()->AsHandle().ptr();
		return *this;
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawBackground( CDeviceContext::refType dc, int iPartId, int iStateId, const nsWin32::RECT* pRect, const nsWin32::RECT* pClipRect )
	{
		return m_UXTheme.DrawThemeBackground( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), iPartId, iStateId, 
			reinterpret_cast< const ::RECT* >( pRect ), 
			reinterpret_cast< const ::RECT* >( pClipRect ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawBackgroundEx( CDeviceContext::refType dc, int iPartId, int iStateId, const nsWin32::RECT* pRect, const nsWin32::DTBGOPTS* pOptions )
	{
		return m_UXTheme.DrawThemeBackgroundEx(
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), iPartId, iStateId,
			reinterpret_cast< const ::RECT* >( pRect ),
			reinterpret_cast< const ::DTBGOPTS* >( pOptions ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawEdge( CDeviceContext::refType dc, int iPartId, int iStateId, const nsWin32::RECT* pDestRect, unsigned int uEdge, unsigned int uFlags, nsWin32::RECT* pContentRect )
	{
		return m_UXTheme.DrawThemeEdge(
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), iPartId, iStateId, 
			reinterpret_cast< const ::RECT* >( pDestRect ),
			uEdge, uFlags, 
			reinterpret_cast< ::RECT* >( pContentRect ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawIcon( CDeviceContext::refType dc, int iPartId, int iStateId, const nsWin32::RECT* pRect, CImageList::refType iml, int iImageIndex )
	{
		return m_UXTheme.DrawThemeIcon(
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), iPartId, iStateId,
			reinterpret_cast< const ::RECT* >( pRect ),
			reinterpret_cast< ::HIMAGELIST >( iml->Handle()->Use() ), iImageIndex );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawParentBackground( COSWindow::refType Wnd, CDeviceContext::refType dc, const nsWin32::RECT* prc )
	{
		return m_UXTheme.DrawThemeParentBackground(
			reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ),
			reinterpret_cast< const ::RECT* >( prc ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawParentBackgroundEx( COSWindow::refType Wnd, CDeviceContext::refType dc, unsigned long dwFlags, const nsWin32::RECT* prc )
	{
		return m_UXTheme.DrawThemeParentBackgroundEx(
			reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ),
			dwFlags,
			reinterpret_cast< const ::RECT* >( prc ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawTextW( CDeviceContext::refType dc, int iPartId, int iStateId, const wchar_t* pszText, int iCharCount, unsigned long dwTextFlags, unsigned long dwTextFlags2, const nsWin32::RECT* pRect )
	{
		return m_UXTheme.DrawThemeText(
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ),
			iPartId, iStateId, pszText, iCharCount, dwTextFlags, dwTextFlags2,
			reinterpret_cast< const ::RECT* >( pRect ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::DrawTextExW( CDeviceContext::refType dc, int iPartId, int iStateId, const wchar_t* pszText, int iCharCount, unsigned long dwFlags, nsWin32::RECT* pRect, const DTTOPTS* pOptions )
	{
		return m_UXTheme.DrawThemeTextEx(
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ),
			iPartId, iStateId, pszText, iCharCount, dwFlags,
			reinterpret_cast< ::RECT* >( pRect ),
			reinterpret_cast< const ::DTTOPTS* >( pOptions ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetBackgroundContentRect( CDeviceContext::refType dc, int iPartId, int iStateId, const nsWin32::RECT* pBoundingRect, nsWin32::RECT* pContentRect )
	{
		return m_UXTheme.GetThemeBackgroundContentRect( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ),
			iPartId, iStateId, 
			reinterpret_cast< const ::RECT* >( pBoundingRect ),
			reinterpret_cast< ::RECT* >( pContentRect ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetBackgroundExtent( CDeviceContext::refType dc, int iPartId, int iStateId, const nsWin32::RECT* pContentRect, nsWin32::RECT* pExtentRect )
	{
		return m_UXTheme.GetThemeBackgroundExtent( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ),
			iPartId, iStateId, 
			reinterpret_cast< const ::RECT* >( pContentRect ),
			reinterpret_cast< ::RECT* >( pExtentRect ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetBackgroundRegion( CDeviceContext::refType dc, int iPartId, int iStateId, const nsWin32::RECT* pRect, CRegion::refType Region )
	{
		return m_UXTheme.GetThemeBackgroundRegion( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), 
			iPartId, iStateId, 
			reinterpret_cast< const ::RECT* >( pRect ),
			reinterpret_cast< ::HRGN* >( Region->Handle()->Use() ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetBitmap( int iPartId, int iStateId, int iPropId, unsigned long dwFlags, CBitmap::refType Bitmap )
	{
		void* phBitmap = 0;
		long lResult = m_UXTheme.GetThemeBitmap(  reinterpret_cast< ::HTHEME >( m_Handle.Use() ), iPartId, iStateId, iPropId, dwFlags,  reinterpret_cast< ::HBITMAP* >( &phBitmap ) );
		Bitmap = CBitmap::FromHandle( CBitmapHandle( 0, phBitmap ).Ref() );
		return lResult;			
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetBool( int iPartId, int iStateId, int iPropId, int* pfVal )
	{
		return m_UXTheme.GetThemeBool( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			iPartId, iStateId, iPropId, pfVal );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetColour( int iPartId, int iStateId, int iPropId, unsigned long* pColor )
	{
		return m_UXTheme.GetThemeColor( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId, iPropId, 
			pColor );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetEnumValue( int iPartId, int iStateId, int iPropId, int* piVal )
	{
		return m_UXTheme.GetThemeEnumValue( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			iPartId, iStateId, iPropId, piVal );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetFileName( int iPartId, int iStateId, int iPropId, wchar_t* pszThemeFilename, int cchMaxBuffChars )
	{
		return m_UXTheme.GetThemeFilename( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId, iPropId, pszThemeFilename, cchMaxBuffChars );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetFont( CDeviceContext::refType dc, int iPartId, int iStateId, int iPropId, nsWin32::LOGFONTW* pFont )
	{
		return m_UXTheme.GetThemeFont( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), 
			iPartId, iStateId, iPropId, 
			reinterpret_cast< ::LOGFONTW* >( pFont ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetInt( int iPartId, int iStateId, int iPropId, int* piVal )
	{
		return m_UXTheme.GetThemeInt( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			iPartId, iStateId, iPropId, piVal );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetIntList( int iPartId, int iStateId, int iPropId, nsWin32::INTLIST* pIntList )
	{
		return m_UXTheme.GetThemeIntList( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			iPartId, iStateId, iPropId, 
			reinterpret_cast< ::INTLIST* >( pIntList ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetMargins( CDeviceContext::refType dc, int iPartId, int iStateId, int iPropId, nsWin32::RECT* prc, nsWin32::MARGINS* pMargins )
	{
		return m_UXTheme.GetThemeMargins( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), 
			iPartId, iStateId, iPropId, 
			reinterpret_cast< ::LPRECT >( prc ), 
			reinterpret_cast< ::MARGINS* >( pMargins ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetMetric( CDeviceContext::refType dc, int iPartId, int iStateId, int iPropId, int* piVal )
	{
		return m_UXTheme.GetThemeMetric( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), 
			iPartId, iStateId, iPropId, piVal );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetPartSize( CDeviceContext::refType dc, int iPartId, int iStateId, nsWin32::RECT* prc, nsWin32::THEMESIZE eSize, nsWin32::SIZE* psz )
	{
		return m_UXTheme.GetThemePartSize( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ),
			iPartId, iStateId, 
			reinterpret_cast< const ::RECT* >( prc ),
			static_cast< ::THEMESIZE >( eSize ), 
			reinterpret_cast< ::SIZE* >( psz ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetPosition( int iPartId, int iStateId, int iPropId, nsWin32::POINT* pPoint )
	{
		return m_UXTheme.GetThemePosition( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId, iPropId, 
			reinterpret_cast< ::POINT* >( pPoint ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetPropertyOrigin( int iPartId, int iStateId, int iPropId, PROPERTYORIGIN* pOrigin )
	{
		return m_UXTheme.GetThemePropertyOrigin( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId, iPropId, 
			reinterpret_cast< ::PROPERTYORIGIN* >( pOrigin ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetRect( int iPartId, int iStateId, int iPropId, nsWin32::RECT* pRect )
	{
		return m_UXTheme.GetThemeRect( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId, iPropId, 
			reinterpret_cast< ::RECT* >( pRect ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetStream( int iPartId, int iStateId, int iPropId, void** ppvStream, unsigned long* pcbStream, InstanceHandle hInst )
	{
		return m_UXTheme.GetThemeStream( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId, iPropId, ppvStream, pcbStream, 
			reinterpret_cast< ::HINSTANCE >( hInst ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetString( int iPartId, int iStateId, int iPropId, wchar_t* pszBuff, int cchMaxBuffChars )
	{
		return m_UXTheme.GetThemeString( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			iPartId, iStateId, iPropId, pszBuff, cchMaxBuffChars );
	}

	//--------------------------------------------------------------------------------
	bool CThemeData::GetSysBool( int iBoolID )
	{
		return m_UXTheme.GetThemeSysBool( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), iBoolID ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	unsigned long CThemeData::GetSysColour( int iColourID )
	{
		return m_UXTheme.GetThemeSysColor( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), iColourID );
	}

	//--------------------------------------------------------------------------------
	CBrush::refType CThemeData::GetSysColourBrush( int iColourID )
	{
		return CBrush::FromHandle( CBrushHandle( 0, (void*)( m_UXTheme.GetThemeSysColorBrush( reinterpret_cast< ::HTHEME >( m_Handle.Use() ), iColourID ) ) ).Ref() );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetSysFont( int iFontID, nsWin32::LOGFONTW* plf )
	{
		return m_UXTheme.GetThemeSysFont( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iFontID, reinterpret_cast< ::LOGFONTW* >( plf ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetSysInt( int iIntID, int* piValue )
	{
		return m_UXTheme.GetThemeSysInt( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			iIntID, piValue );
	}

	//--------------------------------------------------------------------------------
	int CThemeData::GetSysSize( int iSizeID )
	{
		return m_UXTheme.GetThemeSysSize( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iSizeID );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetSysString( int iStringID, wchar_t* pszStringBuff, int cchMaxStringChars )
	{
		return m_UXTheme.GetThemeSysString( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iStringID, pszStringBuff, cchMaxStringChars );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetTextExtent( CDeviceContext::refType dc, int iPartId, int iStateId, const wchar_t* pszText, int iCharCount, unsigned long dwTextFlags, const nsWin32::RECT* pBoundingRect, nsWin32::RECT* pExtentRect )
	{
		return m_UXTheme.GetThemeTextExtent( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), 
			iPartId, iStateId, pszText, iCharCount, dwTextFlags, 
			reinterpret_cast< const ::RECT* >( pBoundingRect ), 
			reinterpret_cast< ::RECT* >( pExtentRect ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetTextMetricsT( CDeviceContext::refType dc, int iPartId, int iStateId, nsWin32::TEXTMETRIC* ptm )
	{
		return m_UXTheme.GetThemeTextMetrics( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), 
			iPartId, iStateId, 
			reinterpret_cast< ::TEXTMETRIC* >( ptm ) );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::GetTransitionDuration( int iPartId, int iStateIdFrom, int iStateIdTo, int iPropId, unsigned long* pdwDuration )
	{
		return m_UXTheme.GetThemeTransitionDuration( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ),
			iPartId, iStateIdFrom, iStateIdTo, iPropId, pdwDuration );
	}

	//--------------------------------------------------------------------------------
	long CThemeData::HitTestBackground( CDeviceContext::refType dc, int iPartId, int iStateId, unsigned long dwOptions, const nsWin32::RECT* pRect, CRegion::refType Rgn, nsWin32::POINT ptTest, unsigned short* pwHitTestCode )
	{
		return m_UXTheme.HitTestThemeBackground( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			reinterpret_cast< ::HDC >( dc->Handle()->Use() ), 
			iPartId, iStateId, dwOptions, 
			reinterpret_cast< const ::RECT* >( pRect ), 
			reinterpret_cast< ::HRGN >( Rgn->Handle()->Use() ), 
			*( reinterpret_cast< ::POINT* >( &ptTest ) ), 
			pwHitTestCode );
	}

	//--------------------------------------------------------------------------------
	bool CThemeData::IsBackgroundPartiallyTransparent( int iPartId, int iStateId ) 
	{
		return m_UXTheme.IsThemeBackgroundPartiallyTransparent( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	bool CThemeData::IsPartDefined( int iPartId, int iStateId )
	{
		return m_UXTheme.IsThemePartDefined( 
			reinterpret_cast< ::HTHEME >( m_Handle.Use() ), 
			iPartId, iStateId ) ? true : false;
	}

	//--------------------------------------------------------------------------------
	CThemeData::refType CThemeData::Ref()
	{
		return refType( this, false );
	}

	//--------------------------------------------------------------------------------
	CThemeHandle::refType CThemeData::Handle( void )
	{
		return m_Handle.Ref();
	}

	//--------------------------------------------------------------------------------
	CThemeData::refType CThemeData::FromHandle( CThemeHandle::refType hTheme )
	{
		_WINQ_SFCONTEXT( "CThemeData::FromHandle" );
		CThemeData* pThemeData = 0;
		bool bOwningRef = false;
		__QOR_PROTECT
		{
			pThemeData = hTheme->Object< CThemeData >();
			
			if( pThemeData == 0 && p_tThemeHandleMap != 0 )
			{
				pThemeData = p_tThemeHandleMap->FindHandle( hTheme );
			}

			if( pThemeData == 0 )
			{
				pThemeData = new CThemeData( hTheme );
				bOwningRef = true;
			}

		}__QOR_ENDPROTECT

		return refType( pThemeData, bOwningRef );
	}

}//nsWin32
