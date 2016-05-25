//Cx86HLAssembler.cpp

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012, 2015
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

#include "ArchQOR.h"

#if		( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )

#include "ArchQOR/Common/HLAssembler/Emittables/EComment.h"
#include "ArchQOR/Common/HLAssembler/Emittables/EData.h"
#include "ArchQOR/Common/HLAssembler/Emittables/EAlign.h"
#include "ArchQOR/x86/HLAssembler/x86HLAssembler.h"
#include "ArchQOR/x86/HLAssembler/Emittables/EFunction.h"
#include "ArchQOR/x86/HLAssembler/Emittables/EVariableHint.h"
#include "ArchQOR/x86/HLAssembler/Emittables/ECall.h"
#include "ArchQOR/x86/HLAssembler/Emittables/ERet.h"
#include "ArchQOR/x86/HLAssembler/HLAssembler.h"
#include "ArchQOR/x86/HLAssembler/x86HLAContext.h"

#include <new>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	namespace nsx86
	{
		//------------------------------------------------------------------------------
		static void delAll( nsArch::CEmittable* first ) __QCMP_THROW
		{
			nsArch::CEmittable* cur = first;

			while( cur )
			{
				nsArch::CEmittable* next = cur->getNext();
				cur->~CEmittable();
				cur = next;
			}
		}

		//------------------------------------------------------------------------------
		static CMMVar MMVarFromData( VarData* vdata )
		{
			CMMVar var;
			var.setId( vdata->id );
			var.setSize( static_cast< Cmp_unsigned__int8 >( vdata->size ) );
			var.setRegisterCode( variableInfo[ vdata->type ].code );
			var.setVariableType( vdata->type );
			return var;
		}

		//------------------------------------------------------------------------------
		static CXMMVar XMMVarFromData( VarData* vdata )
		{
			CXMMVar var;
			var.setId( vdata->id );
			var.setSize( static_cast< Cmp_unsigned__int8 >( vdata->size ) );
			var.setRegisterCode( variableInfo[ vdata->type ].code );
			var.setVariableType( vdata->type );
			return var;
		}

		//------------------------------------------------------------------------------
		Cx86HLAssembler::Cx86HLAssembler( nsArch::CCodeGeneratorBase* codeGenerator ) __QCMP_THROW : nsArch::CHighLevelAssemblerBase( codeGenerator ),
		m_uiError( 0 ),
		m_uiProperties( ( 1 << PROPERTY_OPTIMIZE_ALIGN ) ),
		m_uiEmitOptions( 0 ),
		m_uiFinished( false ),
		m_pFunction( 0 ),
		m_iVarNameId( 0 ),
		m_pContext( 0 ),
		m_CPU( codeGenerator )
		{
		}

		//------------------------------------------------------------------------------
		Cx86HLAssembler::~Cx86HLAssembler() __QCMP_THROW
		{
			free();
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::setLogger( CLogger* logger ) __QCMP_THROW
		{
			m_pLogger = logger;
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::setError( Cmp_unsigned__int32 error ) __QCMP_THROW
		{
			m_uiError = error;
			if( m_uiError == ERROR_NONE )
			{
				return;
			}

			if( m_pLogger )
			{
				m_pLogger->logFormat( "*** COMPILER ERROR: %s (%u).\n", CCPUBase::getErrorCodeAsString( error ), (unsigned int)error );
			}
		}

		//------------------------------------------------------------------------------
		Cmp_unsigned__int32 Cx86HLAssembler::getProperty( Cmp_unsigned__int32 propertyId )
		{
			return ( m_uiProperties & ( 1 << propertyId ) ) != 0;
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::setProperty( Cmp_unsigned__int32 propertyId, Cmp_unsigned__int32 value )
		{
			if( value )
			{
				m_uiProperties |= ( 1 << propertyId );
			}
			else
			{
				m_uiProperties &= ~( 1 << propertyId );
			}
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::clear() __QCMP_THROW
		{
			m_uiFinished = false;

			delAll( m_pFirst );
			m_pFirst = 0;
			m_pLast = 0;
			m_pCurrent = 0;

			m_Zone.freeAll();
			m_TargetData.clear();
			m_VarData.clear();

			m_pContext = 0;

			if( m_uiError )
			{
				setError( ERROR_NONE );
			}
			m_CPU.clear();
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::free() __QCMP_THROW
		{
			clear();

			m_TargetData.free();
			m_VarData.free();
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::comment( const char* fmt, ... ) __QCMP_THROW
		{
			char buf[ 128 ];
			char* p = buf;

			if( fmt )
			{
				*p++ = ';';
				*p++ = ' ';

				va_list ap;
				va_start( ap, fmt );
				p += vsnprintf( p, 100, fmt, ap );
				va_end(ap);
			}

			*p++ = '\n';
			*p   = '\0';

			addEmittable( dynamic_cast< nsArch::CEmittable* >( HLA_newObject< nsArch::CEComment >( this, buf ) ) );
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitInstruction( Cmp_unsigned__int32 code ) __QCMP_THROW
		{
			CEInstruction* e = newInstruction( code, 0, 0 );
			if( !e )
			{
				return;
			}

			addEmittable( e );
			if( m_pContext ) 
			{ 
				e->setOffset( m_pContext->GetCurrentOffset() ); 
				e->prepare( *m_pContext ); 
			}
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitInstruction( Cmp_unsigned__int32 code, const COperand* o0 ) __QCMP_THROW
		{
			COperand** operands = new( m_Zone.zalloc( sizeof( COperand* ) ) ) COperand*[1];
			if( !operands )
			{
				return;
			}

			operands[ 0 ] = o0->Clone( m_Zone );

			CEInstruction* e = newInstruction( code, operands, 1 );
			if( !e )
			{
				return;
			}

			addEmittable( e );
			if( m_pContext ) 
			{ 
				e->setOffset( m_pContext->GetCurrentOffset() );
				e->prepare( *m_pContext ); 
			}
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1 ) __QCMP_THROW
		{
			COperand** operands = new( m_Zone.zalloc( 2 * sizeof( COperand* ) ) ) COperand*[2];
			if( !operands )
			{
				return;
			}

			operands[ 0 ] = o0->Clone( m_Zone );
			operands[ 1 ] = o1->Clone( m_Zone );

			CEInstruction* e = newInstruction( code, operands, 2 );
			if( !e )
			{
				return;
			}

			addEmittable( e );
			if( m_pContext ) 
			{ 
				e->setOffset( m_pContext->GetCurrentOffset() );
				e->prepare( *m_pContext ); 
			}
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1, const COperand* o2 ) __QCMP_THROW
		{
			COperand** operands = new( m_Zone.zalloc( 3 * sizeof( COperand* ) ) ) COperand*[3];
			if( !operands )
			{
				return;
			}

			operands[ 0 ] = o0->Clone( m_Zone );
			operands[ 1 ] = o1->Clone( m_Zone );
			operands[ 2 ] = o2->Clone( m_Zone );

			CEInstruction* e = newInstruction( code, operands, 3 );
			if( !e )
			{
				return;
			}

			addEmittable( e );
			if( m_pContext ) 
			{ 
				e->setOffset( m_pContext->GetCurrentOffset() ); 
				e->prepare( *m_pContext ); 
			}
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1, const COperand* o2, const COperand* o3 ) __QCMP_THROW
		{
			COperand** operands = new( m_Zone.zalloc( 4 * sizeof( COperand* ) ) ) COperand*[4];
			if( !operands ) 
			{
				return;
			}

			operands[ 0 ] = o0->Clone( m_Zone );
			operands[ 1 ] = o1->Clone( m_Zone );
			operands[ 2 ] = o2->Clone( m_Zone );
			operands[ 3 ] = o3->Clone( m_Zone );

			CEInstruction* e = newInstruction( code, operands, 4 );
			if( !e )
			{
				return;
			}

			addEmittable( e );
			if( m_pContext ) 
			{ 
				e->setOffset( m_pContext->GetCurrentOffset() );
				e->prepare( *m_pContext ); 
			}
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1, const COperand* o2, const COperand* o3, const COperand* o4 ) __QCMP_THROW
		{
			COperand** operands = new( m_Zone.zalloc( 5 * sizeof( COperand* ) ) ) COperand*[5];
			if( !operands ) 
			{
				return;
			}

			operands[ 0 ] = o0->Clone( m_Zone );
			operands[ 1 ] = o1->Clone( m_Zone );
			operands[ 2 ] = o2->Clone( m_Zone );
			operands[ 3 ] = o3->Clone( m_Zone );
			operands[ 4 ] = o4->Clone( m_Zone );

			CEInstruction* e = newInstruction(code, operands, 5);
			if( !e )
			{
				return;
			}

			addEmittable( e );
			if( m_pContext ) 
			{ 
				e->setOffset( m_pContext->GetCurrentOffset() ); 
				e->prepare( *m_pContext ); 
			}
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitJcc( Cmp_unsigned__int32 code, const CLabel* label, Cmp_unsigned__int32 hint ) __QCMP_THROW
		{
			if( !hint )
			{
				_emitInstruction( code, label );
			}
			else
			{
				CImm imm( hint );
				_emitInstruction( code, label, &imm );
			}
		}

		//------------------------------------------------------------------------------
		CECall* Cx86HLAssembler::_emitCall( const COperand* o0 ) __QCMP_THROW
		{
			CEFunction* fn = getFunction();
			if( !fn ) 
			{ 
				setError( ERROR_NO_FUNCTION ); 
				return 0; 
			}

			CECall* eCall = HLA_newObject< CECall >( this, fn, o0 );
			if( !eCall ) 
			{ 
				setError( ERROR_NO_HEAP_MEMORY ); 
				return 0; 
			}

			addEmittable( dynamic_cast< nsArch::CEmittable* >( eCall ) );
			return eCall;
		}

		//------------------------------------------------------------------------------
		void Cx86HLAssembler::_emitReturn( const COperand* first, const COperand* second ) __QCMP_THROW
		{
			CEFunction* fn = getFunction();
			if( !fn ) 
			{ 
				setError( ERROR_NO_FUNCTION ); 
				return; 
			}

			CERet* eRet = HLA_newObject< CERet >( this, fn, first, second );
			if( !eRet ) 
			{ 
				setError( ERROR_NO_HEAP_MEMORY ); 
				return; 
			}

			addEmittable( eRet );
		}

		//--------------------------------------------------------------------------
		CEInstruction* Cx86HLAssembler::newInstruction( Cmp_unsigned__int32 code, COperand** paOperandsData, Cmp_unsigned__int32 operandsCount ) __QCMP_THROW
		{
			if( code >= _INST_J_BEGIN && code <= _INST_J_END )
			{
				void* addr = m_Zone.zalloc( sizeof( CEJmp ) );

				return new( addr ) CEJmp( dynamic_cast< Cx86HLAIntrinsics* >( this ), code, paOperandsData, operandsCount );
			}
			else
			{
				void* addr = m_Zone.zalloc( sizeof( CEInstruction ) /*+ operandsCount * sizeof( COperand )*/ );

				return new( addr ) CEInstruction( dynamic_cast< Cx86HLAIntrinsics* >( this ), code, paOperandsData, operandsCount );
			}
		}

		//--------------------------------------------------------------------------
		CEFunction* Cx86HLAssembler::newFunction_( Cmp_unsigned__int32 callingConvention, const Cmp_unsigned__int32* arguments, Cmp_unsigned__int32 argumentsCount, Cmp_unsigned__int32 returnValue ) __QCMP_THROW
		{
			assert( m_pFunction == 0 );
			CEFunction* f = m_pFunction = HLA_newObject< CEFunction >( this );

			f->setPrototype( callingConvention, arguments, argumentsCount, returnValue );
			addEmittable( f );

			bind( f->getEntryLabel() );
			addEmittable( f->getProlog() );

			m_iVarNameId = 0;

			f->_createVariables();
			return f;
		}

		//--------------------------------------------------------------------------
		CEFunction* Cx86HLAssembler::endFunction() __QCMP_THROW
		{
			assert( m_pFunction != 0 );
			CEFunction* f = m_pFunction;

			bind( f->getExitLabel() );
			addEmittable( f->getEpilog() );
			addEmittable( f->getEnd() );

			f->Finish();
			m_pFunction = 0;

			return f;
		}

		//--------------------------------------------------------------------------
		void Cx86HLAssembler::embed( const void* data, Cmp_uint_ptr size ) __QCMP_THROW
		{
			// Align length to 16 bytes.
			Cmp_uint_ptr alignedSize = ( size + 15 ) & ~15;

			nsArch::CEData* e = new( m_Zone.zalloc( sizeof(nsArch::CEData) - sizeof(void*) + alignedSize ) ) nsArch::CEData( this, data, size );
			addEmittable( e );
		}

/*		//--------------------------------------------------------------------------
		void Cx86HLAssembler::align( Cmp_unsigned__int32 m ) __QCMP_THROW
		{
			addEmittable( HLA_newObject< nsArch::CEAlign >( this, m ) );
		}
		*/
		//--------------------------------------------------------------------------
		CLabel Cx86HLAssembler::newLabel() __QCMP_THROW
		{
			CLabel label;
			label.setId( (Cmp_unsigned__int32)m_TargetData.getLength() | OPERAND_ID_TYPE_LABEL );

			CETarget* target = HLA_newObject< CETarget >( this, label );
			m_TargetData.append( target );

			return label;
		}

		//--------------------------------------------------------------------------
		void Cx86HLAssembler::bind( const CLabel& label ) __QCMP_THROW
		{
			Cmp_unsigned__int32 id = label.getId() & OPERAND_ID_VALUE_MASK;
			assert( id != INVALID_VALUE );
			assert( id < m_TargetData.getLength() );

			addEmittable( m_TargetData[ id ] );
		}

		//--------------------------------------------------------------------------
		VarData* Cx86HLAssembler::_newVarData(const char* name, Cmp_unsigned__int32 type, Cmp_unsigned__int32 size) __QCMP_THROW
		{
			VarData* vdata = reinterpret_cast< VarData* >( m_Zone.zalloc( sizeof( VarData ) ) );
			if( vdata == 0 )
			{
				return 0;
			}

			char nameBuffer[ 32 ];
			if( name == 0 )
			{
				sprintf( nameBuffer, "var_%d", m_iVarNameId );
				name = nameBuffer;
				m_iVarNameId++;
			}

			vdata->scope = getFunction();
			vdata->firstEmittable = 0;
			vdata->firstCallable = 0;
			vdata->lastEmittable = 0;
			vdata->name = m_Zone.zstrdup( name );
			vdata->id = (Cmp_unsigned__int32)m_VarData.getLength() | OPERAND_ID_TYPE_VAR;
			vdata->type = type;
			vdata->size = size;
			vdata->homeRegisterIndex = static_cast< Cmp_unsigned__int32 >( INVALID_VALUE );
			vdata->prefRegisterMask = 0;
			vdata->homeMemoryData = 0;
			vdata->registerIndex = static_cast< Cmp_unsigned__int32 >( INVALID_VALUE );
			vdata->workOffset = static_cast< Cmp_unsigned__int32 >( INVALID_VALUE );
			vdata->nextActive = 0;
			vdata->prevActive = 0;
			vdata->priority = 10;
			vdata->calculated = false;
			vdata->isRegArgument = false;
			vdata->isMemArgument = false;
			vdata->state = VARIABLE_STATE_UNUSED;
			vdata->changed = false;
			vdata->saveOnUnuse = false;
			vdata->registerReadCount = 0;
			vdata->registerWriteCount = 0;
			vdata->registerRWCount = 0;
			vdata->registerGPBLoCount = 0;
			vdata->registerGPBHiCount = 0;
			vdata->memoryReadCount = 0;
			vdata->memoryWriteCount = 0;
			vdata->memoryRWCount = 0;
			vdata->tempPtr = 0;

			m_VarData.append( vdata );
			return vdata;
		}

		//--------------------------------------------------------------------------
		CGPVar Cx86HLAssembler::newGP( Cmp_unsigned__int32 variableType, const char* name ) __QCMP_THROW
		{
			assert( ( variableType < _VARIABLE_TYPE_COUNT ) && ( variableInfo[ variableType ].clazz & VariableInfo::CLASS_GP ) != 0 );

#	if ( QOR_ARCH_WORDSIZE == 32 )
			if( variableInfo[ variableType ].size > 4 )
			{
				variableType = VARIABLE_TYPE_GPD;
				if( m_pLogger )
				{
					m_pLogger->logString( "*** COMPILER WARNING: Translated QWORD variable to DWORD, FIX YOUR CODE! ***\n" );
				}
			}
#	endif // ( QOR_ARCH_WORDSIZE == 32 )

			VarData* vdata = _newVarData( name, variableType, variableInfo[ variableType ].size );
			return GPVarFromData( vdata );
		}

		//--------------------------------------------------------------------------
		CGPVar Cx86HLAssembler::argGP( Cmp_unsigned__int32 index ) __QCMP_THROW
		{
			CGPVar var;
			CEFunction* f = getFunction();

			if( f )
			{
				const CFunctionPrototype& prototype = f->getPrototype();
				if( index < prototype.getArgumentsCount() )
				{
					VarData* vdata = getFunction()->getVariableArgument( index );

					var.setId( vdata->id );
					var.setSize( static_cast< Cmp_unsigned__int8 >( vdata->size ) );
					var.setRegisterCode( variableInfo[ vdata->type ].code );
					var.setVariableType( vdata->type );
				}
			}

			return var;
		}

		//--------------------------------------------------------------------------
		CMMVar Cx86HLAssembler::newMM( Cmp_unsigned__int32 variableType, const char* name ) __QCMP_THROW
		{
			assert( ( variableType < _VARIABLE_TYPE_COUNT ) && ( variableInfo[ variableType ].clazz & VariableInfo::CLASS_MM ) != 0 );

			VarData* vdata = _newVarData( name, variableType, 8 );
			return MMVarFromData( vdata );
		}

		//--------------------------------------------------------------------------
		CMMVar Cx86HLAssembler::argMM( Cmp_unsigned__int32 index ) __QCMP_THROW
		{
			CMMVar var;
			CEFunction* f = getFunction();

			if( f )
			{
				const CFunctionPrototype& prototype = f->getPrototype();
				if( index < prototype.getArgumentsCount() )
				{
					VarData* vdata = getFunction()->getVariableArgument( index );

					var.setId( vdata->id );
					var.setSize( static_cast< Cmp_unsigned__int8 >( vdata->size ) );
					var.setRegisterCode( variableInfo[ vdata->type ].code );
					var.setVariableType( vdata->type );
				}
			}

			return var;
		}

		//--------------------------------------------------------------------------
		CXMMVar Cx86HLAssembler::newXMM( Cmp_unsigned__int32 variableType, const char* name ) __QCMP_THROW
		{
			assert( ( variableType < _VARIABLE_TYPE_COUNT ) && ( variableInfo[ variableType ].clazz & VariableInfo::CLASS_XMM ) != 0 );

			VarData* vdata = _newVarData( name, variableType, 16 );
			return XMMVarFromData( vdata );
		}

		//--------------------------------------------------------------------------
		CXMMVar Cx86HLAssembler::argXMM( Cmp_unsigned__int32 index ) __QCMP_THROW
		{
			CXMMVar var;
			CEFunction* f = getFunction();

			if( f )
			{
				const CFunctionPrototype& prototype = f->getPrototype();
				if( index < prototype.getArgumentsCount() )
				{
					VarData* vdata = getFunction()->getVariableArgument( index );

					var.setId( vdata->id );
					var.setSize( static_cast< Cmp_unsigned__int8 >( vdata->size ) );
					var.setRegisterCode( variableInfo[ vdata->type ].code );
					var.setVariableType( vdata->type );
				}
			}

			return var;
		}

		//--------------------------------------------------------------------------
		void Cx86HLAssembler::_vhint( CBaseVar& var, Cmp_unsigned__int32 hintId, Cmp_unsigned__int32 hintValue ) __QCMP_THROW
		{
			if( var.getId() == INVALID_VALUE )
			{
				return;
			}

			VarData* vdata = _getVarData( var.getId() );
			assert( vdata != 0 );

			CEVariableHint* e = HLA_newObject< CEVariableHint >( this, vdata, hintId, hintValue );
			addEmittable( e );
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::alloc( CBaseVar& var ) __QCMP_THROW
		{
			_vhint( var, VARIABLE_HINT_ALLOC, static_cast< Cmp_unsigned__int32 >( INVALID_VALUE ) );
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::alloc( CBaseVar& var, Cmp_unsigned__int32 regIndex ) __QCMP_THROW
		{
			if( regIndex > 31 )
			{
				return;
			}
			_vhint( var, VARIABLE_HINT_ALLOC, 1 << regIndex );
		}

		//--------------------------------------------------------------------------
		void Cx86HLAssembler::alloc( CBaseVar& var, const CBaseReg& reg ) __QCMP_THROW
		{
			_vhint( var, VARIABLE_HINT_ALLOC, 1 << reg.getRegIndex() );
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::save( CBaseVar& var ) __QCMP_THROW
		{
			_vhint( var, VARIABLE_HINT_SAVE, static_cast< Cmp_unsigned__int32 >( INVALID_VALUE ) );
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::spill( CBaseVar& var ) __QCMP_THROW
		{
			_vhint( var, VARIABLE_HINT_SPILL, static_cast< Cmp_unsigned__int32 >( INVALID_VALUE ) );
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::unuse( CBaseVar& var ) __QCMP_THROW
		{
			_vhint( var, VARIABLE_HINT_UNUSE, static_cast< Cmp_unsigned__int32 >( INVALID_VALUE ) );
		}

		//--------------------------------------------------------------------------------
		Cmp_unsigned__int32 Cx86HLAssembler::getPriority( CBaseVar& var ) const __QCMP_THROW
		{
			if( var.getId() == INVALID_VALUE )
			{
				return static_cast< Cmp_unsigned__int32 >( INVALID_VALUE );
			}

			VarData* vdata = _getVarData( var.getId() );
			assert( vdata != 0 );

			return vdata->priority;
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::setPriority( CBaseVar& var, Cmp_unsigned__int32 priority ) __QCMP_THROW
		{
			if( var.getId() == INVALID_VALUE )
			{
				return;
			}

			VarData* vdata = _getVarData( var.getId() );
			assert( vdata != 0 );

			if( priority > 100 )
			{
				priority = 100;
			}
			vdata->priority = (Cmp_unsigned__int8)priority;
		}

		//--------------------------------------------------------------------------------
		bool Cx86HLAssembler::getSaveOnUnuse( CBaseVar& var ) const __QCMP_THROW
		{
			if( var.getId() == INVALID_VALUE )
			{
				return false;
			}

			VarData* vdata = _getVarData( var.getId() );
			assert( vdata != 0 );

			return vdata->saveOnUnuse ? true : false;
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::setSaveOnUnuse( CBaseVar& var, bool value ) __QCMP_THROW
		{
			if( var.getId() == INVALID_VALUE )
			{
				return;
			}

			VarData* vdata = _getVarData( var.getId() );
			assert( vdata != 0 );

			vdata->saveOnUnuse = value;
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::rename( CBaseVar& var, const char* name ) __QCMP_THROW
		{
			if( var.getId() == INVALID_VALUE )
			{
				return;
			}

			VarData* vdata = _getVarData( var.getId() );
			assert( vdata != 0 );

			vdata->name = m_Zone.zstrdup( name );
		}

		//--------------------------------------------------------------------------------
		StateData* Cx86HLAssembler::_newStateData( Cmp_unsigned__int32 memVarsCount ) __QCMP_THROW
		{
			StateData* state = reinterpret_cast< StateData* >( m_Zone.zalloc( sizeof( StateData ) + memVarsCount * sizeof( void* ) ) );
			return state;
		}

		//--------------------------------------------------------------------------------
		void* Cx86HLAssembler::make() __QCMP_THROW
		{
			m_CPU.SetProperties( m_uiProperties );
			m_CPU.setLogger( m_pLogger );

			serialize();

			if( this->getError() )
			{
				return 0;
			}

			if( m_CPU.getError() )
			{
				setError( m_CPU.getError() );
				return 0;
			}

			void* result = m_CPU.make();
			if( m_pLogger )
			{
				m_pLogger->logFormat( "*** HLA SUCCESS - Wrote %u bytes, code: %u, trampolines: %u.\n\n",
				(unsigned int)m_CPU.getCodeSize(),
				(unsigned int)m_CPU.getOffset(),
				(unsigned int)m_CPU.getTrampolineSize());
			}
			return result;
		}

		//--------------------------------------------------------------------------------
		void Cx86HLAssembler::serialize() __QCMP_THROW
		{
			// Context.
			Cx86HLAContext cc( reinterpret_cast< nsArch::CHighLevelAssemblerBase* >( this ) );

			cc.setAssembler( &m_CPU );

			nsArch::CEmittable* start = m_pFirst;
			nsArch::CEmittable* stop = 0;

			// Register all labels.
			m_CPU.registerLabels( m_TargetData.getLength() );

			// Make code.
			for(;;)
			{
				m_pContext = 0;

				//Find a function.
				for(;;)
				{
					if( start == 0 )
					{
						return;
					}
					if( start->getType() == EMITTABLE_FUNCTION )
					{
						break;
					}
					else
					{
						start->emit( *( reinterpret_cast< nsArch::CHighLevelAssemblerBase* >( this ) ) );
					}

					start = start->getNext();
				}

				// Setup code generation context.
				nsArch::CEmittable* cur;

				cc.setFunction( reinterpret_cast< CEFunction* >( start ) );
				cc.setStart( start );
				cc.setStop( stop = cc.getFunction()->getEnd() );
				cc.setExtraBlock( stop->getPrev() );

				// Detect whether the function generation was finished.
				if( !cc.getFunction()->isFinished() || cc.getFunction()->getEnd()->getPrev() == 0 )
				{
					setError( ERROR_INCOMPLETE_FUNCTION );
					return;
				}

				// Step 1:
				// - Assign/increment offset to each emittable.
				// - Extract variables from instructions.
				// - Prepare variables for register allocator:
				//   - Update read(r) / write(w) / overwrite(x) statistics.
				//   - Update register / memory usage statistics.
				//   - Find scope (first / last emittable) of variables.
				for( cur = start; ; cur = cur->getNext() )
				{
					cur->prepare( cc );
					if( cur == stop )
					{
						break;
					}
				}

				// We set HighLevelAssembler context also to so new emitted instructions can call prepare() to itself.
				m_pContext = &cc;

				// Step 2:
				// - Translate special instructions (imul, cmpxchg8b, ...).
				// - Alloc registers.
				// - Translate forward jumps.
				// - Alloc memory operands (variables related).
				// - Emit function prolog.
				// - Emit function epilog.
				// - Patch memory operands (variables related).
				// - Dump function prototype and variable statistics (if enabled).

				// Translate special instructions and run alloc registers.
				cur = start;

				do 
				{
					do 
					{
						// Assign current offset for each emittable back to Cx86HLAContext.
						cc.SetCurrentOffset( cur->getOffset() );
						// Assign previous emittable to compiler so each variable spill/alloc will be emitted before.
						m_pCurrent = cur->getPrev();

						cur = cur->translate( cc );
					} while( cur );

					cc.setUnreachable( 1 );

					Cmp_uint_ptr len = cc.getVecBackCode().getLength();
					while( cc.getBackPos() < len )
					{
						cur = ( cc.getVecBackCode()[ cc.IncrementBackPos() ] )->getNext();
						if( !cur->isTranslated() )
						{
							break;
						}
						cur = 0;
					}
				} while( cur );

				// Translate forward jumps.
				{
					ForwardJumpData* j = cc.getForwardJumps();
					while( j )
					{
						cc._assignState( j->state );
						m_pCurrent = j->inst->getPrev();
						j->inst->DoJump( cc );
						j = j->next;
					}
				}
				
				cc._allocMemoryOperands();						// Alloc memory operands (variables related).
				cc.getFunction()->_preparePrologEpilog( cc );		// Emit function prolog / epilog.

				m_pCurrent = cc.getFunction()->getProlog();
				cc.getFunction()->_emitProlog( cc );

				m_pCurrent = cc.getFunction()->getEpilog();
				cc.getFunction()->_emitEpilog( cc );

				m_pCurrent = m_pLast;							// Patch memory operands (variables related).
				cc._patchMemoryOperands( start, stop );

				if( m_pLogger )									// Dump function prototype and variable statistics (if enabled).
				{
					cc.getFunction()->_dumpFunction( cc );
				}

				//Hack: need to register labels that was created by the Step 2.
				if( m_CPU.m_LabelData.getLength() < m_TargetData.getLength() )
				{
					m_CPU.registerLabels( m_TargetData.getLength() - m_CPU.m_LabelData.getLength() );
				}

				nsArch::CEmittable* extraBlock = cc.getExtraBlock();

				// Step 3:
				// - Emit instructions to Assembler stream.
				for( cur = start; ; cur = cur->getNext() )
				{
					cur->emit( *this );
					if( cur == extraBlock )
					{
						break;
					}
				}

				// Step 4:
				// - Emit everything else (post action).
				for( cur = start; ; cur = cur->getNext() )
				{
					cur->post(*this);
					if( cur == extraBlock )
					{
						break;
					}
				}

				start = extraBlock->getNext();
				cc._clear();
			}
		}

	}//nsx86
}//nsArch

#endif//( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )