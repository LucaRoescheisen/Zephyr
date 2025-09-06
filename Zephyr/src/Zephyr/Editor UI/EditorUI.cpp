#include "zppch.h"
#include "EditorUI.h"

namespace Zephyr {

	EditorUI::EditorUI()
		: m_AppWindow(nullptr), m_AppWidth(1920), m_AppHeight(1080)
	{
	}

	EditorUI::~EditorUI() {
	 if (ImGui::GetCurrentContext()) {
	     ImGui_ImplOpenGL3_Shutdown();
	     ImGui_ImplGlfw_Shutdown();
	     ImGui::DestroyContext();
		}
	}

	void EditorUI::InitEditorUI(GLFWwindow* window) {
		m_AppWindow = window;
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		ImGui::StyleColorsDark();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		ImGuiStyle* style = &ImGui::GetStyle();
		style->Colors[ImGuiCol_TitleBg] =       ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.0f);
		style->Colors[ImGuiCol_Tab] =			ImVec4(0.70f, 0.70f, 0.70f, 1.0f);
		style->Colors[ImGuiCol_TabActive] =		ImVec4(0.60f, 0.60f, 0.60f, 1.0f);
		style->Colors[ImGuiCol_WindowBg] =		ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
		style->Colors[ImGuiCol_Text] =			ImVec4(0.0f , 0.0f , 0.0f , 1.0f);
		style->Colors[ImGuiCol_MenuBarBg] =		ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
		style->Colors[ImGuiCol_PopupBg] =		ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
	}

	void EditorUI::RenderEditorUI() {


		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				ImGui::MenuItem("Open", "ctrl + o");
				ImGui::MenuItem("Close");
				ImGui::MenuItem("Save", "ctrl + s");
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}


		//Scene Window
		ImGui::SetNextWindowSize(ImVec2(m_AppWidth - 400, (float)(m_AppHeight * 0.75)), ImGuiCond_Always);
		ImGui::Begin("Scene Window", nullptr, ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(0, 20), ImGuiCond_Always);
		ImGui::Text("Scene View");
		//ImGui::Image((ImTextureID)sceneWindowBuffer.ReturnSceneTexture(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();


		ImGui::SetNextWindowPos(ImVec2(m_AppWidth - 400, 20), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
		ImGui::Begin("Hello, ImGui!", nullptr, ImGuiWindowFlags_NoMove);
		ImGui::Text("This is a HUD/editor UI");
		ImGui::Button("Click Me");
		ImGui::End();

	

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	};


}
