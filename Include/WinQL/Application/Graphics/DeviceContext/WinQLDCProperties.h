//WinQLDCProperties.h

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

//WinQL inline header file for Device Context properties component classes

#ifndef _QSYS_MSWINDOWS_WIN32_OSGRAPHICS_DC_PROPERTIES_H_
#define _QSYS_MSWINDOWS_WIN32_OSGRAPHICS_DC_PROPERTIES_H_

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CDCIntegerProperty
	{
	public:
		
		__QOR_DECLARE_OCLASS_ID( CDCIntegerPrperty );

		CDCIntegerProperty( CDeviceContext& DC );
		virtual ~CDCIntegerProperty();
		virtual int Get() = 0;
		virtual int Set( int iNewValue ) = 0;

	protected:

		CDeviceContext& m_DC;

	private:

		CDCIntegerProperty& operator = ( const CDCIntegerProperty& Src ); //Not to be implemented

	};

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CMapMode : public CDCIntegerProperty
	{
	public:
		
		CMapMode( CDeviceContext& DC );
		virtual ~CMapMode();
		int Get( void );
		int Set( int iMode );
	};			

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CGraphicsMode : public CDCIntegerProperty
	{
	public:
		
		CGraphicsMode( CDeviceContext& DC );
		virtual ~CGraphicsMode();
		int Get( void );
		int Set( int iMode );
	};


#endif//_QSYS_MSWINDOWS_WIN32_OSGRAPHICS_DC_PROPERTIES_H_
