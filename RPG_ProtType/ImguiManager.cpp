//===================================================================================================================================
//�yImguiManager.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/18
// [�X�V��]2019/10/18
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "ImguiManager.h"
#include "../RPG_ProtType/Imgui/imgui_impl_dx9.h"
#include "../RPG_ProtType/Imgui/imgui_impl_win32.h"
#include "Direct3D9.h"

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
ImguiManager::ImguiManager(HWND wnd)
{
	setRootDirectory();
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	// Enable docking(available in imgui `docking` branch at the moment)

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(wnd);
	ImGui_ImplDX9_Init(getDevice());
}


//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
ImguiManager::~ImguiManager()
{
	setRootDirectory();
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//===================================================================================================================================
//�y�V�K�t���[���̊J�n�z
// beginFrame()�`render()�ɁAbeginImGui()�`endImGui()�����s���邱�ƂŁAGui�E�B���h�E���쐬����B
//===================================================================================================================================
void ImguiManager::beginFrame()
{
	// Start the Dear ImGui frame
	setRootDirectory(); 
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}
//===================================================================================================================================
//�y�X�V�z
// [2019/9/19�F����]GUI�E�B���h�E�̍쐬�T���v���B
//===================================================================================================================================
void ImguiManager::update()
{
	//-------------------------------------------------------------------------------------------------------------------------------
	//Sample
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	//-------------------------------------------------------------------------------------------------------------------------------

}

//===================================================================================================================================
//�y�`��z
// with[ImGui::EndFrame]�F�`�撼�O�Ńt���[���̍쐬���I������B
//===================================================================================================================================
void ImguiManager::render()
{
	//getDevice()->SetRenderState(D3DRS_ZENABLE, false);
	//getDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//getDevice()->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//===================================================================================================================================
//�yImGui�̊J�n�z
//===================================================================================================================================
void ImguiManager::beginImGui(const char* name)
{
	ImGui::Begin(name);
}
//===================================================================================================================================
//�yImGui�̊J�n�z
//===================================================================================================================================
void ImguiManager::beginImGui(const char* name,bool* open)
{
	ImGui::Begin(name,open);
}

//===================================================================================================================================
//�yImGui�̏I���z
//===================================================================================================================================
void ImguiManager::endImGui()
{
	ImGui::End();
}

//===================================================================================================================================
//�ygetter�z
//===================================================================================================================================
D3DCOLOR ImguiManager::getClearColor()
{
	D3DCOLOR color;

	color = D3DCOLOR_RGBA((int)(clearColor.x*255.0f), (int)(clearColor.y*255.0f), (int)(clearColor.z*255.0f), (int)(clearColor.w*255.0f));

	return color;
}

//===================================================================================================================================
//�y�z
//===================================================================================================================================
void ImguiManager::reset()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}
