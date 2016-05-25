//WinQLLocaleThreadData.cpp

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

#include "WinQL/CodeServices/Locale/WinQLLocaleThreadData.h"
#include "WinQL/CodeServices/Locale/WinQLLocale.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	__QOR_IMPLEMENT_OCLASS_LUID( CLocaleThreadData );

	//initial locale information struct, set to the C locale. Used only until the first call to setlocale()
	CThreadLocaleInfo CLocaleThreadData::sInitialLocInfo;
	CMBCInfo CLocaleThreadData::sInitialMBCInfo;

	//------------------------------------------------------------------------------
	CThreadLocaleInfo& CLocaleThreadData::InitialLocInfo()
	{
		return CLocaleThreadData::sInitialLocInfo;
	}

	//------------------------------------------------------------------------------
	CLocaleThreadData::CLocaleThreadData()
	{
		_WINQ_FCONTEXT( "CLocaleThreadData::CLocaleThreadData" );
		m_pLocaleInfo = &sInitialLocInfo;
		m_pMBCInfo = &sInitialMBCInfo;
	}

	//--------------------------------------------------------------------------------
	CLocaleThreadData::CLocaleThreadData( unsigned int codepage )
	{
		_WINQ_FCONTEXT( "CLocaleThreadData::CLocaleThreadData" );
		char locale_name[ 32 ];
		locale_name[0] = '.';
		//_ui64toa_s( codepage, locale_name + 1, sizeof( locale_name ) - 1, 10 );
		CSetLoc::_itoa_s( codepage, locale_name + 1, sizeof( locale_name ) - 1,  10 );
		CLocaleThreadData::CLocaleThreadData( CLocale::LCALL, locale_name );
	}

	//--------------------------------------------------------------------------------
	CLocaleThreadData::CLocaleThreadData( int iCategory, const char* pchLocale )
	{
		_WINQ_FCONTEXT( "CLocaleThreadData::CLocaleThreadData" );
		// Validate input
		if ( ( iCategory < CLocale::LCMIN ) || ( iCategory > CLocale::LCMAX ) || pchLocale == 0 )
		{
			//TODO:ERROR
			return;
		}
		
		m_pLocaleInfo = new CThreadLocaleInfo;

		if ( m_pLocaleInfo == 0 )
		{
			//TODO:ERROR
			//errno = -1;//TODO: ENOMEM;
			return;
		}

		m_pMBCInfo = new CMBCInfo;

		if ( m_pMBCInfo == 0 )
		{
			delete m_pLocaleInfo;
			//TODO:ERROR
			//errno = -1;//TODO:ENOMEM;
			return;
		}

		//_copytlocinfo_nolock( locinfo, &sInitialLocInfo );
		*m_pLocaleInfo = sInitialLocInfo;

		if ( m_pLocaleInfo->SetLocaleNoLock( iCategory, pchLocale ) == 0 )
		{
			m_pLocaleInfo->RemoveLocaleRef();
			m_pLocaleInfo->Free();
			//TODO:ERROR
		}
		else
		{
			if ( m_pMBCInfo->SetMBCPNoLock( m_pLocaleInfo->CodePage() ) != 0 )
			{
				delete m_pMBCInfo;            
				m_pLocaleInfo->RemoveLocaleRef();
				m_pLocaleInfo->Free();
				//TODO: ERROR            
			}
			else
			{
				m_pMBCInfo->InitRefCount();
			}
		}    
	}

	//------------------------------------------------------------------------------
	CLocaleThreadData::~CLocaleThreadData()
	{
		_WINQ_FCONTEXT( "CLocaleThreadData::~CLocaleThreadData" );
	}

	//------------------------------------------------------------------------------
	CThreadLocaleInfo*& CLocaleThreadData::LocaleInfoPtr()
	{
		return m_pLocaleInfo;
	}

	//------------------------------------------------------------------------------
	CMBCInfo*& CLocaleThreadData::MBCInfoPtr()
	{
		return m_pMBCInfo;
	}

	//--------------------------------------------------------------------------------
	void CLocaleThreadData::_free_locale()
	{
		if( this != 0 )
		{
			if (m_pMBCInfo != 0 && m_pMBCInfo->Release() == 0 && m_pMBCInfo != &sInitialMBCInfo )
			{
				delete m_pMBCInfo;
			}

			if (m_pLocaleInfo != 0)
			{
				/* this portion has to be in locale lock as there may be case when
				 * not this thread but some other thread is still holding to this
				 * locale and is also trying to free this locale. In this case
				 * we may end up leaking memory.
				 */

				//TODO: _mlock(_SETLOCALE_LOCK);
				__QCMP_TRY
				{
					m_pLocaleInfo->RemoveLocaleRef();
					if ( (m_pLocaleInfo != NULL) && (m_pLocaleInfo->RefCount() == 0) && (m_pLocaleInfo != &sInitialLocInfo ) ) 
					{
						m_pLocaleInfo->Free();
					}
				}
				__QCMP_FINALLY
				{
					//TODO: _munlock(_SETLOCALE_LOCK);
				}
			}
			// set this structure to zero. This will reduce the chance of using this after it is being freed.
	         
			m_pLocaleInfo = (CThreadLocaleInfo *)(((char *)0) + 0xbaadf00d);
			m_pMBCInfo = (CMBCInfo *)(((char *)0) + 0xbaadf00d);
			delete this;        
		}
	}


	//--------------------------------------------------------------------------------
	int CLocaleThreadData::GetLocaleTime( CLocaleDateTime* lc_time, CThreadLocaleInfo* ploci )
	{
		int ret = 0;
		CLocaleThreadData locinfo;

		// Some things are language-dependent and some are country-dependent.
		//This works around an NT limitation and lets us distinguish the two.

		unsigned long langid = MakeLcId( ploci->LocaleID( CLocale::LCTIME ).wLanguage, CLocale::Sort_Default );
		unsigned long ctryid = MakeLcId( ploci->LocaleID( CLocale::LCTIME ).wCountry, CLocale::Sort_Default );

		if (lc_time == NULL)
		{
			return -1;
		}

		locinfo.m_pLocaleInfo = ploci;
		locinfo.m_pMBCInfo = 0;

		// All the text-strings are Language-dependent:

		ret |= CLocale::GetLocaleString( &locinfo, langid, CLocale::Locale_SAbbrevDayName1, (void*)( lc_time->GetDayAbbrArray( 1 ) ) );
		ret |= CLocale::GetLocaleString( &locinfo, langid, CLocale::Locale_SAbbrevDayName2, (void*)( lc_time->GetDayAbbrArray( 2 ) ) );
		ret |= CLocale::GetLocaleString( &locinfo, langid, CLocale::Locale_SAbbrevDayName3, (void*)( lc_time->GetDayAbbrArray( 3 ) ) );
		ret |= CLocale::GetLocaleString( &locinfo, langid, CLocale::Locale_SAbbrevDayName4, (void*)( lc_time->GetDayAbbrArray( 4 ) ) );
		ret |= CLocale::GetLocaleString( &locinfo, langid, CLocale::Locale_SAbbrevDayName5, (void*)( lc_time->GetDayAbbrArray( 5 ) ) );
		ret |= CLocale::GetLocaleString( &locinfo, langid, CLocale::Locale_SAbbrevDayName6, (void*)( lc_time->GetDayAbbrArray( 6 ) ) );
		ret |= CLocale::GetLocaleString( &locinfo, langid, CLocale::Locale_SAbbrevDayName7, (void*)( lc_time->GetDayAbbrArray( 0 ) ) );

		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SDayName1, (void *)(lc_time->GetDayArray(1) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SDayName2, (void *)(lc_time->GetDayArray(2) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SDayName3, (void *)(lc_time->GetDayArray(3) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SDayName4, (void *)(lc_time->GetDayArray(4) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SDayName5, (void *)(lc_time->GetDayArray(5) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SDayName6, (void *)(lc_time->GetDayArray(6) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SDayName7, (void *)(lc_time->GetDayArray(0) ) );

		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName1, (void *)( lc_time->GetMonthAbbrArray( 0 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName2, (void *)( lc_time->GetMonthAbbrArray( 1 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName3, (void *)( lc_time->GetMonthAbbrArray( 2 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName4, (void *)( lc_time->GetMonthAbbrArray( 3 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName5, (void *)( lc_time->GetMonthAbbrArray( 4 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName6, (void *)( lc_time->GetMonthAbbrArray( 5 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName7, (void *)( lc_time->GetMonthAbbrArray( 6 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName8, (void *)( lc_time->GetMonthAbbrArray( 7 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName9, (void *)( lc_time->GetMonthAbbrArray( 8 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName10, (void *)( lc_time->GetMonthAbbrArray( 9 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName11, (void *)( lc_time->GetMonthAbbrArray( 10 ) ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SAbbrevMonthName12, (void *)( lc_time->GetMonthAbbrArray( 11 ) ) );

		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName1, (void *)(lc_time->GetMonthArray(0)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName2, (void *)(lc_time->GetMonthArray(1)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName3, (void *)(lc_time->GetMonthArray(2)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName4, (void *)(lc_time->GetMonthArray(3)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName5, (void *)(lc_time->GetMonthArray(4)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName6, (void *)(lc_time->GetMonthArray(5)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName7, (void *)(lc_time->GetMonthArray(6)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName8, (void *)(lc_time->GetMonthArray(7)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName9, (void *)(lc_time->GetMonthArray(8)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName10, (void *)(lc_time->GetMonthArray(9)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName11, (void *)(lc_time->GetMonthArray(10)));
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_SMonthName12, (void *)(lc_time->GetMonthArray(11)));

		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_S1159, (void *)(lc_time->GetAMArray() ) );
		ret |= CLocale::GetLocaleString(&locinfo, langid, CLocale::Locale_S2359, (void *)(lc_time->GetPMArray() ) );


		// The following relate to time format and are Country-dependent:

		ret |= CLocale::GetLocaleString(&locinfo, ctryid, CLocale::Locale_SShortDate, (void *)&lc_time->ww_sdatefmt);
		ret |= CLocale::GetLocaleString(&locinfo, ctryid, CLocale::Locale_SLongDate, (void *)&lc_time->ww_ldatefmt);

		ret |= CLocale::GetLocaleString(&locinfo, ctryid, CLocale::Locale_STimeFormat, (void *)&lc_time->ww_timefmt);

		ret |= CLocale::GetLocaleInt(&locinfo, ctryid, CLocale::Locale_ICalendarType, (void *)&lc_time->ww_caltype);

		lc_time->ww_lcid = ctryid;

		return ret;

	}

}//nsWin32
