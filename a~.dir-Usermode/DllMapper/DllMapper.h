#pragma once

#include "Windows.h"
#include "../interface/interface.h"


inline int localPid;

inline uint64_t AllocateMemory(size_t size, uint32_t allocation_type, uint32_t protect)
{
	uint64_t address = 0;
	return kInterface->AllocateVirtualMemory(localPid, size, allocation_type, protect, address);
}
inline NTSTATUS ReadBuffer(uint64_t address, LPVOID lpBuffer, SIZE_T nSize) {
	if (lpBuffer == nullptr)
		return STATUS_INVALID_PARAMETER;

	return kInterface->ReadPhysical(localPid, address, lpBuffer, nSize);
}
inline uint64_t GetModuleBase(const char* moduleName)
{
	return kInterface->BaseAddress(localPid, moduleName);
}
inline NTSTATUS WriteMemory(uint64_t address, uintptr_t dstAddress, SIZE_T nSize) {
	if (dstAddress == 0) {
		return STATUS_INVALID_PARAMETER;
	}
	return kInterface->WritePhysical(localPid, address, reinterpret_cast<void*>(dstAddress), nSize);
}
inline NTSTATUS ProtectMemory(uint64_t address, size_t size, uint32_t protect)
{
	return kInterface->ProtectVirtualMemory(localPid, size, protect, address);
}
inline NTSTATUS FreeMemory(uint64_t address)
{
	return kInterface->FreeVirtualMemory(localPid, address);
}
template<typename T>
inline T Read(uint64_t address)
{
	T buffer{ };
	ReadBuffer(address, &buffer, sizeof(T));
	return buffer;
}


class DllMapper {
public:
	static PVOID LoadLocalImageFromBytes(const unsigned char* imageBytes, DWORD fileSize); // load dll from bytes

	static PVOID LoadLocalImageFromDisk(const char* imagePath); // load dll from disk
	static BOOL LoadModule(PVOID LocalImage, bool Delay);
};
