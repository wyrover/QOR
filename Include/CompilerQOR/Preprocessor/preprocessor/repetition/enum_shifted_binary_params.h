//enum_shifted_binary_params.h

# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2005.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
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

#ifndef QOR_PREPROCESSOR_REPETITION_ENUM_SHIFTED_BINARY_PARAMS_H_1
#define QOR_PREPROCESSOR_REPETITION_ENUM_SHIFTED_BINARY_PARAMS_H_1

#include "../arithmetic/dec.h"
#include "../arithmetic/inc.h"
#include "../cat.h"
#include "../config/config.h"
#include "../punctuation/comma_if.h"
#include "repeat.h"
#include "../tuple/elem.h"
#include "../tuple/rem.h"

//QOR_PP_ENUM_SHIFTED_BINARY_PARAMS

#if	~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#	define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS( count, p1, p2 )		QOR_PP_REPEAT( QOR_PP_DEC( count ), QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M, ( p1, p2 ) )
#else//EDG
#	define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS( count, p1, p2 )		QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_I( count, p1, p2 )
#	define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_I( count, p1, p2 )		QOR_PP_REPEAT( QOR_PP_DEC( count ), QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M, ( p1, p2 ) )
#endif

#if QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_STRICT()
#   define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M( z, n, pp )			QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M_IM( z, n, QOR_PP_TUPLE_REM_2 pp )
#   define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M_IM( z, n, im )		QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I( z, n, im )
#else
#   define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M( z, n, pp )			QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I( z, n, QOR_PP_TUPLE_ELEM( 2, 0, pp ), QOR_PP_TUPLE_ELEM( 2, 1, pp ) )
#endif

#define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I( z, n, p1, p2 )		QOR_PP_COMMA_IF( n ) QOR_PP_CAT( p1, QOR_PP_INC( n ) ) QOR_PP_CAT( p2, QOR_PP_INC( n ) )

//QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_Z

#if	~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#	define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_Z( z, count, p1, p2 )	QOR_PP_REPEAT_ ## z( QOR_PP_DEC( count ), QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M, ( p1, p2 ) )
#else//EDG
#	define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_Z( z, count, p1, p2 )		QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_Z_I( z, count, p1, p2 )
#	define QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_Z_I( z, count, p1, p2 )	QOR_PP_REPEAT_ ## z( QOR_PP_DEC( count ), QOR_PP_ENUM_SHIFTED_BINARY_PARAMS_M, ( p1, p2 ) )
#endif

#endif//QOR_PREPROCESSOR_REPETITION_ENUM_SHIFTED_BINARY_PARAMS_H_1
