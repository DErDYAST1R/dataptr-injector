#pragma once

namespace fusion::string
{
	int tolower( int c )
	{
		if ( c >= 'A' && c <= 'Z' ) return c - 'A' + 'a';
		return c;
	}
	int stricmp( const char* cs, const char* ct )
	{
		if ( cs && ct )
		{
			while ( tolower( *cs ) == tolower( *ct ) )
			{
				if ( *cs == 0 && *ct == 0 ) return 0;
				if ( *cs == 0 || *ct == 0 ) break;
				cs++;
				ct++;
			}
			return tolower( *cs ) - tolower( *ct );
		}
		return -1;
	}


	int strcmp( const char* cs, const char* ct )
	{
		if ( cs && ct )
		{
			while ( *cs == *ct )
			{
				if ( *cs == 0 && *ct == 0 ) return 0;
				if ( *cs == 0 || *ct == 0 ) break;
				cs++;
				ct++;
			}
			return *cs - *ct;
		}
		return -1;
	}

	size_t strlen( const char* const string )
	{
		size_t length = 0;

		while ( string[ length ] != '\0' )
			length++;

		return length;
	}

	char* strstr( const char* _Str, char const* _SubStr )
	{
		const char* bp = _SubStr;
		const char* back_pos;
		while ( *_Str != 0 && _Str != 0 && _SubStr != 0 )
		{
			back_pos = _Str;
			while ( tolower( *back_pos++ ) == tolower( *_SubStr++ ) )
			{
				if ( *_SubStr == 0 )
				{
					return ( char* ) ( back_pos - strlen( bp ) );
				}
			}
			++_Str;
			_SubStr = bp;
		}
		return 0;
	}
}