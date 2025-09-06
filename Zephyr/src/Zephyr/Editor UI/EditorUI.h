#pragma once
#include <zppch.h>
#include "Zephyr/Log.h"
namespace Zephyr {
    class EditorUI
    {
    public:
        EditorUI();
        ~EditorUI();
        void InitEditorUI(GLFWwindow* window);
        void RenderEditorUI();

        void OnWindowResize(int width, int height) {
            m_AppWidth = width;
            m_AppHeight = height;
        }

    private:
        GLFWwindow* m_AppWindow = nullptr;
        int m_AppWidth;
        int m_AppHeight;
    };
}