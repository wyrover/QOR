//slot.h

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

#ifndef QOR_PREPROCESSOR_SLOT_SLOT_H_1
#define QOR_PREPROCESSOR_SLOT_SLOT_H_1

#include "../cat.h"
#include "detail/def.h"

//QOR_PP_ASSIGN_SLOT

#define QOR_PP_ASSIGN_SLOT( i )		QOR_PP_CAT( QOR_PP_ASSIGN_SLOT_, i )

#define QOR_PP_ASSIGN_SLOT_1		<CompilerQOR/Common/preprocessor/slot/detail/slot1.h>
#define QOR_PP_ASSIGN_SLOT_2		<CompilerQOR/Common/preprocessor/slot/detail/slot2.h>
#define QOR_PP_ASSIGN_SLOT_3		<CompilerQOR/Common/preprocessor/slot/detail/slot3.h>
#define QOR_PP_ASSIGN_SLOT_4		<CompilerQOR/Common/preprocessor/slot/detail/slot4.h>
#define QOR_PP_ASSIGN_SLOT_5		<CompilerQOR/Common/preprocessor/slot/detail/slot5.h>

//QOR_PP_SLOT

#define QOR_PP_SLOT( i ) QOR_PP_CAT( QOR_PP_SLOT_, i )()

#endif//QOR_PREPROCESSOR_SLOT_SLOT_H_1
