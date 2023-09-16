#include "scanner.h"

scanner::scanner(DWORD proccesid)
{
	GetSystemInfo(&si);
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, proccesid);
}

scanner::~scanner()
{
	CloseHandle(hProcess); 
}

void scanner::scanstring(std::string& stringtofind)
{
	while (currentmemorypage < si.lpMaximumApplicationAddress)
	{
		NtQueryVirtualMemory(hProcess, currentmemorypage, MemoryBasicInformation, &info, sizeof(info), 0);

		if (info.State == MEM_COMMIT)
		{
			if (info.Protect == PAGE_READWRITE)
			{
				std::string buffer;
				buffer.resize(info.RegionSize + info.RegionSize / 2); // so the buffer don"t overflow

				ZwReadVirtualMemory(hProcess, currentmemorypage, &buffer.at(0), info.RegionSize, 0);

				for (int begin = 0; begin < info.RegionSize; begin++)
				{
					if (buffer[begin] == stringtofind.at(0))
					{
						std::string stringbuffer;

						for (int copy = 0; copy < stringtofind.size(); copy++)
						{
							stringbuffer += buffer[begin + copy];
						}
						 
						// find all strings that contain the word of the string that need to be searched
						if (stringtofind.find(stringbuffer) != std::string::npos)
						{
							addres.push_back((uintptr_t)currentmemorypage + begin);
						}

						// find all strings THAT exactly and exactly look like the string that need to be searched
						/*if (stringtofind == stringbuffer)
						{
							addres.push_back((uintptr_t)currentmemorypage + begin);
						}*/
					}

				}
			}
		}

		currentmemorypage += info.RegionSize;
	}

	currentmemorypage = 0;
}

void scanner::cleanstrings()
{
	std::string replacestring = "wblch";
	char buffer[7];
	for (auto& addresaddres : addres)
	{

		ZwReadVirtualMemory(hProcess, (LPVOID)addresaddres, &buffer, sizeof(buffer) + 1, 0);
		debug("memory addres:" + addresaddres);
		debug("memory addres readed string: " + std::string(buffer));
		std::cout << std::hex << "addres found: " << " " << addresaddres << "\n";

		ZwWriteVirtualMemory(hProcess, (LPVOID)addresaddres, &replacestring.c_str()[0], replacestring.size() + 1, 0); // WRITE.
		ZwReadVirtualMemory(hProcess, (LPVOID)addresaddres, &buffer, sizeof(buffer) + 1, 0);
		std::cout << "memory addres string after writed to it: " << buffer << "\n";
	}
}

void scanner::debug(std::string printthatshit)
{
#ifdef yes
	std::cout << printthatshit << "\n";
#endif 
}

std::vector<uintptr_t> scanner::returnaddreses()
{
	return addres;
}
