//ftw.h

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

#ifndef	QOR_FTW_H_3
#define QOR_FTW_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(ftw)

typedef nsPlatform::FTW FTW;
typedef nsPlatform::stat stat;

#define FTW_F			( nsPlatform::FTWFile )				//File. 
#define FTW_D			( nsPlatform::FTWDirectory )		//Directory. 
#define FTW_DNR			( nsPlatform::FTWDirNoRead )		//Directory without read permission. 
#define FTW_DP			( nsPlatform::FTWDirSubdirVisit )	//Directory with subdirectories visited. 
#define FTW_NS			( nsPlatform::FTWUnknown )			//Unknown type; stat() failed. 
#define FTW_SL			( nsPlatform::FTWSymLink )			//Symbolic link. 
#define FTW_SLN			( nsPlatform::FTWSymLinkNoFile )	//Symbolic link that names a nonexistent file.

#define FTW_PHYS		( nsPlatform::FTWPhysicalWalk )		//Physical walk, does not follow symbolic links. Otherwise, nftw() follows links but does not walk down any path that crosses itself. 
#define FTW_MOUNT		( nsPlatform::FTWMountX )			//The walk does not cross a mount point. 
#define FTW_DEPTH		( nsPlatform::FTWDepth )			//All subdirectories are visited before the directory itself. 
#define FTW_CHDIR		( nsPlatforn::FTWChDir )			//The walk changes to each directory before reading it. 

__QCMP_STARTLINKAGE_C

    __QOR_INTERFACE( __CQOR ) int ftw( const char* szPath, int (*fn)( const char*, const stat*, int ), int ndirs );
    __QOR_INTERFACE( __CQOR ) int nftw( const char* szPath, int (*fn)( const char*, const stat*, int, FTW* ), int fd_limit, int flags );

__QCMP_ENDLINKAGE_C

#endif//QOR_FTW_H_3
