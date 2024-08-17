//
// Created by henry on 4/12/23.
//
#include "game.h"

#include <hagame/graphics/windows.h>
#include <hagame/core/assets.h>
#include <hagame/common/scenes/loading.h>

#include "scenes/mainMenu.h"

#if USE_IMGUI
#include "imgui.h"
#include "imgui_demo.cpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif

using namespace hg::graphics;
using namespace hg::input::devices;

void Game::onInit() {
#if !HEADLESS
    m_window = Windows::Create(GAME_NAME, GAME_SIZE);

    Windows::Events.subscribe(WindowEvents::Close, [&](Window* window) {
        running(false);
    });

    Windows::Events.subscribe(WindowEvents::Resize, [&](Window* window) {

    });

    auto defaultFont = hg::loadFont("8bit", hg::ASSET_DIR + "fonts/8bit.ttf");
    defaultFont->fontSize(16);
    auto lgFont = hg::loadFont("8bit_lg", hg::ASSET_DIR + "fonts/8bit.ttf");
    lgFont->fontSize(24);

    hg::Loading::Settings settings;
    settings.font = SPLASH_FONT;
    settings.logo = SPLASH_SCREEN;
    settings.version = GAME_VERSION;

    auto loading = static_cast<hg::Loading*>(scenes()->add<hg::Loading>("loading", m_window, settings));

    loading->onFinish = [&]() {

#if USE_CONSOLE

        m_console = std::make_unique<hg::Console>(hg::getFont("8bit"), m_window->size(), hg::Vec2i(m_window->size()[0], 26 * 10));

        m_window->input.devices.keyboardMouse()->events.subscribe(KeyboardEvent::KeyPressed, [&](auto keyPress) {
            if (keyPress.key == '`') {
                m_console->toggle();
            }

            if (!m_console->isOpen()) {
                return;
            }

            if (keyPress.key == GLFW_KEY_BACKSPACE) {
                m_console->backspace();
            }

            if (keyPress.key == GLFW_KEY_ENTER) {
                m_console->submit();
            }

            if (keyPress.key == GLFW_KEY_UP) {
                m_console->prevHistory();
            }

            if (keyPress.key == GLFW_KEY_DOWN) {
                m_console->nextHistory();
            }
        });

        m_window->input.devices.keyboardMouse()->events.subscribe(KeyboardEvent::TextInput, [&](auto keyPress) {
            if (m_console->status() == hg::Console::Status::Open) {
                m_console->newChar(keyPress.key);
            }
        });

#endif

        scenes()->add<MainMenu>("main_menu", m_window);
        scenes()->activate("main_menu");
    };

    scenes()->activate("loading");
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
#if USE_CONSOLE
    if (m_console) {
        m_console->render();
    }
#endif
    m_window->render();
#endif
}

void Game::onDestroy() {
    // CLEAN UP
}

void Game::onUpdate(double dt) {
    // FILL ME IN!
#if !HEADLESS
#if USE_CONSOLE
    if (m_console) {
        m_console->scroll(m_window->input.devices.keyboardMouse()->axes[MouseAxes::WheelY]);
        m_console->update(dt);
    }
#endif
#endif

#if USE_IMGUI
    ImGui::Begin("Demo Window");
    ImGui::Text(("DT: " + std::to_string(dt)).c_str());
    ImGui::End();
#endif
}