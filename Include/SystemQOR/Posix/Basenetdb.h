//Basenetdb.h

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

//Base CRT class for Cnetdb

#ifndef SYSTEMQOR_POSIX_NETDB_H_3
#define SYSTEMQOR_POSIX_NETDB_H_3

#include "SystemQOR.h"
#include QOR_SYS_PLATFORMTYPES(netdb)
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	using nsPlatform::addrinfo;
	using nsPlatform::hostent;
	using nsPlatform::socklen_t;
	using nsPlatform::sockaddr;
	using nsPlatform::netent;
	using nsPlatform::uint32_t;
	using nsPlatform::protoent;
	using nsPlatform::servent;

    //------------------------------------------------------------------------------
    class __QOR_INTERFACE( __QSYS ) Cnetdb
    {
        
	public:

		__QOR_DECLARE_OCLASS_ID( Cnetdb );

		virtual void endhostent( void );
		virtual void endnetent( void );
		virtual void endprotoent( void );
		virtual void endservent( void );
		virtual void freeaddrinfo( addrinfo* );
		virtual const char* gai_strerror( int );
		virtual int getaddrinfo( const char*, const char*, const addrinfo*, addrinfo** );
		virtual hostent* gethostbyaddr( const void*, socklen_t, int );
		virtual hostent* gethostbyname( const char* );
		virtual hostent* gethostent( void );
		virtual int getnameinfo( const sockaddr*, socklen_t, char*, socklen_t, char*, socklen_t, int );
		virtual netent* getnetbyaddr( uint32_t, int );
		virtual netent* getnetbyname( const char* );
		virtual netent* getnetent( void );
		virtual protoent* getprotobyname( const char* );
		virtual protoent* getprotobynumber( int );
		virtual protoent* getprotoent( void );
		virtual servent* getservbyname( const char*, const char* );
		virtual servent* getservbyport( int, const char* );
		virtual servent* getservent( void );
		virtual void sethostent( int );
		virtual void setnetent( int );
		virtual void setprotoent( int );
		virtual void setservent( int );

	protected:

		Cnetdb();
		virtual ~Cnetdb();

	private:

		Cnetdb( const Cnetdb& );
		Cnetdb& operator = ( const Cnetdb& );

	};

}//nsBaseCRT

#endif//SYSTEMQOR_POSIX_NETDB_H_3