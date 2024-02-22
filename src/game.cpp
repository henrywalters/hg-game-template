//
// Created by henry on 4/12/23.
//
#include "game.h"

#include <hagame/graphics/windows.h>

#if USE_IMGUI
#include "imgui.h"
#include "imgui_demo.cpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif

using namespace hg::graphics;

void Game::onInit() {
#if !HEADLESS
    m_window = Windows::Create(GAME_NAME, GAME_SIZE);

    Windows::Events.subscribe(WindowEvents::Close, [&](Window* window) {
        running(false);
    });

    Windows::Events.subscribe(WindowEvents::Resize, [&](Window* window) {

    });
#endif

#if USE_IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(m_window->window(), true);
    ImGui_ImplOpenGL3_Init("#version 300 es");
#endif
}

void Game::onBeforeUpdate() {
#if !HEADLESS
    m_window->clear();
#endif

#if USE_IMGUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#endif
}

void Game::onAfterUpdate() {
#if USE_IMGUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

#if !HEADLESS
    m_window->render();
#endif
}

void Game::onDestroy() {
    // CLEAN UP
}

void Game::onUpdate(double dt) {
    // FILL ME IN!
#if USE_IMGUI
    ImGui::Begin("Demo Window");
    ImGui::Text(("DT: " + std::to_string(dt)).c_str());
    ImGui::End();
#endif
}