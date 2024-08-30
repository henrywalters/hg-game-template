//
// Created by henry on 4/12/23.
//
#include "game.h"

#include <hagame/graphics/windows.h>
#include <hagame/core/assets.h>
#include <hagame/common/scenes/loading.h>
#include <hagame/utils/profiler.h>

#include "scenes/mainMenu.h"

#if USE_IMGUI
#include "imgui.h"
#include "imgui_demo.cpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "common/gameState.h"

#endif

using namespace hg::graphics;
using namespace hg::utils;
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

    Profiler::Start(GAME_NAME);

    auto state = GameState::Get();

#if !HEADLESS
    m_window->setVSync(state->persistentSettings.vsync);
    m_window->clear();
#endif

#if USE_IMGUI

    if (state->persistentSettings.debugLevel > 0) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
#endif
}

void Game::onAfterUpdate() {

    auto state = GameState::Get();

    Profiler::End(GAME_NAME);

#if USE_IMGUI

    if (state->persistentSettings.debugLevel > 0) {

        auto vec = std::vector<float>();
        vec.reserve(m_fpsHistory.size());
        std::move(std::begin(m_fpsHistory), std::end(m_fpsHistory), std::back_inserter(vec));

        ImGui::Begin("Statistics");
        ImGui::Text("FPS: %i", static_cast<int>(m_fpsMean));
        ImGui::PlotLines("FPS", vec.data(), vec.size(), 0, nullptr, 0, FLT_MAX, ImVec2(0, 100));
        for (const auto& [key, profile] : Profiler::Profiles()) {
            ImGui::Text("%s: %ius", key.c_str(), static_cast<int>(profile.average() * 1000000));
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
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

    auto state = GameState::Get();

    if (state->persistentSettings.debugLevel > 0) {
        m_fpsHistory.push_back(1.0 / dt);
        m_fpsSum += 1.0 / dt;

        if (m_fpsHistory.size() >= FPS_HISTORY_SIZE) {
            m_fpsSum -= m_fpsHistory.front();
            m_fpsHistory.pop_front();
        }

        m_fpsMean = m_fpsSum / m_fpsHistory.size();

        if (1.0 / dt > m_maxFps) {
            m_maxFps = 1.0 / dt;
        }
    }

#if !HEADLESS
#if USE_CONSOLE
    if (m_console) {
        m_console->scroll(m_window->input.devices.keyboardMouse()->axes[MouseAxes::WheelY]);
        m_console->update(dt);
    }
#endif
#endif
}