#pragma once
#include <intrin.h>

#pragma optimize("", off)
NTKERNELAPI
PVOID
PsGetProcessSectionBaseAddress(
	__in PEPROCESS Process
);

typedef union _virt_addr_t
{
	void* value;
	struct
	{
		uintptr_t offset : 12;
		uintptr_t pt_index : 9;
		uintptr_t pd_index : 9;
		uintptr_t pdpt_index : 9;
		uintptr_t pml4_index : 9;
		uintptr_t reserved : 16;
	};
} virt_addr_t, * pvirt_addr_t;
typedef struct _MI_ACTIVE_PFN
{
	union
	{
		struct
		{
			struct /* bitfield */
			{
				/* 0x0000 */ unsigned __int64 Tradable : 1; /* bit position: 0 */
				/* 0x0000 */ unsigned __int64 NonPagedBuddy : 43; /* bit position: 1 */
			}; /* bitfield */
		} /* size: 0x0008 */ Leaf;
		struct
		{
			struct /* bitfield */
			{
				/* 0x0000 */ unsigned __int64 Tradable : 1; /* bit position: 0 */
				/* 0x0000 */ unsigned __int64 WsleAge : 3; /* bit position: 1 */
				/* 0x0000 */ unsigned __int64 OldestWsleLeafEntries : 10; /* bit position: 4 */
				/* 0x0000 */ unsigned __int64 OldestWsleLeafAge : 3; /* bit position: 14 */
				/* 0x0000 */ unsigned __int64 NonPagedBuddy : 43; /* bit position: 17 */
			}; /* bitfield */
		} /* size: 0x0008 */ PageTable;
		/* 0x0000 */ unsigned __int64 EntireActiveField;
	}; /* size: 0x0008 */
} MI_ACTIVE_PFN, * PMI_ACTIVE_PFN; /* size: 0x0008 */

typedef struct _MMPTE_HARDWARE
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 Dirty1 : 1; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 Owner : 1; /* bit position: 2 */
		/* 0x0000 */ unsigned __int64 WriteThrough : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned __int64 CacheDisable : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Accessed : 1; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Dirty : 1; /* bit position: 6 */
		/* 0x0000 */ unsigned __int64 LargePage : 1; /* bit position: 7 */
		/* 0x0000 */ unsigned __int64 Global : 1; /* bit position: 8 */
		/* 0x0000 */ unsigned __int64 CopyOnWrite : 1; /* bit position: 9 */
		/* 0x0000 */ unsigned __int64 Unused : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 Write : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 PageFrameNumber : 40; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 ReservedForSoftware : 4; /* bit position: 52 */
		/* 0x0000 */ unsigned __int64 WsleAge : 4; /* bit position: 56 */
		/* 0x0000 */ unsigned __int64 WsleProtection : 3; /* bit position: 60 */
		/* 0x0000 */ unsigned __int64 NoExecute : 1; /* bit position: 63 */
	}; /* bitfield */
} MMPTE_HARDWARE, * PMMPTE_HARDWARE; /* size: 0x0008 */

typedef struct _MMPTE_PROTOTYPE
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 DemandFillProto : 1; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 HiberVerifyConverted : 1; /* bit position: 2 */
		/* 0x0000 */ unsigned __int64 ReadOnly : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 Combined : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 Unused1 : 4; /* bit position: 12 */
		/* 0x0000 */ __int64 ProtoAddress : 48; /* bit position: 16 */
	}; /* bitfield */
} MMPTE_PROTOTYPE, * PMMPTE_PROTOTYPE; /* size: 0x0008 */

typedef struct _MMPTE_SOFTWARE
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 PageFileReserved : 1; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 PageFileAllocated : 1; /* bit position: 2 */
		/* 0x0000 */ unsigned __int64 ColdPage : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 PageFileLow : 4; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 UsedPageTableEntries : 10; /* bit position: 16 */
		/* 0x0000 */ unsigned __int64 ShadowStack : 1; /* bit position: 26 */
		/* 0x0000 */ unsigned __int64 Unused : 5; /* bit position: 27 */
		/* 0x0000 */ unsigned __int64 PageFileHigh : 32; /* bit position: 32 */
	}; /* bitfield */
} MMPTE_SOFTWARE, * PMMPTE_SOFTWARE; /* size: 0x0008 */

typedef struct _MMPTE_TIMESTAMP
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 MustBeZero : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 Unused : 3; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 PageFileLow : 4; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 Reserved : 16; /* bit position: 16 */
		/* 0x0000 */ unsigned __int64 GlobalTimeStamp : 32; /* bit position: 32 */
	}; /* bitfield */
} MMPTE_TIMESTAMP, * PMMPTE_TIMESTAMP; /* size: 0x0008 */

typedef struct _MMPTE_TRANSITION
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 Write : 1; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 Spare : 1; /* bit position: 2 */
		/* 0x0000 */ unsigned __int64 IoTracker : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 PageFrameNumber : 40; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 Unused : 12; /* bit position: 52 */
	}; /* bitfield */
} MMPTE_TRANSITION, * PMMPTE_TRANSITION; /* size: 0x0008 */

typedef struct _MMPTE_SUBSECTION
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 Unused0 : 3; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 ColdPage : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 Unused1 : 3; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 ExecutePrivilege : 1; /* bit position: 15 */
		/* 0x0000 */ __int64 SubsectionAddress : 48; /* bit position: 16 */
	}; /* bitfield */
} MMPTE_SUBSECTION, * PMMPTE_SUBSECTION; /* size: 0x0008 */

typedef struct _MMPTE_LIST
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 OneEntry : 1; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 filler0 : 2; /* bit position: 2 */
		/* 0x0000 */ unsigned __int64 SwizzleBit : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Protection : 5; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 Transition : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 filler1 : 16; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 NextEntry : 36; /* bit position: 28 */
	}; /* bitfield */
} MMPTE_LIST, * PMMPTE_LIST; /* size: 0x0008 */

typedef struct _MMPTE
{
	union
	{
		union
		{
			/* 0x0000 */ unsigned __int64 Long;
			/* 0x0000 */ volatile unsigned __int64 VolatileLong;
			/* 0x0000 */ struct _MMPTE_HARDWARE Hard;
			/* 0x0000 */ struct _MMPTE_PROTOTYPE Proto;
			/* 0x0000 */ struct _MMPTE_SOFTWARE Soft;
			/* 0x0000 */ struct _MMPTE_TIMESTAMP TimeStamp;
			/* 0x0000 */ struct _MMPTE_TRANSITION Trans;
			/* 0x0000 */ struct _MMPTE_SUBSECTION Subsect;
			/* 0x0000 */ struct _MMPTE_LIST List;
		}; /* size: 0x0008 */
	} /* size: 0x0008 */ u;
} MMPTE, * PMMPTE; /* size: 0x0008 */

typedef struct _MIPFNBLINK
{
	union
	{
		struct /* bitfield */
		{
			/* 0x0000 */ unsigned __int64 Blink : 40; /* bit position: 0 */
			/* 0x0000 */ unsigned __int64 NodeBlinkLow : 19; /* bit position: 40 */
			/* 0x0000 */ unsigned __int64 TbFlushStamp : 3; /* bit position: 59 */
			/* 0x0000 */ unsigned __int64 PageBlinkDeleteBit : 1; /* bit position: 62 */
			/* 0x0000 */ unsigned __int64 PageBlinkLockBit : 1; /* bit position: 63 */
		}; /* bitfield */
		struct /* bitfield */
		{
			/* 0x0000 */ unsigned __int64 ShareCount : 62; /* bit position: 0 */
			/* 0x0000 */ unsigned __int64 PageShareCountDeleteBit : 1; /* bit position: 62 */
			/* 0x0000 */ unsigned __int64 PageShareCountLockBit : 1; /* bit position: 63 */
		}; /* bitfield */
		/* 0x0000 */ unsigned __int64 EntireField;
		/* 0x0000 */ volatile __int64 Lock;
		struct /* bitfield */
		{
			/* 0x0000 */ unsigned __int64 LockNotUsed : 62; /* bit position: 0 */
			/* 0x0000 */ unsigned __int64 DeleteBit : 1; /* bit position: 62 */
			/* 0x0000 */ unsigned __int64 LockBit : 1; /* bit position: 63 */
		}; /* bitfield */
	}; /* size: 0x0008 */
} MIPFNBLINK, * PMIPFNBLINK; /* size: 0x0008 */

typedef struct _MMPFNENTRY1
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned char PageLocation : 3; /* bit position: 0 */
		/* 0x0000 */ unsigned char WriteInProgress : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned char Modified : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned char ReadInProgress : 1; /* bit position: 5 */
		/* 0x0000 */ unsigned char CacheAttribute : 2; /* bit position: 6 */
	}; /* bitfield */
} MMPFNENTRY1, * PMMPFNENTRY1; /* size: 0x0001 */

typedef struct _MMPFNENTRY3
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned char Priority : 3; /* bit position: 0 */
		/* 0x0000 */ unsigned char OnProtectedStandby : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned char InPageError : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned char SystemChargedPage : 1; /* bit position: 5 */
		/* 0x0000 */ unsigned char RemovalRequested : 1; /* bit position: 6 */
		/* 0x0000 */ unsigned char ParityError : 1; /* bit position: 7 */
	}; /* bitfield */
} MMPFNENTRY3, * PMMPFNENTRY3; /* size: 0x0001 */

typedef struct _MI_PFN_ULONG5
{
	union
	{
		/* 0x0000 */ unsigned long EntireField;
		struct
		{
			struct /* bitfield */
			{
				/* 0x0000 */ unsigned long NodeBlinkHigh : 21; /* bit position: 0 */
				/* 0x0000 */ unsigned long NodeFlinkMiddle : 11; /* bit position: 21 */
			}; /* bitfield */
		} /* size: 0x0004 */ StandbyList;
		struct
		{
			/* 0x0000 */ unsigned char ModifiedListBucketIndex : 4; /* bit position: 0 */
		} /* size: 0x0001 */ MappedPageList;
		struct
		{
			struct /* bitfield */
			{
				/* 0x0000 */ unsigned char AnchorLargePageSize : 2; /* bit position: 0 */
				/* 0x0000 */ unsigned char Spare1 : 6; /* bit position: 2 */
			}; /* bitfield */
			/* 0x0001 */ unsigned char ViewCount;
			/* 0x0002 */ unsigned short Spare2;
		} /* size: 0x0004 */ Active;
	}; /* size: 0x0004 */
} MI_PFN_ULONG5, * PMI_PFN_ULONG5; /* size: 0x0004 */

typedef struct _MMPFN
{
	union
	{
		/* 0x0000 */ struct _LIST_ENTRY ListEntry;
		/* 0x0000 */ struct _RTL_BALANCED_NODE TreeNode;
		struct
		{
			union
			{
				union
				{
					/* 0x0000 */ struct _SINGLE_LIST_ENTRY NextSlistPfn;
					/* 0x0000 */ void* Next;
					struct /* bitfield */
					{
						/* 0x0000 */ unsigned __int64 Flink : 40; /* bit position: 0 */
						/* 0x0000 */ unsigned __int64 NodeFlinkLow : 24; /* bit position: 40 */
					}; /* bitfield */
					/* 0x0000 */ struct _MI_ACTIVE_PFN Active;
				}; /* size: 0x0008 */
			} /* size: 0x0008 */ u1;
			union
			{
				/* 0x0008 */ struct _MMPTE* PteAddress;
				/* 0x0008 */ unsigned __int64 PteLong;
			}; /* size: 0x0008 */
			/* 0x0010 */ struct _MMPTE OriginalPte;
		}; /* size: 0x0018 */
	}; /* size: 0x0018 */
	/* 0x0018 */ struct _MIPFNBLINK u2;
	union
	{
		union
		{
			struct
			{
				/* 0x0020 */ unsigned short ReferenceCount;
				/* 0x0022 */ struct _MMPFNENTRY1 e1;
				/* 0x0023 */ struct _MMPFNENTRY3 e3;
			}; /* size: 0x0004 */
			struct
			{
				/* 0x0020 */ unsigned short ReferenceCount;
			} /* size: 0x0002 */ e2;
			struct
			{
				/* 0x0020 */ unsigned long EntireField;
			} /* size: 0x0004 */ e4;
		}; /* size: 0x0004 */
	} /* size: 0x0004 */ u3;
	/* 0x0024 */ struct _MI_PFN_ULONG5 u5;
	union
	{
		union
		{
			struct /* bitfield */
			{
				/* 0x0028 */ unsigned __int64 PteFrame : 40; /* bit position: 0 */
				/* 0x0028 */ unsigned __int64 ResidentPage : 1; /* bit position: 40 */
				/* 0x0028 */ unsigned __int64 Unused1 : 1; /* bit position: 41 */
				/* 0x0028 */ unsigned __int64 Unused2 : 1; /* bit position: 42 */
				/* 0x0028 */ unsigned __int64 Partition : 10; /* bit position: 43 */
				/* 0x0028 */ unsigned __int64 FileOnly : 1; /* bit position: 53 */
				/* 0x0028 */ unsigned __int64 PfnExists : 1; /* bit position: 54 */
				/* 0x0028 */ unsigned __int64 NodeFlinkHigh : 5; /* bit position: 55 */
				/* 0x0028 */ unsigned __int64 PageIdentity : 3; /* bit position: 60 */
				/* 0x0028 */ unsigned __int64 PrototypePte : 1; /* bit position: 63 */
			}; /* bitfield */
			/* 0x0028 */ unsigned __int64 EntireField;
		}; /* size: 0x0008 */
	} /* size: 0x0008 */ u4;
} MMPFN, * PMMPFN; /* size: 0x0030 */



PVOID GetProcessBaseAddress(int pid)
{
	PEPROCESS pProcess = NULL;
	if (pid == 0) return NULL;

	NTSTATUS NtRet = PsLookupProcessByProcessId((HANDLE)pid, &pProcess);
	if (NtRet != STATUS_SUCCESS) return NULL;

	PVOID Base = PsGetProcessSectionBaseAddress(pProcess);
	ObDereferenceObject(pProcess);
	return Base;
}

#define WINDOWS_1803 17134
#define WINDOWS_1809 17763
#define WINDOWS_1903 18362
#define WINDOWS_1909 18363
#define WINDOWS_2004 19041
#define WINDOWS_20H2 19569
#define WINDOWS_21H1 20180

DWORD GetUserDirectoryTableBaseOffset()
{
	using fn = NTSTATUS(*)(PRTL_OSVERSIONINFOW);
	auto rtl_get_version = (fn)(find_function("ntoskrnl.exe", "RtlGetVersion"));

	RTL_OSVERSIONINFOW ver = { 0 };
	rtl_get_version(&ver);

	switch (ver.dwBuildNumber)
	{
	case WINDOWS_1803:
		return 0x0278;
		break;
	case WINDOWS_1809:
		return 0x0278;
		break;
	case WINDOWS_1903:
		return 0x0280;
		break;
	case WINDOWS_1909:
		return 0x0280;
		break;
	case WINDOWS_2004:
		return 0x0388;
		break;
	case WINDOWS_20H2:
		return 0x0388;
		break;
	case WINDOWS_21H1:
		return 0x0388;
		break;
	default:
		return 0x0388;
	}
}



#define PAGE_OFFSET_SIZE 12
static const uint64_t PMASK = (~0xfull << 8) & 0xfffffffffull;

NTSTATUS ReadPhysicalAddress(PVOID TargetAddress, PVOID lpBuffer, SIZE_T Size, SIZE_T* BytesRead)
{
	MM_COPY_ADDRESS AddrToRead = { 0 };
	AddrToRead.PhysicalAddress.QuadPart = (LONGLONG)TargetAddress;
	return fusion::imports::mm_copy_memory(lpBuffer, AddrToRead, Size, MM_COPY_MEMORY_PHYSICAL, BytesRead);
}

//MmMapIoSpaceEx limit is page 4096 byte
NTSTATUS WritePhysicalAddress(PVOID TargetAddress, PVOID lpBuffer, SIZE_T Size, SIZE_T* BytesWritten)
{
	if (!TargetAddress)
		return STATUS_UNSUCCESSFUL;

	PHYSICAL_ADDRESS AddrToWrite = { 0 };
	AddrToWrite.QuadPart = (LONGLONG)TargetAddress;

	using fn = PVOID(*)(PHYSICAL_ADDRESS, SIZE_T, ULONG);
	auto mm_map_io_space = (fn)(find_function("ntoskrnl.exe", "MmMapIoSpaceEx"));

	using fn2 = PVOID(*)(PVOID, SIZE_T);
	auto mm_unmap_io_space = (fn2)(find_function("ntoskrnl.exe", "MmUnmapIoSpace"));

	PVOID pmapped_mem = mm_map_io_space(AddrToWrite, Size, PAGE_READWRITE);

	if (!pmapped_mem)
		return STATUS_UNSUCCESSFUL;

	memcpy(pmapped_mem, lpBuffer, Size);

	*BytesWritten = Size;
	mm_unmap_io_space(pmapped_mem, Size);
	return STATUS_SUCCESS;
}
namespace pml
{
	PVOID split_memory(PVOID SearchBase, SIZE_T SearchSize, const void* Pattern, SIZE_T PatternSize)
	{
		const UCHAR* searchBase = static_cast<const UCHAR*>(SearchBase);
		const UCHAR* pattern = static_cast<const UCHAR*>(Pattern);

		for (SIZE_T i = 0; i <= SearchSize - PatternSize; ++i) {
			SIZE_T j = 0;
			for (; j < PatternSize; ++j) {
				if (searchBase[i + j] != pattern[j])
					break;
			}
			if (j == PatternSize)
				return const_cast<UCHAR*>(&searchBase[i]);
		}

		return nullptr;
	}

	void* g_mmonp_MmPfnDatabase;
	struct MmPfnDatabaseSearchPattern
	{
		const UCHAR* bytes;
		SIZE_T bytes_size;
		bool hard_coded;
	};
			MmPfnDatabaseSearchPattern patterns;

	static NTSTATUS InitializeMmPfnDatabase()
	{
		

		const auto p_MmGetVirtualForPhysical = reinterpret_cast<UCHAR*>(
			(find_function("ntoskrnl.exe", "MmGetVirtualForPhysical")));

		auto found = reinterpret_cast<UCHAR*>(split_memory(p_MmGetVirtualForPhysical, 0x20, patterns.bytes, patterns.bytes_size));
		if (!found) {
			return STATUS_UNSUCCESSFUL;
		}


		found += patterns.bytes_size;
		if (patterns.hard_coded) {
			g_mmonp_MmPfnDatabase = *reinterpret_cast<void**>(found);
		}
		else {
			const auto mmpfn_address = *reinterpret_cast<ULONG_PTR*>(found);
			g_mmonp_MmPfnDatabase = *reinterpret_cast<void**>(mmpfn_address);
		}

		g_mmonp_MmPfnDatabase = PAGE_ALIGN(g_mmonp_MmPfnDatabase);

		return STATUS_SUCCESS;
	}

	uintptr_t dirbase_from_base_address(void* base)
	{
		if (!NT_SUCCESS(InitializeMmPfnDatabase()))
			return 0;

		virt_addr_t virt_base{}; virt_base.value = base;

		size_t read{};

		auto ranges = MmGetPhysicalMemoryRanges();

		for (int i = 0;; i++) {

			auto elem = &ranges[i];

			if (!elem->BaseAddress.QuadPart || !elem->NumberOfBytes.QuadPart)
				break;

			/*uintptr_t*/UINT64 current_phys_address = elem->BaseAddress.QuadPart;

			for (int j = 0; j < (elem->NumberOfBytes.QuadPart / 0x1000); j++, current_phys_address += 0x1000) {

				_MMPFN* pnfinfo = (_MMPFN*)((uintptr_t)g_mmonp_MmPfnDatabase + (current_phys_address >> 12) * sizeof(_MMPFN));

				if (pnfinfo->u4.PteFrame == (current_phys_address >> 12)) {
					MMPTE pml4e{};
					if (!NT_SUCCESS(ReadPhysicalAddress(PVOID(current_phys_address + 8 * virt_base.pml4_index), &pml4e, 8, &read)))
						continue;

					if (!pml4e.u.Hard.Valid)
						continue;

					MMPTE pdpte{};
					if (!NT_SUCCESS(ReadPhysicalAddress(PVOID((pml4e.u.Hard.PageFrameNumber << 12) + 8 * virt_base.pdpt_index), &pdpte, 8, &read)))
						continue;

					if (!pdpte.u.Hard.Valid)
						continue;

					MMPTE pde{};
					if (!NT_SUCCESS(ReadPhysicalAddress(PVOID((pdpte.u.Hard.PageFrameNumber << 12) + 8 * virt_base.pd_index), &pde, 8, &read)))
						continue;

					if (!pde.u.Hard.Valid)
						continue;

					MMPTE pte{};
					if (!NT_SUCCESS(ReadPhysicalAddress(PVOID((pde.u.Hard.PageFrameNumber << 12) + 8 * virt_base.pt_index), &pte, 8, &read)))
						continue;

					if (!pte.u.Hard.Valid)
						continue;

					return current_phys_address;
				}
			}
		}

		return 0;
	}

}
ULONG_PTR GetKernelDirBase()
{
	PUCHAR process = (PUCHAR)PsGetCurrentProcess();
	ULONG_PTR cr3 = *(PULONG_PTR)(process + 0x28); //dirbase x64, 32bit is 0x18
	return cr3;
}
//check normal dirbase if 0 then get from UserDirectoryTableBas
ULONG_PTR GetProcessCr3(PEPROCESS pProcess)
{
	PUCHAR process = (PUCHAR)pProcess;
	ULONG_PTR process_dirbase = *(PULONG_PTR)(process + 0x28); //dirbase x64, 32bit is 0x18
	if (process_dirbase == 0)
	{
		DWORD UserDirOffset = GetUserDirectoryTableBaseOffset();
		ULONG_PTR process_userdirbase = *(PULONG_PTR)(process + UserDirOffset);
		return process_userdirbase;
	}
	return process_dirbase;
}



PVOID SplitMemory(PVOID SearchBase, SIZE_T SearchSize, const void* Pattern, SIZE_T PatternSize) {
	const UCHAR* searchBase = static_cast<const UCHAR*>(SearchBase);
	const UCHAR* pattern = static_cast<const UCHAR*>(Pattern);

	for (SIZE_T i = 0; i <= SearchSize - PatternSize; ++i)
	{
		SIZE_T j = 0;
		for (; j < PatternSize; ++j)
		{
			if (searchBase[i + j] != pattern[j])
				break;
		}

		if (j == PatternSize)
			return const_cast<UCHAR*>(&searchBase[i]);
	}

	return nullptr;

}

static void* g_mmonp_MmPfnDatabase;

NTSTATUS InitMmpfnDatabase() {
	struct MmPfnDatabaseSearchPattern
	{
		const UCHAR* bytes;
		SIZE_T bytes_size;
		bool hard_coded;
	};

	MmPfnDatabaseSearchPattern patterns;

	// Windows 10 x64 Build 14332+
	static const UCHAR kPatternWin10x64[] = {
		0x48, 0x8B, 0xC1,        // mov     rax, rcx
		0x48, 0xC1, 0xE8, 0x0C,  // shr     rax, 0Ch
		0x48, 0x8D, 0x14, 0x40,  // lea     rdx, [rax + rax * 2]
		0x48, 0x03, 0xD2,        // add     rdx, rdx
		0x48, 0xB8,              // mov     rax, 0FFFFFA8000000008h
	};

	patterns.bytes = kPatternWin10x64;
	patterns.bytes_size = sizeof(kPatternWin10x64);
	patterns.hard_coded = true;

	const auto p_MmGetVirtualForPhysical = reinterpret_cast<UCHAR*>((((MmGetVirtualForPhysical))));

	if (!p_MmGetVirtualForPhysical)
	{
		return STATUS_PROCEDURE_NOT_FOUND;
	}

	auto found = reinterpret_cast<UCHAR*>(SplitMemory(p_MmGetVirtualForPhysical, 0x20, patterns.bytes, patterns.bytes_size));
	if (!found)
	{
		return STATUS_UNSUCCESSFUL;
	}


	found += patterns.bytes_size;
	if (patterns.hard_coded)
	{
		g_mmonp_MmPfnDatabase = *reinterpret_cast<void**>(found);
	}
	else
	{
		const auto mmpfn_address = *reinterpret_cast<ULONG_PTR*>(found);
		g_mmonp_MmPfnDatabase = *reinterpret_cast<void**>(mmpfn_address);
	}

	g_mmonp_MmPfnDatabase = PAGE_ALIGN(g_mmonp_MmPfnDatabase);

	return STATUS_SUCCESS;
}

NTSTATUS ReadPhysical(UINT64 address, PVOID buffer, size_t size, size_t* bytes) {
	MM_COPY_ADDRESS targetAddress = { 0 };
	targetAddress.PhysicalAddress.QuadPart = address;
	return (MmCopyMemory)(buffer, targetAddress, size, MM_COPY_MEMORY_PHYSICAL, bytes);
}

UINT64 DirbaseFromBaseAdress(void* base) {
	if (!NT_SUCCESS(InitMmpfnDatabase()))
		return 0;

	virt_addr_t virtBase{}; virtBase.value = base;

	size_t read{};

	auto ranges = (MmGetPhysicalMemoryRanges)();

	for (int i = 0;; i++)
	{

		auto elem = &ranges[i];

		if (!elem->BaseAddress.QuadPart || !elem->NumberOfBytes.QuadPart)
			break;

		UINT64 currentPhysAddress = elem->BaseAddress.QuadPart;

		for (int j = 0; j < (elem->NumberOfBytes.QuadPart / 0x1000); j++, currentPhysAddress += 0x1000)
		{

			_MMPFN* pnfinfo = (_MMPFN*)((uintptr_t)g_mmonp_MmPfnDatabase + (currentPhysAddress >> 12) * sizeof(_MMPFN));

			if (pnfinfo->u4.PteFrame == (currentPhysAddress >> 12))
			{
				MMPTE pml4e{};
				if (!NT_SUCCESS(ReadPhysical(currentPhysAddress + 8 * virtBase.pml4_index, &pml4e, 8, &read)))
					continue;

				if (!pml4e.u.Hard.Valid)
					continue;

				MMPTE pdpte{};
				if (!NT_SUCCESS(ReadPhysical((pml4e.u.Hard.PageFrameNumber << 12) + 8 * virtBase.pdpt_index, &pdpte, 8, &read)))
					continue;

				if (!pdpte.u.Hard.Valid)
					continue;

				MMPTE pde{};
				if (!NT_SUCCESS(ReadPhysical((pdpte.u.Hard.PageFrameNumber << 12) + 8 * virtBase.pd_index, &pde, 8, &read)))
					continue;

				if (!pde.u.Hard.Valid)
					continue;

				MMPTE pte{};
				if (!NT_SUCCESS(ReadPhysical((pde.u.Hard.PageFrameNumber << 12) + 8 * virtBase.pt_index, &pte, 8, &read)))
					continue;

				if (!pte.u.Hard.Valid)
					continue;

				return currentPhysAddress;
			}
		}
	}

	return 0;
}




struct cache {
	uintptr_t Address;
	MMPTE Value;
};

static cache cached_pml4e[512];
static cache cached_pdpte[512];
static cache cached_pde[512];
static cache cached_pte[512];
typedef union
{
	PVOID value;
	struct
	{
		uint64_t offset : 12;
		uint64_t pt_index : 9;
		uint64_t pd_index : 9;
		uint64_t pdpt_index : 9;
		uint64_t pml4_index : 9;
		uint64_t reserved1 : 16;
	};
} virtual_address_t, * pvirtual_address_t;

uint64_t TranslateLinearAddress(uint64_t directoryTableBase, uint64_t virtualAddress) {
	{
		virtual_address_t virtual_address{};
		virtual_address.value = PVOID(virtualAddress);

		SIZE_T Size = 0;

		// PML4E
		if (cached_pml4e[virtual_address.pml4_index].Address != directoryTableBase + 8 * virtual_address.pml4_index || !cached_pml4e[virtual_address.pml4_index].Value.u.Hard.Valid) {
			cached_pml4e[virtual_address.pml4_index].Address = directoryTableBase + 8 * virtual_address.pml4_index;
			ReadPhysicalAddress((PVOID)cached_pml4e[virtual_address.pml4_index].Address, reinterpret_cast<PVOID>(&cached_pml4e[virtual_address.pml4_index].Value), 8, &Size);
		}

		if (!cached_pml4e[virtual_address.pml4_index].Value.u.Hard.Valid)
			return 0;

		// PDPTE
		if (cached_pdpte[virtual_address.pdpt_index].Address != (cached_pml4e[virtual_address.pml4_index].Value.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pdpt_index || !cached_pdpte[virtual_address.pdpt_index].Value.u.Hard.Valid) {
			cached_pdpte[virtual_address.pdpt_index].Address = (cached_pml4e[virtual_address.pml4_index].Value.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pdpt_index;
			ReadPhysicalAddress((PVOID)cached_pdpte[virtual_address.pdpt_index].Address, reinterpret_cast<PVOID>(&cached_pdpte[virtual_address.pdpt_index].Value), 8, &Size);
		}

		if (!cached_pdpte[virtual_address.pdpt_index].Value.u.Hard.Valid)
			return 0;

		// PDE
		if (cached_pde[virtual_address.pd_index].Address != (cached_pdpte[virtual_address.pdpt_index].Value.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pd_index || !cached_pde[virtual_address.pd_index].Value.u.Hard.Valid) {
			cached_pde[virtual_address.pd_index].Address = (cached_pdpte[virtual_address.pdpt_index].Value.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pd_index;
			ReadPhysicalAddress((PVOID)cached_pde[virtual_address.pd_index].Address, reinterpret_cast<PVOID>(&cached_pde[virtual_address.pd_index].Value), 8, &Size);
		}

		if (!cached_pde[virtual_address.pd_index].Value.u.Hard.Valid)
			return 0;

		// PTE
		if (cached_pte[virtual_address.pt_index].Address != (cached_pde[virtual_address.pd_index].Value.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pt_index || !cached_pte[virtual_address.pt_index].Value.u.Hard.Valid) {
			cached_pte[virtual_address.pt_index].Address = (cached_pde[virtual_address.pd_index].Value.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pt_index;
			ReadPhysicalAddress((PVOID)cached_pte[virtual_address.pt_index].Address, reinterpret_cast<PVOID>(&cached_pte[virtual_address.pt_index].Value), 8, &Size);
		}

		if (!cached_pte[virtual_address.pt_index].Value.u.Hard.Valid)
			return 0;

		return (cached_pte[virtual_address.pt_index].Value.u.Hard.PageFrameNumber << 12) + virtual_address.offset;
	}
}


NTSTATUS ReadVirtual(uint64_t dirbase, uint64_t address, uint8_t* buffer, SIZE_T size, SIZE_T* read)
{
	uint64_t paddress = TranslateLinearAddress(dirbase, address);
	return ReadPhysicalAddress((PVOID)paddress, buffer, size, read);
}

NTSTATUS WriteVirtual(uint64_t dirbase, uint64_t address, uint8_t* buffer, SIZE_T size, SIZE_T* written)
{
	uint64_t paddress = TranslateLinearAddress(dirbase, address);
	return WritePhysicalAddress((PVOID)paddress, buffer, size, written);
}


NTSTATUS ReadProcessMemory(int pid, PVOID Address, PVOID AllocatedBuffer, SIZE_T size, SIZE_T* read)
{
	PEPROCESS pProcess = NULL;
	if (pid == 0) return STATUS_UNSUCCESSFUL;

	NTSTATUS NtRet = fusion::imports::ps_lookup_process_by_process_id((HANDLE)pid, &pProcess);
	if (NtRet != STATUS_SUCCESS) return NtRet;

	//ULONG_PTR process_dirbase = GetProcessCr3(pProcess);
	ULONG_PTR process_dirbase =  DirbaseFromBaseAdress((PsGetProcessSectionBaseAddress)(pProcess));
	ObDereferenceObject(pProcess);

	SIZE_T CurOffset = 0;
	SIZE_T TotalSize = size;
	while (TotalSize)
	{

		uint64_t CurPhysAddr = TranslateLinearAddress(process_dirbase, (ULONG64)Address + CurOffset);
		if (!CurPhysAddr) return STATUS_UNSUCCESSFUL;

		ULONG64 ReadSize = min(PAGE_SIZE - (CurPhysAddr & 0xFFF), TotalSize);
		SIZE_T BytesRead = 0;
		NtRet = ReadPhysicalAddress((PVOID)CurPhysAddr, (PVOID)((ULONG64)AllocatedBuffer + CurOffset), ReadSize, &BytesRead);
		TotalSize -= BytesRead;
		CurOffset += BytesRead;
		if (NtRet != STATUS_SUCCESS) break;
		if (BytesRead == 0) break;
	}

	*read = CurOffset;
	return NtRet;
}

NTSTATUS WriteProcessMemory(int pid, PVOID Address, PVOID AllocatedBuffer, SIZE_T size, SIZE_T* written)
{
	PEPROCESS pProcess = NULL;
	if (pid == 0) return STATUS_UNSUCCESSFUL;

	NTSTATUS NtRet = PsLookupProcessByProcessId((HANDLE)pid, &pProcess);
	if (NtRet != STATUS_SUCCESS) return NtRet;

	ULONG_PTR process_dirbase = DirbaseFromBaseAdress((PsGetProcessSectionBaseAddress)(pProcess));
	ObDereferenceObject(pProcess);

	SIZE_T CurOffset = 0;
	SIZE_T TotalSize = size;
	while (TotalSize)
	{
		uint64_t CurPhysAddr = TranslateLinearAddress(process_dirbase, (ULONG64)Address + CurOffset);
		if (!CurPhysAddr) return STATUS_UNSUCCESSFUL;

		ULONG64 WriteSize = min(PAGE_SIZE - (CurPhysAddr & 0xFFF), TotalSize);
		SIZE_T BytesWritten = 0;
		NtRet = WritePhysicalAddress((PVOID)CurPhysAddr, (PVOID)((ULONG64)AllocatedBuffer + CurOffset), WriteSize, &BytesWritten);
		TotalSize -= BytesWritten;
		CurOffset += BytesWritten;
		if (NtRet != STATUS_SUCCESS) break;
		if (BytesWritten == 0) break;
	}

	*written = CurOffset;
	return NtRet;
}


#pragma optimize("", on)
