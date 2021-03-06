//BfXmlSimpleReader.h

// Copyright Querysoft Limited 2015
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

// XML Simple Reader

#ifndef BLUEFOOT_XML_SAX_SIMPLEREADER_H_3
#define BLUEFOOT_XML_SAX_SIMPLEREADER_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "BluefootQOR/XML/SAX/BfXmlReader.h"
#include "BluefootQOR/XML/SAX/BfXmlLocator.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	class CXmlSimpleReaderPrivate;

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CXmlSimpleReader : public CXmlReader
	{
	public:

		CXmlSimpleReader();
		virtual ~CXmlSimpleReader();

		bool Feature( const nsCodeQOR::CUCS2String& name, bool* ok = 0 ) const;
		void SetFeature( const nsCodeQOR::CUCS2String& name, bool value );
		bool HasFeature( const nsCodeQOR::CUCS2String& name ) const;

		virtual bool Parse( const CBFSource* input, bool incremental );
		virtual bool ParseContinue();

	private:

		__QCS_DECLARE_NONCOPYABLE( CXmlSimpleReader );

		nsCodeQOR::CTLRef< CXmlSimpleReaderPrivate > d_ptr;

		friend class CXmlSimpleReaderPrivate;
		friend class CXmlSimpleReaderLocator;
	};

	//------------------------------------------------------------------------------
	class CXmlSimpleReaderLocator : public CXmlLocator
	{

	public:

		__QOR_DECLARE_OCLASS_ID( CXmlSimpleReaderLocator );

		CXmlSimpleReaderLocator( CXmlSimpleReader* parent );
		virtual ~CXmlSimpleReaderLocator();

		int ColumnNumber() const;
		int LineNumber() const;

	private:

		CXmlSimpleReader* m_pReader;

		CXmlSimpleReaderLocator();
	};

}//nsBluefoot

#endif//BLUEFOOT_XML_SAX_SIMPLEREADER_H_3
