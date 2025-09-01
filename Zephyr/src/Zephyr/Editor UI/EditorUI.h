#pragma once
#include <zppch.h>


class EditorUI
{
public:

    ~EditorUI() {
        if (ImGui::GetCurrentContext()) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }

    void InitEditorUI(GLFWwindow* window) {
        m_Window = window;
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        ImGui::StyleColorsDark();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void RenderEditorUI();

private:
    GLFWwindow* m_Window = nullptr;
};
