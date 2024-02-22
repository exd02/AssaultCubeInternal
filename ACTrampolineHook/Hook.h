#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include "Memory.h"


bool Detour32(BYTE* src, BYTE* dst, const int len); // GH hook
BYTE* TrampHook32(BYTE* src, BYTE* dst, const int len); // GH trampoline hook 

struct Hook
{
	bool bStatus{ false };

	BYTE* src{ nullptr };
	BYTE* dst{ nullptr };
	BYTE* PtrToGatewayFnPtr{ nullptr };
	uintptr_t len{ 0 };

	BYTE originalBytes[10]{ 0 };

	// constructors
	Hook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len);
	Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len);
	Hook();

	void Init(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len);

	void Enable();
	void Disable();
};