#pragma once

namespace fusion::winapi
{
	template<typename _ty> __forceinline _ty get_module_handle(const char* module_name = nullptr)
	{
		void* moduleBase = NULL;
		ULONG info = 0;
		NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, 0, info, &info);

		if (!info)
		{
			return reinterpret_cast<_ty>(moduleBase);
		}

		PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPool, info, 'NEGR');

		status = ZwQuerySystemInformation(SystemModuleInformation, modules, info, &info);

		if (!NT_SUCCESS(status))
		{
			return reinterpret_cast<_ty>(moduleBase);
		}

		PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
		if (modules->NumberOfModules > 0)
		{
			if (!module_name)
			{
				moduleBase = modules->Modules[0].ImageBase;
			}
			else
			{
				for (auto i = 0; i < modules->NumberOfModules; i++)
				{
					if (strstr((CHAR*)module[i].FullPathName, module_name))
					{
						moduleBase = module[i].ImageBase;
					}
				}
			}
		}

		if (modules)
		{
			ExFreePoolWithTag(modules, 'NEGR');
		}

		return reinterpret_cast<_ty>(moduleBase);
	}

	__forceinline PIMAGE_NT_HEADERS get_nt_header(PVOID module)
	{
		return (PIMAGE_NT_HEADERS)((PBYTE)module + PIMAGE_DOS_HEADER(module)->e_lfanew);
	}

	template<typename _ty> __forceinline _ty find_pattern(PVOID module, DWORD size, LPCSTR pattern, LPCSTR mask)
	{

		auto checkMask = [](PBYTE buffer, LPCSTR pattern, LPCSTR mask) -> BOOL
			{
				for (auto x = buffer; *mask; pattern++, mask++, x++)
				{
					auto addr = *(BYTE*)(pattern);
					if (addr != *x && *mask != '?')
						return FALSE;
				}

				return TRUE;
			};

		for (auto x = 0; x < size - strlen(mask); x++)
		{

			auto addr = (PBYTE)module + x;
			if (checkMask(addr, pattern, mask))
				return reinterpret_cast<_ty>(addr);
		}

		return NULL;
	}

	template<typename _ty> __forceinline _ty find_pattern(void* base_address, const char* pattern, const char* mask)
	{
		auto header = get_nt_header(base_address);
		auto section = IMAGE_FIRST_SECTION(header);

		for (auto x = 0; x < header->FileHeader.NumberOfSections; x++, section++)
		{
			if (!memcmp(section->Name, _(".text"), 5) || !memcmp(section->Name, _("PAGE"), 4))
			{
				auto addr = find_pattern<PBYTE>((PBYTE)base_address + section->VirtualAddress, section->Misc.VirtualSize, pattern, mask);
				if (addr)
				{
					return reinterpret_cast<_ty>(addr);
				}
			}
		}

		return NULL;
	}

	__forceinline NTSTATUS get_module_base_address(int process_id, const char* module_name, uintptr_t* base_address)
	{
		ANSI_STRING ansiString;
		UNICODE_STRING compareString;
		KAPC_STATE state;
		NTSTATUS status = STATUS_UNSUCCESSFUL;
		PEPROCESS process = NULL;
		PPEB pPeb = NULL;

		RtlInitAnsiString(&ansiString, module_name);
		RtlAnsiStringToUnicodeString(&compareString, &ansiString, TRUE);

		if (!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)process_id, &process)))
			return STATUS_UNSUCCESSFUL;

		KeStackAttachProcess(process, &state);
		pPeb = PsGetProcessPeb(process);

		if (pPeb)
		{
			PPEB_LDR_DATA pLdr = (PPEB_LDR_DATA)pPeb->Ldr;

			if (pLdr)
			{
				for (PLIST_ENTRY list = (PLIST_ENTRY)pLdr->InMemoryOrderModuleList.Flink; list != &pLdr->InMemoryOrderModuleList; list = (PLIST_ENTRY)list->Flink)
				{
					PLDR_DATA_TABLE_ENTRY pEntry = CONTAINING_RECORD(list, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

					if (RtlCompareUnicodeString(&pEntry->BaseDllName, &compareString, TRUE) == 0)
					{
						*base_address = (uint64_t)pEntry->DllBase;
						status = STATUS_SUCCESS;
						break;
					}
				}
			}
		}
		KeUnstackDetachProcess(&state);
		RtlFreeUnicodeString(&compareString);
		return status;
	}

	__forceinline uintptr_t	get_proc_address(const uintptr_t imageBase, const char* exportName)
	{
		if (!imageBase)
			return 0;

		if (reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase)->e_magic != 0x5A4D)
			return 0;

		const auto ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS64>(imageBase + reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase)->e_lfanew);
		const auto exportDirectory = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(imageBase + ntHeader->OptionalHeader.DataDirectory[0].VirtualAddress);
		if (!exportDirectory)
			return 0;

		const auto exportedFunctions = reinterpret_cast<DWORD*>(imageBase + exportDirectory->AddressOfFunctions);
		const auto exportedNames = reinterpret_cast<DWORD*>(imageBase + exportDirectory->AddressOfNames);
		const auto exportedNameOrdinals = reinterpret_cast<UINT16*>(imageBase + exportDirectory->AddressOfNameOrdinals);

		for (size_t i{}; i < exportDirectory->NumberOfNames; ++i)
		{
			const auto functionName = reinterpret_cast<const char*>(imageBase + exportedNames[i]);
			if (fusion::string::stricmp(exportName, functionName) == 0)
			{
				return imageBase + exportedFunctions[exportedNameOrdinals[i]];
			}
		}

		return 0;
	}

	namespace offsets
	{

		static UINT offset_unique_process_id = 0x0;
		static UINT offset_active_process_links = 0x0;
		static UINT offset_image_file_name = 0x0;
		static UINT offset_active_threads = 0x0;
		static uint64_t* ps_initial_system_process = 0x0;

		__forceinline bool setup()
		{
			ps_initial_system_process = (uint64_t*)winapi::get_proc_address(winapi::get_module_handle<uintptr_t>(_("ntoskrnl.exe")), _("PsInitialSystemProcess"));

			PEPROCESS SystemProcess = (PEPROCESS)*ps_initial_system_process;

			for (int i = 0; i < 0xFFF; i++) // 0xFFF larger than the size of full struct
			{
				if (!offset_unique_process_id && !offset_active_process_links)
				{
					if (
						*(UINT64*)((UINT64)SystemProcess + i) == 4 && // 4 always, pid of system process
						*(UINT64*)((UINT64)SystemProcess + i + 0x8) > 0xFFFF000000000000)  // > 0xFFFF000000000000 always
					{
						offset_unique_process_id = i;
						offset_active_process_links = i + 0x8;
					}
				}
				if (!offset_image_file_name && !offset_active_threads)
				{
					if (*(UINT64*)((UINT64)SystemProcess + i) > 0x0000400000000000 && *(UINT64*)((UINT64)SystemProcess + i) < 0x0000800000000000 && // 0x00006D6574737953 always, but better to make range
						*(UINT64*)((UINT64)SystemProcess + i + 0x48) > 0 && *(UINT64*)((UINT64)SystemProcess + i + 0x48) < 0xFFF) // 80 ~ 300 in general
					{
						offset_image_file_name = i;
						offset_active_threads = i + 0x48;
					}
				}

				if (offset_unique_process_id && offset_active_process_links && offset_image_file_name && offset_active_threads)
				{
					return true;
				}
			}

			return false;
		}
	}

	__forceinline uint64_t get_windows_number()
	{
		RTL_OSVERSIONINFOW  lpVersionInformation{ 0 };
		lpVersionInformation.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW);

		auto RtlGetVersion = (t_RtlGetVersion)get_proc_address(get_module_handle<uintptr_t>(_("ntoskrnl.exe")), _("RtlGetVersion"));
		if (RtlGetVersion)
		{
			RtlGetVersion(&lpVersionInformation);
		}
		else
		{
			auto buildNumber = (PDWORD64)get_proc_address(get_module_handle<uintptr_t>(_("ntoskrnl.exe")), _("NtBuildNumber"));

			lpVersionInformation.dwBuildNumber = *buildNumber;
			lpVersionInformation.dwMajorVersion = *(ULONG*)0xFFFFF7800000026C;
			lpVersionInformation.dwMinorVersion = *(ULONG*)0xFFFFF78000000270;

		}

		if (lpVersionInformation.dwBuildNumber >= WIN_1121H2)
			return WINDOWS_NUMBER_11;
		else if (lpVersionInformation.dwBuildNumber >= WIN_1507 && lpVersionInformation.dwBuildNumber <= WIN_21H2)
			return WINDOWS_NUMBER_10;
	}

	__forceinline  NTSTATUS get_eprocess(uint32_t procId, OUT PEPROCESS* pProcessInfo)
	{

		PEPROCESS SystemProcess = (PEPROCESS)*offsets::ps_initial_system_process;
		PEPROCESS CurrentProcess = SystemProcess;

		do
		{
			if (*(uint64_t*)((UINT64)CurrentProcess + offsets::offset_unique_process_id) == (uint64_t)procId)
			{
				if (*(UINT*)((UINT64)CurrentProcess + offsets::offset_active_threads))
				{
					*pProcessInfo = CurrentProcess;
					return STATUS_SUCCESS;
				}
			}

			PLIST_ENTRY List = (PLIST_ENTRY)((UINT64)(CurrentProcess)+offsets::offset_active_process_links);
			CurrentProcess = (PEPROCESS)((UINT64)List->Flink - offsets::offset_active_process_links);

		} while (CurrentProcess != SystemProcess);

		return STATUS_NOT_FOUND;
	}
}