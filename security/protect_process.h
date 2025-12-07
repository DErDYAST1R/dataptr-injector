#pragma once

namespace fusion::anti_debug
{
	__forceinline void protect_process( uint32_t procId )
	{
		PEPROCESS proc;

		if ( procId && NT_SUCCESS( winapi::get_eprocess( procId, &proc ) ) )
		{
			BYTE* pEProcess = ( BYTE* ) proc;

			uint8_t* pPPL = pEProcess + 0x87a;

			uint64_t version = winapi::get_windows_number( );
			if (  version ==  WINDOWS_NUMBER_7 )
				*( DWORD* ) pPPL |= 1 << 0xB;
			else if (  version ==  WINDOWS_NUMBER_8 )
				*pPPL = true;
			else if ( version ==  WINDOWS_NUMBER_8_1 )
			{
				PS_PROTECTION protection;
				protection.Flags.Signer = PsProtectedSignerWinSystem;// = PsProtectedSignerMax for Windows 8.1
				protection.Flags.Type = PsProtectedTypeMax;
				*pPPL = protection.Level;
			}

			// process hacker can't sea PsProtectedTypeMax  and write Unknown	? WTF?!
			else if ( version ==  WINDOWS_NUMBER_10 ||  version ==  WINDOWS_NUMBER_11 )
			{
				PS_PROTECTION protection;
				protection.Flags.Signer = PsProtectedSignerMax;
				protection.Flags.Type = PsProtectedTypeMax;
				*pPPL = protection.Level;
			}

		}
	}
}