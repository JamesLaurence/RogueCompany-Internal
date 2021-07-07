#pragma once
#pragma warning(disable : 4244)
#include <Windows.h>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>

#include "settings.h"
#include "xorstr.hpp"
#include "structs.h"
#include "UE4_Basic.h"
#include "UE4_Classes.h"
#include "UE4_Core_structs.h"
#include "helper.h"
#include "util.h"
#include "render.h"
#include "core.h"
#include "font.h"

template<typename Ret>
Ret read(PVOID base) {
	return *(Ret*)base;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);