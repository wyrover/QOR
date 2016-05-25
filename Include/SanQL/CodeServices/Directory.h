//Directory.h

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

//SanOS Code Services Directory class

#ifndef SANQL_CODESERV_DIRECTORY_H_1
#define SANQL_CODESERV_DIRECTORY_H_1

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Macros/ClassIdentityMacros.h"
#include "SanQL/CodeServices/String.h"
#include "SanQL/CodeServices/Handle.h"

//------------------------------------------------------------------------------
namespace nsSanOS
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __SANQL ) CDirectory
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CDirectory );

		CDirectory( CHandle* pHandle = 0 );
		~CDirectory();

		//int _readdir(handle_t f, struct direntry *dirp, int count);
		//rewinddir

	private:

		CHandle* m_pHandle;
	};

}//nsSanOS

#endif//SANQL_CODESERV_DIRECTORY_H_1