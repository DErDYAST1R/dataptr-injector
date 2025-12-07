#pragma once

namespace fusion::memory
{
	NTSTATUS read_memory(HANDLE process_handle, void* address, void* buffer, size_t size)
	{
		size_t bytes{};
		PEPROCESS target_process{};

		fusion::imports::ps_lookup_process_by_process_id(process_handle, &target_process);
		return fusion::imports::mm_copy_virutal_memory(target_process, address, PsGetCurrentProcess(), buffer, size, KernelMode, &bytes);

	}

	NTSTATUS write_memory(HANDLE process_handle, void* address, void* buffer, size_t size)
	{
		size_t bytes{};
		PEPROCESS target_process{};

		fusion::imports::ps_lookup_process_by_process_id(process_handle, &target_process);
		return fusion::imports::mm_copy_virutal_memory(IoGetCurrentProcess(), buffer, target_process, address, size, KernelMode, &bytes);
	}

	NTSTATUS CopyMemory(uint32_t CurrentProcessId, uint32_t TargetProcessId, uint64_t CurrentDestAddress, uint64_t TargetDestAddress, uint32_t MemSize)
	{
		NTSTATUS Status = STATUS_SUCCESS;

		PEPROCESS TargetProcess;
		Status = fusion::imports::ps_lookup_process_by_process_id((HANDLE)TargetProcessId, &TargetProcess);

		if (!NT_SUCCESS(Status))
			return STATUS_INVALID_CID;

		PEPROCESS CurrentProcess;
		Status = fusion::imports::ps_lookup_process_by_process_id((HANDLE)CurrentProcessId, &CurrentProcess);

		if (!NT_SUCCESS(Status))
		{
			ObDereferenceObject(CurrentProcess);
			return STATUS_INVALID_CID;
		}

		SIZE_T ReturnSize = 0;

		Status = fusion::imports::mm_copy_virutal_memory(CurrentProcess, (void*)CurrentDestAddress, TargetProcess, (void*)TargetDestAddress, MemSize, KernelMode, &ReturnSize);

		ObDereferenceObject(TargetProcess);
		ObDereferenceObject(CurrentProcess);

		return Status;
	}

	NTSTATUS FreeVirtualMemory(uint32_t TargetProcessId, PVOID BaseAddress)
	{
		NTSTATUS Status = STATUS_SUCCESS;

		PEPROCESS TargetProcess;
		Status = fusion::imports::ps_lookup_process_by_process_id((HANDLE)TargetProcessId, &TargetProcess);

		if (!NT_SUCCESS(Status))
			return STATUS_INVALID_CID;

		KAPC_STATE ApcState;
		fusion::imports::ke_stack_attach_process((PRKPROCESS)TargetProcess, &ApcState);

		SIZE_T RegionSize = 0;

		Status = fusion::imports::nt_free_virtual_memory(ZwCurrentProcess(), &BaseAddress, &RegionSize, MEM_RELEASE);

		fusion::imports::ke_unstack_detach_process(&ApcState);
		ObDereferenceObject(TargetProcess);

		return Status;
	}


	NTSTATUS ProtectVirtualMemory(uint32_t TargetProcessId, PVOID BaseAddress, SIZE_T Size, ULONG NewProtect)
	{
		NTSTATUS Status = STATUS_SUCCESS;

		PEPROCESS TargetProcess;
		Status = fusion::imports::ps_lookup_process_by_process_id((HANDLE)TargetProcessId, &TargetProcess);

		if (!NT_SUCCESS(Status))
			return STATUS_INVALID_CID;

		KAPC_STATE ApcState;
		fusion::imports::ke_stack_attach_process((PRKPROCESS)TargetProcess, &ApcState);

		ULONG OldProtect = 0;

		Status = fusion::imports::nt_protect_virtual_memory(ZwCurrentProcess(), &BaseAddress, &Size, NewProtect, &OldProtect);

		fusion::imports::ke_unstack_detach_process(&ApcState);
		NewProtect = OldProtect;
		ObDereferenceObject(TargetProcess);

		return Status;
	}


	NTSTATUS AllocateVirtualMemory(uint32_t TargetProcessId, PVOID* BaseAddress, SIZE_T Size, ULONG AllocationType, ULONG Protect)
	{
		NTSTATUS Status = STATUS_SUCCESS;

		PEPROCESS TargetProcess;
		Status = fusion::imports::ps_lookup_process_by_process_id((HANDLE)TargetProcessId, &TargetProcess);

		if (!NT_SUCCESS(Status))
			return STATUS_INVALID_CID;

		KAPC_STATE ApcState;
		fusion::imports::ke_stack_attach_process((PRKPROCESS)TargetProcess, &ApcState);

		Status = fusion::imports::nt_allocate_virtual_memory(ZwCurrentProcess(), BaseAddress, 0, &Size, AllocationType, Protect);

		fusion::imports::ke_unstack_detach_process(&ApcState);
		ObDereferenceObject(TargetProcess);

		return Status;
	}


	bool safe_copy(void* dst, void* src, size_t size)
	{
		SIZE_T bytes = 0;

		if (fusion::imports::mm_copy_virutal_memory(PsGetCurrentProcess(), src, PsGetCurrentProcess(), dst, size, KernelMode, &bytes) == STATUS_SUCCESS && bytes == size)
		{
			return true;
		}

		return false;
	}
	BOOL get_request_data(void* dest, void* src, size_t size)
	{
		size_t bytes{};
		if (NT_SUCCESS(fusion::imports::mm_copy_virutal_memory(PsGetCurrentProcess(), src, PsGetCurrentProcess(), dest, size, KernelMode, &bytes)) && size == bytes)
		{
			return true;
		}

		return false;
	}
}