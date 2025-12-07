#pragma once
#include "comms.h"
#include <cstddef>
#include <string>

inline __int64(__fastcall* function_address)(void*) = nullptr;


class Interface {
public:
	Interface( const char* kernelFunc);

	bool ConnectToDriver();
	bool ReadPhysical(const int pid, const std::uintptr_t address, void* buffer, const std::size_t size);
	template <typename t>
	t ReadPhysical(const int pid, const std::uintptr_t address)
	{
		t response{ };
		ReadPhysical(pid, address, &response, sizeof(t));
		return response;
	}

	bool WritePhysical(const int pid, const std::uintptr_t address, void* buffer, const std::size_t size);

	template <typename t>
	bool WritePhysical(const int pid, const std::uintptr_t address, t value)
	{
		return WritePhysical(pid, address, &value, sizeof(t));
	}
	uintptr_t BaseAddress(int pid, const char* module);
	bool Unload();
	void* AllocateMemory(const std::size_t size, std::uintptr_t* mdl);
	bool SendRequest(void* data, request_codes code);

	void ProectProcess(int pid);

	uint64_t AllocateVirtualMemory(ULONGLONG targetPid, size_t size, uint32_t allocationType, uint32_t protect, uintptr_t sourceAddress);
	NTSTATUS CopyVirtualMemory(ULONGLONG srcPid, uintptr_t srcAddr, ULONGLONG targetPid, uintptr_t targetAddr, SIZE_T size);
	NTSTATUS ProtectVirtualMemory( ULONGLONG targetPid, size_t size, uint32_t protect, uintptr_t sourceAddress);
	NTSTATUS FreeVirtualMemory(ULONGLONG targetPid, uintptr_t address);

	bool CallEntryPoint(ULONGLONG targetPid, uintptr_t address, uintptr_t stub);
};

extern Interface* kInterface;