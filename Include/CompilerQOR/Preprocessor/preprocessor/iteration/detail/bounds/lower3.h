//lower3.h

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

#include "../../../slot/detail/shared.h"

# undef QOR_PP_ITERATION_START_3
#
# undef QOR_PP_ITERATION_START_3_DIGIT_1
# undef QOR_PP_ITERATION_START_3_DIGIT_2
# undef QOR_PP_ITERATION_START_3_DIGIT_3
# undef QOR_PP_ITERATION_START_3_DIGIT_4
# undef QOR_PP_ITERATION_START_3_DIGIT_5
# undef QOR_PP_ITERATION_START_3_DIGIT_6
# undef QOR_PP_ITERATION_START_3_DIGIT_7
# undef QOR_PP_ITERATION_START_3_DIGIT_8
# undef QOR_PP_ITERATION_START_3_DIGIT_9
# undef QOR_PP_ITERATION_START_3_DIGIT_10
#
# if QOR_PP_SLOT_TEMP_3 == 0
#    define QOR_PP_ITERATION_START_3_DIGIT_3 0
# elif QOR_PP_SLOT_TEMP_3 == 1
#    define QOR_PP_ITERATION_START_3_DIGIT_3 1
# elif QOR_PP_SLOT_TEMP_3 == 2
#    define QOR_PP_ITERATION_START_3_DIGIT_3 2
# elif QOR_PP_SLOT_TEMP_3 == 3
#    define QOR_PP_ITERATION_START_3_DIGIT_3 3
# elif QOR_PP_SLOT_TEMP_3 == 4
#    define QOR_PP_ITERATION_START_3_DIGIT_3 4
# elif QOR_PP_SLOT_TEMP_3 == 5
#    define QOR_PP_ITERATION_START_3_DIGIT_3 5
# elif QOR_PP_SLOT_TEMP_3 == 6
#    define QOR_PP_ITERATION_START_3_DIGIT_3 6
# elif QOR_PP_SLOT_TEMP_3 == 7
#    define QOR_PP_ITERATION_START_3_DIGIT_3 7
# elif QOR_PP_SLOT_TEMP_3 == 8
#    define QOR_PP_ITERATION_START_3_DIGIT_3 8
# elif QOR_PP_SLOT_TEMP_3 == 9
#    define QOR_PP_ITERATION_START_3_DIGIT_3 9
# endif
#
# if QOR_PP_SLOT_TEMP_2 == 0
#    define QOR_PP_ITERATION_START_3_DIGIT_2 0
# elif QOR_PP_SLOT_TEMP_2 == 1
#    define QOR_PP_ITERATION_START_3_DIGIT_2 1
# elif QOR_PP_SLOT_TEMP_2 == 2
#    define QOR_PP_ITERATION_START_3_DIGIT_2 2
# elif QOR_PP_SLOT_TEMP_2 == 3
#    define QOR_PP_ITERATION_START_3_DIGIT_2 3
# elif QOR_PP_SLOT_TEMP_2 == 4
#    define QOR_PP_ITERATION_START_3_DIGIT_2 4
# elif QOR_PP_SLOT_TEMP_2 == 5
#    define QOR_PP_ITERATION_START_3_DIGIT_2 5
# elif QOR_PP_SLOT_TEMP_2 == 6
#    define QOR_PP_ITERATION_START_3_DIGIT_2 6
# elif QOR_PP_SLOT_TEMP_2 == 7
#    define QOR_PP_ITERATION_START_3_DIGIT_2 7
# elif QOR_PP_SLOT_TEMP_2 == 8
#    define QOR_PP_ITERATION_START_3_DIGIT_2 8
# elif QOR_PP_SLOT_TEMP_2 == 9
#    define QOR_PP_ITERATION_START_3_DIGIT_2 9
# endif
#
# if QOR_PP_SLOT_TEMP_1 == 0
#    define QOR_PP_ITERATION_START_3_DIGIT_1 0
# elif QOR_PP_SLOT_TEMP_1 == 1
#    define QOR_PP_ITERATION_START_3_DIGIT_1 1
# elif QOR_PP_SLOT_TEMP_1 == 2
#    define QOR_PP_ITERATION_START_3_DIGIT_1 2
# elif QOR_PP_SLOT_TEMP_1 == 3
#    define QOR_PP_ITERATION_START_3_DIGIT_1 3
# elif QOR_PP_SLOT_TEMP_1 == 4
#    define QOR_PP_ITERATION_START_3_DIGIT_1 4
# elif QOR_PP_SLOT_TEMP_1 == 5
#    define QOR_PP_ITERATION_START_3_DIGIT_1 5
# elif QOR_PP_SLOT_TEMP_1 == 6
#    define QOR_PP_ITERATION_START_3_DIGIT_1 6
# elif QOR_PP_SLOT_TEMP_1 == 7
#    define QOR_PP_ITERATION_START_3_DIGIT_1 7
# elif QOR_PP_SLOT_TEMP_1 == 8
#    define QOR_PP_ITERATION_START_3_DIGIT_1 8
# elif QOR_PP_SLOT_TEMP_1 == 9
#    define QOR_PP_ITERATION_START_3_DIGIT_1 9
# endif
#
# if QOR_PP_ITERATION_START_3_DIGIT_3
#    define QOR_PP_ITERATION_START_3 QOR_PP_SLOT_CC_3(QOR_PP_ITERATION_START_3_DIGIT_3, QOR_PP_ITERATION_START_3_DIGIT_2, QOR_PP_ITERATION_START_3_DIGIT_1)
# elif QOR_PP_ITERATION_START_3_DIGIT_2
#    define QOR_PP_ITERATION_START_3 QOR_PP_SLOT_CC_2(QOR_PP_ITERATION_START_3_DIGIT_2, QOR_PP_ITERATION_START_3_DIGIT_1)
# else
#    define QOR_PP_ITERATION_START_3 QOR_PP_ITERATION_START_3_DIGIT_1
# endif
