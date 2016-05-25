//RTTI.cpp

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

#include "SystemQOR.h"
#include "../Source/SystemQOR/MSWindows/WinCmpSupQORVC/include/RTTI/RTTI.h"
#include <typeinfo>

#if ( __QCMP_COMPILER == __QCMP_INTEL )

int type_info::special_dummy_to_force_gen_of_vtable( int iDummy )
{
    this->~type_info();
}

type_info::~type_info()
{

}
#endif

//#if !(defined(__LIBCPP_TYPEINFO) || defined(LIBCXXRT))

#ifndef __MINGW32__
/*
std::bad_cast::bad_cast() __QCMP_THROW
{
}

std::bad_cast::~bad_cast() __QCMP_THROW
{
}

const char* std::bad_cast::what() const __QCMP_THROW
{
  return "std::bad_cast";
}


std::bad_typeid::bad_typeid() __QCMP_THROW
{
}

std::bad_typeid::~bad_typeid() __QCMP_THROW
{
}

const char*
std::bad_typeid::what() const __QCMP_THROW
{
  return "std::bad_typeid";
}
*/
#endif

#if __APPLE__
  // On Darwin, the cxa_bad_* functions cannot be in the lower level library
  // because bad_cast and bad_typeid are defined in his higher level library
  void __cxxabiv1::__cxa_bad_typeid() { throw std::bad_typeid(); }
  void __cxxabiv1::__cxa_bad_cast() { throw std::bad_cast(); }
#endif

//#endif  // _LIBCPPABI_VERSION

#if	( __QCMP_EXTENSION( RunTimeTypeInformation ) )

	//--------------------------------------------------------------------------------
	void* AdjustPointer( void* _pThis, const PMD& pmd )
	{
		unsigned char* pThis = ( unsigned char* )_pThis;
		unsigned char* pRet = pThis + pmd.mdisp;
		if (pmd.pdisp >= 0)
		{
			pRet += *(unsigned int*)(*(unsigned char**)(pThis+pmd.pdisp) + pmd.vdisp);
			pRet += pmd.pdisp;
		}
		return pRet;
	}

    //--------------------------------------------------------------------------------
    int rtti_strcmp( const char* s1, const char* s2 )
    {
		while( *s1 != '\0' && *s1 == *s2 )
        {
            s1++;
            s2++;
        }

        return ( ( *( const_cast< unsigned char* >( reinterpret_cast< const unsigned char* >( s1 ) ) ) ) -
                ( *( const_cast< unsigned char* >( reinterpret_cast< const unsigned char* >( s2 ) ) ) ) );
	}

	//--------------------------------------------------------------------------------
	//Type comparison by name
	bool operator == ( const TypeDescriptor& lhs, const TypeDescriptor& rhs )
	{
		return &lhs == &rhs || rtti_strcmp( lhs.name, rhs.name ) == 0;
	}

#endif//( __QCMP_DEFINED_RTTI_ENABLED == 1 )

