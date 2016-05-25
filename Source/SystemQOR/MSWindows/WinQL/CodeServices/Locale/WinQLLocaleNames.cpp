//WinQLLocaleNames.cpp

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

#include "WinQL/CodeServices/Locale/WinQLLocale.h"
#include <string.h>

namespace nsWin32
{
	/*
	//  non-NLS language string table
	const CLocale::CLOCALETAB CLocale::s_aLanguage[] =
	{
		{"american",                    "ENU"},
		{"american english",            "ENU"},
		{"american-english",            "ENU"},
		{"australian",                  "ENA"},
		{"belgian",                     "NLB"},
		{"canadian",                    "ENC"},
		{"chh",                         "ZHH"},
		{"chi",                         "ZHI"},
		{"chinese",                     "CHS"},
		{"chinese-hongkong",            "ZHH"},
		{"chinese-simplified",          "CHS"},
		{"chinese-singapore",           "ZHI"},
		{"chinese-traditional",         "CHT"},
		{"dutch-belgian",               "NLB"},
		{"english-american",            "ENU"},
		{"english-aus",                 "ENA"},
		{"english-belize",              "ENL"},
		{"english-can",                 "ENC"},
		{"english-caribbean",           "ENB"},
		{"english-ire",                 "ENI"},
		{"english-jamaica",             "ENJ"},
		{"english-nz",                  "ENZ"},
		{"english-south africa",        "ENS"},
		{"english-trinidad y tobago",   "ENT"},
		{"english-uk",                  "ENG"},
		{"english-us",                  "ENU"},
		{"english-usa",                 "ENU"},
		{"french-belgian",              "FRB"},
		{"french-canadian",             "FRC"},
		{"french-luxembourg",           "FRL"},
		{"french-swiss",                "FRS"},
		{"german-austrian",             "DEA"},
		{"german-lichtenstein",         "DEC"},
		{"german-luxembourg",           "DEL"},
		{"german-swiss",                "DES"},
		{"irish-english",               "ENI"},
		{"italian-swiss",               "ITS"},
		{"norwegian",                   "NOR"},
		{"norwegian-bokmal",            "NOR"},
		{"norwegian-nynorsk",           "NON"},
		{"portuguese-brazilian",        "PTB"},
		{"spanish-argentina",           "ESS"},
		{"spanish-bolivia",             "ESB"},
		{"spanish-chile",               "ESL"},
		{"spanish-colombia",            "ESO"},
		{"spanish-costa rica",          "ESC"},
		{"spanish-dominican republic",  "ESD"},
		{"spanish-ecuador",             "ESF"},
		{"spanish-el salvador",         "ESE"},
		{"spanish-guatemala",           "ESG"},
		{"spanish-honduras",            "ESH"},
		{"spanish-mexican",             "ESM"},
		{"spanish-modern",              "ESN"},
		{"spanish-nicaragua",           "ESI"},
		{"spanish-panama",              "ESA"},
		{"spanish-paraguay",            "ESZ"},
		{"spanish-peru",                "ESR"},
		{"spanish-puerto rico",         "ESU"},
		{"spanish-uruguay",             "ESY"},
		{"spanish-venezuela",           "ESV"},
		{"swedish-finland",             "SVF"},
		{"swiss",                       "DES"},
		{"uk",                          "ENG"},
		{"us",                          "ENU"},
		{"usa",                         "ENU"}
	};
	*/
	//const unsigned int CLocale::s_NumLangs = 64;

	//  non-NLS country/region string table
	/*
	const CLocale::CLOCALETAB CLocale::s_aCountry[] =
	{
		{"america",                     "USA"},
		{"britain",                     "GBR"},
		{"china",                       "CHN"},
		{"czech",                       "CZE"},
		{"england",                     "GBR"},
		{"great britain",               "GBR"},
		{"holland",                     "NLD"},
		{"hong-kong",                   "HKG"},
		{"new-zealand",                 "NZL"},
		{"nz",                          "NZL"},
		{"pr china",                    "CHN"},
		{"pr-china",                    "CHN"},
		{"puerto-rico",                 "PRI"},
		{"slovak",                      "SVK"},
		{"south africa",                "ZAF"},
		{"south korea",                 "KOR"},
		{"south-africa",                "ZAF"},
		{"south-korea",                 "KOR"},
		{"trinidad & tobago",           "TTO"},
		{"uk",                          "GBR"},
		{"united-kingdom",              "GBR"},
		{"united-states",               "USA"},
		{"us",                          "USA"},
	};

	const unsigned int CLocale::s_NumCountries = 22;
	*/
	//--------------------------------------------------------------------------------
	bool CLocale::TranslateName ( const CLocale::CLOCALETAB* lpTable, int iHigh, const char** ppchName )
	{
		int	i;
		int	iCmp = 1;
		int	iLow = 0;

		//  typical binary search - do until no more to search or match
		while ( iLow <= iHigh && iCmp != 0 )
		{
			i = ( iLow + iHigh ) / 2;
			iCmp = stricmp( *ppchName, (const char *) ( *(lpTable + i)).szName );

			if ( iCmp == 0 )
			{
				*ppchName = ( *(lpTable + i) ).chAbbrev;
			}
			else if ( iCmp < 0 )
			{
				iHigh = i - 1;
			}
			else
			{
				iLow = i + 1;
			}
		}

		return !iCmp;
	}

}//nsWin32