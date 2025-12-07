#pragma once

#define WIN_1507 10240
#define WIN_1511 10586
#define WIN_1607 14393
#define WIN_1703 15063
#define WIN_1709 16299
#define WIN_1803 17134
#define WIN_1809 17763
#define WIN_1903 18362
#define WIN_1909 18363
#define WIN_2004 19041
#define WIN_20H2 19042
#define WIN_21H1 19043
#define WIN_21H2 19044
#define WIN_22H2 19045
#define WIN_22H22 19045

#define WIN_1121H2 22000
#define WIN_1122H2 22621
#define WIN_1123H2 22631

#define WINDOWS_NUMBER_7 7
#define WINDOWS_NUMBER_8 8
#define WINDOWS_NUMBER_8_1 9
#define WINDOWS_NUMBER_10 10
#define WINDOWS_NUMBER_11 11

#define IMAGE_DOS_SIGNATURE                 0x5A4D
#define IMAGE_NT_SIGNATURE                  0x00004550

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data

#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor

typedef struct _PEB_LDR_DATA
{
    BYTE Reserved1[ 8 ];
    PVOID Reserved2[ 3 ];
    LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB
{
    BYTE Reserved1[ 2 ];
    BYTE BeingDebugged;
    BYTE Reserved2[ 1 ];
    PVOID Reserved3[ 2 ];
    PPEB_LDR_DATA Ldr;
    PVOID ProcessParameters;
    PVOID Reserved4[ 3 ];
    PVOID AtlThunkSListPtr;
    PVOID Reserved5;
    ULONG Reserved6;
    PVOID Reserved7;
    ULONG Reserved8;
    ULONG AtlThunkSListPtr32;
    PVOID Reserved9[ 45 ];
    BYTE Reserved10[ 96 ];
    PVOID PostProcessInitRoutine;
    BYTE Reserved11[ 128 ];
    PVOID Reserved12[ 1 ];
    ULONG SessionId;
} PEB, * PPEB;

typedef struct _TEB
{
    PVOID Reserved1[ 12 ];
    PPEB ProcessEnvironmentBlock;
    PVOID Reserved2[ 399 ];
    BYTE Reserved3[ 1952 ];
    PVOID TlsSlots[ 64 ];
    BYTE Reserved4[ 8 ];
    PVOID Reserved5[ 26 ];
    PVOID ReservedForOle;  // Windows 2000 only
    PVOID Reserved6[ 4 ];
    PVOID TlsExpansionSlots;
} TEB, * PTEB;

typedef struct _LDR_DATA_TABLE_ENTRY
{
    struct _LIST_ENTRY InLoadOrderLinks;                                    //0x0
    struct _LIST_ENTRY InMemoryOrderLinks;                                  //0x10
    struct _LIST_ENTRY InInitializationOrderLinks;                          //0x20
    VOID* DllBase;                                                          //0x30
    VOID* EntryPoint;                                                       //0x38
    ULONG SizeOfImage;                                                      //0x40
    struct _UNICODE_STRING FullDllName;                                     //0x48
    struct _UNICODE_STRING BaseDllName;                                     //0x58
    union
    {
        UCHAR FlagGroup[ 4 ];                                                 //0x68
        ULONG Flags;                                                        //0x68
        struct
        {
            ULONG PackagedBinary : 1;                                         //0x68
            ULONG MarkedForRemoval : 1;                                       //0x68
            ULONG ImageDll : 1;                                               //0x68
            ULONG LoadNotificationsSent : 1;                                  //0x68
            ULONG TelemetryEntryProcessed : 1;                                //0x68
            ULONG ProcessStaticImport : 1;                                    //0x68
            ULONG InLegacyLists : 1;                                          //0x68
            ULONG InIndexes : 1;                                              //0x68
            ULONG ShimDll : 1;                                                //0x68
            ULONG InExceptionTable : 1;                                       //0x68
            ULONG ReservedFlags1 : 2;                                         //0x68
            ULONG LoadInProgress : 1;                                         //0x68
            ULONG LoadConfigProcessed : 1;                                    //0x68
            ULONG EntryProcessed : 1;                                         //0x68
            ULONG ProtectDelayLoad : 1;                                       //0x68
            ULONG ReservedFlags3 : 2;                                         //0x68
            ULONG DontCallForThreads : 1;                                     //0x68
            ULONG ProcessAttachCalled : 1;                                    //0x68
            ULONG ProcessAttachFailed : 1;                                    //0x68
            ULONG CorDeferredValidate : 1;                                    //0x68
            ULONG CorImage : 1;                                               //0x68
            ULONG DontRelocate : 1;                                           //0x68
            ULONG CorILOnly : 1;                                              //0x68
            ULONG ChpeImage : 1;                                              //0x68
            ULONG ReservedFlags5 : 2;                                         //0x68
            ULONG Redirected : 1;                                             //0x68
            ULONG ReservedFlags6 : 2;                                         //0x68
            ULONG CompatDatabaseProcessed : 1;                                //0x68
        };
    };
    USHORT ObsoleteLoadCount;                                               //0x6c
    USHORT TlsIndex;                                                        //0x6e
    struct _LIST_ENTRY HashLinks;                                           //0x70
    ULONG TimeDateStamp;                                                    //0x80
    struct _ACTIVATION_CONTEXT* EntryPointActivationContext;                //0x88
    VOID* Lock;                                                             //0x90
    struct _LDR_DDAG_NODE* DdagNode;                                        //0x98
    struct _LIST_ENTRY NodeModuleLink;                                      //0xa0
    struct _LDRP_LOAD_CONTEXT* LoadContext;                                 //0xb0
    VOID* ParentDllBase;                                                    //0xb8
    VOID* SwitchBackContext;                                                //0xc0
    struct _RTL_BALANCED_NODE BaseAddressIndexNode;                         //0xc8
    struct _RTL_BALANCED_NODE MappingInfoIndexNode;                         //0xe0
    ULONGLONG OriginalBase;                                                 //0xf8
    union _LARGE_INTEGER LoadTime;                                          //0x100
    ULONG BaseNameHashValue;                                                //0x108
    enum _LDR_DLL_LOAD_REASON LoadReason;                                   //0x10c
    ULONG ImplicitPathOptions;                                              //0x110
    ULONG ReferenceCount;                                                   //0x114
    ULONG DependentLoadFlags;                                               //0x118
    UCHAR SigningLevel;                                                     //0x11c
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemInformationClassMin = 0,
	SystemBasicInformation = 0,
	SystemProcessorInformation = 1,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3,
	SystemPathInformation = 4,
	SystemNotImplemented1 = 4,
	SystemProcessInformation = 5,
	SystemProcessesAndThreadsInformation = 5,
	SystemCallCountInfoInformation = 6,
	SystemCallCounts = 6,
	SystemDeviceInformation = 7,
	SystemConfigurationInformation = 7,
	SystemProcessorPerformanceInformation = 8,
	SystemProcessorTimes = 8,
	SystemFlagsInformation = 9,
	SystemGlobalFlag = 9,
	SystemCallTimeInformation = 10,
	SystemNotImplemented2 = 10,
	SystemModuleInformation = 11,
	SystemLocksInformation = 12,
	SystemLockInformation = 12,
	SystemStackTraceInformation = 13,
	SystemNotImplemented3 = 13,
	SystemPagedPoolInformation = 14,
	SystemNotImplemented4 = 14,
	SystemNonPagedPoolInformation = 15,
	SystemNotImplemented5 = 15,
	SystemHandleInformation = 16,
	SystemObjectInformation = 17,
	SystemPageFileInformation = 18,
	SystemPagefileInformation = 18,
	SystemVdmInstemulInformation = 19,
	SystemInstructionEmulationCounts = 19,
	SystemVdmBopInformation = 20,
	SystemInvalidInfoClass1 = 20,
	SystemFileCacheInformation = 21,
	SystemCacheInformation = 21,
	SystemPoolTagInformation = 22,
	SystemInterruptInformation = 23,
	SystemProcessorStatistics = 23,
	SystemDpcBehaviourInformation = 24,
	SystemDpcInformation = 24,
	SystemFullMemoryInformation = 25,
	SystemNotImplemented6 = 25,
	SystemLoadImage = 26,
	SystemUnloadImage = 27,
	SystemTimeAdjustmentInformation = 28,
	SystemTimeAdjustment = 28,
	SystemSummaryMemoryInformation = 29,
	SystemNotImplemented7 = 29,
	SystemNextEventIdInformation = 30,
	SystemNotImplemented8 = 30,
	SystemEventIdsInformation = 31,
	SystemNotImplemented9 = 31,
	SystemCrashDumpInformation = 32,
	SystemExceptionInformation = 33,
	SystemCrashDumpStateInformation = 34,
	SystemKernelDebuggerInformation = 35,
	SystemContextSwitchInformation = 36,
	SystemRegistryQuotaInformation = 37,
	SystemLoadAndCallImage = 38,
	SystemPrioritySeparation = 39,
	SystemPlugPlayBusInformation = 40,
	SystemNotImplemented10 = 40,
	SystemDockInformation = 41,
	SystemNotImplemented11 = 41,
	SystemInvalidInfoClass2 = 42,
	SystemProcessorSpeedInformation = 43,
	SystemInvalidInfoClass3 = 43,
	SystemCurrentTimeZoneInformation = 44,
	SystemTimeZoneInformation = 44,
	SystemLookasideInformation = 45,
	SystemSetTimeSlipEvent = 46,
	SystemCreateSession = 47,
	SystemDeleteSession = 48,
	SystemInvalidInfoClass4 = 49,
	SystemRangeStartInformation = 50,
	SystemVerifierInformation = 51,
	SystemAddVerifier = 52,
	SystemSessionProcessesInformation = 53,
	SystemInformationClassMax
} SYSTEM_INFORMATION_CLASS;

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR  FullPathName[ 256 ];

} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[ 1 ];

} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;

typedef union _PS_PROTECTION
{
	UCHAR Level;
	struct
	{
		int Type : 3;
		int Audit : 1;
		int Signer : 4;
	} Flags;
} PS_PROTECTION, * PPS_PROTECTION;

typedef enum _PS_PROTECTED_SIGNER
{
	PsProtectedSignerNone = 0,
	PsProtectedSignerAuthenticode = 1,
	PsProtectedSignerCodeGen = 2,
	PsProtectedSignerAntimalware = 3,
	PsProtectedSignerLsa = 4,
	PsProtectedSignerWindows = 5,
	PsProtectedSignerWinTcb = 6,
	PsProtectedSignerWinSystem = 7,
	PsProtectedSignerApp = 8,
	PsProtectedSignerMax = 9
} PS_PROTECTED_SIGNER;

typedef enum _PS_PROTECTED_TYPE
{
	PsProtectedTypeNone = 0,
	PsProtectedTypeProtectedLight = 1,
	PsProtectedTypeProtected = 2,
	PsProtectedTypeMax = 3

} PS_PROTECTED_TYPE;

typedef  NTSTATUS( NTAPI* t_RtlGetVersion )( PRTL_OSVERSIONINFOW lpVersionInformation );

enum struct e_sys_dll_type : int
{
	ps_native_system_dll,
	ps_wow_x86_system_dll,
	ps_wow_arm32_system_dll,
	ps_wow_amd64_system_dll,
	ps_wow_chpex86_system_dll,
	ps_vsm_enclave_runtime_dll,
	ps_system_dll_total_types
};

struct wow64_process_t
{
	PEB* m_peb;
	uint16_t			m_machine;
	e_sys_dll_type	m_ntdll_type;
};


struct rtl_avl_tree_t
{
	PRTL_BALANCED_NODE	m_root;
	void* m_node_hint;
	uint64_t					m_number_generic_table_elements;
};

struct eprocess_t
{
	char pad[ 0x28 ];
	ULONGLONG m_directory_table_base; // 0x28
	char pad_0[ 0x3a8 ];// 0x30
	void* m_instrumentation_callback; // 0x3d8
	char pad_1[ 0x60 ];// 0x3e0
	uint64_t m_process_id; // 0x440
	char pad_2[ 0x108 ];// 0x448
	PEB* m_peb; // 0x550
	char pad_3[ 0x28 ];// 0x558
	wow64_process_t* m_wow64_process; // 0x580
	char pad_4[ 0x20 ];// 0x588
	char m_image_file_name[ 15 ]; // 0x5a8
	char pad_5[ 0x29 ];// 0x5b7
	_LIST_ENTRY m_thread_list_head; // 0x5e0
	char pad_6[ 0x1e4 ];// 0x5f0
	uint32_t m_exit_status; // 0x7d4
	rtl_avl_tree_t m_vad_root; // 0x7d8
	//void* m_vad_hint; // 0x7e0
	//uint64_t m_vad_count; // 0x7e8
	char pad_7[ 0x8c ];// 0x7f0
	uint32_t m_flags3; // 0x87c
};

struct ethread_t
{
	char				pad0[ 184u ];
	eprocess_t* m_proc; // 0xb8
	char pad_0[ 0x30 ];// 0xc0
	void* m_teb; // 0xf0
	char pad_1[ 0x8c ];// 0xf8
	uint8_t m_state; // 0x184
	char pad_2[ 0x2 ];// 0x185
	uint8_t m_wait_mode; // 0x187
	char pad_3[ 0xaa ];// 0x188
	uint8_t			m_prev_mode; // 0x232
	char pad_4[ 0x50 ];// 0x233
	uint8_t m_wait_reason; // 0x283
	char pad_5[ 0x1f4 ];// 0x284
	_CLIENT_ID		m_client_id; // 0x478
	char				pad3[ 96u ];// 0x488
	_LIST_ENTRY		m_thread_list_entry; // 0x4e8
	char				pad4[ 24u ]; // 0x4f8
	uint32_t			m_cross_thread_flags; // 0x510
	char				pad5[ 52u ]; // 0x514
	uint32_t			m_exit_status; // 0x548
};