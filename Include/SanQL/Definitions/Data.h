//Data.h

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

//SanOS Data Definitions

#ifndef SANQL_DEFINITIONS_DATA_H_1
#define SANQL_DEFINITIONS_DATA_H_1

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

//------------------------------------------------------------------------------
namespace nsSanOS
{
	typedef long long off64_t;
	typedef long loff_t;
	typedef long time_t;
	typedef unsigned int dev_t;
	typedef unsigned int ino_t;
	typedef unsigned short mode_t;
	typedef unsigned short nlink_t;
	typedef unsigned short uid_t;
	typedef unsigned short gid_t;

	//------------------------------------------------------------------------------
	struct iovec 
	{ 
		size_t iov_len;
		void* iov_base;
	};

	//------------------------------------------------------------------------------
	struct utimbuf 
	{
		time_t modtime;
		time_t actime;
		time_t ctime;
	};

	//------------------------------------------------------------------------------
	struct stat
	{
		dev_t st_dev;
		ino_t st_ino;
		mode_t st_mode;
		nlink_t st_nlink;
		uid_t st_uid;
		gid_t st_gid;
		dev_t st_rdev;
		loff_t st_size;
		time_t st_atime;
		time_t st_mtime;
		time_t st_ctime;
	};

	//------------------------------------------------------------------------------
	struct stat64
	{
		dev_t st_dev;
		ino_t st_ino;
		mode_t st_mode;
		nlink_t st_nlink;
		uid_t st_uid;
		gid_t st_gid;
		dev_t st_rdev;
		off64_t st_size;
		time_t st_atime;
		time_t st_mtime;
		time_t st_ctime;
	};

}//nsSanOS

#endif//SANQL_DEFINITIONS_DATA_H_1
