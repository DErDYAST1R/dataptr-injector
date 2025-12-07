#pragma once
#include <ntifs.h>
#include <ntddk.h>
#include <windef.h>
#include <ntimage.h>

#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
#define PROJECT_NAME "[ DEBUG ] "
#define TRACE(str, ...) DbgPrintEx(0, 0, PROJECT_NAME str"\n", __VA_ARGS__)
#else
#define TRACE(...)
#endif

#include "vcruntime/cstdint.h"
#include "pe/pe.h"
#include "exports/exports.h"

#include "helpers/struct.h"

#include "xorstr/xorstr.h"
#include "hash/hash.h"

#include "vcruntime/string.h"
#include "vcruntime/runtime.h"

#include "winapi/winapi.h"
#include "imports/imports.h"

#include "memory/memory.h"
 
#include "security/hide_process.h"
#include "security/protect_process.h"
#include "security/mapper_token.h"

#include "pte/pte.h"

#include "hook/function.h"

#define RVA(addr, size)			((PBYTE)(addr + *(DWORD*)(addr + ((size) - 4)) + size))