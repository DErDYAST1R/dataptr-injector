 #include "interface/interface.h"
#include <iostream>
#include <TlHelp32.h>
#include <vector>
#include "DllMapper/DllMapper.h"
#include "logger/logger.h"
#include <conio.h>

#include <thread>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include "util/LazyImporter.h"

bool IsProcessRunning(const std::string& exeName)
{
	bool isRunning = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		return false;
	}

	if (Process32First(snapshot, &entry)) {
		do {
			if (exeName == entry.szExeFile) {
				isRunning = true;
				break;
			}
		} while (Process32Next(snapshot, &entry));
	}

	CloseHandle(snapshot);
	return isRunning;
}
using namespace std;
#include <Windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <sddl.h>

auto PID(std::string name) -> int
{
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 entry{ };
	entry.dwSize = sizeof(PROCESSENTRY32);

	Process32First(snapshot, &entry);
	do
	{
		if (!name.compare(entry.szExeFile))
		{
			return entry.th32ProcessID;
		}

	} while (Process32Next(snapshot, &entry));
}
#include <fstream>
#include <string>
using namespace std;
Interface* kInterface;
uint8_t* raw_data = 0;
size_t data_size = 0;

#include <filesystem>
#include "mapper/intel_driver.hpp"
#include "mapper/kdmapper.hpp"
#include "mapper/driver.h"

void InjectorShit()
{
	DWORD pid = LI_FN(GetCurrentProcessId)();

	kInterface->ProectProcess(pid);
	std::string process;
	std::cout << "Enter Process Name : ";
	std::cin >> process;
	localPid = PID(process);

	LI_FN(Sleep)(3000);
	if (localPid == 0)
	{
		printf("\n cant find %s\n", process);
		LI_FN(Sleep)(5000);
		*(uintptr_t*)(0) = 0;
	}


	std::string current_path = std::filesystem::current_path().string();
	std::string dllname;
	std::cout << "\nEnter Dll : ";
	std::cin >> dllname;

	PVOID LocalImage = DllMapper::LoadLocalImageFromDisk(dllname.c_str());

	if (!LocalImage)
	{
		logger::set_error(("error 5"));
		LI_FN(Sleep)(5000);
		*(uintptr_t*)(0) = 0;
	}

	logger::set_warning(("Injecting...."));

	bool delay_for_free = false;

	if (!DllMapper::LoadModule(LocalImage, delay_for_free))
	{
		logger::set_error(("injection failed"));
		LI_FN(Sleep)(5000);
		*(uintptr_t*)(0) = 0;
	}


	if (kInterface->Unload())
	{
		logger::set_ok(("Injection Successful"));
		LI_FN(Sleep)(5000);
	}
	else
	{
		logger::set_error(("err #7"));
		LI_FN(Sleep)(5000);
		*(uintptr_t*)(0) = 0;
	}
}


#define EntityListOffset 0x1F16E28
#define LocalPlayerOffset 0x22b1528

int main()
{
	// 48 8B 05 A9 E9 05 00 NtUserSetDesktopColorTransform - DEV
		// 48 8B 05 D1 F9 05 00 NtUserHardErrorControl - FREE
				// 48 8B 05 59 F6 05 00 NtUserInitializeClientPfnArrays - FREE
				// 48 8B 05 81 FA 05 00 NtUserGetWindowMinimizeRect - Giraffe
				// 48 8B 05 25 01 06 00 NtUserGetDpiForCurrentProcess - FREE
				// 48 8B 05 7D 93 05 00 NtUserCreateActivationObject - FREE
	kInterface = new Interface(("NtUserSetDesktopColorTransform"));

	if (kInterface->ConnectToDriver())
	{
		// do driver loading here
	//	HANDLE iqvw64e_device_handle = intel_driver::Load();

	//	if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE)
	//	{
	//		//std::cout << "[-] Couldn't Load Driver iqvw64e.sys" << std::endl;
	//		return -1;
	//	}

	//	if (!kdmapper::MapDriver(iqvw64e_device_handle, RawData))
	//	{
		//	std::cout << "[-] Failder To Map Driver" << std::endl;
	//		intel_driver::Unload(iqvw64e_device_handle);
	//		return -1;
	//	}

	//	intel_driver::Unload(iqvw64e_device_handle);
//	}
//	else
		{
			DWORD pid = LI_FN(GetCurrentProcessId)();

			kInterface->ProectProcess(pid);

			InjectorShit();
		}

		LI_FN(Sleep)(5000);

		return 0;
	}
}

