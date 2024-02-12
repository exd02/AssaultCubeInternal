#pragma once

#include <vector>

namespace Memory
{
	HMODULE GetModuleHandleByName(const wchar_t* modName);
	bool Patch(BYTE* destination, BYTE* source, unsigned int size);
	uintptr_t FindDMAAddy(uintptr_t address, std::vector<uintptr_t> offsets);
};

