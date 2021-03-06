//WinQLWindowModel.cpp

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

//Model for Window 

#include "CompilerQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: this stored in members for later usage" )
#include "WinQL/GUI/VisualModels/WindowModel.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	
	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CWindowModel );
	
	//--------------------------------------------------------------------------------
	//default construct
	CWindowModel::CWindowModel( CModel* pContainer ) : CPropertySet( pContainer )
	,	m_Class	( this, _TXT( "Class" ).str()	, 0 )
	,	m_Style	( this, _TXT( "Style" ).str()	, 0	)
	,	m_Menu	( this, _TXT( "Menu" ).str()	, 0 )
	,	m_Layout( this, _TXT( "Layout" ).str(), CWindowLayoutModel( this )	)
	,	m_Name	( this, _TXT( "Name" ).str(),	_TXT( "WinQLWindow" ).c_str() )
	,	m_Parent( this, _TXT( "Parent" ).str(), 0 )
	,	m_Module( this, _TXT( "Module" ).str(), 0 )
	{
		
	}

	//--------------------------------------------------------------------------------
	CWindowModel::~CWindowModel()
	{
	}

	//--------------------------------------------------------------------------------
	//Copy construct
	CWindowModel::CWindowModel( const CWindowModel& src ) : CPropertySet( src )
	,	m_Class	( src.m_Class	)
	,	m_Style	( src.m_Style	)
	,	m_Menu	( src.m_Menu	)
	,	m_Layout( src.m_Layout	)
	,	m_Name	( src.m_Name	)
	,	m_Parent( src.m_Parent	)
	,	m_Module( src.m_Module	)
	{
	}

	//--------------------------------------------------------------------------------
	//Construct from a generic PropertySet
	CWindowModel::CWindowModel( nsMammut::CPropertySet& src ) : CPropertySet( src )
	,	m_Class	( this, _TXT( "Class" ).str()	 , src[ _TXT( "Class" ).str()	 	] )
	,	m_Style	( this, _TXT( "Style" ).str()	 , src[ _TXT( "Style" ).str()	 	] )
	,	m_Menu	( this, _TXT( "Menu" ).str()	 , src[ _TXT( "Menu" ).str()		] )
	,	m_Layout( this, _TXT( "Layout" ).str() , src[ _TXT( "Layout" ).str() 	] )
	,	m_Name	( this, _TXT( "Name" ).str()	 , src[ _TXT( "Name" ).str()		] )
	,	m_Parent( this, _TXT( "Parent" ).str() , src[ _TXT( "Parent" ).str()	] )
	,	m_Module( this, _TXT( "Module" ).str() , src[ _TXT( "Module" ).str()	] )
	{
	}

	//--------------------------------------------------------------------------------
	//assign from another CWindowLayoutModel
	CWindowModel& CWindowModel::operator = ( const CWindowModel& src )
	{
		if( &src != this )
		{
			m_Class	= src.m_Class	;
			m_Style	= src.m_Style	;
			m_Menu	= src.m_Menu	;
			m_Layout= src.m_Layout	;
			m_Name	= src.m_Name	;
			m_Parent = src.m_Parent	;
			m_Module = src.m_Module ;
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//assign from a generic property set
	CWindowModel& CWindowModel::operator = ( const nsMammut::CPropertySet& src )
	{
		if( &src != this )
		{
			m_Class	 = src[ _TXT( "Class" ).str()	 	];
			m_Style	 = src[ _TXT( "Style" ).str()	 	];
			m_Menu	 = src[ _TXT( "Menu" ).str()		];
			m_Layout = src[ _TXT( "Layout" ).str() 	];
			m_Name	 = src[ _TXT( "Name" ).str()		];
			m_Parent = src[ _TXT( "Parent" ).str()	];
			m_Module = src[ _TXT( "Module" ).str()	];
		}
		return *this;
	}

}//nsWin32
