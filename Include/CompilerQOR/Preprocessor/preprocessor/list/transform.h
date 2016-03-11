//transform.h

# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */

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

#ifndef QOR_PREPROCESSOR_LIST_TRANSFORM_H_1
#define QOR_PREPROCESSOR_LIST_TRANSFORM_H_1

#include "../config/config.h"
#include "fold_right.h"
#include "../tuple/elem.h"
#include "../tuple/rem.h"

//QOR_PP_LIST_TRANSFORM

#if ~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#   define QOR_PP_LIST_TRANSFORM( op, data, list )		QOR_PP_TUPLE_ELEM( 3, 2, QOR_PP_LIST_FOLD_RIGHT( QOR_PP_LIST_TRANSFORM_O, ( op, data, QOR_PP_NIL ), list ) )
#else
#   define QOR_PP_LIST_TRANSFORM( op, data, list )		QOR_PP_LIST_TRANSFORM_I( op, data, list )
#   define QOR_PP_LIST_TRANSFORM_I( op, data, list )	QOR_PP_TUPLE_ELEM( 3, 2, QOR_PP_LIST_FOLD_RIGHT( QOR_PP_LIST_TRANSFORM_O, ( op, data, QOR_PP_NIL ), list ) )
#endif

#if ~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#   define QOR_PP_LIST_TRANSFORM_O( d, odr, elem )		QOR_PP_LIST_TRANSFORM_O_D( d, QOR_PP_TUPLE_ELEM( 3, 0, odr ), QOR_PP_TUPLE_ELEM( 3, 1, odr ), QOR_PP_TUPLE_ELEM( 3, 2, odr ), elem )
#else
#   define QOR_PP_LIST_TRANSFORM_O( d, odr, elem )		QOR_PP_LIST_TRANSFORM_O_I( d, QOR_PP_TUPLE_REM_3 odr, elem )
#   define QOR_PP_LIST_TRANSFORM_O_I( d, im, elem )		QOR_PP_LIST_TRANSFORM_O_D( d, im, elem )
#endif

#define QOR_PP_LIST_TRANSFORM_O_D( d, op, data, res, elem )		( op, data, ( op( d, data, elem ), res ) )

//QOR_PP_LIST_TRANSFORM_D

#if ~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#   define QOR_PP_LIST_TRANSFORM_D( d, op, data, list )			QOR_PP_TUPLE_ELEM( 3, 2, QOR_PP_LIST_FOLD_RIGHT_ ## d( QOR_PP_LIST_TRANSFORM_O, ( op, data, QOR_PP_NIL ), list ) )
#else
#   define QOR_PP_LIST_TRANSFORM_D( d, op, data, list )			QOR_PP_LIST_TRANSFORM_D_I( d, op, data, list )
#   define QOR_PP_LIST_TRANSFORM_D_I( d, op, data, list	)		QOR_PP_TUPLE_ELEM( 3, 2, QOR_PP_LIST_FOLD_RIGHT_ ## d( QOR_PP_LIST_TRANSFORM_O, ( op, data, QOR_PP_NIL ), list ) )
#endif

#endif//QOR_PREPROCESSOR_LIST_TRANSFORM_H_1