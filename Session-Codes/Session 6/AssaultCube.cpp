#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"

int main()
{
	DWORD procId = GetProcId(L"ac_client.exe");
	uintptr_t moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	//Get Handle to Process
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

	//Resolve base address of the pointer chain
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x10f4f4;

	std::cout << "DynamicPtrBaseAddr = " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	//Resolve ammo pointer chain
	std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
	uintptr_t ammoAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, ammoOffsets);

	std::cout << "ammoAddr = " << "0x" << std::hex << ammoAddr << std::endl;

	int ammoValue = 0;
	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "Curent ammo = " << std::dec << ammoValue << std::endl;

	int newAmmo = 6900;
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);
	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "New ammo = " << std::dec << ammoValue << std::endl;

	getchar();

	return 0;
}