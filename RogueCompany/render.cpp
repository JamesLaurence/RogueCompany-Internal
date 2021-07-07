#include "render.h"
#include "UE4_Classes.h"
#include "bones.h"
#include "Discord.h"
#include "aimkeys.h"

uintptr_t keys[] = { VK_LSHIFT, VK_LCONTROL, VK_LBUTTON, VK_RBUTTON };
const char* keyItems[] = { "Shift", "Control", "LMB", "RMB" };
int aimbot_key = 3;

namespace Render {
	bool DrawFov = false;
	/*
	* Global Variables.
	*/
	const ImVec4 color = { 255.0,255.0,255.0,1 };
	const ImVec4 red = { 0.65,0,0,1 };
	const ImVec4 white = { 255.0,255.0,255.0,1 };
	const ImVec4 green = { 0.03,0.81,0.14,1 };
	const ImVec4 blue = { 0.21960784313,0.56470588235,0.90980392156,1.0 };

	static BOOL RenderInit = FALSE;
	BOOL status = FALSE;
	HWND hWnd;
	float width, height;

	HRESULT(WINAPI* PresentOriginal)(IDXGISwapChain*, UINT, UINT) = NULL;
	HRESULT(WINAPI* ResizeBuffersOriginal)(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) = NULL;

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext = NULL;
	ID3D11RenderTargetView* renderTargetView = NULL;
	WNDPROC WndProc;

	LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

		if (msg == WM_KEYUP && (wParam == VK_INSERT || (Settings.ShowMenu && wParam == VK_ESCAPE))) {
			Settings.ShowMenu = !Settings.ShowMenu;
			ImGui::GetIO().MouseDrawCursor = Settings.ShowMenu;
		}

		if (msg == WM_QUIT && Settings.ShowMenu) {
			exit(0);
		}

		if (Settings.ShowMenu) {
			ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
			return TRUE;
		}

		return CallWindowProcA(WndProc, hWnd, msg, wParam, lParam);
	}

	HRESULT Present(IDXGISwapChain* swapChain, UINT buffer, UINT syncInterval) {

		static auto beginScene = []() -> ImGuiWindow& {

			ImGui_ImplDX11_NewFrame(); {
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
				ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
				ImGui::Begin(xorstr_("##scene"), NULL, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

				auto& io = ImGui::GetIO();
				ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
				ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
			}

			return *ImGui::GetCurrentWindow();
		};

		if (!device) {

			swapChain->GetDevice(__uuidof(device), (VOID**)(&device));
			device->GetImmediateContext(&deviceContext);

			ID3D11Texture2D* renderTarget = NULL;
			swapChain->GetBuffer(0, __uuidof(renderTarget), (VOID**)(&renderTarget));
			device->CreateRenderTargetView(renderTarget, NULL, &renderTargetView);
			renderTarget->Release();

			ID3D11Texture2D* backBuffer = 0;
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (VOID**)&backBuffer);
			D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
			backBuffer->GetDesc(&backBufferDesc);


			DXGI_SWAP_CHAIN_DESC Window;
			swapChain->GetDesc(&Window);

			hWnd = Window.OutputWindow;

			width = (float)backBufferDesc.Width;
			height = (float)backBufferDesc.Height;
			backBuffer->Release();

			ImGui::GetIO().Fonts->AddFontFromMemoryTTF(arial, 16, 16);

			ImGui_ImplDX11_Init(hWnd, device, deviceContext);
			ImGui_ImplDX11_CreateDeviceObjects();
		}

		if (!RenderInit) {
			WndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProcHook);
			RenderInit = TRUE;
		}

		deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

		float closestDistance = FLT_MAX;
		APawn* closestPawn = NULL;

		std::vector<APawn*> pawns;
		auto& window = beginScene();

		/*
		* To handle errors.
		*/
		do {
			if (DrawFov)
			{
				window.DrawList->AddCircle(ImVec2(width / 2, height / 2), Settings.FOV, ImGui::GetColorU32({ 255.0f, 255.0f, 255.0f, 1.0f }), 64);
			}

			UWorld* World = Util::World->GetWorld();
			if (!World) break;
			//printf("\n-----------------------------------------------------------------------------\nWorld %p\n", World);

			UGameInstance* GameInstance = World->OwningGameInstance;
			if (!GameInstance) break;
			//printf("GameInstance %p\n", GameInstance);

			UPlayer* LocalPlayer = GameInstance->LocalPlayers[0];
			if (!LocalPlayer) break;
			//printf("LocalPlayer %p\n", LocalPlayer);

			APlayerController* PlayerController = LocalPlayer->PlayerController;
			if (!PlayerController) break;
			//printf("PlayerController %p\n", PlayerController);

			APawn* PlayerPawn = PlayerController->AcknowledgedPawn;
			if (!PlayerPawn) break;
			//printf("PlayerPawn %p\n", PlayerPawn);

			AKSPlayerState* PlayerState = (AKSPlayerState*)PlayerPawn->PlayerState;
			if (!PlayerState) break;
			//printf("PlayerState %p\n", PlayerState);

			AKSTeamState* TeamState = PlayerState->r_Team;
			if (!TeamState) break;
			//printf("TeamState %p\n", TeamState);

			for (auto levels = 0; levels < World->Levels.Num(); levels++) {

				if (!World->Levels.IsValidIndex(levels)) break;
				auto level = World->Levels[levels];

				if (!level) continue;

				for (auto actors = 0; actors < level->Actors.Num(); actors++) {

					if (!level || !level->Actors.IsValidIndex(actors)) break;

					AActor* actor = level->Actors[actors];
					if (!actor || !actor->RootComponent ||
						(PlayerPawn && PlayerPawn == actor))
						continue;

					auto name = Util::GetObjectName(actor);


					if (strstr(name, xorstr_("DefaultPVPBotCharacter_C")) ||
						strstr(name, xorstr_("MainCharacter_C"))) {

						pawns.push_back((APawn*)actor);
					}

				}

			}

			for (APawn* pawn : pawns) {

				if (!pawn) continue;

				USkeletalMeshComponent* mesh = pawn->Mesh;
				if (!mesh) continue;
				//printf("pawn mesh %p\n", mesh);

				AKSPlayerState* state = (AKSPlayerState*)pawn->PlayerState;
				if (!state) continue;
				//printf("pawn state %p\n", state);

				int eliminatedState = state->EliminatedState;
				if (eliminatedState != TRUE) continue;
				//printf("pawn eliminatedState %d\n", eliminatedState);

				AKSTeamState* pTeamState = state->r_Team;
				if (!pTeamState) continue;
				//printf("pawn pTeamState %p\n", pTeamState);

				auto color = ImGui::GetColorU32({ green });

				auto headPos = Util::GetBoneMatrix(mesh, 110).ToScreen(PlayerController);
				if (headPos.IsValid()) {

					if (!Util::LineOfSightTo(PlayerController, pawn) ||
						pTeamState->r_TeamNum == TeamState->r_TeamNum) {
						color = ImGui::GetColorU32({ 255.0f, 0.0, 0.0f, 1.0f });
					}
					else {

						headPos.X -= width / 2;
						headPos.Y -= height / 2;

						auto distance = headPos.distance();

						if (distance < Settings.FOV && distance < closestDistance) {

							closestDistance = distance;
							closestPawn = pawn;
						}
					}
				}
				
					
				if (pTeamState->r_TeamNum == TeamState->r_TeamNum) {
					color = ImGui::GetColorU32({ 0.0f, 191.0f, 255.0f, 1.0f });
				}

				auto box = Util::GetBoundingBox(mesh, pawn->RootComponent->RelativeLocation);

				auto min = box.Min.ToScreen(PlayerController);
				auto max = box.Max.ToScreen(PlayerController);
				auto headpos = Util::GetBoneMatrix(mesh, 110).ToScreen(PlayerController);
				auto ChestPos = Util::GetBoneMatrix(mesh, 178).ToScreen(PlayerController);
				auto lshoulder = Util::GetBoneMatrix(mesh, 69).ToScreen(PlayerController);
				auto lelbow = Util::GetBoneMatrix(mesh, 64).ToScreen(PlayerController);
				auto lhand = Util::GetBoneMatrix(mesh, 39).ToScreen(PlayerController);
				auto relbow = Util::GetBoneMatrix(mesh, 100).ToScreen(PlayerController);
				auto rhand = Util::GetBoneMatrix(mesh, 75).ToScreen(PlayerController);
				auto rshoulder = Util::GetBoneMatrix(mesh, 105).ToScreen(PlayerController);
				auto pelvis = Util::GetBoneMatrix(mesh, 1).ToScreen(PlayerController);
				auto llegup = Util::GetBoneMatrix(mesh, 22).ToScreen(PlayerController);
				auto llegdown = Util::GetBoneMatrix(mesh, 26).ToScreen(PlayerController);
				auto rlegup = Util::GetBoneMatrix(mesh, 10).ToScreen(PlayerController);
				auto rlegdown = Util::GetBoneMatrix(mesh, 14).ToScreen(PlayerController);
				auto lknee = Util::GetBoneMatrix(mesh, 21).ToScreen(PlayerController);
				auto ltoe = Util::GetBoneMatrix(mesh, 18).ToScreen(PlayerController);
				auto rtoe = Util::GetBoneMatrix(mesh, 6).ToScreen(PlayerController);
				auto rknee = Util::GetBoneMatrix(mesh, 9).ToScreen(PlayerController);


				if (min.IsValid() && max.IsValid()) {

					auto topLeft = ImVec2(min.X, min.Y);
					auto bottomRight = ImVec2(max.X, max.Y);
					auto topRight = ImVec2(bottomRight.x, topLeft.y);
					auto bottomLeft = ImVec2(topLeft.x, bottomRight.y);
					auto bottomCenter = ImVec2(((topLeft.x - 20.0f) + bottomRight.x) / 2.0f, topLeft.y + 20.0f);

					{
						if (Settings.CornerESP)
						{
							// Top Left.
							window.DrawList->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + ((bottomRight.y - topLeft.y) / 3)), color, 1.0);
							window.DrawList->AddLine(topLeft, ImVec2(topLeft.x + ((bottomRight.x - topLeft.x) / 3), topLeft.y), color, 1.0);


							// Bottom Left
							window.DrawList->AddLine(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - ((bottomRight.y - topLeft.y) / 3)), color, 1.0);
							window.DrawList->AddLine(bottomLeft, ImVec2(bottomLeft.x + ((bottomRight.x - topLeft.x) / 3), bottomLeft.y), color, 1.0);

							// Top Right
							window.DrawList->AddLine(topRight, ImVec2(topRight.x, topRight.y + ((bottomRight.y - topLeft.y) / 3)), color, 1.0);
							window.DrawList->AddLine(topRight, ImVec2(topRight.x - ((bottomRight.x - topLeft.x) / 3), topRight.y), color, 1.0);

							// Bottom Right
							window.DrawList->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - ((bottomRight.y - topLeft.y) / 3)), color, 1.0);
							window.DrawList->AddLine(bottomRight, ImVec2(bottomRight.x - ((bottomRight.x - topLeft.x) / 3), bottomRight.y), color, 1.0);

							// Filled Box
							window.DrawList->AddRectFilled(ImVec2(min.X, min.Y), ImVec2(max.X, max.Y), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 0.15 }));
						}
						if (Settings.HealEsp)
						{
							float enhealth = *(float*)((uintptr_t)pawn + 0x23F8);
							char buffer[20];
							sprintf_s(buffer, "Health : %0.f", enhealth);
							window.DrawList->AddText(ImVec2(bottomRight), color, buffer);
						}
						if (Settings.Skeleton)
						{
							//Left Side
							window.DrawList->AddLine(ImVec2(headpos.X, headpos.Y), ImVec2(ChestPos.X, ChestPos.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(ChestPos.X, ChestPos.Y), ImVec2(lshoulder.X, lshoulder.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(lshoulder.X, lshoulder.Y), ImVec2(lelbow.X, lelbow.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(lelbow.X, lelbow.Y), ImVec2(lhand.X, lhand.Y), ImGui::GetColorU32(blue), 2);
							//Right Side
							window.DrawList->AddLine(ImVec2(ChestPos.X, ChestPos.Y), ImVec2(rshoulder.X, rshoulder.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(rshoulder.X, rshoulder.Y), ImVec2(relbow.X, relbow.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(relbow.X, relbow.Y), ImVec2(rhand.X, rhand.Y), ImGui::GetColorU32(blue), 2);
							//Lower Left
							window.DrawList->AddLine(ImVec2(ChestPos.X, ChestPos.Y), ImVec2(pelvis.X, pelvis.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(pelvis.X, pelvis.Y), ImVec2(llegup.X, llegup.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(pelvis.X, pelvis.Y), ImVec2(llegdown.X, llegdown.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(lknee.X, lknee.Y), ImVec2(ltoe.X, ltoe.Y), ImGui::GetColorU32(blue), 2);
							//Lower Right
							window.DrawList->AddLine(ImVec2(pelvis.X, pelvis.Y), ImVec2(rlegup.X, rlegup.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(rlegup.X, rlegup.Y), ImVec2(rlegdown.X, rlegdown.Y), ImGui::GetColorU32(blue), 2);
							window.DrawList->AddLine(ImVec2(rknee.X, rknee.Y), ImVec2(rtoe.X, rtoe.Y), ImGui::GetColorU32(blue), 2);
						}
						if (Settings.ESP)
						{
							window.DrawList->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + ((bottomRight.y - topLeft.y))), color, 1.0);
							window.DrawList->AddLine(topLeft, ImVec2(topLeft.x + ((bottomRight.x - topLeft.x)), topLeft.y), color, 1.0);
							window.DrawList->AddLine(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - ((bottomRight.y - topLeft.y))), color, 1.0);
							window.DrawList->AddLine(bottomLeft, ImVec2(bottomLeft.x + ((bottomRight.x - topLeft.x)), bottomLeft.y), color, 1.0);
							window.DrawList->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - ((bottomRight.y - topLeft.y))), color, 1.0);
							window.DrawList->AddLine(bottomRight, ImVec2(bottomRight.x - ((bottomRight.x - topLeft.x)), bottomRight.y), color, 1.0);

						}
						if (Settings.HeadCircle)
						{
							window.DrawList->AddCircle(ImVec2(headpos.X, headpos.Y), (ChestPos.X, ChestPos.Y), ImGui::GetColorU32(blue), 2);
						}

						if (Settings.PlayerName) {

							FString playerName = state->PlayerNamePrivate;
							if (playerName.IsValid()) {

								CHAR buffer[32]; // -> Name won't be longer than 32 characters, so lets not abuse the stack.
								strcpy_s(buffer, sizeof(buffer), playerName.c_str());

								auto size = ImGui::GetFont()->CalcTextSizeA(window.DrawList->_Data->FontSize, FLT_MAX, NULL, buffer);
								window.DrawList->AddText(ImVec2(bottomCenter.x - size.x / 2.0f, bottomCenter.y - size.y), color, buffer);
							}
						}

					}
				}
			}

			status = TRUE;

		} while (FALSE); // executes ONCE.

		if (Settings.Crosshair) {
			window.DrawList->AddLine(ImVec2(width / 2 - 15, height / 2), ImVec2(width / 2 + 15, height / 2), ImGui::GetColorU32(red), 2);
			window.DrawList->AddLine(ImVec2(width / 2, height / 2 - 15), ImVec2(width / 2, height / 2 + 15), ImGui::GetColorU32(red), 2);
		}


		/*
		* Draw Menu here.
		*/
		if (Settings.ShowMenu) {

			ImGuiStyle* style = &ImGui::GetStyle();

			style->WindowPadding = ImVec2(15, 15);
			style->WindowRounding = 5.0f;
			style->FramePadding = ImVec2(5, 5);
			style->FrameRounding = 4.0f;
			style->ItemSpacing = ImVec2(12, 8);
			style->ItemInnerSpacing = ImVec2(8, 6);
			style->IndentSpacing = 25.0f;
			style->ScrollbarSize = 15.0f;
			style->ScrollbarRounding = 9.0f;
			style->GrabMinSize = 5.0f;
			style->GrabRounding = 3.0f;

			style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
			style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
			style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
			style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
			style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
			style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
			style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
			style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
			style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

			static int Tab = 0;
			ImGui::Begin(xorstr_(" Rogue Company Multi Hack"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize); {
				ImGui::SetWindowSize(ImVec2(500, 300));
				if (ImGui::Button("Aimbot", ImVec2(120, 45))) Tab = 0;
				ImGui::SameLine();
				if (ImGui::Button("Visuals", ImVec2(120, 45))) Tab = 1;
				ImGui::SameLine();
				ImGui::Text("");

				if (Tab == 0) {
					ImGui::Text("[+] World Aim Options");
					ImGui::Checkbox(xorstr_("Toggle Aimbot"), &Settings.Aimbot);

					if (Settings.Aimbot)
					{
						ImGui::Combo(xorstr_("Aimbot Key"), &aimbot_key, keyItems, IM_ARRAYSIZE(keyItems));
						ImGui::Checkbox(xorstr_("Shoot Downed"), &Settings.ShootDowned);
					}

					ImGui::Checkbox(xorstr_("Rage Aim [+] Higher Ban Risk"), &Settings.HeadBox);
					if (&Settings.HeadBox)
					{
						DrawFov = false;
					}
					ImGui::Checkbox(xorstr_("Legit Aim"), &Settings.ChestBox);
					if (Settings.ChestBox)
					{
						DrawFov = true;

						ImGui::SliderFloat(xorstr_("Aim Fov"), &Settings.FOV, 0.0f, 300.0f);

					}
					ImGui::Checkbox(xorstr_("Crosshair"), &Settings.Crosshair);


				}
				if (Tab == 1)
				{
					ImGui::Text("[+] World Visual Options");
					//ImGui::SliderFloat(xorstr_("Camera FOV"), &Settings.FOV, 80.0f, 180.0f);
					//ImGui::Checkbox(xorstr_("Glow"), &Settings.Glow);
					ImGui::Checkbox(xorstr_("2D Box"), &Settings.ESP);
					ImGui::Checkbox(xorstr_("2D Corner Box"), &Settings.CornerESP);
					ImGui::Checkbox(xorstr_("Player Names"), &Settings.PlayerName);
					ImGui::Checkbox(xorstr_("Skeleton"), &Settings.Skeleton);
					ImGui::Checkbox(xorstr_("Health ESP"), &Settings.HealEsp);
					ImGui::Checkbox(xorstr_("Head Circle"), &Settings.HeadCircle);
				}


			}
			ImGui::End();

		}
		ImGui::End();
		ImGui::Render();

		if (!status) {
			Core::Pawn = closestPawn = NULL;
		}
		else {
			Core::Pawn = closestPawn;
		}

		return PresentOriginal(swapChain, buffer, syncInterval);
	}

	HRESULT ResizeBuffers(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		// SHUTDOWN RENDERER
		ImGui_ImplDX11_Shutdown();
		renderTargetView->Release();
		renderTargetView = nullptr;

		deviceContext->Release();
		deviceContext = nullptr;

		device->Release();
		device = nullptr;

		return ResizeBuffersOriginal(SwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	}

	VOID Init(HMODULE module)
	{
		auto PresentDC = Helper::PatternScan(Discord::GetDiscordModuleBase(), "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B D9 41 8B F8");
		if (!PresentDC)
			return;

		auto ResizeDC = Helper::PatternScan(Discord::GetDiscordModuleBase(), "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8B D9 41 8B F8");
		if (!ResizeDC)
			return;

		DISCORD.HookFunction(PresentDC, (uintptr_t)Present, (uintptr_t)&PresentOriginal);
	}
}