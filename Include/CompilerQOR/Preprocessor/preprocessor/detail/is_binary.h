//is_binary.h

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

#ifndef QOR_PREPROCESSOR_DETAIL_IS_BINARY_H_1
#define QOR_PREPROCESSOR_DETAIL_IS_BINARY_H_1

#include "../config/config.h"
#include "check.h"

//QOR_PP_IS_BINARY

#if ~QOR_PP_CONFIG_FLAGS() & QOR_PP_CONFIG_EDG()
#   define QOR_PP_IS_BINARY( x )					QOR_PP_CHECK( x, QOR_PP_IS_BINARY_CHECK )
#else
#   define QOR_PP_IS_BINARY( x )					QOR_PP_IS_BINARY_I( x )
#   define QOR_PP_IS_BINARY_I( x )					QOR_PP_CHECK( x, QOR_PP_IS_BINARY_CHECK )
#endif

#define QOR_PP_IS_BINARY_CHECK( a, b )				1
#define QOR_PP_CHECK_RESULT_QOR_PP_IS_BINARY_CHECK	0, QOR_PP_NIL

#endif//QOR_PREPROCESSOR_DETAIL_IS_BINARY_H_1
