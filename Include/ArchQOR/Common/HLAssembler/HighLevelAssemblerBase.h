//HighLevelAssemblerBase.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012
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

//Base class for High Level Assembler

#ifndef ARCHQOR_HLASMBASE_H_2
#define ARCHQOR_HLASMBASE_H_2

#include "CompilerQOR.h"
#include "ArchQOR/Common/Assembler/Zone.h"
#include "ArchQOR/Common/Assembler/CodeGenerator.h"
#include "ArchQOR/Common/Assembler/Logger.h"
#include "ArchQOR/Common/HLAssembler/Emittables/Emittable.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"

//--------------------------------------------------------------------------------
namespace nsArch
{

	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __ARCHQOR ) CHighLevelAssemblerBase
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CHighLevelAssemblerBase);

		CHighLevelAssemblerBase( CCodeGeneratorBase* codeGenerator );
		virtual ~CHighLevelAssemblerBase();

		//------------------------------------------------------------------------------
		// Get code generator.
		inline CCodeGeneratorBase* getCodeGenerator() const
		{
			return m_pCodeGenerator;
		}

		//------------------------------------------------------------------------------
		// Get zone memory manager.
		inline CZone& getZone()
		{
			return m_Zone;
		}

		//------------------------------------------------------------------------------
		// Get logger.
		inline CLogger* getLogger() const __QCMP_THROW
		{
			return m_pLogger;
		}

		//------------------------------------------------------------------------------
		// Get first emittable.
		inline nsArch::CEmittable* getFirstEmittable() const __QCMP_THROW
		{
			return m_pFirst;
		}

		//------------------------------------------------------------------------------
		// Get last emittable.
		inline nsArch::CEmittable* getLastEmittable() const __QCMP_THROW
		{
			return m_pLast;
		}

		//------------------------------------------------------------------------------
		// Get current emittable. Note If this method return 0, it means that nothing emitted yet.
		inline nsArch::CEmittable* getCurrentEmittable() const __QCMP_THROW
		{
			return m_pCurrent;
		}

		//------------------------------------------------------------------------------
		inline CEmittable* setCurrentEmittable( CEmittable* current ) __QCMP_THROW
		{
			CEmittable* old = m_pCurrent;
			m_pCurrent = current;
			return old;
		}

		void align( Cmp_unsigned__int32 m ) __QCMP_THROW;									// Align target buffer to m bytes. Typical usage of this is to align labels at start of the inner loops. Inserts nop() instructions or CPU optimized NOPs.
		void addEmittable( CEmittable* emittable ) __QCMP_THROW;							// Add emittable after current and set current to emittable.
		void addEmittableAfter( CEmittable* emittable, CEmittable* ref ) __QCMP_THROW;		// Add emittable after ref.
		void removeEmittable( CEmittable* emittable ) __QCMP_THROW;							// Remove emittable (and if needed set current to previous).
		virtual CCPUBase* getAssembler( void ) __QCMP_THROW = 0;

	protected:

		CCodeGeneratorBase* m_pCodeGenerator;	// Code generator.
		CZone m_Zone;							// Zone memory management.
		CLogger* m_pLogger;						// Logger.

		nsArch::CEmittable* m_pFirst;			// First emittable.
		nsArch::CEmittable* m_pLast;			// Last emittable.
		nsArch::CEmittable* m_pCurrent;			// Current emittable.

	private:

		__QCS_DECLARE_NONCOPYABLE( CHighLevelAssemblerBase );
	};

	//------------------------------------------------------------------------------
	template< typename T >
	T* HLA_newObject( CHighLevelAssemblerBase* self ) __QCMP_THROW
	{
		void* addr = self->getZone().zalloc( sizeof(T) );
		return new( addr ) T( self );
	}

	//------------------------------------------------------------------------------
	template< typename T, typename P1 >
	T* HLA_newObject( CHighLevelAssemblerBase* self, P1 p1 ) __QCMP_THROW
	{
		void* addr = self->getZone().zalloc( sizeof(T) );
		return new( addr ) T( self, p1 );
	}

	//------------------------------------------------------------------------------
	template< typename T, typename P1, typename P2 >
	T* HLA_newObject( CHighLevelAssemblerBase* self, P1 p1, P2 p2 ) __QCMP_THROW
	{
		void* addr = self->getZone().zalloc( sizeof(T) );
		return new( addr ) T( self, p1, p2 );
	}

	//------------------------------------------------------------------------------
	template< typename T, typename P1, typename P2, typename P3 >
	T* HLA_newObject( CHighLevelAssemblerBase* self, P1 p1, P2 p2, P3 p3 ) __QCMP_THROW
	{
		void* addr = self->getZone().zalloc( sizeof(T) );
		return new( addr ) T( reinterpret_cast< CHighLevelAssemblerBase* >( self ), p1, p2, p3 );
	}

	//------------------------------------------------------------------------------
	template< typename T, typename P1, typename P2, typename P3, typename P4 >
	T* HLA_newObject( CHighLevelAssemblerBase* self, P1 p1, P2 p2, P3 p3, P4 p4 ) __QCMP_THROW
	{
		void* addr = self->getZone().zalloc( sizeof(T) );
		return new( addr ) T( reinterpret_cast< CHighLevelAssemblerBase* >( self ), p1, p2, p3, p4 );
	}

	//------------------------------------------------------------------------------
	template< typename T, typename P1, typename P2, typename P3, typename P4, typename P5 >
	T* HLA_newObject( CHighLevelAssemblerBase* self, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) __QCMP_THROW
	{
		void* addr = self->getZone().zalloc( sizeof(T) );
		return new( addr ) T( reinterpret_cast< CHighLevelAssemblerBase* >( self ), p1, p2, p3, p4, p5 );
	}

}//nsArch

#endif//ARCHQOR_HLASMBASE_H_2
