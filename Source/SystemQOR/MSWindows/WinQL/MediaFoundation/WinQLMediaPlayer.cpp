//WinQLMediaPlayer.cpp

// Copyright Querysoft Limited 2013, 2015
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
#include "WinQL/CodeServices/WinQLPolicy.h"
#include "WinQL/Application/Threading/WinQLCriticalSection.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: saved in member for later use" );
#include "WinQL/MediaFoundation/MediaPlayer.h"
#include "WinQAPI/MedFoundAPI.h"
__QCMP_WARNING_POP

//--------------------------------------------------------------------------------
namespace nsWin32
{
	const GUID IMFMediaEventQueue::_IID				= { 0x36f846fc, 0x2256, 0x48b6, 0xb5, 0x8e, 0xe2, 0xb6, 0x38, 0x31, 0x65, 0x81 };
	const GUID IMFNetCredentialCache::_IID			= { 0x5b87ef6c, 0x7ed8, 0x434f, 0xba, 0x0e, 0x18, 0x4f, 0xac, 0x16, 0x28, 0xd1 };
	const GUID IMFQualityManager::_IID				= { 0x8D009D86, 0x5B9F, 0x4115, 0xB1, 0xFC, 0x9F, 0x80, 0xD5, 0x2A, 0xB8, 0xAB };
	const GUID IMFRemoteDesktopPlugin::_IID			= { 0x1cde6309, 0xcae0, 0x4940, 0x90, 0x7e, 0xc1, 0xec, 0x9c, 0x3d, 0x1d, 0x4a };
	const GUID IMFSinkWriter::_IID					= { 0x3137f1cd, 0xfe5e, 0x4805, 0xa5, 0xd8, 0xfb, 0x47, 0x74, 0x48, 0xcb, 0x3d };
	const GUID IMFSourceResolver::_IID				= { 0xFBE5A32D, 0xA497, 0x4b61, 0xBB, 0x85, 0x97, 0xB1, 0xA8, 0x48, 0xA6, 0xE3 };
	const GUID IMFSampleGrabberSinkCallback::_IID	= { 0x8C7B80BF, 0xEE42, 0x4b59, 0xB1, 0xDF, 0x55, 0x66, 0x8E, 0x1B, 0xDC, 0xA8 };
	const GUID IMMDevice::_IID						= { 0xD666063F, 0x1587, 0x4E43, 0x81, 0xF1, 0xB9, 0x48, 0xE8, 0x07, 0x36, 0x3F };
	const GUID IMMDeviceCollection::_IID			= { 0x0BD7A1BE, 0x7A1A, 0x44DB, 0x83, 0x97, 0xCC, 0x53, 0x92, 0x38, 0x7B, 0x5E };
	const GUID IMMNotificationClient::_IID			= { 0x7991EEC9, 0x7E89, 0x4D85, 0x83, 0x90, 0x6C, 0x70, 0x3C, 0xEC, 0x60, 0xC0 };
	const GUID IMMDeviceEnumerator::_IID			= { 0xA95664D2, 0x9614, 0x4F35, 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6 };
	const GUID IMFPMediaPlayer::_IID				= { 0xA714590A, 0x58AF, 0x430a, 0x85, 0xBF, 0x44, 0xF5, 0xEC, 0x83, 0x8D, 0x85 };
	const GUID IMFPMediaPlayerCallback::_IID		= { 0x766C8FFB, 0x5FDB, 0x4fea, 0xA2, 0x8D, 0xB9, 0x12, 0x99, 0x6F, 0x51, 0xBD };



	//--------------------------------------------------------------------------------
	namespace nsMediaFoundation
	{

		__QOR_IMPLEMENT_OCLASS_LUID( CMediaPlayer );

		//--------------------------------------------------------------------------------
		CMediaPlayer::CMediaPlayer( const wchar_t* pwszURL, int fStartPlayback, Cmp_unsigned__int32 creationOptions, IMFPMediaPlayerCallback* pCallback, COSWindow::refType Wnd ) :
			m_MFPlay( *( new nsWinQAPI::CMFPlay ) )
		{
			_WINQ_FCONTEXT( "CMediaPlayer::CMediaPlayer" );
			m_ulStatus = m_MFPlay.MFPCreateMediaPlayer( pwszURL, fStartPlayback, creationOptions, 
				reinterpret_cast< ::IMFPMediaPlayerCallback* >( pCallback ), 
				reinterpret_cast< ::HWND >( Wnd->Handle()->Use() ), 
				reinterpret_cast< ::IMFPMediaPlayer** >( &m_p ) );
		}

		//--------------------------------------------------------------------------------
		CMediaPlayer::~CMediaPlayer()
		{
			_WINQ_FCONTEXT( "CMediaPlayer::~CMediaPlayer" );
		}


		__QOR_IMPLEMENT_OCLASS_LUID( CMediaPlayerCallbackHandler );

		//--------------------------------------------------------------------------------
		void __QCMP_STDCALLCONVENTION CMediaPlayerCallbackHandler::OnMediaPlayerEvent( MFP_EVENT_HEADER* pEventHeader )
		{
			_WINQ_FCONTEXT( "CMediaPlayerCallbackHandler::OnMediaPlayerEvent" );

			if( !pEventHeader || pEventHeader->hrEvent != 0 )
			{
				//Raise error
			}

			switch( pEventHeader->eEventType )
			{
			case MFP_EVENT_TYPE_PLAY:
				{
					//the IMFPMediaPlayer::Play method completed
					MFP_PLAY_EVENT* pPlayEvent =  MFP_GET_PLAY_EVENT( pEventHeader );
					OnPlayEvent( pPlayEvent );
					break;
				}
			case MFP_EVENT_TYPE_PAUSE:
				{
					MFP_PAUSE_EVENT* pPauseEvent = MFP_GET_PAUSE_EVENT( pEventHeader );
					OnPauseEvent( pPauseEvent );
					break;
				}
			case MFP_EVENT_TYPE_STOP:
				{
					MFP_STOP_EVENT* pStopEvent = MFP_GET_STOP_EVENT( pEventHeader );
					OnStopEvent( pStopEvent );
					break;
				}
			case MFP_EVENT_TYPE_POSITION_SET:
				{
					MFP_POSITION_SET_EVENT* pPositionSetEvent = MFP_GET_POSITION_SET_EVENT( pEventHeader );
					OnPositionSetEvent( pPositionSetEvent );
					break;
				}
			case MFP_EVENT_TYPE_RATE_SET:
				{
					MFP_RATE_SET_EVENT* pRateSetEvent = MFP_GET_RATE_SET_EVENT( pEventHeader );
					OnRateSetEvent( pRateSetEvent );
					break;
				}
			case MFP_EVENT_TYPE_MEDIAITEM_CREATED:
				{
					MFP_MEDIAITEM_CREATED_EVENT* pMediaItemCreatedEvent = MFP_GET_MEDIAITEM_CREATED_EVENT( pEventHeader );
					OnMediaItemCreatedEvent( pMediaItemCreatedEvent );
					break;
				}
			case MFP_EVENT_TYPE_MEDIAITEM_SET:
				{
					MFP_MEDIAITEM_SET_EVENT* pMediaItemSetEvent = MFP_GET_MEDIAITEM_SET_EVENT( pEventHeader );
					OnMediaItemSetEvent( pMediaItemSetEvent );
					break;
				}
			case MFP_EVENT_TYPE_FRAME_STEP:
				{
					MFP_FRAME_STEP_EVENT* pFrameStepEvent = MFP_GET_FRAME_STEP_EVENT( pEventHeader );
					OnFrameStepEvent( pFrameStepEvent );
					break;
				}
			case MFP_EVENT_TYPE_MEDIAITEM_CLEARED:
				{
					MFP_MEDIAITEM_CLEARED_EVENT* pMediaItemCleared = MFP_GET_MEDIAITEM_CLEARED_EVENT( pEventHeader );
					OnMediaItemCleared( pMediaItemCleared );
					break;
				}
			case MFP_EVENT_TYPE_MF:
				{
					MFP_MF_EVENT* pMFEvent = MFP_GET_MF_EVENT( pEventHeader );
					OnMFEvent( pMFEvent );
					break;
				}
			case MFP_EVENT_TYPE_ERROR:
				{
					MFP_ERROR_EVENT* pErrorEvent = MFP_GET_ERROR_EVENT( pEventHeader );
					OnErrorEvent( pErrorEvent );
					break;
				}
			case MFP_EVENT_TYPE_PLAYBACK_ENDED:
				{
					MFP_PLAYBACK_ENDED_EVENT* pPlaybackEndedEvent = MFP_GET_PLAYBACK_ENDED_EVENT( pEventHeader );
					OnPlaybackEndedEvent( pPlaybackEndedEvent );
					break;
				}
			case MFP_EVENT_TYPE_ACQUIRE_USER_CREDENTIAL:
				{
					MFP_ACQUIRE_USER_CREDENTIAL_EVENT* pAcquireUserCredentialEvent = MFP_GET_ACQUIRE_USER_CREDENTIAL_EVENT( pEventHeader );
					OnAcquireUserCredentialEvent( pAcquireUserCredentialEvent );
					break;
				}
			default:
				{
					//TODO: Raise error unknown event type
				}
			}
		}

	}//nsMediaFoundation

}//nsWin32
