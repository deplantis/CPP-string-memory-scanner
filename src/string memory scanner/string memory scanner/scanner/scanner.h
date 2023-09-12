#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#pragma comment(lib, "ntdll.lib")

typedef enum _MEMORY_INFORMATION_CLASS
{
	MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;

extern "C" NTSYSCALLAPI NTSTATUS ZwReadVirtualMemory(
	  HANDLE  hProcess,
	  LPCVOID lpBaseAddress,
	  LPVOID  lpBuffer,
	  SIZE_T  nSize,
	  SIZE_T * lpNumberOfBytesRead
);

extern "C" NTSYSCALLAPI NTSTATUS ZwWriteVirtualMemory(
	  HANDLE  hProcess,
	  LPVOID  lpBaseAddress,
	  LPCVOID lpBuffer,
	  SIZE_T  nSize,
	  SIZE_T * lpNumberOfBytesWritten
);


extern "C" NTSYSCALLAPI NTSTATUS NtQueryVirtualMemory(
	HANDLE                   ProcessHandle,
	PVOID                    BaseAddress,
	MEMORY_INFORMATION_CLASS MemoryInformationClass,
	PVOID                    MemoryInformation,
	SIZE_T                   MemoryInformationLength,
	PSIZE_T                  ReturnLength
);


class scanner
{
public:
	scanner(DWORD proccesid);
	~scanner();
	void scanstring(std::string stringtofind);
	void showallstrings();
	void cleanstrings();
private:
	void debug(std::string printthatshit);
private:
	std::vector<uintptr_t> addres;
	MEMORY_BASIC_INFORMATION info; 

	HANDLE hProcess;
	SYSTEM_INFO si;
	char* currentmemorypage = 0;
};