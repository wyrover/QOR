//insert.h

# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */

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

#ifndef QOR_PREPROCESSOR_ARRAY_INSERT_H_1
#define QOR_PREPROCESSOR_ARRAY_INSERT_H_1

#include "../arithmetic/inc.h"
#include "elem.h"
#include "push_back.h"
#include "size.h"
#include "../comparison/not_equal.h"
#include "../control/deduce_d.h"
#include "../control/iif.h"
#include "../control/while.h"
#include "../tuple/elem.h"

//QOR_PP_ARRAY_INSERT

#define QOR_PP_ARRAY_INSERT( array, i, elem )			QOR_PP_ARRAY_INSERT_I( QOR_PP_DEDUCE_D(), array, i, elem )
#define QOR_PP_ARRAY_INSERT_I( d, array, i, elem )		QOR_PP_ARRAY_INSERT_D( d, array, i, elem )

//QOR_PP_ARRAY_INSERT_D

#if	~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#	define QOR_PP_ARRAY_INSERT_D( d, array, i, elem )	QOR_PP_TUPLE_ELEM( 5, 3, QOR_PP_WHILE_ ## d( QOR_PP_ARRAY_INSERT_P, QOR_PP_ARRAY_INSERT_O, ( 0, i, elem, ( 0, () ), array ) ) )
#else//EDG
#    define QOR_PP_ARRAY_INSERT_D( d, array, i, elem )	QOR_PP_ARRAY_INSERT_D_I( d, array, i, elem )
#    define QOR_PP_ARRAY_INSERT_D_I( d, array, i, elem )	QOR_PP_TUPLE_ELEM(5, 3, QOR_PP_WHILE_ ## d( QOR_PP_ARRAY_INSERT_P, QOR_PP_ARRAY_INSERT_O, ( 0, i, elem, ( 0, () ), array ) ) )
#endif

#if QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_STRICT()
#	define QOR_PP_ARRAY_INSERT_P( d, state )			QOR_PP_ARRAY_INSERT_P_I state
#else
#	define QOR_PP_ARRAY_INSERT_P( d, state )			QOR_PP_ARRAY_INSERT_P_I( nil, nil, nil, QOR_PP_TUPLE_ELEM( 5, 3, state ), QOR_PP_TUPLE_ELEM( 5, 4, state ) )
#endif

#define QOR_PP_ARRAY_INSERT_P_I( _i, _ii, _iii, res, arr ) QOR_PP_NOT_EQUAL( QOR_PP_ARRAY_SIZE( res ), QOR_PP_INC( QOR_PP_ARRAY_SIZE( arr ) ) )

#if QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_STRICT()
#	define QOR_PP_ARRAY_INSERT_O( d, state )			QOR_PP_ARRAY_INSERT_O_I state
#else
#	define QOR_PP_ARRAY_INSERT_O( d, state )			QOR_PP_ARRAY_INSERT_O_I( QOR_PP_TUPLE_ELEM( 5, 0, state ), QOR_PP_TUPLE_ELEM( 5, 1, state ), QOR_PP_TUPLE_ELEM( 5, 2, state ), QOR_PP_TUPLE_ELEM( 5, 3, state ), QOR_PP_TUPLE_ELEM( 5, 4, state ) )
#endif

#define QOR_PP_ARRAY_INSERT_O_I( n, i, elem, res, arr ) ( QOR_PP_IIF( QOR_PP_NOT_EQUAL( QOR_PP_ARRAY_SIZE( res ), i ), QOR_PP_INC( n ), n ), i, elem, QOR_PP_ARRAY_PUSH_BACK( res, QOR_PP_IIF( QOR_PP_NOT_EQUAL( QOR_PP_ARRAY_SIZE( res ), i ), QOR_PP_ARRAY_ELEM( n, arr ), elem ) ), arr )

#endif//QOR_PREPROCESSOR_ARRAY_INSERT_H_1
