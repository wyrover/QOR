//WinQLAnimate.cpp

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

#include "SystemQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: saved in member for later use" );
#include "WinQL/GUI/Windows/Animate.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{

	//--------------------------------------------------------------------------------
	CAnimateClass::CAnimateClass() : CCommonCtrlClass( CCommonCtrl::CCANIMATE_CLASS, _TXT( "SysAnimate32" ) )
	{
	}


	const long CAnimateFactory::ACS_CENTER = 0x0001;
	const long CAnimateFactory::ACS_TRANSPARENT = 0x0002;
	const long CAnimateFactory::ACS_AUTOPLAY = 0x0004;

#if		(_WIN32_IE >= 0x0300)
	const long CAnimateFactory::ACS_TIMER = 0x0008; // don't use threads... use timers
#endif//(_WIN32_IE >= 0x0300)
	
	//--------------------------------------------------------------------------------
	CAnimateFactory::CAnimateFactory() : CCommonCtrlFactory< CAnimate >()
	{
	}

	//--------------------------------------------------------------------------------
	bool CAnimateFactory::GetCenter()
	{
		return GetStyleBits( ACS_CENTER );
	}

	//--------------------------------------------------------------------------------
	void CAnimateFactory::SetCenter( bool bFlag )
	{
		SetStyleBits( ACS_CENTER, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CAnimateFactory::GetTransparent()
	{
		return GetStyleBits( ACS_TRANSPARENT );
	}

	//--------------------------------------------------------------------------------
	void CAnimateFactory::SetTransparent( bool bFlag )
	{
		SetStyleBits( ACS_TRANSPARENT, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CAnimateFactory::GetAutoPlay()
	{
		return GetStyleBits( ACS_AUTOPLAY );
	}

	//--------------------------------------------------------------------------------
	void CAnimateFactory::SetAutoPlay( bool bFlag )
	{
		SetStyleBits( ACS_AUTOPLAY, bFlag );
	}

	//--------------------------------------------------------------------------------
	bool CAnimateFactory::GetTimer()
	{
		return GetStyleBits( ACS_TIMER );
	}

	//--------------------------------------------------------------------------------
	void CAnimateFactory::SetTimer( bool bFlag )
	{
		SetStyleBits( ACS_TIMER, bFlag );
	}


	//--------------------------------------------------------------------------------
	CAnimate::CAnimate() : CWinCtrlWindow()
	{
	}

	//--------------------------------------------------------------------------------
	CAnimate::~CAnimate()
	{
	}

	//--------------------------------------------------------------------------------
	void CAnimate::OnStart()
	{
	}

	//--------------------------------------------------------------------------------
	void CAnimate::OnStop()
	{
	}

	//--------------------------------------------------------------------------------
	bool CAnimate::IsPlaying()
	{
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int)ACM_ISPLAYING, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CAnimate::Open( nsWin32::InstanceHandle hInst, Cmp_long_ptr AVIResource )
	{
		Cmp_uint_ptr wParam = 0;
#if		( _WIN32_IE >= 0x0400 )
		wParam = reinterpret_cast< Cmp_uint_ptr >( hInst );
#endif//( _WIN32_IE >= 0x0400 )
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int)ACM_OPEN, wParam, AVIResource ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CAnimate::Play( unsigned int uiRepeatCount, unsigned short wBeginFrame, unsigned short wEndFrame )
	{
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int)ACM_PLAY, static_cast< Cmp_uint_ptr >( uiRepeatCount ), MakeLParam( wBeginFrame, wEndFrame ) ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	bool CAnimate::Stop()
	{
		bool bResult = ( m_Win32MsgHandler.Send( Ref(), (unsigned int)ACM_STOP, 0, 0 ) ? true : false );
		return bResult;
	}

	//--------------------------------------------------------------------------------
	void CAnimate::OnCommand( unsigned short wCtrlID, unsigned short wCode )
	{
		switch ( wCode )
		{
		case ACN_START:
			{
				OnStart();
			}
			break;
		case ACN_STOP:
			{
				OnStop();
			}
			break;
		}
	}

}//nsWin32

