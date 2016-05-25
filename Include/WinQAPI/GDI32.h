//GDI32.h

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

#ifndef _QSYS_API_WIN32_MODULES_GDI32_H_
#define _QSYS_API_WIN32_MODULES_GDI32_H_

#include "Kernel32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/DynamicLibrary.h"

#if		( WINVER < 0x0400 )

	typedef struct tagENUMLOGFONTEXA
	{
		LOGFONTA    elfLogFont;
		BYTE        elfFullName[LF_FULLFACESIZE];
		BYTE        elfStyle[LF_FACESIZE];
		BYTE        elfScript[LF_FACESIZE];
	} ENUMLOGFONTEXA, FAR *LPENUMLOGFONTEXA;

	typedef struct tagENUMLOGFONTEXW
	{
		LOGFONTW    elfLogFont;
		WCHAR       elfFullName[LF_FULLFACESIZE];
		WCHAR       elfStyle[LF_FACESIZE];
		WCHAR       elfScript[LF_FACESIZE];
	} ENUMLOGFONTEXW, FAR *LPENUMLOGFONTEXW;

#		ifdef UNICODE
			typedef ENUMLOGFONTEXW ENUMLOGFONTEX;
			typedef LPENUMLOGFONTEXW LPENUMLOGFONTEX;
#		else
			typedef ENUMLOGFONTEXA ENUMLOGFONTEX;
			typedef LPENUMLOGFONTEXA LPENUMLOGFONTEX;
#		endif // UNICODE
#endif//( WINVER < 0x0400 )

#if		( _WIN32_WINDOWS <= 0x0410 || _WIN32_WINNT < 0x0500 )

	typedef struct tagWCRANGE
	{
		WCHAR  wcLow;
		USHORT cGlyphs;
	} WCRANGE, *PWCRANGE,FAR *LPWCRANGE;

	typedef struct tagGLYPHSET
	{
		DWORD    cbThis;
		DWORD    flAccel;
		DWORD    cGlyphsSupported;
		DWORD    cRanges;
		WCRANGE  ranges[1];
	} GLYPHSET, *PGLYPHSET, FAR *LPGLYPHSET;

#	define STAMP_DESIGNVECTOR  (0x8000000 + 'd' + ('v' << 8))
#	define STAMP_AXESLIST      (0x8000000 + 'a' + ('l' << 8))
#	define MM_MAX_NUMAXES      16

	typedef struct tagDESIGNVECTOR
	{
		DWORD  dvReserved;
		DWORD  dvNumAxes;
		LONG   dvValues[MM_MAX_NUMAXES];
	} DESIGNVECTOR, *PDESIGNVECTOR, FAR *LPDESIGNVECTOR;

	typedef struct tagENUMLOGFONTEXDVA
	{
		ENUMLOGFONTEXA elfEnumLogfontEx;
		DESIGNVECTOR   elfDesignVector;
	} ENUMLOGFONTEXDVA, *PENUMLOGFONTEXDVA, FAR *LPENUMLOGFONTEXDVA;

	typedef struct tagENUMLOGFONTEXDVW
	{
		ENUMLOGFONTEXW elfEnumLogfontEx;
		DESIGNVECTOR   elfDesignVector;
	} ENUMLOGFONTEXDVW, *PENUMLOGFONTEXDVW, FAR *LPENUMLOGFONTEXDVW;

#	ifdef UNICODE
		typedef ENUMLOGFONTEXDVW ENUMLOGFONTEXDV;
		typedef PENUMLOGFONTEXDVW PENUMLOGFONTEXDV;
		typedef LPENUMLOGFONTEXDVW LPENUMLOGFONTEXDV;
#	else
		typedef ENUMLOGFONTEXDVA ENUMLOGFONTEXDV;
		typedef PENUMLOGFONTEXDVA PENUMLOGFONTEXDV;
		typedef LPENUMLOGFONTEXDVA LPENUMLOGFONTEXDV;
#	endif // UNICODE

#endif//( _WIN32_WINDOWS <= 0x0410 || WIN32_WINNT < 0x0500 )

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//Updated to match Windows XP SP2 System32\GDI32.dll

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQAPI ) CGDI32 : public CLibrary
	{

	public:

		__QOR_DECLARE_OCLASS_ID( CGDI32 );

		//--------------------------------------------------------------------------------
		CGDI32()
		{			
			m_hModule = CKernel32::LoadLibrary( TEXT("GDI32") );
		}

		//--------------------------------------------------------------------------------
		static CGDI32& Instance( void )
		{
			static CGDI32 _instance;
			return _instance;
		}

		//--------------------------------------------------------------------------------
		~CGDI32()
		{			
			CKernel32::FreeLibrary( m_hModule );
		}

		//--------------------------------------------------------------------------------
		//Bitmap functions
		BOOL BitBlt( HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop );
		HBITMAP CreateBitmap( int nWidth, int nHeight, UINT cPlanes, UINT cBitsPerPel, CONST VOID* lpvBits );
		HBITMAP CreateBitmapIndirect( CONST ::BITMAP* lpbm );
		HBITMAP CreateCompatibleBitmap( HDC hdc, int nWidth, int nHeight );
		HBITMAP CreateDIBitmap( HDC hdc, CONST ::BITMAPINFOHEADER* lpbmih, DWORD fdwInit, CONST VOID* lpbInit, CONST ::BITMAPINFO* lpbmi, UINT fuUsage );
		HBITMAP CreateDIBSection( HDC hdc, CONST ::BITMAPINFO* pbmi, UINT iUsage, VOID** ppvBits, HANDLE hSection, DWORD dwOffset );
		HBITMAP CreateDiscardableBitmap( HDC hdc, int nWidth, int nHeight );
		BOOL ExtFloodFill( HDC hdc, int nXStart, int nYStart, COLORREF crColor, UINT fuFillType );
		BOOL FloodFill( HDC hdc, int nXStart, int nYStart, COLORREF crFill );
		LONG GetBitmapBits( HBITMAP hbmp, LONG cbBuffer, LPVOID lpvBits );
		BOOL GetBitmapDimensionEx( HBITMAP hBitmap, LPSIZE lpDimension );
		UINT GetDIBColorTable( HDC hdc, UINT uStartIndex, UINT cEntries, ::RGBQUAD* pColors );
		int GetDIBits( HDC hdc, HBITMAP hbmp, UINT uStartScan, UINT cScanLines, LPVOID lpvBits, ::LPBITMAPINFO lpbi, UINT uUsage );
		COLORREF GetPixel( HDC hdc, int nXPos, int nYPos );
		int GetStretchBltMode( HDC hdc );
		BOOL MaskBlt( HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop );
		BOOL PlgBlt( HDC hdcDest, CONST ::POINT* lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask );
		LONG SetBitmapBits( HBITMAP hbmp, DWORD cBytes, CONST VOID* lpBits );
		BOOL SetBitmapDimensionEx( HBITMAP hBitmap, int nWidth, int nHeight, LPSIZE lpSize );
		UINT SetDIBColorTable( HDC hdc, UINT uStartIndex, UINT cEntries, CONST ::RGBQUAD* pColors );
		int SetDIBits( HDC hdc, HBITMAP hbmp, UINT uStartScan, UINT cScanLines, CONST VOID* lpvBits, CONST ::BITMAPINFO* lpbmi, UINT fuColorUse );
		int SetDIBitsToDevice( HDC hdc, int XDest, int YDest, DWORD dwWidth, DWORD dwHeight, int XSrc, int YSrc, UINT uStartScan, UINT cScanLines, CONST VOID* lpvBits, CONST ::BITMAPINFO* lpbmi, UINT fuColorUse );
		COLORREF SetPixel( HDC hdc, int X, int Y, COLORREF crColor );
		BOOL SetPixelV( HDC hdc, int X, int Y, COLORREF crColor );
		int SetStretchBltMode( HDC hdc, int iStretchMode );
		BOOL StretchBlt( HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop );
		int StretchDIBits( HDC hdc, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, CONST VOID* lpBits, CONST ::BITMAPINFO* lpBitsInfo, UINT iUsage, DWORD dwRop );

		//--------------------------------------------------------------------------------
		//Brush functions
		HBRUSH CreateBrushIndirect( CONST ::LOGBRUSH* lplb );
		HBRUSH CreateDIBPatternBrush( HGLOBAL hglbDIBPacked, UINT fuColorSpec );
		HBRUSH CreateDIBPatternBrushPt( CONST VOID* lpPackedDIB, UINT iUsage );
		HBRUSH CreateHatchBrush( int fnStyle, COLORREF clrref );
		HBRUSH CreatePatternBrush( HBITMAP hbmp );
		HBRUSH CreateSolidBrush( COLORREF crColor );
		HBRUSH ClearBrushAttributes( HBRUSH hbm, DWORD dwFlags );
		BOOL GetBrushOrgEx( HDC hdc, ::LPPOINT lppt );
		BOOL PatBlt( HDC hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop );
		BOOL SetBrushOrgEx( HDC hdc, int nXOrg, int nYOrg, ::LPPOINT lppt );
		DWORD GetBrushAttributes ( HBRUSH hbr );
		HBRUSH SetBrushAttributes ( HBRUSH hbm, DWORD dwFlags );
		HBRUSH SelectBrushLocal ( HBRUSH Currenthbm, HBRUSH Newhbm );

		//--------------------------------------------------------------------------------
		//Clipping functions
		int ExcludeClipRect( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
		int ExtSelectClipRgn( HDC hdc, HRGN hrgn, int fnMode );
		int GetClipBox( HDC hdc, ::LPRECT lprc );
		int GetClipRgn( HDC hdc, HRGN hrgn );
		int GetMetaRgn( HDC hdc, HRGN hrgn );
		int SetMetaRgn( HDC hdc );
		int GetRandomRgn( HDC hdc, HRGN hrgn, INT iNum );
		int IntersectClipRect( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
		int OffsetClipRgn( HDC hdc, int nXOffset, int nYOffset );
		BOOL PtVisible( HDC hdc, int X, int Y );
		BOOL RectVisible( HDC hdc, CONST ::RECT* lprc );
		BOOL SelectClipPath( HDC hdc, int iMode );
		int SelectClipRgn( HDC hdc, HRGN hrgn );

		//--------------------------------------------------------------------------------
		//Colour functions
		BOOL AnimatePalette( HPALETTE hpal, UINT iStartIndex, UINT cEntries, CONST ::PALETTEENTRY* ppe );
		HPALETTE CreateHalftonePalette( HDC hdc );
		HPALETTE CreatePalette( CONST ::LOGPALETTE* lplgpl );
		BOOL GetColorAdjustment( HDC hdc, ::LPCOLORADJUSTMENT lpca );
		COLORREF GetNearestColor( HDC hdc, COLORREF crColor );
		UINT GetNearestPaletteIndex( HPALETTE hpal, COLORREF crColor );
		UINT GetPaletteEntries( HPALETTE hpal, UINT iStartIndex, UINT nEntries, ::LPPALETTEENTRY lppe );
		UINT GetSystemPaletteEntries( HDC hdc, UINT iStartIndex, UINT nEntries, ::LPPALETTEENTRY lppe );
		UINT GetSystemPaletteUse( HDC hdc );
		UINT RealizePalette( HDC hdc );
		BOOL ResizePalette( HPALETTE hpal, UINT nEntries );
		HPALETTE SelectPalette( HDC hdc, HPALETTE hpal, BOOL bForceBackground );
		BOOL SetColorAdjustment( HDC hdc, CONST ::COLORADJUSTMENT* lpca );
		UINT SetPaletteEntries( HPALETTE hpal, UINT iStart, UINT cEntries, CONST ::PALETTEENTRY* lppe );
		UINT SetSystemPaletteUse( HDC hdc, UINT uUsage );
		BOOL UnrealizeObject( HGDIOBJ hgdiobj );
		BOOL UpdateColors( HDC hdc );
		BOOL GetDeviceGammaRamp( HDC hDC, LPVOID lpRamp );
		BOOL SetDeviceGammaRamp( HDC hDC, LPVOID lpRamp );
		int EnumICMProfiles( HDC hDC, ::ICMENUMPROC lpEnumICMProfilesFunc, LPARAM lParam );
		BOOL GetICMProfile( HDC hDC, LPDWORD lpcbName, LPTSTR lpszFilename );
		int SetICMMode( HDC hDC, int iEnableICM );
		BOOL SetICMProfile( HDC hDC, LPTSTR lpFileName );
		BOOL UpdateICMRegKey( DWORD dwReserved, LPTSTR lpszCMID, LPTSTR lpszFileName, UINT nCommand );
		BOOL CheckColorsInGamut( HDC hDC, LPVOID lpRGBTriples, LPVOID lpBuffer, UINT nCount );
		BOOL ColorCorrectPalette( HDC hDC, HPALETTE hPalette, DWORD dwFirstEntry, DWORD dwNumOfEntries );
		BOOL ColorMatchToTarget( HDC hDC, HDC hdcTarget, DWORD uiAction );
		HCOLORSPACE CreateColorSpace( ::LPLOGCOLORSPACE lpLogColorSpace );
		BOOL DeleteColorSpace( HCOLORSPACE hColorSpace );
		HCOLORSPACE GetColorSpace( HDC hDC );
		BOOL GetLogColorSpace( HCOLORSPACE hColorSpace, ::LPLOGCOLORSPACE lpBuffer, DWORD nSize );
		HCOLORSPACE SetColorSpace( HDC hDC, HCOLORSPACE hColorSpace );
		BOOL SetMagicColors( HDC hdc, ULONG u1, ULONG u2 );

		//--------------------------------------------------------------------------------
		//Coordinate transformation functions
		BOOL CombineTransform( ::LPXFORM lpxformResult, CONST ::XFORM* lpxform1, CONST ::XFORM* lpxform2 );
		BOOL DPtoLP( HDC hdc, ::LPPOINT lpPoints, int nCount );
		BOOL GetCurrentPositionEx( HDC hdc, ::LPPOINT lpPoint );
		int GetGraphicsMode( HDC hdc );
		int GetMapMode( HDC hdc );
		BOOL GetViewportExtEx( HDC hdc, ::LPSIZE lpSize );
		BOOL GetViewportOrgEx( HDC hdc, ::LPPOINT lpPoint );
		BOOL GetWindowExtEx( HDC hdc, ::LPSIZE lpSize );
		BOOL GetWindowOrgEx( HDC hdc, ::LPPOINT lpPoint );
		BOOL GetWorldTransform( HDC hdc, ::LPXFORM lpXform );
		BOOL LPtoDP( HDC hdc, ::LPPOINT lpPoints, int nCount );
		BOOL ModifyWorldTransform( HDC hdc, CONST ::XFORM* lpXform, DWORD iMode );
		BOOL OffsetViewportOrgEx( HDC hdc, int nXOffset, int nYOffset, ::LPPOINT lpPoint );
		BOOL OffsetWindowOrgEx( HDC hdc, int nXOffset, int nYOffset, ::LPPOINT lpPoint );
		BOOL ScaleViewportExtEx( HDC hdc, int Xnum, int Xdenom, int Ynum, int Ydenom, ::LPSIZE lpSize );
		BOOL ScaleWindowExtEx( HDC hdc, int Xnum, int Xdenom, int Ynum, int Ydenom, ::LPSIZE lpSize );
		int SetGraphicsMode( HDC hdc, int iMode );
		int SetMapMode( HDC hdc, int fnMapMode );
		BOOL SetViewportExtEx( HDC hdc, int nXExtent, int nYExtent, ::LPSIZE lpSize );
		BOOL SetViewportOrgEx( HDC hdc, int X, int Y, ::LPPOINT lpPoint );
		BOOL SetWindowExtEx( HDC hdc, int nXExtent, int nYExtent, ::LPSIZE lpSize );
		BOOL SetWindowOrgEx( HDC hdc, int X, int Y, ::LPPOINT lpPoint );
		BOOL SetWorldTransform( HDC hdc, CONST ::XFORM* lpXform );

		//--------------------------------------------------------------------------------
		//Device Context functions
		HDC CreateCompatibleDC( HDC hdc );
		HDC CreateDC( LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput, CONST ::DEVMODE* lpInitData );
		BOOL DeleteDC( HDC hdc );
		BOOL CancelDC( HDC hdc );
		HDC CreateIC( LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput, CONST ::DEVMODE* lpdvmInit );
		BOOL DeleteObject( HGDIOBJ hObject );
		int DrawEscape( HDC hdc, int nEscape, int cbInput, LPCSTR lpszInData );
		int EnumObjects( HDC hdc, int nObjectType, GOBJENUMPROC lpObjectFunc, LPARAM lParam );
		HGDIOBJ GetCurrentObject( HDC hdc, UINT uObjectType );
		COLORREF GetDCBrushColor( HDC hdc );
		BOOL GetDCOrgEx( HDC hdc, ::LPPOINT lpPoint );
		COLORREF GetDCPenColor( HDC hdc );
		int GetDeviceCaps( HDC hdc, int nIndex );
		DWORD GetLayout( HDC hdc );
		int GetObject( HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject );
		DWORD GetObjectType( HGDIOBJ h );
		HGDIOBJ GetStockObject( int fnObject );
		HDC ResetDC( HDC hdc, CONST ::DEVMODE* lpInitData );
		BOOL RestoreDC( HDC hdc, int nSavedDC );
		int SaveDC( HDC hdc );
		HGDIOBJ SelectObject( HDC hdc, HGDIOBJ hgdiobj );
		COLORREF SetDCBrushColor( HDC hdc, COLORREF crColor );
		COLORREF SetDCPenColor( HDC hdc, COLORREF crColor );
		DWORD SetLayout( HDC hdc, DWORD dwLayout );
		BOOL AlphaBlend( HDC hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, HDC hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, BLENDFUNCTION ftn );

		//--------------------------------------------------------------------------------
		//Drawing & Filled shape functions
		BOOL AngleArc( HDC hdc, int X, int Y, DWORD dwRadius, FLOAT eStartAngle, FLOAT eSweepAngle );
		BOOL Arc( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc );
		BOOL ArcTo( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 );
		int GetArcDirection( HDC hdc );
		BOOL LineDDA( int nXStart, int nYStart, int nXEnd, int nYEnd, ::LINEDDAPROC lpLineFunc, LPARAM lpData );
		BOOL LineTo( HDC hdc, int nXEnd, int nYEnd );
		BOOL MoveToEx( HDC hdc, int X, int Y, ::LPPOINT lpPoint );
		BOOL PolyBezier( HDC hdc, CONST ::POINT* lppt, DWORD cPoints );
		BOOL PolyBezierTo( HDC hdc, CONST ::POINT* lppt, DWORD cCount );
		BOOL PolyDraw( HDC hdc, CONST ::POINT* lppt, CONST BYTE* lpbTypes, int cCount );
		BOOL Polyline( HDC hdc, CONST ::POINT* lppt, int cPoints );
		BOOL PolylineTo( HDC hdc, CONST ::POINT* lppt, DWORD cCount );
		BOOL PolyPolyline( HDC hdc, CONST ::POINT* lppt, CONST DWORD* lpdwPolyPoints, DWORD cCount );
		int SetArcDirection( HDC hdc, int ArcDirection );
		BOOL Chord( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 );
		BOOL Ellipse( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
		BOOL Pie( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 );
		BOOL Polygon( HDC hdc, CONST ::POINT* lpPoints, int nCount );
		BOOL PolyPolygon( HDC hdc, CONST ::POINT* lpPoints, CONST INT* lpPolyCounts, int nCount );
		BOOL Rectangle( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
		BOOL RoundRect( HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight );

		//--------------------------------------------------------------------------------
		//Font & Text functions
		HANDLE AddFontMemResourceEx( PVOID pbFont, DWORD cbFont, PVOID pdv, DWORD* pcFonts );
		int AddFontResource( LPCTSTR lpszFilename );
		int AddFontResourceEx( LPCTSTR lpszFilename, DWORD fl, PVOID pdv );
		int AddFontResourceTracking ( LPCSTR lpString, int unknown );
		HFONT CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace );
		HFONT CreateFontIndirect( CONST ::LOGFONT* lplf );
		HFONT CreateFontIndirectEx( CONST ::ENUMLOGFONTEXDV* penumlfex );
		BOOL CreateScalableFontResource( DWORD fdwHidden, LPCTSTR lpszFontRes, LPCTSTR lpszFontFile, LPCTSTR lpszCurrentPath );
		BOOL EnableEUDC( BOOL fEnableEUDC );
		int EnumFontFamilies( HDC hdc, LPCTSTR lpszFamily, ::FONTENUMPROC lpEnumFontFamProc, LPARAM lParam );
		int EnumFontFamiliesEx( HDC hdc, ::LPLOGFONT lpLogfont, ::FONTENUMPROC lpEnumFontFamExProc, LPARAM lParam, DWORD dwFlags );
		int EnumFonts( HDC hdc, LPCTSTR lpFaceName, ::FONTENUMPROC lpFontFunc, LPARAM lParam );
		BOOL ExtTextOut( HDC hdc, int X, int Y, UINT fuOptions, CONST ::RECT* lprc, LPCTSTR lpString, UINT cbCount, CONST INT* lpDx );
		BOOL GetAspectRatioFilterEx( HDC hdc, ::LPSIZE lpAspectRatio );
		BOOL GetCharABCWidths( HDC hdc, UINT uFirstChar, UINT uLastChar, LPABC lpabc );
		BOOL GetCharABCWidthsFloat( HDC hdc, UINT iFirstChar, UINT iLastChar, ::LPABCFLOAT lpABCF );
		BOOL GetCharABCWidthsI( HDC hdc, UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc );
		DWORD GetCharacterPlacement( HDC hdc, LPCTSTR lpString, int nCount, int nMaxExtent, ::LPGCP_RESULTS lpResults, DWORD dwFlags );
		BOOL GetCharWidth( HDC hdc, UINT iFirstChar, UINT iLastChar, LPINT lpBuffer );
		BOOL GetCharWidth32( HDC hdc, UINT iFirstChar, UINT iLastChar, LPINT lpBuffer );
		BOOL GetCharWidthFloat( HDC hdc, UINT iFirstChar, UINT iLastChar, PFLOAT pxBuffer );
		BOOL GetCharWidthI( HDC hdc, UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer );
		DWORD GetFontData( HDC hdc, DWORD dwTable, DWORD dwOffset, LPVOID lpvBuffer, DWORD cbData );
		DWORD GetFontLanguageInfo( HDC hdc );
		DWORD GetFontUnicodeRanges( HDC hdc, ::LPGLYPHSET lpgs );
		DWORD GetGlyphIndices( HDC hdc, LPCTSTR lpstr, int c, LPWORD pgi, DWORD fl );
		DWORD GetFontResourceInfo( LPCTSTR szFontName, DWORD dwBufSize, LPTSTR szBuffer, DWORD dwInfo);
		DWORD GetGlyphOutline( HDC hdc, UINT uChar, UINT uFormat, ::LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, CONST ::MAT2* lpmat2 );
		DWORD GetKerningPairs( HDC hdc, DWORD nNumPairs, ::LPKERNINGPAIR lpkrnpair );
		UINT GetOutlineTextMetrics( HDC hdc, UINT cbData, ::LPOUTLINETEXTMETRIC lpOTM );
		BOOL GetRasterizerCaps( ::LPRASTERIZER_STATUS lprs, UINT cb );
		UINT GetTextAlign( HDC hdc );
		int GetTextCharacterExtra( HDC hdc );
		int GetTextCharset( HDC hdc );
		int GetTextCharsetInfo( HDC hdc, ::LPFONTSIGNATURE lpSig, DWORD dwFlags );
		COLORREF GetTextColor( HDC hdc );
		BOOL GetTextExtentExPoint( HDC hdc, LPCTSTR lpszStr, int cchString, int nMaxExtent, LPINT lpnFit, LPINT alpDx, ::LPSIZE lpSize );
		BOOL GetTextExtentExPointI( HDC hdc, LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, ::LPSIZE lpSize );
		BOOL GetTextExtentPoint( HDC hdc, LPCTSTR lpString, int cbString, ::LPSIZE lpSize );
		BOOL GetTextExtentPoint32( HDC hdc, LPCTSTR lpString, int c, ::LPSIZE lpSize );
		BOOL GetTextExtentPointI( HDC hdc, LPWORD pgiIn, int cgi, ::LPSIZE lpSize );
		int GetTextFace( HDC hdc, int nCount, LPTSTR lpFaceName );
		BOOL GetTextMetrics( HDC hdc, ::LPTEXTMETRIC lptm );
		BOOL PolyTextOut( HDC hdc, CONST ::POLYTEXT* pptxt, int cStrings );
		BOOL RemoveFontMemResourceEx( HANDLE fh );
		BOOL RemoveFontResource( LPCTSTR lpFileName );
		BOOL RemoveFontResourceEx( LPCTSTR lpFileName, DWORD fl, PVOID pdv );
		DWORD SetMapperFlags( HDC hdc, DWORD dwFlag );
		UINT SetTextAlign( HDC hdc, UINT fMode );
		int SetTextCharacterExtra( HDC hdc, int nCharExtra );
		COLORREF SetTextColor( HDC hdc, COLORREF crColor );
		BOOL SetTextJustification( HDC hdc, int nBreakExtra, int nBreakCount );
		BOOL TextOut( HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString );
		BOOL TranslateCharsetInfo( DWORD* pSrc, LPCHARSETINFO lpCs, DWORD dwFlags );

		//--------------------------------------------------------------------------------
		//MetaFile and EnhMetaFile functions
		HENHMETAFILE CloseEnhMetaFile( HDC hdc );
		HMETAFILE CloseMetaFile( HDC hdc );
		HENHMETAFILE CopyEnhMetaFile( HENHMETAFILE hemfSrc, LPCTSTR lpszFile );
		HMETAFILE CopyMetaFile( HMETAFILE hmfSrc, LPCTSTR lpszFile );
		HDC CreateEnhMetaFile( HDC hdcRef, LPCTSTR lpFilename, CONST ::RECT* lpRect, LPCTSTR lpDescription );
		HDC CreateMetaFile( LPCTSTR lpszFile );
		BOOL DeleteEnhMetaFile( HENHMETAFILE hemf );
		BOOL DeleteMetaFile( HMETAFILE hmf );
		BOOL EnumEnhMetaFile( HDC hdc, HENHMETAFILE hemf, ::ENHMFENUMPROC lpEnhMetaFunc, LPVOID lpData, CONST ::RECT* lpRect );
		BOOL EnumMetaFile( HDC hdc, HMETAFILE hmf, ::MFENUMPROC lpMetaFunc, LPARAM lParam );
		BOOL GdiComment( HDC hdc, UINT cbSize, CONST BYTE* lpData );
		HENHMETAFILE GetEnhMetaFile( LPCTSTR lpszMetaFile );
		UINT GetEnhMetaFileBits( HENHMETAFILE hemf, UINT cbBuffer, LPBYTE lpbBuffer );
		UINT GetEnhMetaFileDescription( HENHMETAFILE hemf, UINT cchBuffer, LPTSTR lpszDescription );
		UINT GetEnhMetaFileHeader( HENHMETAFILE hemf, UINT cbBuffer, ::LPENHMETAHEADER lpemh );
		UINT GetEnhMetaFilePaletteEntries( HENHMETAFILE hemf, UINT cEntries, ::LPPALETTEENTRY lppe );
		UINT GetMetaFileBitsEx( HMETAFILE hmf, UINT nSize, LPVOID lpvData );
		UINT GetWinMetaFileBits( HENHMETAFILE hemf, UINT cbBuffer, LPBYTE lpbBuffer, INT fnMapMode, HDC hdcRef );
		BOOL PlayEnhMetaFile( HDC hdc, HENHMETAFILE hemf, CONST ::RECT* lpRect );
		BOOL PlayEnhMetaFileRecord( HDC hdc, LPHANDLETABLE lpHandletable, CONST ENHMETARECORD* lpEnhMetaRecord, UINT nHandles );
		BOOL PlayMetaFile( HDC hdc, HMETAFILE hmf );
		BOOL PlayMetaFileRecord( HDC hdc, LPHANDLETABLE lpHandletable, LPMETARECORD lpMetaRecord, UINT nHandles );
		HENHMETAFILE SetEnhMetaFileBits( UINT cbBuffer, CONST BYTE* lpData );
		HMETAFILE SetMetaFileBitsEx( UINT nSize, CONST BYTE* lpData );
		HENHMETAFILE SetWinMetaFileBits( UINT cbBuffer, CONST BYTE* lpbBuffer, HDC hdcRef, CONST ::METAFILEPICT* lpmfp );

		//--------------------------------------------------------------------------------
		//OpenGl extension functions
		int ChoosePixelFormat( HDC hdc, CONST ::PIXELFORMATDESCRIPTOR* ppfd );
		int DescribePixelFormat( HDC hdc, int iPixelFormat, UINT nBytes, ::LPPIXELFORMATDESCRIPTOR ppfd );
		UINT GetEnhMetaFilePixelFormat( HENHMETAFILE hemf, DWORD cbBuffer, CONST ::PIXELFORMATDESCRIPTOR* ppfd );
		int GetPixelFormat( HDC hdc );
		BOOL SetPixelFormat( HDC hdc, int iPixelFormat, CONST ::PIXELFORMATDESCRIPTOR* ppfd );
		BOOL SwapBuffers( HDC hdc );

		//--------------------------------------------------------------------------------
		//Painting functions
		BOOL GdiFlush(VOID);
		DWORD GdiGetBatchLimit(VOID);
		DWORD GdiSetBatchLimit( DWORD dwLimit );
		COLORREF GetBkColor( HDC hdc );
		int GetBkMode( HDC hdc );
		UINT GetBoundsRect( HDC hdc, ::LPRECT lprcBounds, UINT flags );
		int GetROP2( HDC hdc );
		COLORREF SetBkColor( HDC hdc, COLORREF crColor );
		int SetBkMode( HDC hdc, int iBkMode );
		UINT SetBoundsRect( HDC hdc, CONST RECT* lprcBounds, UINT flags );
		int SetROP2( HDC hdc, int fnDrawMode );

		//--------------------------------------------------------------------------------
		//Path functions
		BOOL AbortPath( HDC hdc );
		BOOL BeginPath( HDC hdc );
		BOOL CloseFigure( HDC hdc );
		BOOL EndPath( HDC hdc );
		BOOL FillPath( HDC hdc );
		BOOL FlattenPath( HDC hdc );
		BOOL GetMiterLimit( HDC hdc, PFLOAT peLimit );
		int GetPath( HDC hdc, ::LPPOINT lpPoints, LPBYTE lpTypes, int nSize );
		HRGN PathToRegion( HDC hdc );
		BOOL SetMiterLimit( HDC hdc, FLOAT eNewLimit, PFLOAT peOldLimit );
		BOOL StrokeAndFillPath( HDC hdc );
		BOOL StrokePath( HDC hdc );
		BOOL WidenPath( HDC hdc );

		//--------------------------------------------------------------------------------
		//Pen functions
		HPEN CreatePen( int fnPenStyle, int nWidth, COLORREF crColor );
		HPEN CreatePenIndirect( CONST ::LOGPEN* lplgpn );
		HPEN ExtCreatePen( DWORD dwPenStyle, DWORD dwWidth, CONST ::LOGBRUSH* lplb, DWORD dwStyleCount, CONST DWORD* lpStyle );

		//--------------------------------------------------------------------------------
		//Printing & Spooling functions
		int AbortDoc( HDC hdc );
		int EndDoc( HDC hdc );
		int EndPage( HDC hdc );
		int Escape( HDC hdc, int nEscape, int cbInput, LPCSTR lpvInData, LPVOID lpvOutData );
		int ExtEscape( HDC hdc, int nEscape, int cbInput, LPCSTR lpszInData, int cbOutput, LPSTR lpszOutData );
		int SetAbortProc( HDC hdc, ::ABORTPROC lpAbortProc );
		int StartDoc( HDC hdc, CONST ::DOCINFO* lpdi );
		int StartPage( HDC hDC );

		//--------------------------------------------------------------------------------
		//Region functions
		int CombineRgn( HRGN hrgnDest, HRGN hrgnSrc1, HRGN hrgnSrc2, int fnCombineMode );
		HRGN CreateEllipticRgn( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
		HRGN CreateEllipticRgnIndirect( CONST ::RECT* lprc );
		HRGN CreatePolygonRgn( CONST ::POINT* lppt, int cPoints, int fnPolyFillMode );
		HRGN CreatePolyPolygonRgn( CONST ::POINT* lppt, CONST INT* lpPolyCounts, int nCount, int fnPolyFillMode );
		HRGN CreateRectRgn( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
		HRGN CreateRectRgnIndirect( CONST ::RECT* lprc );
		HRGN CreateRoundRectRgn( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidthEllipse, int nHeightEllipse );
		BOOL EqualRgn( HRGN hSrcRgn1, HRGN hSrcRgn2 );
		HRGN ExtCreateRegion( CONST ::XFORM* lpXform, DWORD nCount, CONST ::RGNDATA* lpRgnData );
		BOOL FillRgn( HDC hdc, HRGN hrgn, HBRUSH hbr );
		BOOL FrameRgn( HDC hdc, HRGN hrgn, HBRUSH hbr, int nWidth, int nHeight );
		int GetPolyFillMode( HDC hdc );
		DWORD GetRegionData( HRGN hRgn, DWORD dwCount, ::LPRGNDATA lpRgnData );
		int GetRgnBox( HRGN hrgn, ::LPRECT lprc );
		BOOL InvertRgn( HDC hdc, HRGN hrgn );
		int OffsetRgn( HRGN hrgn, int nXOffset, int nYOffset );
		BOOL PtInRegion( HRGN hrgn, int X, int Y );
		BOOL PaintRgn( HDC hdc, HRGN hrgn );
		BOOL RectInRegion( HRGN hrgn, CONST ::RECT* lprc );
		int SetPolyFillMode( HDC hdc, int iPolyFillMode );
		BOOL SetRectRgn( HRGN hrgn, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );

	private:

		HMODULE m_hModule;
	};

}//nsWinQAPI

/*				
		//Undocumented APIs

		AnyLinkedFonts
		bInitSystemAndFontsDirectoriesW
		ClearBitmapAttributes
		GetBitmapAttributes
		SetBitmapAttributes
		GdiDescribePixelFormat		
		GdiSetPixelFormat
		cGetTTFFromFOT
		EudcLoadLinkW
		EudcUnloadLinkW
		FontIsLinked
		GetETM
		GetEUDCTimeStamp
		GetEUDCTimeStampExW
		GetFontAssocStatus
		GetHFONT
		GetRelAbs
		GetStringBitmapA
		GetStringBitmapW
		GetTransform		
		NamedEscape
		PolyPatBlt
		QueryFontAssocStatus
		SelectFontLocal				
		SetFontEnumeration
		SetLayoutWidth
		SetRelAbs
		SetVirtualResolution
		UnloadNetworkFonts		


		GdiAddFontResourceW
		GdiAddGlsBounds
		GdiAddGlsRecord
		GdiAlphaBlend
		GdiArtificialDecrementDriver
		GdiCleanCacheDC
		GdiConsoleTextOut
		GdiConvertAndCheckDC
		GdiConvertBitmap
		GdiConvertBitmapV5
		GdiConvertBrush
		GdiConvertDC
		GdiConvertEnhMetaFile
		GdiConvertFont
		GdiConvertMetaFilePict
		GdiConvertPalette
		GdiConvertRegion
		GdiConvertToDevmodeW
		GdiCreateLocalEnhMetaFile
		GdiCreateLocalMetaFilePict
		GdiDeleteLocalDC
		GdiDeleteSpoolFileHandle
		GdiDllInitialize
		GdiDrawStream
		GdiEndDocEMF
		GdiEndPageEMF
		GdiEntry1
		GdiEntry10
		GdiEntry11
		GdiEntry12
		GdiEntry13
		GdiEntry14
		GdiEntry15
		GdiEntry16
		GdiEntry2
		GdiEntry3
		GdiEntry4
		GdiEntry5
		GdiEntry6
		GdiEntry7
		GdiEntry8
		GdiEntry9
		GdiFixUpHandle
		GdiFullscreenControl
		
		GdiGetBitmapBitsSize
		GdiGetCharDimensions
		GdiGetCodePage
		GdiGetDC
		GdiGetDevmodeForPage
		GdiGetLocalBrush
		GdiGetLocalDC
		GdiGetLocalFont
		GdiGetPageCount
		GdiGetPageHandle
		GdiGetSpoolFileHandle
		GdiGetSpoolMessage
		GdiGradientFill
		GdiInitializeLanguagePack
		GdiInitSpool
		GdiIsMetaFileDC
		GdiIsMetaPrintDC
		GdiIsPlayMetafileDC
		GdiPlayDCScript
		GdiPlayEMF
		GdiPlayJournal
		GdiPlayPageEMF
		GdiPlayPrivatePageEMF
		GdiPlayScript
		gdiPlaySpoolStream
		GdiPrinterThunk
		GdiProcessSetup
		GdiQueryFonts
		GdiQueryTable
		GdiRealizationInfo
		GdiReleaseDC
		GdiReleaseLocalDC
		GdiResetDCEMF
		GdiSetAttrs
		GdiSetLastError		
		GdiSetServerAttr
		GdiStartDocEMF
		GdiStartPageEMF
		GdiSwapBuffers
		GdiTransparentBlt
		GdiValidateHandle
		
	

		HT_Get8BPPFormatPalette
		HT_Get8BPPMaskPalette


		EngAcquireSemaphore
		EngAlphaBlend
		EngAssociateSurface
		EngBitBlt
		EngCheckAbort
		EngComputeGlyphSet
		EngCopyBits
		EngCreateBitmap
		EngCreateClip
		EngCreateDeviceBitmap
		EngCreateDeviceSurface
		EngCreatePalette
		EngCreateSemaphore
		EngDeleteClip
		EngDeletePalette
		EngDeletePath
		EngDeleteSemaphore
		EngDeleteSurface
		EngEraseSurface
		EngFillPath
		EngFindResource
		EngFreeModule
		EngGetCurrentCodePage
		EngGetDriverName
		EngGetPrinterDataFileName
		EngGradientFill
		EngLineTo
		EngLoadModule
		EngLockSurface
		EngMarkBandingSurface
		EngMultiByteToUnicodeN
		EngMultiByteToWideChar
		EngPaint
		EngPlgBlt
		EngQueryEMFInfo
		EngQueryLocalTime
		EngReleaseSemaphore
		EngStretchBlt
		EngStretchBltROP
		EngStrokeAndFillPath
		EngStrokePath
		EngTextOut
		EngTransparentBlt
		EngUnicodeToMultiByteN
		EngUnlockSurface
		EngWideCharToMultiByte

		PATHOBJ_bEnum
		PATHOBJ_bEnumClipLines
		PATHOBJ_vEnumStart
		PATHOBJ_vEnumStartClipLines
		PATHOBJ_vGetBounds		
		BRUSHOBJ_hGetColorTransform
		BRUSHOBJ_pvAllocRbrush
		BRUSHOBJ_pvGetRbrush
		BRUSHOBJ_ulGetBrushColor
		CLIPOBJ_bEnum
		CLIPOBJ_cEnumStart
		CLIPOBJ_ppoGetPath
		FONTOBJ_cGetAllGlyphHandles
		FONTOBJ_cGetGlyphs
		FONTOBJ_pfdg
		FONTOBJ_pifi
		FONTOBJ_pQueryGlyphAttrs
		FONTOBJ_pvTrueTypeFontFile
		FONTOBJ_pxoGetXform
		FONTOBJ_vGetInfo
		STROBJ_bEnum
		STROBJ_bEnumPositionsOnly
		STROBJ_bGetAdvanceWidths
		STROBJ_dwGetCodePage
		STROBJ_vEnumStart
		XFORMOBJ_bApplyXform
		XFORMOBJ_iGetXform
		XLATEOBJ_cGetPalette
		XLATEOBJ_hGetColorTransform
		XLATEOBJ_iXlate
		XLATEOBJ_piVector

		DdEntry0
		DdEntry1
		DdEntry10
		DdEntry11
		DdEntry12
		DdEntry13
		DdEntry14
		DdEntry15
		DdEntry16
		DdEntry17
		DdEntry18
		DdEntry19
		DdEntry2
		DdEntry20
		DdEntry21
		DdEntry22
		DdEntry23
		DdEntry24
		DdEntry25
		DdEntry26
		DdEntry27
		DdEntry28
		DdEntry29
		DdEntry3
		DdEntry30
		DdEntry31
		DdEntry32
		DdEntry33
		DdEntry34
		DdEntry35
		DdEntry36
		DdEntry37
		DdEntry38
		DdEntry39
		DdEntry4
		DdEntry40
		DdEntry41
		DdEntry42
		DdEntry43
		DdEntry44
		DdEntry45
		DdEntry46
		DdEntry47
		DdEntry48
		DdEntry49
		DdEntry5
		DdEntry50
		DdEntry51
		DdEntry52
		DdEntry53
		DdEntry54
		DdEntry55
		DdEntry56
		DdEntry6
		DdEntry7
		DdEntry8
		DdEntry9

		*/

#endif//_QSYS_API_WIN32_MODULES_GDI32_H_
