#pragma once
#include "stdafx.h"

#define RVA(addr, size) ((PBYTE)(addr + *(DWORD*)(addr + ((size) - 4)) + size))

namespace Util {

	PIMAGE_NT_HEADERS getHeader(HMODULE base);
	PBYTE FindPattern(HMODULE module, LPCSTR pattern, LPCSTR mask);
}
#pragma once

#include <vector>

class Helper
{
public:
    /// <summary>
    /// Scan for a given byte pattern on a moduleAdress.\n
    /// Example: PatternScan(GetModuleHandleW(L"engine.dll"), "53 56 57 8B DA 8B F9 FF 15")
    /// </summary>
    /// <param name="moduleAdress">Base of the moduleAdress to search</param>
    /// <param name="signature">signature IDA-style byte array pattern</param>
    /// <returns>Address of the first occurence</returns>
    static uintptr_t PatternScan(uintptr_t moduleAdress, const char* signature);

    // ********************************************************************************
    /// <summary>
    /// Open console CMD
    /// </summary>
    // ********************************************************************************
    static void OpenConsole();
};