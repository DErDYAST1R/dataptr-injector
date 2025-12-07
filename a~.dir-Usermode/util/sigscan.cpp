#include "sigscan.h"

scanner::scanner(DWORD proccesid)
{
	GetSystemInfo(&si);
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, proccesid);
}

scanner::~scanner()
{
	CloseHandle(hProcess);
}

uintptr_t scanner::findsignature(std::string& pattern, std::string& mask)
{
	while (currentmemorypage < si.lpMaximumApplicationAddress)
	{
		NtQueryVirtualMemory(hProcess, currentmemorypage, MemoryBasicInformation, &info, sizeof(info), 0);

		if (info.State == MEM_COMMIT)
		{
			std::string buffer;
			buffer.resize(info.RegionSize + info.RegionSize / 2); // so the buffer don"t overflow

			ZwReadVirtualMemory(hProcess, currentmemorypage, &buffer.at(0), info.RegionSize, 0);

			for (int begin = 0; begin < info.RegionSize; begin++)
			{
				if (buffer[begin] == pattern.at(0))
				{
					std::string stringbuffer;

					for (int copy = 0; copy < pattern.size(); copy++)
					{
						if (mask.at(copy) == '?')
						{
							stringbuffer += "\x00"s;
						}
						else
						{
							stringbuffer += buffer[(begin)+copy];
						}
					}

					if (pattern == stringbuffer)
					{
						addres.push_back((uintptr_t)currentmemorypage + begin);
					}
				}
			}

		}

		currentmemorypage += info.RegionSize;
	}

	currentmemorypage = 0;

	if (addres.empty())
	{
		return 0; // return 0, a error that nothing got found
	}
	else
	{
		return addres.at(0); // return the first addres that the scanner found
	}
}

void scanner::debug(std::string printthatshit)
{
#ifdef debug
	std::cout << printthatshit << "\n";
#endif 
}

std::vector<uintptr_t> scanner::returnaddreses()
{
	return addres;
}