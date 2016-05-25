//ERet.cpp

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

//implements an x86 function ret emittable

#include "ArchQOR.h"

#if		( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )

#include "ArchQOR/x86/HLAssembler/Emittables/ERet.h"
#include "ArchQOR/x86/HLAssembler/x86HLAContext.h"
#include <assert.h>

//------------------------------------------------------------------------------
namespace nsArch
{
	namespace nsx86
	{
		//------------------------------------------------------------------------------
		CERet::CERet( nsArch::CHighLevelAssemblerBase* c, CEFunction* function, const COperand* first, const COperand* second ) __QCMP_THROW : CEmittable( c, EMITTABLE_RET ),
		m_pFunction( function )
		{
			if( first ) 
			{
				m_apRet[ 0 ] = const_cast< COperand* >( first );
			}
			else
			{
				m_apRet[ 0 ] = 0;
			}

			if( second )
			{
				m_apRet[ 1 ] = const_cast< COperand* >( second );
			}
			else
			{
				m_apRet[ 1 ] = 0;
			}

			/*
			// TODO:?

			// Check whether the return value is compatible.
			Cmp_unsigned__int32 retValType = function->getPrototype().getReturnValue();
			bool valid = false;

			switch (retValType)
			{
			case VARIABLE_TYPE_GPD:
			case VARIABLE_TYPE_GPQ:
			if ((m_aRet[0].isVar() && (reinterpret_cast<const BaseVar&>(m_aRet[0]).isGPVar())) ||
			(m_aRet[0].isImm()))
			{
			valid = true;
			}
			break;

			case VARIABLE_TYPE_X87:
			case VARIABLE_TYPE_X87_1F:
			case VARIABLE_TYPE_X87_1D:
			if ((m_aRet[0].isVar() && (reinterpret_cast<const BaseVar&>(m_aRet[0]).isX87Var() ||
							reinterpret_cast<const BaseVar&>(m_aRet[0]).isXMMVar() )) )
			{
			valid = true;
			}
			break;

			case VARIABLE_TYPE_MM:
			break;

			case INVALID_VALUE:
			if (m_aRet[0].isNone() && 
			m_aRet[1].isNone())
			{
			valid = true;
			}
			break;

			default:
			break;
			}

			// Incompatible return value.
			if (!valid)
			{
			c->setError(ERROR_INCOMPATIBLE_RETURN_VALUE);
			}
			*/
		}

		//------------------------------------------------------------------------------
		CERet::~CERet() __QCMP_THROW
		{
		}

		//------------------------------------------------------------------------------
		void CERet::prepare( CHLAssemblerContextBase& hlac ) __QCMP_THROW
		{
			Cx86HLAContext& cc = dynamic_cast< Cx86HLAContext& >( hlac );
			m_uiOffset = cc.GetCurrentOffset();

			Cmp_unsigned__int32 retValType = getFunction()->getPrototype().getReturnValue();
			if( retValType != INVALID_VALUE )
			{
				Cmp_unsigned__int32 i;
				for( i = 0; i < 2; i++ )
				{
					COperand* o = m_apRet[ i ];

					if( o->isVar() )
					{
						assert( o->getId() != INVALID_VALUE );
						VarData* vdata = ( dynamic_cast< Cx86HLAssembler* >( m_pHLAssembler ) )->_getVarData( o->getId() );
						assert( vdata != 0 );

						// First emittable (begin of variable scope).
						if( vdata->firstEmittable == 0 )
						{
							vdata->firstEmittable = this;
						}

						// Last emittable (end of variable scope).
						vdata->lastEmittable = this;

						if( vdata->workOffset == m_uiOffset )
						{
							continue;
						}

						if( !cc._isActive( vdata ) )
						{
							cc._addActive( vdata );
						}

						vdata->workOffset = m_uiOffset;
						vdata->registerReadCount++;

						if( isVariableInteger( vdata->type ) && isVariableInteger( retValType ) )
						{
							cc._newRegisterHomeIndex( vdata, ( i == 0 ) ? REG_INDEX_EAX : REG_INDEX_EDX );
						}
					}
				}
			}

			cc.IncrementCurrentOffset();
		}

		//------------------------------------------------------------------------------
		nsArch::CEmittable* CERet::translate( CHLAssemblerContextBase& hlac ) __QCMP_THROW
		{
			Cx86HLAContext& cc = dynamic_cast< Cx86HLAContext& >( hlac );
			Cx86HLAIntrinsics* compiler = dynamic_cast< Cx86HLAIntrinsics* >( cc.getHighLevelAssembler() );

			// Check whether the return value is compatible.
			Cmp_unsigned__int32 retValType = getFunction()->getPrototype().getReturnValue();
			Cmp_unsigned__int32 i;

			switch( retValType )
			{
			case VARIABLE_TYPE_GPD:
			case VARIABLE_TYPE_GPQ:
				for( i = 0; i < 2; i++ )
				{
					Cmp_unsigned__int32 dsti = ( i == 0 ) ? REG_INDEX_EAX : REG_INDEX_EDX;
					Cmp_unsigned__int32 srci;

					if( m_apRet[ i ]->isVar() )
					{
						if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isGPVar() )
						{
							VarData* vdata = ( dynamic_cast< Cx86HLAssembler* >( m_pHLAssembler ) )->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							if( srci == INVALID_VALUE )
							{
								CGPReg Reg( gpn( dsti ) );
								CMem Mem( cc._getVarMem( vdata ) );
								compiler->emit( INST_MOV, &Reg, &Mem );
							}
							else if( dsti != srci )
							{
								CGPReg dstReg( gpn( dsti ) );
								CGPReg srcReg( gpn( srci ) );
								compiler->emit( INST_MOV, &dstReg, &srcReg );
							}
						}
					}
					else if( m_apRet[ i ]->isImm() )
					{
						CGPReg dstReg( gpn( dsti ) );
						compiler->emit( INST_MOV, &dstReg, m_apRet[ i ] );
					}
				}
				break;

			case VARIABLE_TYPE_X87:
			case VARIABLE_TYPE_X87_1F:
			case VARIABLE_TYPE_X87_1D:
				// There is case that we need to return two values (Unix-ABI specific):
				// - FLD #2
				//-  FLD #1
				i = 2;
				do 
				{
					i--;
					//Cmp_unsigned__int32 dsti = i;
					Cmp_unsigned__int32 srci;

					if( m_apRet[ i ]->isVar() )
					{
						if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isX87Var() )
						{
							// TODO: X87.
						}
						else if ( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isXMMVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							if( srci != INVALID_VALUE )
							{
								cc.saveXMMVar( vdata );
							}

							switch( vdata->type )
							{
							case VARIABLE_TYPE_XMM_1F:
							case VARIABLE_TYPE_XMM_4F:
								{
									CMem srcMem( _BaseVarMem( *( dynamic_cast< CBaseVar* >( m_apRet[ i ] ) ), 4 ) );
									compiler->emit( INST_FLD, &srcMem );
									break;
								}
							case VARIABLE_TYPE_XMM_1D:
							case VARIABLE_TYPE_XMM_2D:
								{
									CMem srcMem( _BaseVarMem( *( dynamic_cast< CBaseVar* >( m_apRet[ i ] ) ), 8 ) );
									compiler->emit( INST_FLD, &srcMem );
									break;
								}
							}
						}
					}
				} while( i != 0 );
				break;

			case VARIABLE_TYPE_MM:
				for( i = 0; i < 2; i++ )
				{
					Cmp_unsigned__int32 dsti = i;
					Cmp_unsigned__int32 srci;

					if( m_apRet[ i ]->isVar() )
					{
						if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isGPVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							Cmp_unsigned__int32 inst = m_apRet[ i ]->isRegType( REG_TYPE_GPQ ) ? INST_MOVQ : INST_MOVD;

							if( srci == INVALID_VALUE )
							{
								CMMReg MMReg( mm( dsti ) );
								CMem Mem( cc._getVarMem( vdata ) );
								compiler->emit( inst, &MMReg, &Mem );
							}
							else
							{
								CMMReg MMReg( mm( dsti ) );
								CGPReg GPReg( gpd( srci ) );
#	if ( QOR_ARCH_WORDSIZE == 32 )
								compiler->emit( inst, &MMReg, &GPReg );
#	else
								CGPReg GPQReg( gpq( srci ) );
								compiler->emit( inst, &MMReg, m_apRet[ i ]->isRegType( REG_TYPE_GPQ ) ? &GPQReg : &GPReg );
#	endif
							}
						}
						else if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isMMVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							Cmp_unsigned__int32 inst = INST_MOVQ;

							if( srci == INVALID_VALUE )
							{
								CMMReg MMReg( mm( dsti ) );
								CMem Mem( cc._getVarMem( vdata ) );
								compiler->emit( inst, &MMReg, &Mem );
							}
							else if( dsti != srci )
							{
								CMMReg dstReg( mm( dsti ) );
								CMMReg srcReg( mm( srci ) );
								compiler->emit( inst, &dstReg, &srcReg );
							}
						}
						else if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isXMMVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							Cmp_unsigned__int32 inst = INST_MOVQ;
							if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->getVariableType() == VARIABLE_TYPE_XMM_1F )
							{
								inst = INST_MOVD;
							}

							if( srci == INVALID_VALUE )
							{
								CMMReg dstReg( mm( dsti ) );
								CMem Mem( cc._getVarMem( vdata ) );
								compiler->emit(inst, &dstReg, &Mem );
							}
							else
							{
								CMMReg dstReg( mm( dsti ) );
								CXMMReg srcReg( xmm( srci ) );
								compiler->emit( inst, &dstReg, &srcReg );
							}
						}
					}
				}
				break;

			case VARIABLE_TYPE_XMM:
			case VARIABLE_TYPE_XMM_4F:
			case VARIABLE_TYPE_XMM_2D:
				for( i = 0; i < 2; i++ )
				{
					Cmp_unsigned__int32 dsti = i;
					Cmp_unsigned__int32 srci;

					if( m_apRet[i]->isVar() )
					{
						if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isGPVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							Cmp_unsigned__int32 inst = m_apRet[ i ]->isRegType( REG_TYPE_GPQ ) ? INST_MOVQ : INST_MOVD;

							if( srci == INVALID_VALUE )
							{
								CXMMReg dstReg( xmm( dsti ) );
								CMem Mem( cc._getVarMem( vdata ) );
								compiler->emit( inst, &dstReg, &Mem );
							}
							else
							{
								CXMMReg dstReg( xmm( dsti ) );
								CGPReg srcReg( gpd( srci ) );
#	if ( QOR_ARCH_WORDSIZE == 32 )
								compiler->emit( inst, &dstReg, &srcReg );
#	else
								CGPReg srcQReg( gpq( srci ) );
								compiler->emit( inst, &dstReg, m_apRet[ i ]->isRegType( REG_TYPE_GPQ ) ? &srcQReg : &srcReg );
#	endif
							}
						}
						else if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isX87Var() )
						{
							// TODO: X87.
						}
						else if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isMMVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							if( srci == INVALID_VALUE )
							{
								CXMMReg dstReg( xmm( dsti ) );
								CMem srcMem( cc._getVarMem( vdata ) );
								compiler->emit( INST_MOVQ, &dstReg, &srcMem );
							}
							else
							{
								CXMMReg dstReg( xmm( dsti ) );
								CMMReg srcReg( mm( srci ) );
								compiler->emit( INST_MOVQ, &dstReg, &srcReg );
							}
						}
						else if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isXMMVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							if( srci == INVALID_VALUE )
							{
								CXMMReg dstReg( xmm( dsti ) );
								CMem srcMem( cc._getVarMem( vdata ) );
								compiler->emit( INST_MOVDQA, &dstReg, &srcMem );
							}
							else if( dsti != srci )
							{
								CXMMReg dstReg( xmm( dsti ) );
								CXMMReg srcReg( xmm( srci ) );
								compiler->emit( INST_MOVDQA, &dstReg, &srcReg );
							}
						}
					}
				}
				break;

			case VARIABLE_TYPE_XMM_1F:
				for( i = 0; i < 2; i++ )
				{
					Cmp_unsigned__int32 dsti = i;
					Cmp_unsigned__int32 srci;

					if( m_apRet[ i ]->isVar() )
					{
						if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isX87Var() )
						{
							// TODO: X87.
						}
						else if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isXMMVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert( vdata != 0 );

							srci = vdata->registerIndex;
							switch( vdata->type )
							{
							case VARIABLE_TYPE_XMM:
								if( srci == INVALID_VALUE )
								{
									CXMMReg XMMReg( xmm( dsti ) );
									CMem Mem( cc._getVarMem( vdata ) );
									compiler->emit( INST_MOVDQA, &XMMReg, &Mem );
								}
								else if( dsti != srci )
								{
									CXMMReg dstXMMReg( xmm( dsti ) );
									CXMMReg srcXMMReg( xmm( srci ) );
									compiler->emit( INST_MOVDQA, &dstXMMReg, &srcXMMReg );
								}
								break;
							case VARIABLE_TYPE_XMM_1F:
							case VARIABLE_TYPE_XMM_4F:
								if( srci == INVALID_VALUE )
								{
									CXMMReg dstXMMReg( xmm( dsti ) );
									CMem srcMem( cc._getVarMem( vdata ) );
									compiler->emit( INST_MOVSS, &dstXMMReg, &srcMem );
								}
								else
								{
									CXMMReg dstXMMReg( xmm( dsti ) );
									CXMMReg srcXMMReg( xmm( srci ) );
									compiler->emit( INST_MOVSS, &dstXMMReg, &srcXMMReg );
								}
								break;
							case VARIABLE_TYPE_XMM_1D:
							case VARIABLE_TYPE_XMM_2D:
								if( srci == INVALID_VALUE )
								{
									CXMMReg dstXMMReg( xmm( dsti ) );
									CMem srcMem( cc._getVarMem( vdata ) );
									compiler->emit( INST_CVTSD2SS, &dstXMMReg, &srcMem );
								}
								else if( dsti != srci )
								{
									CXMMReg dstXMMReg( xmm( dsti ) );
									CXMMReg srcXMMReg( xmm( srci ) );
									compiler->emit( INST_CVTSD2SS, &dstXMMReg, &srcXMMReg );
								}
								break;
							}
						}
					}
				}
				break;

			case VARIABLE_TYPE_XMM_1D:
				for( i = 0; i < 2; i++ )
				{
					Cmp_unsigned__int32 dsti = i;
					Cmp_unsigned__int32 srci;

					if( m_apRet[ i ]->isVar() )
					{
						if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isX87Var() )
						{
							// TODO: X87.
						}
						else if( dynamic_cast< const CBaseVar* >( m_apRet[ i ] )->isXMMVar() )
						{
							VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
							assert(vdata != 0 );

							srci = vdata->registerIndex;
							switch( vdata->type )
							{
							case VARIABLE_TYPE_XMM:
								if( srci == INVALID_VALUE )
								{
									CXMMReg dstXMMReg( xmm( dsti ) );
									CMem srcMem( cc._getVarMem( vdata ) );
									compiler->emit( INST_MOVDQA, &dstXMMReg, &srcMem );
								}
								else if( dsti != srci )
								{
									CXMMReg dstXMMReg( xmm( dsti ) );
									CXMMReg srcXMMReg( xmm( srci ) );
									compiler->emit( INST_MOVDQA, &dstXMMReg, &srcXMMReg );
								}
								break;
							case VARIABLE_TYPE_XMM_1F:
							case VARIABLE_TYPE_XMM_4F:
								{
									if( srci == INVALID_VALUE )
									{
										CXMMReg dstXMMReg( xmm( dsti ) );
										CMem srcMem( cc._getVarMem( vdata ) );
										compiler->emit( INST_CVTSS2SD, &dstXMMReg, &srcMem );
									}
									else
									{
										CXMMReg dstXMMReg( xmm( dsti ) );
										CXMMReg srcXMMReg( xmm( srci ) );
										compiler->emit( INST_CVTSS2SD, &dstXMMReg, &srcXMMReg );
									}
								}
								break;
							case VARIABLE_TYPE_XMM_1D:
							case VARIABLE_TYPE_XMM_2D:
								{
									if( srci == INVALID_VALUE )
									{
										CXMMReg dstXMMReg( xmm( dsti ) );
										CMem srcMem( cc._getVarMem( vdata ) );
										compiler->emit( INST_MOVSD, &dstXMMReg, &srcMem );
									}
									else
									{
										CXMMReg dstXMMReg( xmm( dsti ) );
										CXMMReg srcXMMReg( xmm( srci ) );
										compiler->emit( INST_MOVSD, &dstXMMReg, &srcXMMReg );
									}
								}
								break;
							}
						}
					}
				}
				break;

			case INVALID_VALUE:
				default:
				break;
			}

			if( shouldEmitJumpToEpilog() )
			{
				cc.setUnreachable( 1 );
			}

			for( i = 0; i < 2; i++ )
			{
				if( m_apRet[ i ] && m_apRet[ i ]->isVar() )
				{
					VarData* vdata = compiler->_getVarData( m_apRet[ i ]->getId() );
					cc._unuseVarOnEndOfScope( this, vdata );
				}
			}

			return translated();
		}

		//------------------------------------------------------------------------------
		void CERet::emit( CHighLevelAssemblerBase& ab ) __QCMP_THROW
		{
			Cx86HLAIntrinsics& a = dynamic_cast< Cx86HLAIntrinsics& >( ab );
			if( shouldEmitJumpToEpilog() )
			{
				a.jmp( getFunction()->getExitLabel() );
			}
		}

		//------------------------------------------------------------------------------
		int CERet::getMaxSize() const __QCMP_THROW
		{
			return shouldEmitJumpToEpilog() ? 15 : 0;
		}

		//------------------------------------------------------------------------------
		bool CERet::shouldEmitJumpToEpilog() const __QCMP_THROW
		{
			// Iterate over next emittables. If we found emittable that emits real 
			// instruction then we must return @c true.
			nsArch::CEmittable* e = this->getNext();

			while( e )
			{
				switch( e->getType() )
				{
				// Non-interesting emittables.
				case EMITTABLE_COMMENT:
				case EMITTABLE_DUMMY:
				case EMITTABLE_ALIGN:
				case EMITTABLE_BLOCK:
				case EMITTABLE_VARIABLE_HINT:
				case EMITTABLE_TARGET:
					break;

					// Interesting emittables.
				case EMITTABLE_EMBEDDED_DATA:
				case EMITTABLE_INSTRUCTION:
				case EMITTABLE_JUMP_TABLE:
				case EMITTABLE_CALL:
				case EMITTABLE_RET:
					return true;

					// These emittables shouldn't be here. We are inside function, after
					// prolog.
				case EMITTABLE_FUNCTION:
				case EMITTABLE_PROLOG:
					break;

				// Stop station, we can't go forward from here.
				case EMITTABLE_EPILOG:
					return false;
				}
				e = e->getNext();
			}

			return false;
		}

	}//nsx86
}//nsArch

#endif//( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )