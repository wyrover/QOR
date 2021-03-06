//BaseCRT.h

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

//Base CRT0 class

#ifndef _SYSTEMQOR_POSIX_CRT_H_3
#define _SYSTEMQOR_POSIX_CRT_H_3

#include "SystemQOR/Posix/Baseaio.h"
#include "SystemQOR/Posix/Baseassert.h"
#include "SystemQOR/Posix/Basecomplex.h"
#include "SystemQOR/Posix/Basectype.h"
#include "SystemQOR/Posix/Basedirent.h"
#include "SystemQOR/Posix/Basedlfcn.h"
#include "SystemQOR/Posix/Baseerrno.h"
#include "SystemQOR/Posix/Basefcntl.h"
#include "SystemQOR/Posix/Basefenv.h"
#include "SystemQOR/Posix/Basefloat.h"
#include "SystemQOR/Posix/Basefmtmsg.h"
#include "SystemQOR/Posix/Basefnmatch.h"
#include "SystemQOR/Posix/Baseftw.h"
#include "SystemQOR/Posix/Baseglob.h"
#include "SystemQOR/Posix/Baseinttypes.h"
#include "SystemQOR/Posix/Baseiso646.h"
#include "SystemQOR/Posix/Baselimits.h"
#include "SystemQOR/Posix/Baselocale.h"
#include "SystemQOR/Posix/Basemath.h"
#include "SystemQOR/Posix/Basesetjmp.h"
#include "SystemQOR/Posix/Basesignal.h"
#include "SystemQOR/Posix/Basestdarg.h"
#include "SystemQOR/Posix/Basestdbool.h"
#include "SystemQOR/Posix/Basestddef.h"
#include "SystemQOR/Posix/Basestdint.h"
#include "SystemQOR/Posix/Basestdio.h"
#include "SystemQOR/Posix/Basestdlib.h"
#include "SystemQOR/Posix/Basestring.h"
#include "SystemQOR/Posix/Basetgmath.h"
#include "SystemQOR/Posix/Basetime.h"
#include "SystemQOR/Posix/Basewchar.h"
#include "SystemQOR/Posix/Basewctype.h"
#include "SystemQOR/Posix/Basepthread.h"
#include "SystemQOR/Posix/Baseulimit.h"
#include "SystemQOR/Posix/Baseunistd.h"
#include "SystemQOR/Posix/Baseutime.h"
#include "SystemQOR/Posix/Baseutmpx.h"
#include "SystemQOR/Posix/Basewordexp.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
    class __QOR_INTERFACE( __QSYS ) CCRTImpl
    {
    public:

		__QOR_DECLARE_OCLASS_ID( CCRTImpl );

		CCRTImpl();
		virtual ~CCRTImpl();

        virtual void Init() = 0;
		virtual void Cleanup() = 0;

        Caio* m_paio;
        Cassert* m_passert;
        Ccomplex* m_pcomplex;
        Cctype* m_pctype;
        Cdirent* m_pdirent;
        Cdlfcn* m_pdlcfn;
        Cerrno* m_perrno;
        Cfcntl* m_pfcntl;
        Cfenv* m_pfenv;
        Cfmtmsg* m_pfmtmsg;
        Cfnmatch* m_pfnmatch;
        Cftw* m_pftw;
        Cglob* m_pglob;
        Cinttypes* m_pinttypes;
        Ciso646* m_piso646;
        Climits* m_plimits;
        Clocale* m_plocale;
        Cmath* m_pmath;
        Csetjmp* m_psetjmp;
        Csignal* m_psignal;
        Cstdarg* m_pstdarg;
        Cstdbool* m_pstdbool;
        Cstddef* m_pstddef;
        Cstdint* m_pstdint;
        Cstdio* m_pstdio;
        Cstdlib* m_pstdlib;
        Cstring* m_pstring;
        Ctgmath* m_ptgmath;
        Ctime* m_ptime;
        Cwchar* m_pwchar;
        Cwctype* m_pwctype;
        Cpthread* m_ppthread;
        Culimit* m_pulimit;
        Cunistd* m_punistd;
        Cutime* m_putime;
        Cutmpx* m_putmpx;
        Cwordexp* m_pwordexp;

    };

}//nsBaseCRT

#endif//_SYSTEMQOR_POSIX_CRT_H_3
