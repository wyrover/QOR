//SupportedOsList.h

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

//This header declares the list of Operating Systems supported by QOR

#define _QSYS_SUPPORTED_OS_LIST 2

#define QOR_SYS_AIX				1
#define	QOR_SYS_AMIGAOS			2
#define QOR_SYS_ANDROID			3
#define QOR_SYS_BEOS			4
#define QOR_SYS_BSD				5
#define QOR_SYS_CHROMEOS		6	//- April 3013 nightly Virtual Box image
#define QOR_SYS_CYGWIN			7
#define QOR_SYS_HAIKU			8
#define QOR_SYS_HPUX			9
#define QOR_SYS_INFERNO			10
#define QOR_SYS_IOS				11
#define QOR_SYS_IRIX			12
#define QOR_SYS_KOLIBRIOS		13	//- Fork of MenuetOS, Written in FASM, does it have C/C++ dev tools - Yes apparently MSVC can be used with extras, http://wiki.kolibrios.org/wiki/C/C%2B%2B_programming
#define QOR_SYS_LINUX			14
#define QOR_SYS_MACOS			15
#define QOR_SYS_MINIX			16
#define QOR_SYS_OS400			17
#define QOR_SYS_OSX				18
#define QOR_SYS_PLAN9			19	//- redownload after blowing up the vm, needs to be run frequently or continuously online to remain valid for updates
#define QOR_SYS_POSIX			20	//- generic fallback POSIX
#define QOR_SYS_QNXNTO			21
#define QOR_SYS_SANOS			22
#define QOR_SYS_SKYOS			23	//- 4Q7W5-HTRRW-6WYHW-45KW7-XQLXL
#define QOR_SYS_SOLARIS			24
#define QOR_SYS_SYLLABLE		25	//- v 0.6.6 VMWare image, http://sourceforge.net/projects/syllable/?source=typ_redirect
#define QOR_SYS_UNIX			26
#define QOR_SYS_VMS				27
#define QOR_SYS_MSW				28


/*
For each OS we need -
Preprocessor detection method
Hardware or a VM with account, password details
A way to get the latest source.
Tool chains to build all the QOR variants that can be built on that OS
Some like SanOS and probably Kolibrios are just targets and can be built from Windows
iOS is probably best targetted from OSX
Many of the Linux and other nix can probably be targetted from Linux using clang
*/
