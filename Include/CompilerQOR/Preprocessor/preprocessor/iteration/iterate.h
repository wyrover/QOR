//iterate.h

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

#ifndef QOR_PREPROCESSOR_ITERATION_ITERATE_H_1
#define QOR_PREPROCESSOR_ITERATION_ITERATE_H_1

#include "../arithmetic/dec.h"
#include "../arithmetic/inc.h"
#include "../array/elem.h"
#include "../array/size.h"
#include "../cat.h"
#include "../slot/slot.h"
#include "../tuple/elem.h"

//QOR_PP_ITERATION_DEPTH

#define QOR_PP_ITERATION_DEPTH()			0

//QOR_PP_ITERATION

#define QOR_PP_ITERATION()					QOR_PP_CAT( QOR_PP_ITERATION_, QOR_PP_ITERATION_DEPTH() )

//QOR_PP_ITERATION_START && QOR_PP_ITERATION_FINISH

#define QOR_PP_ITERATION_START()			QOR_PP_CAT( QOR_PP_ITERATION_START_, QOR_PP_ITERATION_DEPTH() )
#define QOR_PP_ITERATION_FINISH()			QOR_PP_CAT( QOR_PP_ITERATION_FINISH_, QOR_PP_ITERATION_DEPTH() )

//QOR_PP_ITERATION_FLAGS

#define QOR_PP_ITERATION_FLAGS()			( QOR_PP_CAT( QOR_PP_ITERATION_FLAGS_, QOR_PP_ITERATION_DEPTH() )() )

//QOR_PP_FRAME_ITERATION

#define QOR_PP_FRAME_ITERATION( i )			QOR_PP_CAT( QOR_PP_ITERATION_, i )

//QOR_PP_FRAME_START && QOR_PP_FRAME_FINISH

#define QOR_PP_FRAME_START( i )				QOR_PP_CAT( QOR_PP_ITERATION_START_, i )
#define QOR_PP_FRAME_FINISH( i )			QOR_PP_CAT( QOR_PP_ITERATION_FINISH_, i )

//QOR_PP_FRAME_FLAGS

#define QOR_PP_FRAME_FLAGS( i )				( QOR_PP_CAT( QOR_PP_ITERATION_FLAGS_, i )() )

//QOR_PP_RELATIVE_ITERATION

#define QOR_PP_RELATIVE_ITERATION( i )		QOR_PP_CAT( QOR_PP_RELATIVE_, i )( QOR_PP_ITERATION_ )
#define QOR_PP_RELATIVE_0( m )				QOR_PP_CAT( m, QOR_PP_ITERATION_DEPTH() )
#define QOR_PP_RELATIVE_1( m )				QOR_PP_CAT( m, QOR_PP_DEC( QOR_PP_ITERATION_DEPTH() ) )
#define QOR_PP_RELATIVE_2( m )				QOR_PP_CAT( m, QOR_PP_DEC( QOR_PP_DEC( QOR_PP_ITERATION_DEPTH() ) ) )
#define QOR_PP_RELATIVE_3( m )				QOR_PP_CAT( m, QOR_PP_DEC( QOR_PP_DEC( QOR_PP_DEC( QOR_PP_ITERATION_DEPTH() ) ) ) )
#define QOR_PP_RELATIVE_4( m )				QOR_PP_CAT( m, QOR_PP_DEC( QOR_PP_DEC( QOR_PP_DEC( QOR_PP_DEC( QOR_PP_ITERATION_DEPTH() ) ) ) ) )

//QOR_PP_RELATIVE_START && QOR_PP_RELATIVE_FINISH

#define QOR_PP_RELATIVE_START( i )			QOR_PP_CAT( QOR_PP_RELATIVE_, i )( QOR_PP_ITERATION_START_ )
#define QOR_PP_RELATIVE_FINISH( i )			QOR_PP_CAT( QOR_PP_RELATIVE_, i )( QOR_PP_ITERATION_FINISH_ )

//QOR_PP_RELATIVE_FLAGS

#define QOR_PP_RELATIVE_FLAGS( i )			( QOR_PP_CAT( QOR_PP_RELATIVE_, i )( QOR_PP_ITERATION_FLAGS_ )() )

//QOR_PP_ITERATE

#define QOR_PP_ITERATE()					QOR_PP_CAT( QOR_PP_ITERATE_, QOR_PP_INC( QOR_PP_ITERATION_DEPTH() ) )
#define QOR_PP_ITERATE_1					<CompilerQOR/Preprocessor/preprocessor/iteration/detail/iter/forward1.h>
#define QOR_PP_ITERATE_2					<CompilerQOR/Preprocessor/preprocessor/iteration/detail/iter/forward2.h>
#define QOR_PP_ITERATE_3					<CompilerQOR/Preprocessor/preprocessor/iteration/detail/iter/forward3.h>
#define QOR_PP_ITERATE_4					<CompilerQOR/Preprocessor/preprocessor/iteration/detail/iter/forward4.h>
#define QOR_PP_ITERATE_5					<CompilerQOR/Preprocessor/preprocessor/iteration/detail/iter/forward5.h>

#endif//QOR_PREPROCESSOR_ITERATION_ITERATE_H_1
