//WinQLDCDraw.h

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

//inline header file for Device Context Draw component class

#ifndef WINQL_OSGRAPHICS_DC_DRAW_H_3
#define WINQL_OSGRAPHICS_DC_DRAW_H_3

//--------------------------------------------------------------------------------
class __QOR_INTERFACE( __WINQL ) CDraw
{
public:

	__QOR_DECLARE_OCLASS_ID( CDraw );

	CDraw( CDeviceContext& DC );
	virtual ~CDraw();
	bool AngleArc( int X, int Y, unsigned long dwRadius, float eStartAngle, float eSweepAngle );
	bool Arc( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc );
	bool ArcTo( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 );
	int GetArcDirection( void );
	bool LineDDA( int nXStart, int nYStart, int nXEnd, int nYEnd, nsWin32::LINEDDAPROC lpLineFunc, Cmp_long_ptr lpData );
	bool LineTo( int nXEnd, int nYEnd );
	bool MoveToEx( int X, int Y, nsWin32::POINT* lpPoint );
	bool PolyBezier( const nsWin32::POINT* lppt, unsigned long cPoints );
	bool PolyBezierTo( const nsWin32::POINT* lppt, unsigned long cCount );
	bool PolyDraw( const nsWin32::POINT* lppt, const unsigned char* lpbTypes, int cCount );
	bool Polyline( const nsWin32::POINT* lppt, int cPoints );
	bool PolylineTo( const nsWin32::POINT* lppt, unsigned long cCount );
	bool PolyPolyline( const nsWin32::POINT* lppt, const unsigned long* lpdwPolyPoints, unsigned long cCount );
	int SetArcDirection( int ArcDirection );
	bool Chord( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 );
	bool Ellipse( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
	bool Pie( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 );
	bool Polygon( const nsWin32::POINT* lpPoints, int nCount );
	bool PolyPolygon( const nsWin32::POINT* lpPoints, const int* lpPolyCounts, int nCount );
	bool Rectangle( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
	bool RoundRect( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight );

protected:

	CDeviceContext& m_DC;

private:

	CDraw& operator = ( const CDraw& Src ); //Not to be implemented

};

#endif//WINQL_OSGRAPHICS_DC_DRAW_H_3