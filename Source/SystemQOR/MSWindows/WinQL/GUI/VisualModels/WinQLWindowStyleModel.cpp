//WinQLWindowStyleModel.cpp

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

//Model for style data relating to Window visualization

#include "CompilerQOR.h"
__QCMP_WARNING_PUSH
__QCMP_WARNING_DISABLE( __QCMP_WARN_THIS_USED_IN_BASE_INIT_LIST, "Safe usage: this stored in members for later usage" )
#include "WinQL/GUI/VisualModels/WindowStyleModel.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{
	
	//--------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID( CWindowStyleModel );

	//--------------------------------------------------------------------------------
	//default construct
	CWindowStyleModel::CWindowStyleModel( CModel* pContainer ) : nsMammut::CModel( pContainer )
	,	m_InstanceStyleProperties( this )
	,	m_Popup				( &m_InstanceStyleProperties, _TXT("Popup").str()				, false	)
	,	m_Child				( &m_InstanceStyleProperties, _TXT("Child").str()				, false	)
	,	m_Minimize			( &m_InstanceStyleProperties, _TXT("Minimize").str()			, false	)
	,	m_Visisble			( &m_InstanceStyleProperties, _TXT("Visible").str()			, false )
	,	m_Disabled			( &m_InstanceStyleProperties, _TXT("Disabled").str()			, false )
	,	m_ClipSiblings		( &m_InstanceStyleProperties, _TXT("ClipSiblings").str()		, false )
	,	m_ClipChildren		( &m_InstanceStyleProperties, _TXT("ClipChildren").str()		, false )
	,	m_Maximize			( &m_InstanceStyleProperties, _TXT("Maximize").str()			, false )
	,	m_Caption			( &m_InstanceStyleProperties, _TXT("Caption").str()			, false )
	,	m_Border			( &m_InstanceStyleProperties, _TXT("Border").str()			, false )
	,	m_DlgFrame			( &m_InstanceStyleProperties, _TXT("DlgFrame").str()			, false )
	,	m_VScroll			( &m_InstanceStyleProperties, _TXT("VScroll").str()			, false )
	,	m_HScroll			( &m_InstanceStyleProperties, _TXT("HSCroll").str()			, false )
	,	m_SysMenu			( &m_InstanceStyleProperties, _TXT("SysMenu").str()			, false )
	,	m_ThickFrame		( &m_InstanceStyleProperties, _TXT("ThickFrame").str()		, false )
	,	m_Group				( &m_InstanceStyleProperties, _TXT("Group").str()			, false )
	,	m_TabStop			( &m_InstanceStyleProperties, _TXT("TabStop").str()			, false )
	,	m_MinimizeBox		( &m_InstanceStyleProperties, _TXT("MinimizeBox").str()		, false )
	,	m_MaximizeBox		( &m_InstanceStyleProperties, _TXT("MaximizeBox").str()		, false )
	,	m_OverlappedWindow	( &m_InstanceStyleProperties, _TXT("Overlapped").str()		, false )
	,	m_Left				( &m_InstanceStyleProperties, _TXT("Left").str()				, false )
	,	m_DlgModalFrame		( &m_InstanceStyleProperties, _TXT("DlgModalFrame").str()		, false )
	,	m_NoParentNotify	( &m_InstanceStyleProperties, _TXT("NoParentNotify").str()	, false )
	,	m_Topmost			( &m_InstanceStyleProperties, _TXT("Topmost").str()			, false )
	,	m_AcceptFiles		( &m_InstanceStyleProperties, _TXT("AcceptFiles").str()		, false )
	,	m_Transparent		( &m_InstanceStyleProperties, _TXT("Transparent").str()		, false )
	,	m_MDIChild			( &m_InstanceStyleProperties, _TXT("MDIChild").str()			, false )
	,	m_ToolWindow		( &m_InstanceStyleProperties, _TXT("ToolWindow").str()		, false )
	,	m_WindowEdge		( &m_InstanceStyleProperties, _TXT("WindowEdge").str()		, false )
	,	m_ClientEdge		( &m_InstanceStyleProperties, _TXT("ClientEdge").str()		, false )
	,	m_ContextHelp		( &m_InstanceStyleProperties, _TXT("ContextHelp").str()		, false )
	,	m_Right				( &m_InstanceStyleProperties, _TXT("Right").str()				, false )
	,	m_RTLReading		( &m_InstanceStyleProperties, _TXT("RTLReading").str()		, false )
	,	m_LeftSrollBar		( &m_InstanceStyleProperties, _TXT("LeftScrollBar").str()		, false )
	,	m_RightScrollBar	( &m_InstanceStyleProperties, _TXT("RightScrollBar").str()	, false )
	,	m_ControlParent		( &m_InstanceStyleProperties, _TXT("ControlParent").str()		, false )
	,	m_StaticEdge		( &m_InstanceStyleProperties, _TXT("StaticEdge").str()		, false )
	,	m_AppWindow			( &m_InstanceStyleProperties, _TXT("AppWindow").str()			, false )
	,	m_Layered			( &m_InstanceStyleProperties, _TXT("Layered").str()			, false )
	,	m_NoInheritLayout	( &m_InstanceStyleProperties, _TXT("NoInheritLayout").str()	, false )
	,	m_LayoutRTL			( &m_InstanceStyleProperties, _TXT("LayoutRTL").str()			, false )
	,	m_Composited		( &m_InstanceStyleProperties, _TXT("Composited").str()		, false )
	,	m_NoActivate		( &m_InstanceStyleProperties, _TXT("NoActivate").str()		, false )
	{
	}

	//--------------------------------------------------------------------------------
	CWindowStyleModel::~CWindowStyleModel()
	{
	}

	//--------------------------------------------------------------------------------
	//copy construct
	CWindowStyleModel::CWindowStyleModel( const CWindowStyleModel& src ) : 
		m_InstanceStyleProperties( src.m_InstanceStyleProperties )
	,	m_Popup				( &m_InstanceStyleProperties, src.m_Popup )
	,	m_Child				( &m_InstanceStyleProperties, src.m_Child )
	,	m_Minimize			( &m_InstanceStyleProperties, src.m_Minimize )
	,	m_Visisble			( &m_InstanceStyleProperties, src.m_Visisble )
	,	m_Disabled			( &m_InstanceStyleProperties, src.m_Disabled )
	,	m_ClipSiblings		( &m_InstanceStyleProperties, src.m_ClipSiblings )
	,	m_ClipChildren		( &m_InstanceStyleProperties, src.m_ClipChildren )
	,	m_Maximize			( &m_InstanceStyleProperties, src.m_Maximize )
	,	m_Caption			( &m_InstanceStyleProperties, src.m_Caption )
	,	m_Border			( &m_InstanceStyleProperties, src.m_Border )
	,	m_DlgFrame			( &m_InstanceStyleProperties, src.m_DlgFrame )
	,	m_VScroll			( &m_InstanceStyleProperties, src.m_VScroll )
	,	m_HScroll			( &m_InstanceStyleProperties, src.m_HScroll )
	,	m_SysMenu			( &m_InstanceStyleProperties, src.m_SysMenu )
	,	m_ThickFrame		( &m_InstanceStyleProperties, src.m_ThickFrame )
	,	m_Group				( &m_InstanceStyleProperties, src.m_Group )
	,	m_TabStop			( &m_InstanceStyleProperties, src.m_TabStop )
	,	m_MinimizeBox		( &m_InstanceStyleProperties, src.m_MinimizeBox )
	,	m_MaximizeBox		( &m_InstanceStyleProperties, src.m_MaximizeBox )
	,	m_OverlappedWindow	( &m_InstanceStyleProperties, src.m_OverlappedWindow )
	,	m_Left				( &m_InstanceStyleProperties, src.m_Left )
	,	m_DlgModalFrame		( &m_InstanceStyleProperties, src.m_DlgModalFrame )
	,	m_NoParentNotify	( &m_InstanceStyleProperties, src.m_NoParentNotify )
	,	m_Topmost			( &m_InstanceStyleProperties, src.m_Topmost )
	,	m_AcceptFiles		( &m_InstanceStyleProperties, src.m_AcceptFiles )
	,	m_Transparent		( &m_InstanceStyleProperties, src.m_Transparent )
	,	m_MDIChild			( &m_InstanceStyleProperties, src.m_MDIChild )
	,	m_ToolWindow		( &m_InstanceStyleProperties, src.m_ToolWindow )
	,	m_WindowEdge		( &m_InstanceStyleProperties, src.m_WindowEdge )
	,	m_ClientEdge		( &m_InstanceStyleProperties, src.m_ClientEdge )
	,	m_ContextHelp		( &m_InstanceStyleProperties, src.m_ContextHelp )
	,	m_Right				( &m_InstanceStyleProperties, src.m_Right )
	,	m_RTLReading		( &m_InstanceStyleProperties, src.m_RTLReading )
	,	m_LeftSrollBar		( &m_InstanceStyleProperties, src.m_LeftSrollBar )
	,	m_RightScrollBar	( &m_InstanceStyleProperties, src.m_RightScrollBar )
	,	m_ControlParent		( &m_InstanceStyleProperties, src.m_ControlParent )
	,	m_StaticEdge		( &m_InstanceStyleProperties, src.m_StaticEdge )
	,	m_AppWindow			( &m_InstanceStyleProperties, src.m_AppWindow )
	,	m_Layered			( &m_InstanceStyleProperties, src.m_Layered )
	,	m_NoInheritLayout	( &m_InstanceStyleProperties, src.m_NoInheritLayout )
	,	m_LayoutRTL			( &m_InstanceStyleProperties, src.m_LayoutRTL )
	,	m_Composited		( &m_InstanceStyleProperties, src.m_Composited )
	,	m_NoActivate		( &m_InstanceStyleProperties, src.m_NoActivate )
	{
		*this = src;
	}

	//--------------------------------------------------------------------------------
	//Construct from a generic PropertySet
	CWindowStyleModel::CWindowStyleModel( nsMammut::CPropertySet& src ) : nsMammut::CModel()
	,	m_InstanceStyleProperties( this )
	,	m_Popup				( &m_InstanceStyleProperties, _TXT( "Popup").str()			, src[ _TXT("Popup").str()			] )
	,	m_Child				( &m_InstanceStyleProperties, _TXT( "Child").str()			, src[ _TXT("Child").str()			] )
	,	m_Minimize			( &m_InstanceStyleProperties, _TXT( "Minimize").str()			, src[ _TXT("Minimize").str()			] )
	,	m_Visisble			( &m_InstanceStyleProperties, _TXT( "Visible").str()			, src[ _TXT("Visible").str()			] )
	,	m_Disabled			( &m_InstanceStyleProperties, _TXT( "Disabled").str()			, src[ _TXT("Disabled").str()			] )
	,	m_ClipSiblings		( &m_InstanceStyleProperties, _TXT( "ClipSiblings").str()		, src[ _TXT("ClipSiblings").str()		] )
	,	m_ClipChildren		( &m_InstanceStyleProperties, _TXT( "ClipChildren").str()		, src[ _TXT("ClipChildren").str()		] )
	,	m_Maximize			( &m_InstanceStyleProperties, _TXT( "Maximize").str()			, src[ _TXT("Maximize").str()			] )
	,	m_Caption			( &m_InstanceStyleProperties, _TXT( "Caption").str()			, src[ _TXT("Caption").str()			] )
	,	m_Border			( &m_InstanceStyleProperties, _TXT( "Border").str()			, src[ _TXT("Border").str()			] )
	,	m_DlgFrame			( &m_InstanceStyleProperties, _TXT( "DlgFrame").str()			, src[ _TXT("DlgFrame").str()			] )
	,	m_VScroll			( &m_InstanceStyleProperties, _TXT( "VScroll").str()			, src[ _TXT("VScroll").str()			] )
	,	m_HScroll			( &m_InstanceStyleProperties, _TXT( "HSCroll").str()			, src[ _TXT("HSCroll").str()			] )
	,	m_SysMenu			( &m_InstanceStyleProperties, _TXT( "SysMenu").str()			, src[ _TXT("SysMenu").str()		] )
	,	m_ThickFrame		( &m_InstanceStyleProperties, _TXT( "ThickFrame").str()		, src[ _TXT("ThickFrame").str()		] )
	,	m_Group				( &m_InstanceStyleProperties, _TXT( "Group").str()			, src[ _TXT("Group").str()			] )
	,	m_TabStop			( &m_InstanceStyleProperties, _TXT( "TabStop").str()			, src[ _TXT("TabStop").str()			] )
	,	m_MinimizeBox		( &m_InstanceStyleProperties, _TXT( "MinimizeBox").str()		, src[ _TXT("MinimizeBox").str()		] )
	,	m_MaximizeBox		( &m_InstanceStyleProperties, _TXT( "MaximizeBox").str()		, src[ _TXT("MaximizeBox").str()		] )
	,	m_OverlappedWindow	( &m_InstanceStyleProperties, _TXT( "Overlapped").str()		, src[ _TXT("Overlapped").str()		] )
	,	m_Left				( &m_InstanceStyleProperties, _TXT( "Left").str()				, src[ _TXT("Left").str()				] )
	,	m_DlgModalFrame		( &m_InstanceStyleProperties, _TXT( "DlgModalFrame").str()	, src[ _TXT("DlgModalFrame").str()	] )
	,	m_NoParentNotify	( &m_InstanceStyleProperties, _TXT( "NoParentNotify").str()	, src[ _TXT("NoParentNotify").str()	] )
	,	m_Topmost			( &m_InstanceStyleProperties, _TXT( "Topmost").str()			, src[ _TXT("Topmost").str()			] )
	,	m_AcceptFiles		( &m_InstanceStyleProperties, _TXT( "AcceptFiles").str()		, src[ _TXT("AcceptFiles").str()		] )
	,	m_Transparent		( &m_InstanceStyleProperties, _TXT( "Transparent").str()		, src[ _TXT("Transparent").str()		] )
	,	m_MDIChild			( &m_InstanceStyleProperties, _TXT( "MDIChild").str()			, src[ _TXT("MDIChild").str()			] )
	,	m_ToolWindow		( &m_InstanceStyleProperties, _TXT( "ToolWindow").str()		, src[ _TXT("ToolWindow").str()		] )
	,	m_WindowEdge		( &m_InstanceStyleProperties, _TXT( "WindowEdge").str()		, src[ _TXT("WindowEdge").str()		] )
	,	m_ClientEdge		( &m_InstanceStyleProperties, _TXT( "ClientEdge").str()		, src[ _TXT("ClientEdge").str()		] )
	,	m_ContextHelp		( &m_InstanceStyleProperties, _TXT( "ContextHelp").str()		, src[ _TXT("ContextHelp").str()		] )
	,	m_Right				( &m_InstanceStyleProperties, _TXT( "Right").str()			, src[ _TXT("Right").str()			] )	
	,	m_RTLReading		( &m_InstanceStyleProperties, _TXT( "RTLReading").str()		, src[ _TXT("RTLReading").str()		] )
	,	m_LeftSrollBar		( &m_InstanceStyleProperties, _TXT( "LeftScrollBar").str()	, src[ _TXT("LeftScrollBar").str()	] )	
	,	m_RightScrollBar	( &m_InstanceStyleProperties, _TXT( "RightScrollBar").str()	, src[ _TXT("RightScrollBar").str()	] )
	,	m_ControlParent		( &m_InstanceStyleProperties, _TXT( "ControlParent").str()	, src[ _TXT("ControlParent").str()	] )	
	,	m_StaticEdge		( &m_InstanceStyleProperties, _TXT( "StaticEdge").str()		, src[ _TXT("StaticEdge").str()		] )
	,	m_AppWindow			( &m_InstanceStyleProperties, _TXT( "AppWindow").str()		, src[ _TXT("AppWindow").str()		] )	
	,	m_Layered			( &m_InstanceStyleProperties, _TXT( "Layered").str()			, src[ _TXT("Layered").str()			] )
	,	m_NoInheritLayout	( &m_InstanceStyleProperties, _TXT( "NoInheritLayout").str()	, src[ _TXT("NoInheritLayout").str()	] )
	,	m_LayoutRTL			( &m_InstanceStyleProperties, _TXT( "LayoutRTL").str()		, src[ _TXT("LayoutRTL").str()		] )	
	,	m_Composited		( &m_InstanceStyleProperties, _TXT( "Composited").str()		, src[ _TXT("Composited").str()		] )
	,	m_NoActivate		( &m_InstanceStyleProperties, _TXT( "NoActivate").str()		, src[ _TXT("NoActivate").str()		] )
	{
	}
	
__QCMP_WARNING_POP

	//--------------------------------------------------------------------------------
	//assign from another CWindowStyleModel
	CWindowStyleModel& CWindowStyleModel::operator = ( const CWindowStyleModel& src )
	{
		if( &src != this )
		{
			m_InstanceStyleProperties = src.m_InstanceStyleProperties;
			m_Popup = ( src.m_Popup );
			m_Child = ( src.m_Child );
			m_Minimize = ( src.m_Minimize );
			m_Visisble = ( src.m_Visisble );
			m_Disabled = ( src.m_Disabled );
			m_ClipSiblings = ( src.m_ClipSiblings );
			m_ClipChildren = ( src.m_ClipChildren );
			m_Maximize = ( src.m_Maximize );
			m_Caption = ( src.m_Caption );
			m_Border = ( src.m_Border );
			m_DlgFrame = ( src.m_DlgFrame );
			m_VScroll = ( src.m_VScroll );
			m_HScroll = ( src.m_HScroll );
			m_SysMenu = ( src.m_SysMenu );
			m_ThickFrame = ( src.m_ThickFrame );
			m_Group = ( src.m_Group );
			m_TabStop = ( src.m_TabStop );
			m_MinimizeBox = ( src.m_MinimizeBox );
			m_MaximizeBox = ( src.m_MaximizeBox );
			m_OverlappedWindow = ( src.m_OverlappedWindow );
			m_Left = ( src.m_Left );
			m_DlgModalFrame = ( src.m_DlgModalFrame );
			m_NoParentNotify = ( src.m_NoParentNotify );
			m_Topmost = ( src.m_Topmost );
			m_AcceptFiles = ( src.m_AcceptFiles );
			m_Transparent = ( src.m_Transparent );
			m_MDIChild = ( src.m_MDIChild );
			m_ToolWindow = ( src.m_ToolWindow );
			m_WindowEdge = ( src.m_WindowEdge );
			m_ClientEdge = ( src.m_ClientEdge );
			m_ContextHelp = ( src.m_ContextHelp );
			m_Right = ( src.m_Right );
			m_RTLReading = ( src.m_RTLReading );
			m_LeftSrollBar = ( src.m_LeftSrollBar );
			m_RightScrollBar = ( src.m_RightScrollBar );
			m_ControlParent = ( src.m_ControlParent );
			m_StaticEdge = ( src.m_StaticEdge );
			m_AppWindow = ( src.m_AppWindow );
			m_Layered = ( src.m_Layered );
			m_NoInheritLayout = ( src.m_NoInheritLayout );
			m_LayoutRTL = ( src.m_LayoutRTL );
			m_Composited = ( src.m_Composited );
			m_NoActivate = ( src.m_NoActivate );
		}
		return *this;
	}

	//--------------------------------------------------------------------------------
	//assign from a generic property set
	CWindowStyleModel& CWindowStyleModel::operator = ( const nsMammut::CPropertySet& src )
	{
		if( (void*)&src != (void*)this )
		{
			m_Popup				=	src[ _TXT("Popup").str()			];
			m_Child				=	src[ _TXT("Child").str()			];
			m_Minimize			=	src[ _TXT("Minimize").str()		];
			m_Visisble			=	src[ _TXT("Visible").str()		];
			m_Disabled			=	src[ _TXT("Disabled").str()		];
			m_ClipSiblings		=	src[ _TXT("ClipSiblings").str()	];
			m_ClipChildren		=	src[ _TXT("ClipChildren").str()	];
			m_Maximize			=	src[ _TXT("Maximize").str()		];
			m_Caption			=	src[ _TXT("Caption").str()		];
			m_Border			=	src[ _TXT("Border").str()			];
			m_DlgFrame			=	src[ _TXT("DlgFrame").str()		];
			m_VScroll			=	src[ _TXT("VScroll").str()		];
			m_HScroll			=	src[ _TXT("HSCroll").str()		];
			m_SysMenu			=	src[ _TXT("SysMenu").str()		];
			m_ThickFrame		=	src[ _TXT("ThickFrame").str()		];
			m_Group				=	src[ _TXT("Group").str()			];
			m_TabStop			=	src[ _TXT("TabStop").str()		];
			m_MinimizeBox		=	src[ _TXT("MinimizeBox").str()	];
			m_MaximizeBox		=	src[ _TXT("MaximizeBox").str()	];
			m_OverlappedWindow	=	src[ _TXT("Overlapped").str()		];
			m_Left				=	src[ _TXT("Left").str()			];
			m_DlgModalFrame		=	src[ _TXT("DlgModalFrame").str()	];
			m_NoParentNotify	=	src[ _TXT("NoParentNotify").str()	];
			m_Topmost			=	src[ _TXT("Topmost").str()		];
			m_AcceptFiles		=	src[ _TXT("AcceptFiles").str()	];
			m_Transparent		=	src[ _TXT("Transparent").str()	];
			m_MDIChild			=	src[ _TXT("MDIChild").str()		];
			m_ToolWindow		=	src[ _TXT("ToolWindow").str()		];
			m_WindowEdge		=	src[ _TXT("WindowEdge").str()		];
			m_ClientEdge		=	src[ _TXT("ClientEdge").str()		];
			m_ContextHelp		=	src[ _TXT("ContextHelp").str()	];
			m_Right				=	src[ _TXT("Right").str()			];
			m_RTLReading		=	src[ _TXT("RTLReading").str()		];
			m_LeftSrollBar		=	src[ _TXT("LeftScrollBar").str()	];
			m_RightScrollBar	=	src[ _TXT("RightScrollBar").str()	];
			m_ControlParent		=	src[ _TXT("ControlParent").str()	];
			m_StaticEdge		=	src[ _TXT("StaticEdge").str()		];
			m_AppWindow			=	src[ _TXT("AppWindow").str()		];
			m_Layered			=	src[ _TXT("Layered").str()		];
			m_NoInheritLayout	=	src[ _TXT("NoInheritLayout").str()];
			m_LayoutRTL			=	src[ _TXT("LayoutRTL").str()		];
			m_Composited		=	src[ _TXT("Composited").str()		];
			m_NoActivate		=	src[ _TXT("NoActivate").str()		];
		}
		return *this;
	}























}//nsWin32