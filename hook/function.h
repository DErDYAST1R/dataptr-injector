#pragma once
#include <intrin.h>
#include "safe_memory.h"


__int64( __fastcall* o_NtUserDoSoundConnect)( PVOID );
PBYTE address = 0x0;
#pragma optimize("", off)


//
//
//enum status : int
//{
//	success = STATUS_SUCCESS,
//	failure = STATUS_UNSUCCESSFUL
//};
//
//
//PMMVAD_SHORT(*mi_allocate_vad)(UINT_PTR start, UINT_PTR end, LOGICAL deletable);
//
//NTSTATUS(*mi_insert_vad_charges)(PMMVAD_SHORT vad, PEPROCESS process);
//
//VOID(*mi_insert_vad)(PMMVAD_SHORT vad, PEPROCESS process);
//#define in_range(x,a,b)    (x >= a && x <= b) 
//#define get_bits( x )    (in_range((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xA) : (in_range(x,'0','9') ? x - '0' : 0))
//#define get_byte( x )    (get_bits(x[0]) << 4 | get_bits(x[1]))
//#define rva(addr, size)       ((uintptr_t)((uintptr_t)(addr) + *(int*)((uintptr_t)(addr) + ((size) - sizeof(INT))) + (size)))
//
//
//auto set_vad() -> status
//{
//	auto ntoskrnl = fusion::winapi::get_module_handle<void*>(_("ntoskrnl.exe"));
//
//	//mi_allocate_vad
//	uintptr_t faddr =
//		fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
//			("\x44\x8D\x42\x02\xE8\x00\x00\x00\x00\x48\x89\x43\x08"), _("xxxxx????xxxx"));
//
//	if (!faddr) return status::failure;
//
//	faddr += 4;
//	faddr = rva(faddr, 5);
//
//	mi_allocate_vad = (decltype(mi_allocate_vad))faddr;
//
//	//mi_insert_vad_charges
//	faddr =
//		fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
//			("\xE8\x00\x00\x00\x00\x8B\xF0\x85\xC0\x0F\x88\x00\x00\x00\x00\x48\x8B\xD3"), _("x????xxxxxx????xxx"));
//	//pattern::find_pattern((uintptr_t)ntoskrnl, "\xE8\x00\x00\x00\x00\x8B\xF0\x85\xC0\x0F\x88\x00\x00\x00\x00\x48\x8B\xD3", "x????xxxxxx????xxx");
//	if (!ntoskrnl) return status::failure;
//
//	faddr = rva(faddr, 5);
//
//	mi_insert_vad_charges = (decltype(mi_insert_vad_charges))faddr;
//
//	//mi_insert_vad
//	faddr =
//		fusion::winapi::find_pattern<uintptr_t>(ntoskrnl,
//			("\xE8\x00\x00\x00\x00\x8B\x5B\x30"), _("x????xxx"));
//	//pattern::find_pattern((uintptr_t)ntoskrnl, "\xE8\x00\x00\x00\x00\x8B\x5B\x30", "x????xxx");
//	if (!ntoskrnl) return status::failure;
//
//	faddr = rva(faddr, 5);
//
//	mi_insert_vad = (decltype(mi_insert_vad))faddr;
//
//	return status::success;
//}
//
//#define MM_EXECUTE_READWRITE   0x6
//
//
//auto allocate_memory(allocate_request data) -> status
//{
//
//	auto process = PEPROCESS();
//	fusion::imports::ps_lookup_process_by_process_id((HANDLE)data.targetPid, &process);
//
//	uintptr_t start = data.sourceAddress;
//	uintptr_t end = start + data.size;
//
//	auto o_process = attach_process((uintptr_t)process);
//
//	MEMORY_BASIC_INFORMATION mbi;
//	if (ZwQueryVirtualMemory(ZwCurrentProcess(), (PVOID)start, MemoryBasicInformation, &mbi, sizeof(mbi), 0) != status::success)
//	{
//		attach_process(o_process);
//		ObfDereferenceObject(process);
//
//		return status::failure;
//	}
//
//
//	PMMVAD_SHORT vad = mi_allocate_vad(start, end, 1);
//	if (!vad)
//	{
//		attach_process(o_process);
//		ObfDereferenceObject(process);
//
//		data.sourceAddress = 0;
//
//		return status::failure;
//	}
//
//	PMMVAD_FLAGS flags = (PMMVAD_FLAGS)&vad->u.LongFlags;
//	flags->Protection = MM_EXECUTE_READWRITE;
//	flags->NoChange = 0;
//
//	if (mi_insert_vad_charges(vad, process) != status::success)
//	{
//		attach_process(o_process);
//		ObfDereferenceObject(process);
//
//		ExFreePoolWithTag(vad, NULL);
//
//		data.sourceAddress = 0;
//
//		return status::failure;
//	}
//
//	mi_insert_vad(vad, process);
//
//	attach_process(o_process);
//	ObfDereferenceObject(process);
//
//	data.sourceAddress = start;
//
//	return status::success;
//}

__int64 __fastcall hk_ntuser_do_connect( PVOID a1)
{
	static bool once = true;

	if (once)
	{
		TRACE("Hooked!");

		once = false;
	}
	if (fusion::imports::ex_get_previous_mode() != UserMode)
	{
		return o_NtUserDoSoundConnect(a1);
	}

	const auto request = reinterpret_cast<request_data*>(a1);

	if (request->unique != request_unique)
		return o_NtUserDoSoundConnect(a1);

	switch (request->code)
	{
	case init_driver:
	{
		driver_init data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(driver_init)))
		{
			return 0;
		}

		reinterpret_cast<driver_init*> (request->data)->init = true;
		TRACE("successfully init driver!");

		return request_success;
	}
	case get_base:
	{
		base_request data{ 0 };

		if (!fusion::memory::safe_copy(&data, request->data, sizeof(base_request)))
		{
			return 0;
		}

		if (!data.name || !data.pid)
		{
			return 0;
		}

		uintptr_t address{};
		//TRACE("base_request: %s", base_request->module_name);

		if (NT_SUCCESS(fusion::winapi::get_module_base_address(data.pid, data.name, &address)))
		{
			TRACE("\"%s\" on process %d = 0x%llx", data.name, data.pid, address);

			reinterpret_cast<base_request*> (request->data)->handle = address;
		}
		else
		{
			TRACE("failed to get \"%s\" on process %d", data.name, data.pid);
		}

		//reinterpret_cast<base_request*> (request->data)->handle = base;

		return request_success;
	}
	case read_memory:
	{
		read_request data{ 0 };

		if (!fusion::memory::safe_copy(&data, request->data, sizeof(read_request)))
		{
			return 0;
		}

		if (!data.address || !data.pid || !data.buffer || !data.size)
		{
			return 0;
		}

		SIZE_T read;
		ReadProcessMemory(data.pid, (PVOID)data.address, data.buffer, data.size, &read);

		return request_success;
	}
	case write_memory:
	{

		write_request data{ 0 };

		if (!fusion::memory::safe_copy(&data, request->data, sizeof(write_request)))
		{
			return 0;
		}

		if (!data.address || !data.pid || !data.buffer || !data.size)
		{
			return 0;
		}

		SIZE_T written;
		WriteProcessMemory(data.pid, (PVOID)data.address, data.buffer, data.size, &written);

		return request_success;
	}
	case alloc_memory:
	{

		allocate_request data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(allocate_request)))
		{
			return 0;
		}


	//	auto code = allocate_memory(data);
		auto status = fusion::memory::AllocateVirtualMemory(data.targetPid, (PVOID*)&data.sourceAddress, data.size, data.allocationType, data.protect);

		reinterpret_cast<allocate_request*> (request->data)->targetAddress = data.sourceAddress;
		reinterpret_cast<allocate_request*> (request->data)->code = status;

		return request_success;
	}
	case protect_memory:
	{

		protect_request data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(protect_request)))
		{
			return 0;
		}

		auto status = fusion::memory::ProtectVirtualMemory(data.targetPid, (PVOID)data.sourceAddress, data.size, data.protect);
		reinterpret_cast<protect_request*> (request->data)->code = status;
		reinterpret_cast<protect_request*> (request->data)->protect = data.protect;



		return request_success;
	}
	case free_memory:
	{

		free_request data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(free_request)))
		{
			return 0;
		}

		auto status = fusion::memory::FreeVirtualMemory(data.targetPid, (PVOID)data.address);

		reinterpret_cast<protect_request*> (request->data)->code = status;

		return request_success;
	}
	case copy_memory:
	{
		copy_request data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(copy_request)))
		{
			return 0;
		}

		auto status = fusion::memory::CopyMemory(data.sourcePid, data.targetPid, data.sourceAddress, data.targetAddress, data.size);

		reinterpret_cast<protect_request*> (request->data)->size = status;

		return request_success;
	}
	case protect_process:
	{
		process_request_t data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(process_request_t)))
		{
			return 0;
		}

		fusion::anti_debug::protect_process(data.process_id);
		break;
	}

	case request_unload:
	{
		unload_request data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(unload_request)))
		{
			return 0;
		}

		reinterpret_cast<unload_request*> (request->data)->buffer = true;

		InterlockedExchangePointer((void**)address, (void**)o_NtUserDoSoundConnect);
		break;
	}
	case call_entry:
	{
		call_entry_request data{ 0 };
		if (!fusion::memory::safe_copy(&data, request->data, sizeof(call_entry_request)))
		{
			return 0;
		}


		auto address = reinterpret_cast<PVOID>(data.address);
		auto shellcode = reinterpret_cast<PVOID>(data.shellcode);
		auto process_id = data.process_id;


		TRACE("data.address = 0x%llx", address);
		TRACE("data.shellcode = 0x%llx", shellcode);
		TRACE("data.process_id = %d", process_id);

		KAPC_STATE apc_state{ };
		PEPROCESS process{};
		bool result = false;

		if (PsLookupProcessByProcessId(process_id, &process) == STATUS_SUCCESS)
		{
			fusion::imports::ke_stack_attach_process(process, &apc_state);
			{
				auto size = sizeof(uint64_t);

				ULONG old_protect{};
				fusion::imports::nt_protect_virtual_memory(((HANDLE)(LONG_PTR)-1), &address, &size, PAGE_READWRITE, &old_protect);
				if (NT_SUCCESS(fusion::memory::write_memory(process_id, address, shellcode, sizeof(uint64_t))))
				{
					if (address != nullptr)
					{
						fusion::imports::nt_protect_virtual_memory(((HANDLE)(LONG_PTR)-1), &address, &size, PAGE_READONLY, &old_protect);
					}
					result = true;

				}
			}
			fusion::imports::ke_unstack_detach_process(&apc_state);

			reinterpret_cast<call_entry_request*> (request->data)->result = result;
		}


		return request_success;
	}
	}

	return NULL;
}

#pragma optimize("", on)
