//link_types.h

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


#ifndef SYSTEMQOR_LIN_TYPES_LINK_H_3
#define SYSTEMQOR_LIN_TYPES_LINK_H_3

#include "SystemQOR/Linux/types/elf_types.h"

#define __NEED_size_t
#define __NEED_uint32_t
#include QOR_SYS_ARCHHEADER(alltypes.h)

#if UINTPTR_MAX > 0xffffffff
#	define ElfW(type) Elf64_ ## type
#else
#	define ElfW(type) Elf32_ ## type
#endif

//------------------------------------------------------------------------------
namespace nsLinux
{
	// this is the same everywhere except alpha and s390
	typedef uint32_t Elf_Symndx;

	//------------------------------------------------------------------------------
	struct dl_phdr_info 
	{
		ElfW(Addr) dlpi_addr;
		const char *dlpi_name;
		const ElfW(Phdr) *dlpi_phdr;
		ElfW(Half) dlpi_phnum;
		unsigned long long int dlpi_adds;
		unsigned long long int dlpi_subs;
		size_t dlpi_tls_modid;
		void *dlpi_tls_data;
	};

	//------------------------------------------------------------------------------
	struct link_map 
	{
		ElfW(Addr) l_addr;
		char *l_name;
		ElfW(Dyn) *l_ld;
		struct link_map *l_next, *l_prev;
	};

	//------------------------------------------------------------------------------
	struct r_debug 
	{
		int r_version;
		struct link_map *r_map;
		ElfW(Addr) r_brk;
		enum { RT_CONSISTENT, RT_ADD, RT_DELETE } r_state;
		ElfW(Addr) r_ldbase;
	};

}//nsLinux

#endif//SYSTEMQOR_LIN_TYPES_LINK_H_3
