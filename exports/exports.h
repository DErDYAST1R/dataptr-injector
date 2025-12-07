#pragma once

extern "C"
{
	NTKERNELAPI NTSTATUS IoCreateDriver( PUNICODE_STRING DriverName, PDRIVER_INITIALIZE InitializationFunction );
	NTKERNELAPI NTSTATUS MmCopyVirtualMemory( PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress, SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode, PSIZE_T ReturnSize );
	NTKERNELAPI NTSTATUS ZwQuerySystemInformation( SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, PULONG returnLength );
	NTKERNELAPI PVOID PsGetProcessSectionBaseAddress( PEPROCESS Process );
	NTKERNELAPI PPEB NTAPI PsGetProcessPeb( IN PEPROCESS Process );
	NTKERNELAPI NTSTATUS NTAPI ZwProtectVirtualMemory( HANDLE, PVOID*, PSIZE_T, ULONG, PULONG );

}
