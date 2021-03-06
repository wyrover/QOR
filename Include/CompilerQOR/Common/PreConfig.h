// PreConfig.h

// Copyright Querysoft Limited 2015
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

// Set up simple preprocessor definitions usable in the configuration header

#ifndef QCMP_PRECONFIG_H_1
#define QCMP_PRECONFIG_H_1

#define __QCS_NO_		0
#define __QCS_YES_		1

#define __QCS_MAX_PERFORMANCE_		10
#define __QCS_BALANCED_PERF_		5
#define __QCS_MAX_SAFETY_			0

/*Defines standard version numbers, with these properties:

* Decimal base whole numbers in the range \[0,1000000000).
  The number range is designed to allow for a (2,3,4) triplet.
  Which fits within a 32 bit value.
* The `major` number can be in the \[0,99\] range.
* The `minor` number can be in the \[0,999\] range.
* The `patch` number can be in the \[0,9999\] range.
* Values can be specified in any base. As the defined value
  is an constant expression.
* Value can be directly used in both preprocessor and compiler
  expressions for comparison to other similarly defined values.
* The implementation enforces the individual ranges for the
  major, minor, and patch numbers. And values over the ranges
  are truncated (modulo).
*/
#define QOR_PP_VERSION_NUMBER(major,minor,patch) \
    ( (((major)%100)*10000000) + (((minor)%1000)*10000) + ((patch)%10000) )

#define QOR_PP_VERSION_MAKE_10_VRP(V) QOR_PP_VERSION_NUMBER(((V)/100)%10,((V)/10)%10,(V)%10)
#define QOR_PP_VERSION_MAKE_10_VV00(V) QOR_PP_VERSION_NUMBER(((V)/100)%100,0,0)

#define QOR_PP_VERSION_MAJOR(V) (V / 10000000)
#define QOR_PP_VERSION_MINOR(V) ( ( V - ( (V / 10000000) * 10000000 ) ) / 10000 )
#define QOR_PP_VERSION_PATCH(V) ( V - ( QOR_PP_VERSION_MINOR(V) * 10000 ) )

#endif//QCMP_PRECONFIG_H_1

