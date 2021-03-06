//CallContextBase.cpp

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

//Implementation of a basic call Context tracking object

#include "CompilerQOR.h"
#include "CodeQOR.h"
#include "CodeQOR/Tracing/CallContextBase.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/ErrorSystem/BaseErrorDomain.h"
#include "CodeQOR/Interception/CallInterceptor.h"
#include "CodeQOR/Instancing/TInstancePtr.h"

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
	//--------------------------------------------------------------------------------
	CParameterBase::CParameterBase()
	{
	}

	//--------------------------------------------------------------------------------
	CParameterBase::~CParameterBase()
	{
	}

	//--------------------------------------------------------------------------------
	CParameterBase::CParameterBase( const CParameterBase& src )
	{
		*this = src;
	}

	//--------------------------------------------------------------------------------
	CParameterBase& CParameterBase::operator = ( const CParameterBase& src )
	{
		m_p = src.m_p;
		return *this;
	}

	//--------------------------------------------------------------------------------
	void CParameterBase::Clear( void )
	{
		m_p = 0;
	}

	//--------------------------------------------------------------------------------
	CCallContextBase::CCallContextBase()
	{
		m_ucParamCount = 0;
	}

	//--------------------------------------------------------------------------------
	CCallContextBase::~CCallContextBase()
	{
		Cleanup();
	}

	//--------------------------------------------------------------------------------
	void CCallContextBase::CallMade( CFunctionContextBase* pCalledContext )
	{
		//Execution has reached the context of the callee
		CTInstancePtr< CCallInterceptor > ptrInterceptor;
		if( ptrInterceptor.operator->() )
		{
			ptrInterceptor->CallMade( this, pCalledContext );
		}
	}

	//--------------------------------------------------------------------------------
	void CCallContextBase::OnReturnAssignment()
	{
		CTInstancePtr< CCallInterceptor > ptrInterceptor;
		if( ptrInterceptor.operator->() )
		{
			ptrInterceptor->OnReturnAssignment( this );
		}
	}

	//--------------------------------------------------------------------------------
	void CCallContextBase::CallCompleted()
	{
		//Execution of the callee is winding up in preparation for returning
		CTInstancePtr< CCallInterceptor > ptrInterceptor;
		if( ptrInterceptor.operator->() )
		{
			ptrInterceptor->CallCompleted( this );
		}
	}

	//--------------------------------------------------------------------------------
	CParameterBase* CCallContextBase::Parameters( void )
	{
		return m_aParameters;	//Access to the list of registered parameters
	}

	//--------------------------------------------------------------------------------
	CParameterBase* CCallContextBase::ReturnValue( void )
	{
		return &m_ReturnValue;
	}

	//--------------------------------------------------------------------------------
	void CCallContextBase::Cleanup()
	{
		/*
		if( !m_pParameters.IsNull() )
		{
			m_pParameters().Clear();	//Delete all the parameter nodes without deferencing or deleting any of the parameters they refered to
		}
		*/
		//delete m_ReturnValue;
		//m_ReturnValue = 0;
		m_ReturnValue.Clear();
		m_ucParamCount = 0;
		if( CThreadContextBase::GetCurrent() )
		{
			if( CThreadContextBase::GetCurrent()->FunctionContext() )
			{
				CThreadContextBase::GetCurrent()->FunctionContext()->Unlock();
			}
		}
	}

	//--------------------------------------------------------------------------------
	void CCallContextBase::OutOfLineRegistration( CParameterBase& Param )
	{
		if( m_ucParamCount < 9 )
		{
#pragma warning(suppress: 6385)
			m_aParameters[ ++m_ucParamCount ] = Param;
		}
		//m_pParameters().Append( Param );
	}

}//nsCodeQOR

