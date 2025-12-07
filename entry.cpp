#include "include.h"

#include <ntddk.h>

#define REGISTRY_PATH L"\\Registry\\Machine\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"
#define REGISTRY_VALUE L"UBR"

NTSTATUS ReadRegistryValue(PUNICODE_STRING RegistryPath, PUNICODE_STRING ValueName, PULONG Value) {
	NTSTATUS status;
	HANDLE keyHandle;
	OBJECT_ATTRIBUTES objectAttributes;
	ULONG resultLength;
	PKEY_VALUE_PARTIAL_INFORMATION keyValueInformation;

	InitializeObjectAttributes(&objectAttributes, RegistryPath, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	status = ZwOpenKey(&keyHandle, KEY_READ, &objectAttributes);
	if (!NT_SUCCESS(status)) {
		return status;
	}

	ULONG bufferSize = sizeof(KEY_VALUE_PARTIAL_INFORMATION) + sizeof(ULONG);
	keyValueInformation = (PKEY_VALUE_PARTIAL_INFORMATION)ExAllocatePoolWithTag(PagedPool, bufferSize, 'regV');

	if (!keyValueInformation) {
		ZwClose(keyHandle);
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	status = ZwQueryValueKey(keyHandle, ValueName, KeyValuePartialInformation, keyValueInformation, bufferSize, &resultLength);

	if (NT_SUCCESS(status) && keyValueInformation->Type == REG_DWORD && keyValueInformation->DataLength == sizeof(ULONG)) {
		*Value = *(PULONG)keyValueInformation->Data;
	}

	ExFreePoolWithTag(keyValueInformation, 'regV');
	ZwClose(keyHandle);

	return status;
}

NTSTATUS driver_entry( uintptr_t magic_key, PDRIVER_OBJECT driver_object )
{
	UNREFERENCED_PARAMETER( driver_object );
#ifndef DEBUG_OUTPUT
	auto mapper_token = fusion::security::generate_mapper_token( );
	TRACE( "0x%llx", mapper_token );

	if ( magic_key != mapper_token )
	{
		return STATUS_ABANDONED;
	}
#endif

	if ( fusion::winapi::offsets::setup( ) )
	{
		auto ntoskrnl = fusion::winapi::get_module_handle<void*>( _( "win32k.sys" ) );
		TRACE( "win32k: 0x%llx", ntoskrnl );

		//set_vad();

		RTL_OSVERSIONINFOW  lpVersionInformation{ 0 };
		lpVersionInformation.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW);

		auto RtlGetVersion = (t_RtlGetVersion)fusion::winapi::get_proc_address(fusion::winapi::get_module_handle<uintptr_t>(_("ntoskrnl.exe")), _("RtlGetVersion"));
		if (RtlGetVersion)
		{
			RtlGetVersion(&lpVersionInformation);
		}
		else
		{
			auto buildNumber = (PDWORD64)fusion::winapi::get_proc_address(fusion::winapi::get_module_handle<uintptr_t>(_("ntoskrnl.exe")), _("NtBuildNumber"));

			lpVersionInformation.dwBuildNumber = *buildNumber;
			lpVersionInformation.dwMajorVersion = *(ULONG*)0xFFFFF7800000026C;
			lpVersionInformation.dwMinorVersion = *(ULONG*)0xFFFFF78000000270;

		}

		uintptr_t function = 0x0;

		UNICODE_STRING registryPath = RTL_CONSTANT_STRING(REGISTRY_PATH);
		UNICODE_STRING valueName = RTL_CONSTANT_STRING(REGISTRY_VALUE);
		ULONG ubrValue = 0;

		NTSTATUS status = ReadRegistryValue(&registryPath, &valueName, &ubrValue);


		switch (lpVersionInformation.dwBuildNumber)
		{
		case WIN_1123H2:
		{
			// win10 ltsc 21h2
			//48 8B 05 55 77 06 00
			//48 8B 05 15 77 06 00
			if (!function)
				function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
					("\x48\x8B\x05\x55\x77\x06\x00"), _("xxxxxx?"));
			//48 8B 05 85 A4 06 00
			break;
		}
		case WIN_1121H2:
		{
			// win10 ltsc 21h2
			if (!function)
				function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
					("\x48\x8B\x05\xB9\x99\x06\x00"), _("xxxxxx?"));
			break;
		}
		case WIN_22H2:
		{

			
			
				//48 8B 05 E9 E9 05 00
				if (!function)
					function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
						("\x48\x8B\x05\xE9\xE9\x05\x00"), _("xxxxxx?"));

				//48 8B 05 25 09 06 00 
			

			//if (ubrValue == 3803)
			//{
			//	if (!function)
			//		function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
			//			("\x48\x8B\x05\x25\x09\x06\x00"), _("xxxxxx?"));

			//	//48 8B 05 25 09 06 00 
			//}
			//else if (ubrValue == 4529)
			//{
			//	if (!function)
			//		function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
			//			("\x48\x8B\x05\x65\x09\x06\x00"), _("xxxxxx?"));

			//	//48 8B 05 65 09 06 00
			//	//48 8B 05 25 09 06 00 
			//}
			//else if (ubrValue == 2006)
			//{
			//	if (!function)
			//		function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
			//			("\x48\x8B\x05\x25\xF9\x05\x00"), _("xxxxxx?"));

			//	//48 8B 05 25 F9 05 00
			//	//48 8B 05 65 09 06 00
			//	//48 8B 05 25 09 06 00 
			//}
			//else if (ubrValue == 3930)
			//{
			//	if (!function)
			//		function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
			//			("\x48\x8B\x05\x25\x09\x06\x00"), _("xxxxxx?"));
			//}
			//else
			//{
			//	// win10 ltsc 21h2
			//	if (!function)
			//		function = fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
			//			("\x48\x8B\x05\x65\x09\x06\x00"), _("xxxxxx?"));

			//	//48 8B 05 41 09 06 00 // disconnect
			//	// 48 8B 05 65 09 06 00 // connect

			//	//48 8B 05 41 09 06 00
			//}
		
			// 

			break;
		}
		}
	
		//48 8B 05 65 09 06 00


		if ( !function )
		{
			TRACE("CANT FIND FUNC - %p", address);
			return STATUS_SUCCESS;
		}

		address = RVA( function, 7 );
		TRACE( "address: 0x%llx", address );


		*( void** ) &o_NtUserDoSoundConnect = InterlockedExchangePointer( ( volatile PVOID* ) address, hk_ntuser_do_connect);

		return STATUS_SUCCESS;
	}

	return STATUS_ABANDONED;
}