//WinQLRawInput.h

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

//Win32 Raw Input

#ifndef WINQL_DEVICEIO_RAWINPUT_H_3
#define WINQL_DEVICEIO_RAWINPUT_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "WinQL/Definitions/Handles.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	class __QOR_INTERFACE( __WINQAPI ) CUser32;
}

//--------------------------------------------------------------------------------
namespace nsWin32
{
	//--------------------------------------------------------------------------------
	typedef struct tagRAWINPUTDEVICE 
	{
		unsigned short usUsagePage; // Toplevel collection UsagePage
		unsigned short usUsage;     // Toplevel collection Usage
		unsigned long dwFlags;
		void*	 phwndTarget;    // Target hwnd. NULL = follows keyboard focus
	} RAWINPUTDEVICE, *PRAWINPUTDEVICE, *LPRAWINPUTDEVICE;

	//--------------------------------------------------------------------------------
	typedef struct tagRAWINPUTDEVICELIST 
	{
		void* hDevice;
		unsigned long dwType;
	} RAWINPUTDEVICELIST, *PRAWINPUTDEVICELIST;

	//--------------------------------------------------------------------------------
	typedef struct tagRAWINPUTHEADER 
	{
		unsigned long dwType;
		unsigned long dwSize;
		void* hDevice;
		Cmp_uint_ptr wParam;
	} RAWINPUTHEADER, *PRAWINPUTHEADER, *LPRAWINPUTHEADER;

	//--------------------------------------------------------------------------------
	typedef struct tagRAWMOUSE 
	{
		unsigned short usFlags;//Indicator flags.

__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_NAMELESS_STRUCTUNION, "Deliberate use of Microsoft extension" )

		//The transition state of the mouse buttons.
		union __CQOR_NAMELESS_STRUCT
		{
			unsigned long ulButtons;
			struct __QCMP_NAMELESS_STRUCT
			{
				unsigned short usButtonFlags;
				unsigned short usButtonData;
			};
		};

__QCMP_WARNING_POP

		unsigned long ulRawButtons;//The raw state of the mouse buttons.
		long lLastX;//The signed relative or absolute motion in the X direction.		
		long lLastY;//The signed relative or absolute motion in the Y direction.
		unsigned long ulExtraInformation;//Device-specific additional information for the event.

	} RAWMOUSE, *PRAWMOUSE, *LPRAWMOUSE;

	//--------------------------------------------------------------------------------
	typedef struct tagRAWKEYBOARD 
	{
		
		unsigned short MakeCode;//The "make" scan code (key depression).		
		unsigned short Flags;//The flags field indicates a "break" (key release) and other miscellaneous scan code information defined in ntddkbd.h.
		unsigned short Reserved;
		
		//Windows message compatible information
		unsigned short VKey;
		unsigned int Message;

		unsigned long ExtraInformation;//Device-specific additional information for the event.

	} RAWKEYBOARD, *PRAWKEYBOARD, *LPRAWKEYBOARD;

	//--------------------------------------------------------------------------------
	typedef struct tagRAWHID 
	{
		unsigned long dwSizeHid;    // byte size of each report
		unsigned long dwCount;      // number of input packed
		unsigned char bRawData[ 1 ];
	} RAWHID, *PRAWHID, *LPRAWHID;

	//--------------------------------------------------------------------------------
	typedef struct tagRAWINPUT 
	{
		RAWINPUTHEADER header;
		union 
		{
			RAWMOUSE    mouse;
			RAWKEYBOARD keyboard;
			RAWHID      hid;
		} data;
	} RAWINPUT, *PRAWINPUT, *LPRAWINPUT;

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __WINQL ) CRawInput
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CRawInput );

		CRawInput();
		virtual ~CRawInput();
		Cmp_long_ptr DefaultProc( nsWin32::PRAWINPUT* paRawInput, int nInput, unsigned int cbSizeHeader );
		unsigned int GetBuffer( nsWin32::PRAWINPUT pData, unsigned int* pcbSize, unsigned int cbSizeHeader );
		unsigned int GetData( RawInputHandle hRawInput, unsigned int uiCommand, void* pData, unsigned int* pcbSize, unsigned int cbSizeHeader );
		unsigned int GetDeviceInfo( void* hDevice, unsigned int uiCommand, void* pData, unsigned int* pcbSize );
		unsigned int GetDeviceList( nsWin32::PRAWINPUTDEVICELIST pRawInputDeviceList, unsigned int* puiNumDevices, unsigned int cbSize );
		unsigned int GetRegisteredDevices( nsWin32::PRAWINPUTDEVICE pRawInputDevices, unsigned int* puiNumDevices, unsigned int cbSize );
		bool RegisterDevices( const nsWin32::RAWINPUTDEVICE* pRawInputDevices, unsigned int uiNumDevices, unsigned int cbSize );

	private:

		nsWinQAPI::CUser32& m_Library;

		__QCS_DECLARE_NONCOPYABLE( CRawInput );

	};

}//nsWin32

#endif//WINQL_DEVICEIO_RAWINPUT_H_3
