#include <Windows.h>

#include "ModUtils.h"

using namespace ModUtils;

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Log("Activating ultrawide fix...");
	std::vector<unsigned char> originalBytes = { 0x8b, 0x01, 0x85, 0xc0, 0x74, 0x42, 0x44, 0x8b, 0x59, 0x04 };
	std::vector<unsigned char> newBytes = { 0x8b, 0x01, 0x85, 0xc0, 0xeb, 0x42, 0x44, 0x8b, 0x59, 0x04 };
	uintptr_t patchAddress = SigScan(originalBytes);
	if (patchAddress != 0)
	{
		Replace(patchAddress, originalBytes, newBytes);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, &MainThread, 0, 0, NULL);
	}
	return 1;
}