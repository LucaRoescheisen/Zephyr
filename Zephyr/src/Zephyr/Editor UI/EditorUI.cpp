#include "zppch.h"
#include "EditorUI.h"



void EditorUI::RenderEditorUI() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Appearing);
	ImGui::Begin("Hello, ImGui!", nullptr, ImGuiWindowFlags_NoMove);
	ImGui::Text("This is a HUD/editor UI");
	ImGui::Button("Click Me");
	ImGui::End();



	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	
	




};