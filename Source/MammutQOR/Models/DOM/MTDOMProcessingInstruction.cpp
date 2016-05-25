//MTDOMProcessingInstruction.cpp

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

#include "MammutQOR/Models/DOM/MTDOMProcessingInstruction.h"

#define ATT_TARGET _TXT( "Target" )
#define ATT_DATA _TXT( "Data" )

//------------------------------------------------------------------------------
namespace nsMammut
{
	//------------------------------------------------------------------------------
	CProcessingInstruction::CProcessingInstruction(CModel* pContainer) : CDOMNode(pContainer)
	, m_Target(this, ATT_TARGET)
	, m_Data(this, ATT_DATA)
	{
		m_NodeType.Set(CMUint16(PROCESSING_INSTRUCTION_NODE));
	}

	//------------------------------------------------------------------------------
	CProcessingInstruction::CProcessingInstruction(const CProcessingInstruction& src) : CDOMNode(src)
	, m_Target(this, src.m_Target)
	, m_Data(this, src.m_Data)
	{
	}

	//--------------------------------------------------------------------------------
	//Construct from a generic PropertySet
	CProcessingInstruction::CProcessingInstruction(CPropertySet& src) : CDOMNode(src)
	, m_Target(this, ATT_TARGET, src[ATT_TARGET])
	, m_Data(this, ATT_DATA, src[ATT_DATA])
	{
		m_NodeType.Set(CMUint16(PROCESSING_INSTRUCTION_NODE));
	}

	//------------------------------------------------------------------------------
	CProcessingInstruction::~CProcessingInstruction()
	{
	}

	//------------------------------------------------------------------------------
	CProcessingInstruction& CProcessingInstruction::operator = (const CProcessingInstruction& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_Target = src.m_Target;
			m_Data = src.m_Data;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//assign from a generic property set
	CProcessingInstruction& CProcessingInstruction::operator = (CPropertySet& src)
	{
		if (&src != this)
		{
			CDOMNode::operator=(src);
			m_Target= src[ATT_TARGET];
			m_Data = src[ATT_DATA];
		}
		return *this;
	}

	//------------------------------------------------------------------------------
	bool CProcessingInstruction::operator == (const CProcessingInstruction& src)
	{
		return &(const_cast< CProcessingInstruction& >(src)) == this ? true : false;
	}

	//------------------------------------------------------------------------------
	CDOMNode& CProcessingInstruction::InsertBefore( CDOMNode& newChild, CDOMNode& refChild )
	{
		//TODO: Raise error
		return newChild;
	}

	//------------------------------------------------------------------------------
	CDOMNode& CProcessingInstruction::ReplaceChild( CDOMNode& newChild, CDOMNode& oldChild )
	{
		//TODO: Raise error
		return newChild;
	}

	//------------------------------------------------------------------------------
	CDOMNode& CProcessingInstruction::RemoveChild( CDOMNode& oldChild )
	{
		//TODO: Raise Error
		return oldChild;
	}

	//------------------------------------------------------------------------------
	CDOMNode& CProcessingInstruction::AppendChild( CDOMNode& newChild )
	{
		//TODO: Raise Error HIERARCHY_REQUEST_ERR
		return newChild;
	}

	//------------------------------------------------------------------------------
	bool CProcessingInstruction::HasChildNodes( void )
	{
		return false;
	}

}//nsMammut
