//MTDOMEntity.cpp

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

#include "MammutQOR/Models/DOM/MTDOMEntity.h"

#define ATT_PUBLICID _TXT( "PublicID" )
#define ATT_SYSTEMID _TXT( "SystemID" )
#define ATT_NOTATIONNAME _TXT( "NotationName" )

//------------------------------------------------------------------------------
namespace nsMammut
{
	//------------------------------------------------------------------------------
	CEntity::CEntity(CModel* pContainer) : CDOMNode(pContainer)
	, m_PublicID(this, ATT_PUBLICID)
	, m_SystemID(this, ATT_SYSTEMID)
	, m_NotationName(this, ATT_NOTATIONNAME)
	{
		m_NodeType.Set(CMUint16(ENTITY_NODE));
	}

	//------------------------------------------------------------------------------
	CEntity::CEntity(const CEntity& src) : CDOMNode(src)
	, m_PublicID(this, src.m_PublicID)
	, m_SystemID(this, src.m_SystemID)
	, m_NotationName(this, src.m_NotationName)
	{
	}

	//--------------------------------------------------------------------------------
	//Construct from a generic PropertySet
	CEntity::CEntity(CPropertySet& src) : CDOMNode(src)
	, m_PublicID(this, ATT_PUBLICID, src[ATT_PUBLICID])
	, m_SystemID(this, ATT_SYSTEMID, src[ATT_SYSTEMID])
	, m_NotationName(this, ATT_NOTATIONNAME, src[ATT_NOTATIONNAME])
	{
		m_NodeType.Set(CMUint16(ENTITY_NODE));
	}

	//------------------------------------------------------------------------------
	CEntity::~CEntity()
	{
	}

	//------------------------------------------------------------------------------
	CEntity& CEntity::operator = (const CEntity& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_PublicID = src.m_PublicID;
			m_SystemID = src.m_SystemID;
			m_NotationName = src.m_NotationName;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//assign from a generic property set
	CEntity& CEntity::operator = (CPropertySet& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_PublicID = src[ATT_PUBLICID];
			m_SystemID = src[ATT_SYSTEMID];
			m_NotationName = src[ATT_NOTATIONNAME];
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	bool CEntity::operator == (const CEntity& src)
	{
		return &(const_cast< CEntity& >(src)) == this ? true : false;
	}

	//------------------------------------------------------------------------------
	bool CEntity::ValidChildType( CMUint16 NodeType )
	{
		return ( NodeType == ELEMENT_NODE || NodeType == PROCESSING_INSTRUCTION_NODE || NodeType == COMMENT_NODE || NodeType == TEXT_NODE || NodeType == CDATA_SECTION_NODE || NodeType == ENTITY_REFERENCE_NODE );
	}

}//nsMammut
