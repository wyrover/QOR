//MTDOMDocumentType.cpp

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

#include "MammutQOR/Models/DOM/MTDOMDocumentType.h"

#define ATT_NAME _TXT( "Name" )
#define ATT_ENTITIES _TXT( "Entities" )
#define ATT_NOTATIONS _TXT( "Notations" )

//------------------------------------------------------------------------------
namespace nsMammut
{
	//------------------------------------------------------------------------------
	CDocumentType::CDocumentType(CModel* pContainer) : CDOMNode(pContainer)
	, m_Name(this, ATT_NAME)
	, m_Entities( this, ATT_ENTITIES)
	, m_Notations( this, ATT_NOTATIONS)
	{
		m_NodeType.Set(CMUint16(DOCUMENT_TYPE_NODE));
	}

	//------------------------------------------------------------------------------
	CDocumentType::CDocumentType(const CDocumentType& src) : CDOMNode(src)
	, m_Name(this, src.m_Name)
	, m_Entities(this, src.m_Entities)
	, m_Notations(this, src.m_Notations)
	{
	}

	//--------------------------------------------------------------------------------
	//Construct from a generic PropertySet
	CDocumentType::CDocumentType(CPropertySet& src) : CDOMNode(src)
	, m_Name(this, ATT_NAME, src[ATT_NAME])
	, m_Entities(this, ATT_ENTITIES, src[ATT_ENTITIES])
	, m_Notations(this, ATT_NOTATIONS, src[ATT_NOTATIONS])
	{
		m_NodeType.Set(CMUint16(DOCUMENT_TYPE_NODE));
	}

	//------------------------------------------------------------------------------
	CDocumentType::~CDocumentType()
	{
	}

	//------------------------------------------------------------------------------
	CDocumentType& CDocumentType::operator = (const CDocumentType& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_Name = src.m_Name;
			m_Entities = src.m_Entities;
			m_Notations = src.m_Notations;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//assign from a generic property set
	CDocumentType& CDocumentType::operator = (CPropertySet& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_Name = src[ATT_NAME];
			m_Entities = src[ATT_ENTITIES];
			m_Notations = src[ATT_NOTATIONS];
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	bool CDocumentType::operator == (const CDocumentType& src)
	{
		return &(const_cast< CDocumentType& >(src)) == this ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CDocumentType::ValidChildType( CMUint16 NodeType )
	{
		return false;
	}

}//nsMammut

