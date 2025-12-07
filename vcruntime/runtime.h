#pragma once

namespace fusion::memory
{
	const void* memchr( const void* s, int c, size_t n )
	{
		if ( n )
		{
			const char* p = ( const char* ) s;
			do
			{
				if ( *p++ == c ) return ( void* ) ( p - 1 );
			} while ( --n != 0 );
		}
		return 0;
	}

	int memcmp( const void* s1, const void* s2, size_t n )
	{
		if ( n != 0 )
		{
			const unsigned char* p1 = ( unsigned char* ) s1, * p2 = ( unsigned char* ) s2;
			do
			{
				if ( *p1++ != *p2++ ) return ( *--p1 - *--p2 );
			} while ( --n != 0 );
		}
		return 0;
	}

	void* memcpy( void* dest, const void* src, size_t count )
	{
		char* char_dest = ( char* ) dest;
		char* char_src = ( char* ) src;
		if ( ( char_dest <= char_src ) || ( char_dest >= ( char_src + count ) ) )
		{
			while ( count > 0 )
			{
				*char_dest = *char_src;
				char_dest++;
				char_src++;
				count--;
			}
		}
		else
		{
			char_dest = ( char* ) dest + count - 1;
			char_src = ( char* ) src + count - 1;
			while ( count > 0 )
			{
				*char_dest = *char_src;
				char_dest--;
				char_src--;
				count--;
			}
		}
		return dest;
	}

	void* memmove( void* destination, const void* source, size_t size )
	{
		char* char_dest = ( char* ) destination;
		char* char_src = ( char* ) source;
		if ( ( char_dest <= char_src ) || ( char_dest >= ( char_src + size ) ) )
		{
			while ( size > 0 )
			{
				*char_dest = *char_src;
				char_dest++;
				char_src++;
				size--;
			}
		}
		else
		{
			char_dest = ( char* ) destination + size - 1;
			char_src = ( char* ) source + size - 1;
			while ( size > 0 )
			{
				*char_dest = *char_src;
				char_dest--;
				char_src--;
				size--;
			}
		}
		return destination;
	}
 
	void* memset( void* src, int val, size_t count )
	{
		int           i;
		unsigned char* p = ( unsigned char* ) src;
		i = 0;
		while ( count > 0 )
		{
			*p = val;
			p++;
			count--;
		}
		return( src );
	}
}