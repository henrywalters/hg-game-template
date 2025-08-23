//
// Created by henry on 8/13/25.
//
#include "editor.h"
#include "../systems/renderer.h"

//
// Created by henry on 8/16/24.
//

#include <hagame/graphics/windows.h>

using namespace hg;
using namespace hg::graphics;

Editor::Editor(hg::graphics::Window *window):
        m_window(window),
        m_editor(std::make_unique<hge::Editor>(this))
{}

void Editor::onInit() {
    auto state = GameState::Get();

    addSystem<Renderer>(m_window);

    m_editor->onNewScene = [&, state](){
        game()->scenes()->active()->clear();
    };

    m_editor->onReset = [&, state](){
        state->elapsedTime = 0;
        state->running = false;
    };

    m_editor->onPause = [&, state]() {
        state->running = false;
    };

    m_editor->onPlay = [&, state]() {
        state->running = true;
    };
}


void Editor::onUpdate(double dt) {
    auto state = GameState::Get();

    auto renderer = getSystem<Renderer>();

    m_editor->render(
            m_window->input.devices.keyboardMouse()->mousePosition(),
            true,
            hg::Recti(hg::Vec2i::Zero(), m_window->size()),
            renderer->projection,
            renderer->view
    );

    ImGui::Begin("Runtime");
    ImGui::Text("Elapsed Time: %f", state->elapsedTime);

    // hge::enumField("Test", &testEnum, ENUMS(TestEnum));

    ImGui::End();

    auto texture = renderer->m_renderPasses.get(RenderMode::Combined)->textures[0].get();
    m_editor->setOutput((void*)texture->id, texture->size);

    if (state->running) {
        state->elapsedTime += dt;
    }
}

void Editor::resize() {

}
