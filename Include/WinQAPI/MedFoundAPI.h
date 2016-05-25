//MedFoundAPI.h

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

#ifndef _QSYS_API_WIN32_MODULES_MEDIAFOUNDAPI_H_
#define _QSYS_API_WIN32_MODULES_MEDIAFOUNDAPI_H_

#include "Kernel32.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/DynamicLibrary.h"

#if		( _WIN32_WINNT >= 0x0600 )
#	include<mfapi.h>
#	include<mfplay.h>
#	include<Mfidl.h>
#	include<Wmcontainer.h>
#	include<evr.h>
#	include<Ks.h>
#	include<KsMedia.h>
#	if		( _WIN32_WINNT >= 0601 )
#		include <mfreadwrite.h>
#	endif//	( _WIN32_WINNT >= 0601 )
#else
#define MFSTARTUP_FULL 0
#endif//( _WIN32_WINNT >= 0x0600 )

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------	
	class __QOR_INTERFACE( __WINQAPI ) CMFPlay : public CDll
	{
	public:
		//--------------------------------------------------------------------------------	
		CMFPlay() : CDll( TEXT( "Mfplay" ) )
		{
		}

		//--------------------------------------------------------------------------------
		static CMFPlay& Instance( void )
		{
			static CMFPlay _instance;
			return _instance;
		}

		//--------------------------------------------------------------------------------
		~CMFPlay()
		{
		}

		HRESULT MFPCreateMediaPlayer( LPCWSTR pwszURL, BOOL fStartPlayback, MFP_CREATION_OPTIONS creationOptions, IMFPMediaPlayerCallback* pCallback, HWND hWnd, IMFPMediaPlayer** ppMediaPlayer );
	};

	//--------------------------------------------------------------------------------	
	class __QOR_INTERFACE( __WINQAPI ) CEVRAPI : public CDll
	{
	public:
		//--------------------------------------------------------------------------------
		CEVRAPI() : CDll( TEXT( "Evr" ) )
		{
		}

		//--------------------------------------------------------------------------------
		static CEVRAPI& Instance( void )
		{
			static CEVRAPI _instance;
			return _instance;
		}

		//--------------------------------------------------------------------------------
		~CEVRAPI()
		{
		}

		HRESULT MFCreateVideoMixer( IUnknown* pOwner, REFIID riidDevice, REFIID riid, void** ppVideoMixer );
		HRESULT MFCreateVideoMixerAndPresenter( IUnknown* pMixerOwner, IUnknown* pPresenterOwner, REFIID riidMixer, void** ppvVideoMixer, REFIID riidPresenter, void** ppvVideoPresenter );
		HRESULT MFCreateVideoPresenter( IUnknown* pOwner, REFIID riidDevice, REFIID riid, void** ppvVideoPresenter );
		HRESULT MFCreateVideoSampleAllocator( REFIID riid, void** ppSampleAllocator );
		HRESULT MFCreateVideoSampleFromSurface( IUnknown* pUnkSurface, IMFSample** ppSample );
		BOOL MFIsFormatYUV( DWORD Format );
	};

	//--------------------------------------------------------------------------------	
	class __QOR_INTERFACE( __WINQAPI ) CMFReadWrite : public CDll
	{
	public:
		//--------------------------------------------------------------------------------
		CMFReadWrite() : CDll( TEXT( "Mfreadwrite" ) )
		{
		}

		//--------------------------------------------------------------------------------
		static CMFReadWrite& Instance( void )
		{
			static CMFReadWrite _instance;
			return _instance;
		}

		//--------------------------------------------------------------------------------
		~CMFReadWrite()
		{
		}

		HRESULT MFCreateSinkWriterFromMediaSink( IMFMediaSink* pMediaSink, IMFAttributes* pAttributes, IMFSinkWriter** ppSinkWriter );
		HRESULT MFCreateSinkWriterFromURL( LPCWSTR pwszOutputURL, IMFByteStream* pByteStream, IMFAttributes* pAttributes, IMFSinkWriter** ppSinkWriter );
		HRESULT MFCreateSourceReaderFromByteStream( IMFByteStream* pByteStream, IMFAttributes* pAttributes, IMFSourceReader** ppSourceReader );
		HRESULT MFCreateSourceReaderFromMediaSource( IMFMediaSource* pMediaSource, IMFAttributes* pAttributes, IMFSourceReader** ppSourceReader );
		HRESULT MFCreateSourceReaderFromURL( LPCWSTR pwszURL, IMFAttributes* pAttributes, IMFSourceReader** ppSourceReader );
	};

	//--------------------------------------------------------------------------------	
	class __QOR_INTERFACE( __WINQAPI ) CMF : public CDll
	{
	public:

		//--------------------------------------------------------------------------------
		CMF() : CDll( TEXT("Mf") )
		{						
		}

		//--------------------------------------------------------------------------------
		static CMF& Instance( void )
		{
			static CMF _instance;
			return _instance;
		}

		//--------------------------------------------------------------------------------
		~CMF()
		{						
		}

		//--------------------------------------------------------------------------------
		HRESULT MFCreate3GPMediaSink( IMFByteStream* pIByteStream, IMFMediaType* pVideoMediaType, IMFMediaType* pAudioMediaType, IMFMediaSink** ppIMediaSink );
		HRESULT MFCreateAggregateSource( IMFCollection* pSourceCollection, IMFMediaSource** ppAggSource );
		HRESULT MFCreateASFContentInfo( IMFASFContentInfo** ppIContentInfo );
		HRESULT MFCreateASFIndexer( IMFASFIndexer** ppIIndexer );
		HRESULT MFCreateASFIndexerByteStream( IMFByteStream* pIContentByteStream, QWORD cbIndexStartOffset, IMFByteStream** pIIndexByteStream );
		HRESULT MFCreateASFMediaSink( IMFByteStream* pIByteStream, IMFMediaSink** ppIMediaSink );
		HRESULT MFCreateASFMediaSinkActivate( LPCWSTR pwszFileName, IMFASFContentInfo* pContentInfo, IMFActivate** ppIActivate );
		HRESULT MFCreateASFMultiplexer( IMFASFMultiplexer** ppIMultiplexer );
		HRESULT MFCreateASFProfile( IMFASFProfile** ppIProfile );
		HRESULT MFCreateASFProfileFromPresentationDescriptor( IMFPresentationDescriptor* pIPD, IMFASFProfile** ppIProfile );
		HRESULT MFCreateASFSplitter( IMFASFSplitter** ppISplitter );
		HRESULT MFCreateASFStreamingMediaSink( IMFByteStream* pIByteStream, IMFMediaSink** ppIMediaSink );
		HRESULT MFCreateASFStreamingMediaSinkActivate( IMFActivate* pByteStreamActivate, IMFASFContentInfo* pContentInfo, IMFActivate** ppIActivate );
		HRESULT MFCreateAudioRenderer( IMFAttributes* pAudioAttributes, IMFMediaSink** ppSink );
		HRESULT MFCreateAudioRendererActivate( IMFActivate** ppActivate );
		HRESULT MFCreateCredentialCache( IMFNetCredentialCache** ppCache );
		HRESULT MFCreateDeviceSource( IMFAttributes* pAttributes, IMFMediaSource** ppSource );
		HRESULT MFCreateDeviceSourceActivate( IMFAttributes* pAttributes, IMFActivate** ppActivate );
		HRESULT MFCreatePMPMediaSession( DWORD dwCreationFlags, IMFAttributes* pConfiguration, IMFMediaSession** ppMediaSession, IMFActivate** ppEnablerActivate );
		HRESULT MFCreateMP3MediaSink( IMFByteStream* pTargetByteStream, IMFMediaSink** ppMediaSink );
		HRESULT MFCreateMPEG4MediaSink( IMFByteStream* pIByteStream, IMFMediaType* pVideoMediaType, IMFMediaType* pAudioMediaType, IMFMediaSink** ppIMediaSink );
		HRESULT MFCreateNetSchemePlugin( REFIID riid, LPVOID* ppvHandler );
		HRESULT MFCreatePMPServer( DWORD dwCreationFlags, IMFPMPServer** ppPMPServer );
		HRESULT MFCreatePresentationClock( IMFPresentationClock** ppPresentationClock );
		HRESULT MFCreatePresentationDescriptorFromASFProfile( IMFASFProfile* pIProfile, IMFPresentationDescriptor** ppIPD );
		HRESULT MFCreateProxyLocator( LPCWSTR pszProtocol, IPropertyStore* pProxyConfig, IMFNetProxyLocator** ppProxyLocator );
		HRESULT MFCreateRemoteDesktopPlugin( IMFRemoteDesktopPlugin** ppPlugin );
		HRESULT MFCreateSampleCopierMFT( IMFTransform** ppCopierMFT );
		HRESULT MFCreateSampleGrabberSinkActivate( IMFMediaType* pIMFMediaType, IMFSampleGrabberSinkCallback* pIMFSampleGrabberSinkCallback, IMFActivate** ppIActivate );
		HRESULT MFCreateSequencerSegmentOffset( MFSequencerElementId dwId, MFTIME hnsOffset, PROPVARIANT* pvarSegmentOffset );
		HRESULT MFCreateSequencerSource( IUnknown* pReserved, IMFSequencerSource** ppSequencerSource );
		HRESULT MFCreateSimpleTypeHandler( IMFMediaTypeHandler** ppHandler );
		HRESULT MFCreateStandardQualityManager( IMFQualityManager** ppQualityManager );
		HRESULT MFCreateTopoLoader( IMFTopoLoader** ppObj );
		HRESULT MFCreateTopology( IMFTopology** ppTopo );
		HRESULT MFCreateTopologyNode( MF_TOPOLOGY_TYPE NodeType, IMFTopologyNode** ppNode );
		HRESULT MFCreateTranscodeProfile( IMFTranscodeProfile** ppTranscodeProfile );
		HRESULT MFCreateTranscodeSinkActivate( IMFActivate** ppActivate );
		HRESULT MFCreateTranscodeTopology( IMFMediaSource* pSrc, LPCWSTR pwszOutputFilePath, IMFTranscodeProfile* pProfile, IMFTopology** ppTranscodeTopo );
		HRESULT MFCreateVideoRenderer( REFIID riidRenderer, void** ppVideoRenderer );
		HRESULT MFCreateVideoRendererActivate( HWND hwndVideo, IMFActivate** ppActivate );
		HRESULT MFCreateWMAEncoderActivate( IMFMediaType* pMediaType, IPropertyStore* pEncodingConfigurationProperties, IMFActivate** ppActivate );
		HRESULT MFCreateWMVEncoderActivate( IMFMediaType* pMediaType, IPropertyStore* pEncodingConfigurationProperties, IMFActivate** ppActivate );
		HRESULT MFGetSupportedMimeTypes( PROPVARIANT* pPropVarMimeTypeArray );
		HRESULT MFGetSupportedSchemes( PROPVARIANT* pPropVarSchemeArray );
		HRESULT MFGetTopoNodeCurrentType( IMFTopologyNode* pNode, DWORD dwStreamIndex, BOOL fOutput, IMFMediaType** ppType );
		HRESULT MFRequireProtectedEnvironment( IMFPresentationDescriptor* pPresentationDescriptor );
	};

	//--------------------------------------------------------------------------------	
	class __QOR_INTERFACE( __WINQAPI ) CMFAPI : public CDll
	{
	public:

		//--------------------------------------------------------------------------------
		CMFAPI() : CDll( TEXT("Mfplat") )
		{						
		}

		//--------------------------------------------------------------------------------
		static CMFAPI& Instance( void )
		{
			static CMFAPI _instance;
			return _instance;
		}

		//--------------------------------------------------------------------------------
		~CMFAPI()
		{						
		}

		//--------------------------------------------------------------------------------
		HRESULT __QCMP_STDCALLCONVENTION MFStartup( ULONG Version, DWORD dwFlags = MFSTARTUP_FULL );
		HRESULT MFShutdown( void );

		HRESULT MFAddPeriodicCallback( MFPERIODICCALLBACK Callback, IUnknown* pContext, DWORD* pdwKey );
		HRESULT MFAllocateWorkQueue( DWORD* pdwWorkQueue );
		HRESULT MFAllocateWorkQueueEx( MFASYNC_WORKQUEUE_TYPE WorkQueueType, DWORD* pdwWorkQueue );
		HRESULT MFAverageTimePerFrameToFrameRate( UINT64 unAverageTimePerFrame, UINT32* punNumerator, UINT32* punDenominator );
		HRESULT MFBeginCreateFile( MF_FILE_ACCESSMODE AccessMode, MF_FILE_OPENMODE OpenMode, MF_FILE_FLAGS fFlags, LPCWSTR pwszFilePath, IMFAsyncCallback* pCallback, IUnknown* pState, IUnknown** ppCancelCookie );
		HRESULT MFBeginRegisterWorkQueueWithMMCSS( DWORD dwWorkQueueId, LPCWSTR wszClass, DWORD dwTaskId, IMFAsyncCallback* pDoneCallback, IUnknown* pDoneState );
		HRESULT MFBeginUnregisterWorkQueueWithMMCSS( DWORD dwWorkQueueId, IMFAsyncCallback* pDoneCallback, IUnknown* pDoneState );

		HRESULT MFCalculateBitmapImageSize( const BITMAPINFOHEADER* pBMIH, UINT32 cbBufSize, UINT32* pcbImageSize, BOOL* pbKnown );
		HRESULT MFCalculateImageSize( REFGUID guidSubtype, UINT32 unWidth, UINT32 unHeight, UINT32* pcbImageSize );
		HRESULT MFCancelCreateFile( IUnknown *pCancelCookie );
		HRESULT MFCancelWorkItem( MFWORKITEM_KEY Key );
		BOOL MFCompareFullToPartialMediaType( IMFMediaType* pMFTypeFull, IMFMediaType* pMFTypePartial );
		HRESULT MFConvertFromFP16Array( float* pDest, const WORD* pSrc, DWORD dwCount );
		HRESULT MFConvertToFP16Array( WORD* pDest, const float* pSrc, DWORD dwCount );
		HRESULT MFCopyImage( BYTE *pDest, LONG lDestStride, const BYTE *pSrc, LONG lSrcStride, DWORD dwWidthInBytes, DWORD dwLines );
		HRESULT MFCreateAlignedMemoryBuffer( DWORD cbMaxLength, DWORD fAlignmentFlags, IMFMediaBuffer** ppBuffer );
		HRESULT MFCreateAMMediaTypeFromMFMediaType( IMFMediaType* pMFType, GUID guidFormatBlockType, AM_MEDIA_TYPE** ppAMType );
		HRESULT MFCreateAsyncResult( IUnknown* punkObject, IMFAsyncCallback* pCallback, IUnknown* punkState, IMFAsyncResult** ppAsyncResult );
		HRESULT MFCreateAttributes( IMFAttributes** ppMFAttributes, UINT32 cInitialSize );
		HRESULT MFCreateCollection( IMFCollection** ppIMFCollection );
		HRESULT MFCreateEventQueue( IMFMediaEventQueue** ppMediaEventQueue );
		HRESULT MFCreateFile( MF_FILE_ACCESSMODE AccessMode, MF_FILE_OPENMODE OpenMode, MF_FILE_FLAGS fFlags, LPCWSTR pwszFileURL, IMFByteStream** ppIByteStream );
		HRESULT MFCreateLegacyMediaBufferOnMFMediaBuffer( IMFSample* pIMFSample, IMFMediaBuffer* pIMFMediaBuffer, DWORD cbOffset, IMediaBuffer** ppIMediaBuffer );
		HRESULT MFCreateMediaBufferWrapper( IMFMediaBuffer* pBuffer, DWORD cbOffset, DWORD dwLength, IMFMediaBuffer** ppBuffer );
		HRESULT MFCreateMediaEvent( MediaEventType met, REFGUID guidExtendedType, HRESULT hrStatus, const PROPVARIANT* pvValue, IMFMediaEvent** ppEvent );
		HRESULT MFCreateMediaSession( IMFAttributes* pConfiguration, IMFMediaSession** ppMS );
		HRESULT MFCreateMediaType( IMFMediaType** ppMFType );
		HRESULT MFCreateMediaTypeFromRepresentation( GUID guidRepresentation, LPVOID pvRepresentation, IMFMediaType** ppIMediaType );
		HRESULT MFCreateMemoryBuffer( DWORD cbMaxLength, IMFMediaBuffer** ppBuffer );
		HRESULT MFCreateMFByteStreamOnStream( IStream* pStream, IMFByteStream** ppByteStream );
		HRESULT MFCreatePresentationDescriptor( DWORD cStreamDescriptors, IMFStreamDescriptor** apStreamDescriptors, IMFPresentationDescriptor** ppPresentationDescriptor );		
		HRESULT MFCreateSample( IMFSample** ppIMFSample );
		HRESULT MFCreateSourceResolver( IMFSourceResolver** ppISourceResolver );
		HRESULT MFCreateStreamDescriptor( DWORD dwStreamIdentifier, DWORD cMediaTypes, IMFMediaType** apMediaTypes, IMFStreamDescriptor** ppDescriptor );
		HRESULT MFCreateSystemTimeSource( IMFPresentationTimeSource** ppSystemTimeSource );
		HRESULT MFCreateTempFile( MF_FILE_ACCESSMODE AccessMode, MF_FILE_OPENMODE OpenMode, MF_FILE_FLAGS fFlags, IMFByteStream** ppIByteStream );
		HRESULT MFCreateTransformActivate( IMFActivate** ppActivate );
		HRESULT MFCreateVideoMediaTypeFromBitMapInfoHeaderEx( const BITMAPINFOHEADER* pbmihBitMapInfoHeader, UINT32 cbBitMapInfoHeader, DWORD dwPixelAspectRatioX, DWORD dwPixelAspectRatioY, MFVideoInterlaceMode InterlaceMode, QWORD VideoFlags, DWORD dwFramesPerSecondNumerator, DWORD dwFramesPerSecondDenominator, DWORD dwMaxBitRate, IMFVideoMediaType** ppIVideoMediaType );
		HRESULT MFCreateVideoMediaTypeFromSubtype( const GUID* pAMSubtype, IMFVideoMediaType** ppIVideoMediaType );
		HRESULT MFCreateVideoMediaTypeFromVideoInfoHeader( const KS_VIDEOINFOHEADER* pVideoInfoHeader, DWORD cbVideoInfoHeader, DWORD dwPixelAspectRatioX, DWORD dwPixelAspectRatioY, MFVideoInterlaceMode InterlaceMode, QWORD VideoFlags, const GUID* pSubtype, IMFVideoMediaType** ppIVideoMediaType );
		HRESULT MFCreateVideoMediaTypeFromVideoInfoHeader2( const KS_VIDEOINFOHEADER2* pVideoInfoHeader, DWORD cbVideoInfoHeader, QWORD AdditionalVideoFlags, const GUID* pSubtype, IMFVideoMediaType** ppIVideoMediaType );
		HRESULT MFCreateWaveFormatExFromMFMediaType( IMFMediaType* pMFType, WAVEFORMATEX** ppWF, UINT32* pcbSize, UINT32 Flags = MFWaveFormatExConvertFlag_Normal );
		HRESULT MFDeserializeAttributesFromStream( IMFAttributes* pAttr, DWORD dwOptions, IStream* pStm );
		HRESULT MFDeserializePresentationDescriptor( DWORD cbData, BYTE* pbData, IMFPresentationDescriptor** ppPD );
		HRESULT MFEndCreateFile( IMFAsyncResult* pResult, IMFByteStream** ppFile );
		HRESULT MFEndRegisterWorkQueueWithMMCSS( IMFAsyncResult* pResult, DWORD* pdwTaskId );
		HRESULT MFEndUnregisterWorkQueueWithMMCSS( IMFAsyncResult* pResult );
		HRESULT MFEnumDeviceSources( IMFAttributes* pAttributes, IMFActivate*** pppSourceActivate, UINT32* pcSourceActivate );
		HRESULT MFFrameRateToAverageTimePerFrame( UINT32 unNumerator, UINT32 unDenominator, UINT64* punAverageTimePerFrame );
		double MFGetAttributeDouble( IMFAttributes* pAttributes, REFGUID guidKey, double fDefault );
		HRESULT MFGetAttributeRatio( IMFAttributes* pAttributes, REFGUID guidKey, UINT32* pnNumerator, UINT32* punDenominator );
		HRESULT MFGetAttributesAsBlob( IMFAttributes* pAttributes, UINT8* pBuf, UINT cbBufSize );
		HRESULT MFGetAttributesAsBlobSize( IMFAttributes* pAttributes, UINT32* pcbBufSize );
		HRESULT MFGetAttributeSize( IMFAttributes* pAttributes, REFGUID guidKey, UINT32* punWidth, UINT32* punHeight );
		HRESULT MFGetTimerPeriodicity( DWORD* Periodicity );
		HRESULT MFGetMFTMerit( IUnknown* pMFT, UINT32 cbVerifier, const BYTE* verifier, DWORD* merit );
		HRESULT MFGetPluginControl( IMFPluginControl** ppPluginControl );
		MFTIME MFGetSystemTime( void );
		HRESULT MFGetWorkQueueMMCSSClass( DWORD dwWorkQueueId, LPWSTR pwszClass, DWORD* pcchClass );
		HRESULT MFGetWorkQueueMMCSSTaskId( DWORD dwWorkQueueId, LPDWORD pdwTaskId );
		HRESULT MFInitAttributesFromBlob( IMFAttributes* pAttributes, const UINT8* pBuf, UINT cbBufSize );
		HRESULT MFInitMediaTypeFromAMMediaType( IMFMediaType* pMFType, const AM_MEDIA_TYPE* pAMType );
		HRESULT MFInitMediaTypeFromMPEG1VideoInfo( IMFMediaType* pMFType, const MPEG1VIDEOINFO* pMP1VI, UINT32 cbBufSize, const GUID *pSubtype = NULL );
		HRESULT MFInitMediaTypeFromMPEG2VideoInfo( IMFMediaType* pMFType, const MPEG2VIDEOINFO* pMP2VI, UINT32 cbBufSize, const GUID *pSubtype = NULL );
		HRESULT MFInitMediaTypeFromVideoInfoHeader( IMFMediaType* pMFType, const VIDEOINFOHEADER* pVIH, UINT32 cbBufSize, const GUID *pSubtype = NULL );
		HRESULT MFInitMediaTypeFromVideoInfoHeader2( IMFMediaType* pMFType, const VIDEOINFOHEADER2* pVIH2, UINT32 cbBufSize, const GUID *pSubtype = NULL );
		HRESULT MFInitMediaTypeFromWaveFormatEx( IMFMediaType* pMFType, const WAVEFORMATEX* pWaveFormat, UINT32 cbBufSize );
		HRESULT MFLockPlatform(void);
		HRESULT MFLockWorkQueue( DWORD dwWorkQueue );

		HRESULT MFPutWorkItem( DWORD dwQueue, IMFAsyncCallback* pCallback, IUnknown* pState );
		HRESULT MFPutWorkItemEx( DWORD dwQueue, IMFAsyncResult* pResult );
		HRESULT MFRemovePeriodicCallback( DWORD dwKey );
		HRESULT MFScheduleWorkItem( IMFAsyncCallback* pCallback, IUnknown* pState, INT64 Timeout, MFWORKITEM_KEY* pKey );
		HRESULT MFScheduleWorkItemEx( IMFAsyncResult* pResult, INT64 Timeout, MFWORKITEM_KEY* pKey );
		HRESULT MFSerializeAttributesToStream( IMFAttributes* pAttr, DWORD dwOptions, IStream* pStm );
		HRESULT MFSerializePresentationDescriptor( IMFPresentationDescriptor* pPD, DWORD* pcbData, BYTE** ppbData );

		HRESULT MFUnlockPlatform(void);
		HRESULT MFUnlockWorkQueue( DWORD dwWorkQueue );
		
	};

}//nsWinQAPI

#endif//_QSYS_API_WIN32_MODULES_MEDIAFOUNDAPI_H_
