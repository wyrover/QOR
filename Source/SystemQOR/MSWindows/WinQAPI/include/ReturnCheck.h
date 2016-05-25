//ReturnCheck.h

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

#ifndef WINQAPI_CS_RETURNCHECK_H_1
#define WINQAPI_CS_RETURNCHECK_H_1

#include "CodeQOR/Parameters/ParamChecking.h"
#include "../Source/SystemQOR/MSWindows/WinQAPI/include/FunctionContext.h"

//--------------------------------------------------------------------------------
namespace nsWinQAPI
{
	//--------------------------------------------------------------------------------
	//Generic validated return value class
	//TReturn is the type of the return value
	//TCheck is the type of validation check to be performed
	template<class TReturn, class TCheck >
	class CCheckReturn
	{
	public:

#if		( __QOR_PARAMETER_CHECKING_ == __QCS_YES_ )
		typedef CCheckReturn< TReturn, TCheck > TType;
#else
		typedef TReturn TType;
#endif
		
		//--------------------------------------------------------------------------------
		CCheckReturn() : m_bInitialised( false )
		{
			TCheck AutoCheck;
			TCheck::Init( m_Param, &AutoCheck );
		}

		//--------------------------------------------------------------------------------
		CCheckReturn( TReturn param ) : m_Param( param ), m_bInitialised( true )
		{		
			TCheck AutoCheck;
			TCheck::Check( m_Param, &AutoCheck );
		}

		//--------------------------------------------------------------------------------
		CCheckReturn& operator = ( TReturn& value )
		{
			m_Param = value;
			m_bInitialised = true;
			TCheck AutoCheck;
			TCheck::Check( m_Param, &AutoCheck );
			return *this;
		}

		//--------------------------------------------------------------------------------
		operator TReturn()
		{					
			if( !m_bInitialised )
			{
				nsCodeQOR::CError::Raise( UNINITIALIZED_PARAMETER, nsWinQAPI::ErrorDomainPtr(), nsCodeQOR::CError::ERR_LVL_SERIOUS );
			}
			return m_Param;
		}

	protected:

		TReturn m_Param;			//Instance of parameter type

	private:

		bool m_bInitialised;
	};

	//--------------------------------------------------------------------------------
	template< typename TValue, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
	class CAutoErrorCheck
	{
	public:

		//--------------------------------------------------------------------------------
		CAutoErrorCheck()
		{
		}

		//--------------------------------------------------------------------------------
		virtual ~CAutoErrorCheck()
		{
		}

		//--------------------------------------------------------------------------------
		virtual bool Test( TValue& value )
		{
			return false;
		}

		//--------------------------------------------------------------------------------
		virtual void DefaultInit( TValue& value )
		{
		}

		//--------------------------------------------------------------------------------
		static void Check( TValue& value, CAutoErrorCheck* pInstance )
		{
			if( !pInstance->Test( value ) )
			{				
				//unsigned long ulLastError = nsWinQAPI::CKernel32::Instance().GetLastError();
				//TODO: Get the function context details from the point of failure and add them as error parameters
				nsCodeQOR::CError::Raise( iErr, nsWinQAPI::ErrorDomainPtr(), eLevel );
			}
		}

		//--------------------------------------------------------------------------------
		static void Init( TValue& value, CAutoErrorCheck* pInstance )
		{
			pInstance->DefaultInit( value );
		}
	};

	//--------------------------------------------------------------------------------
	template< nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
 	class CBoolCheck : public CAutoErrorCheck< BOOL, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( BOOL& value )
		{
 			return value ? true : false;
		}

		//--------------------------------------------------------------------------------
		virtual void DefaultInit( BOOL& value )
		{
			value = 0;
		}
	};

	//--------------------------------------------------------------------------------
	template< nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
 	class CHandleCheck : public CAutoErrorCheck< HANDLE, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( HANDLE& value )
		{
 			return ( value == (HANDLE)0xFFFFFFFF ) ? false : true;
		}
	};

	//--------------------------------------------------------------------------------
	template< nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
 	class CHandleNullCheck : public CAutoErrorCheck< HANDLE, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( HANDLE& value )
		{
 			return ( value == (HANDLE)0xFFFFFFFF || value == (HANDLE)0x00000000 ) ? false : true;
		}
	};

	//--------------------------------------------------------------------------------
	template< typename THandle, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
	class CCheckNonZeroHandle : public CAutoErrorCheck< THandle, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( THandle& value )
		{
 			return ( value == 0x00000000 ) ? false : true;
		}
	};

	//--------------------------------------------------------------------------------
	template< nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
 	class CSuccessCheck : public CAutoErrorCheck< long, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( long& value )
		{
 			return ( value == 0 ) ? true : false;
		}
	};

	//--------------------------------------------------------------------------------
	template< typename TNumeric, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
 	class CTSuccessCheck : public CAutoErrorCheck< TNumeric, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( TNumeric& value )
		{
 			return ( value == 0 ) ? true : false;
		}
	};

	//--------------------------------------------------------------------------------
	template< typename TNumeric, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
	class CCheckNonZero : public CAutoErrorCheck< TNumeric, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( TNumeric& value )
		{
 			return ( value == 0 ) ? false : true;
		}
	};

	//--------------------------------------------------------------------------------
	template< int iFailure, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
	class CCheckFailureInt : public CAutoErrorCheck< int, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual bool Test( int& value )
		{
 			return ( value == iFailure ) ? false : true;
		}
	};

	//--------------------------------------------------------------------------------
	template< typename TFailure, TFailure iFailure, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
	class CTCheckFailureValue : public CAutoErrorCheck< TFailure, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual void DefaultInit( TFailure& value )
		{
			value = iFailure;
		}

		//--------------------------------------------------------------------------------
		virtual bool Test( TFailure& value )
		{
 			return ( value == iFailure ) ? false : true;
		}
	};

	//--------------------------------------------------------------------------------
	template< typename TReturn, TReturn Min, TReturn Max, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
	class CTRangeCheck : public CAutoErrorCheck< TReturn, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual void DefaultInit( TReturn& value )
		{
			value = Min - 1;
		}

		//--------------------------------------------------------------------------------
		virtual bool Test( TReturn& value )
		{
 			return ( value >= Min && value <= Max ) ? true : false;
		}
	};

	//--------------------------------------------------------------------------------
	template< typename TReturn, TReturn Min, nsCodeQOR::CError::Level eLevel = nsCodeQOR::CError::ERR_LVL_CONTINUE, int iErr = nsWinQAPI::GENERAL_API_ERROR >
 	class CTCheckNotLess : public CAutoErrorCheck< TReturn, eLevel, iErr >
	{
	public:

		//--------------------------------------------------------------------------------
		virtual void DefaultInit( TReturn& value )
		{
			value = Min - 1;
		}

		//--------------------------------------------------------------------------------
		virtual bool Test( TReturn& value )
		{
 			return ( value < Min ) ? false : true;
		}
	};

}//nsWinQAPI

#endif//WINQAPI_CS_RETURNCHECK_H_1
