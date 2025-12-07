#pragma once
#define find_function( mod, func ) fusion::winapi::get_proc_address( fusion::winapi::get_module_handle<uintptr_t>( _( mod ) ), _( func ) )

namespace fusion::imports
{
	NTSTATUS
		mm_copy_memory(
			PVOID TargetAddress,
			MM_COPY_ADDRESS SourceAddress,
			SIZE_T NumberOfBytes,
			ULONG Flags,
			PSIZE_T NumberOfBytesTransferred
		)
	{
		using fn = NTSTATUS(*)(PVOID, MM_COPY_ADDRESS, SIZE_T, ULONG, PSIZE_T);
		auto fn_mm_copy_mem = (fn)(find_function("ntoskrnl.exe", "MmCopyMemory"));

		return fn_mm_copy_mem(TargetAddress, SourceAddress, NumberOfBytes, Flags, NumberOfBytesTransferred);
	}


	NTSTATUS mm_copy_virutal_memory(PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress, SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode, PSIZE_T ReturnSize)
	{
		using fn = NTSTATUS(*)(PEPROCESS, PVOID, PEPROCESS, PVOID, SIZE_T, KPROCESSOR_MODE, PSIZE_T);
		auto fn_mm_copy_virtual_memory = (fn)(find_function("ntoskrnl.exe", "MmCopyVirtualMemory"));

		return fn_mm_copy_virtual_memory(SourceProcess, SourceAddress, TargetProcess, TargetAddress, BufferSize, PreviousMode, ReturnSize);
	}

	NTSTATUS ps_lookup_process_by_process_id(HANDLE process_id, PEPROCESS* process)
	{
		using fn = NTSTATUS(*)(HANDLE, PEPROCESS*);
		auto fn_ps_lookup_process_by_process_id = (fn)(find_function("ntoskrnl.exe", "PsLookupProcessByProcessId"));

		return fn_ps_lookup_process_by_process_id(process_id, process);
	}

	NTSTATUS nt_allocate_virtual_memory(HANDLE ProcessHandle, PVOID* BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect)
	{
		using fn = NTSTATUS(*)(HANDLE, PVOID*, ULONG_PTR, PSIZE_T, ULONG, ULONG);
		auto fn_nt_allocate_virtual_memory = (fn)(find_function("ntoskrnl.exe", "ZwAllocateVirtualMemory"));

		return fn_nt_allocate_virtual_memory(ProcessHandle, BaseAddress, ZeroBits, RegionSize, AllocationType, Protect);
	}

	NTSTATUS nt_free_virtual_memory(HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, ULONG FreeType)
	{
		using fn = NTSTATUS(*)(HANDLE, PVOID*, PSIZE_T, ULONG);
		auto fn_nt_allocate_virtual_memory = (fn)(find_function("ntoskrnl.exe", "ZwFreeVirtualMemory"));

		return fn_nt_allocate_virtual_memory(ProcessHandle, BaseAddress, RegionSize, FreeType);
	}

	NTSTATUS nt_protect_virtual_memory(HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, ULONG newProtection, PULONG OldProtection)
	{
		using fn = NTSTATUS(*)(HANDLE, PVOID*, PSIZE_T, ULONG, PULONG);
		auto fn_nt_protect_virtual_memory = (fn)(find_function("ntoskrnl.exe", "ZwProtectVirtualMemory"));

		return fn_nt_protect_virtual_memory(ProcessHandle, BaseAddress, RegionSize, newProtection, OldProtection);
	}

	void ke_stack_attach_process(PRKPROCESS PROCESS, PRKAPC_STATE ApcState)
	{
		using fn = void(*)(PRKPROCESS, PRKAPC_STATE);
		auto fn_ke_stack_attach_process = (fn)(find_function("ntoskrnl.exe", "KeStackAttachProcess"));

		return fn_ke_stack_attach_process(PROCESS, ApcState);
	}

	void ke_unstack_detach_process(PRKAPC_STATE ApcState)
	{
		using fn = void(*)(PRKAPC_STATE);
		auto fn_ke_unstack_detach_process = (fn)(find_function("ntoskrnl.exe", "KeUnstackDetachProcess"));

		return fn_ke_unstack_detach_process(ApcState);
	}

	KPROCESSOR_MODE ex_get_previous_mode()
	{
		using fn = KPROCESSOR_MODE(*)();
		auto fn_ex_get_previous_mode = (fn)(find_function("ntoskrnl.exe", "ExGetPreviousMode"));

		return fn_ex_get_previous_mode();
	}

	NTSTATUS nt_query_system_information(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, PULONG returnLength)
	{
		using fn = NTSTATUS(*)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);
		auto fn_nt_allocate_virtual_memory = (fn)(find_function("ntoskrnl.exe", "ZwQuerySystemInformation"));

		return fn_nt_allocate_virtual_memory(systemInformationClass, systemInformation, systemInformationLength, returnLength);
	}

}