#include "interface.h"
#include "../util/LazyImporter.h"

Interface::Interface(const char* kernelFunc)
{
	LI_FN(LoadLibraryA)(("user32.dll"));
	auto moduleName = ("win32u.dll");


	auto hModule = LI_FN(LoadLibraryA)(moduleName);
	if (!hModule)
		return;

	*(void**)&function_address = LI_FN(GetProcAddress)(hModule, kernelFunc);
}

bool Interface::SendRequest(void* data, request_codes code)
{
	if (!data || !code)
	{
		return false;
	}

	request_data request{ 0 };

	request.unique = request_unique;
	request.data = data;
	request.code = code;

	const auto result = function_address(&request);

	if (result != request_success)
	{
		return false;
	}

	return true;
}

bool Interface::ConnectToDriver()
{
	driver_init data{ 0 };

	data.init = 0;

	SendRequest(&data, init_driver);

	return data.init;
}
//
bool Interface::Unload()
{
	unload_request data{ 0 };

	data.buffer = 0;

	SendRequest(&data, request_unload);

	return data.buffer;
}

void Interface::ProectProcess(int pid)
{
	process_request_t data{ 0 };

	data.process_id = pid;

	SendRequest(&data, protect_process);
}

bool Interface::ReadPhysical(const int pid, const std::uintptr_t address, void* buffer, const std::size_t size)
{
	read_request data{ 0 };

	data.pid = pid;
	data.address = address;
	data.buffer = buffer;
	data.size = size;

	return SendRequest(&data, read_memory);
}

uintptr_t Interface::BaseAddress(int pid, const char* module)
{
	base_request data{ 0 };

	data.pid = pid;
	data.name = module;

	SendRequest(&data, get_base);

	return data.handle;
}

bool Interface::WritePhysical(const int pid, const std::uintptr_t address, void* buffer, const std::size_t size)
{
	write_request data{ 0 };

	data.pid = pid;
	data.address = address;
	data.buffer = buffer;
	data.size = size;

	return SendRequest(&data, write_memory);
}

NTSTATUS Interface::CopyVirtualMemory(ULONGLONG srcPid, uintptr_t srcAddr, ULONGLONG targetPid, uintptr_t targetAddr, SIZE_T size)
{
	copy_request serverRequest{ 0 };

	serverRequest.sourcePid = srcPid;
	serverRequest.sourceAddress = srcAddr;

	serverRequest.targetPid = targetPid;
	serverRequest.targetAddress = targetAddr;

	serverRequest.size = size;

	SendRequest(&serverRequest, copy_memory);

	return (NTSTATUS)serverRequest.size;
}

NTSTATUS Interface::FreeVirtualMemory(ULONGLONG targetPid, uintptr_t address)
{
	free_request serverRequest{ 0 };

	serverRequest.targetPid = targetPid;
	serverRequest.address = address;

	SendRequest(&serverRequest, free_memory);

	return NTSTATUS(serverRequest.code);
}

NTSTATUS Interface::ProtectVirtualMemory(ULONGLONG targetPid, size_t size, uint32_t protect, uintptr_t sourceAddress)
{
	protect_request serverRequest{ 0 };
	serverRequest.targetPid = targetPid;
	serverRequest.sourceAddress = sourceAddress;

	serverRequest.protect = protect;

	serverRequest.size = size;

	SendRequest(&serverRequest, protect_memory);

	return NTSTATUS(serverRequest.code);
}

uint64_t Interface::AllocateVirtualMemory(ULONGLONG targetPid, size_t size, uint32_t allocationType, uint32_t protect, uintptr_t sourceAddress)
{
	allocate_request serverRequest{ 0 };


	serverRequest.targetPid = targetPid;
	serverRequest.sourceAddress = sourceAddress;

	serverRequest.allocationType = allocationType;
	serverRequest.protect = protect;

	serverRequest.size = size;
	
	SendRequest(&serverRequest, alloc_memory);

	return serverRequest.targetAddress;
}

bool Interface::CallEntryPoint(ULONGLONG targetPid, uintptr_t address, uintptr_t stub)
{
	call_entry_request serverRequest{ 0 };

	serverRequest.process_id = (HANDLE)targetPid;
	serverRequest.address = address;
	serverRequest.shellcode = stub;

	SendRequest(&serverRequest, call_entry);

	return serverRequest.result;
}