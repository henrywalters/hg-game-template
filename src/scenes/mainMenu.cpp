//
// Created by henry on 8/16/24.
//
#include <hagame/core/game.h>
#include <hagame/ui/elements/divider.h>
#include <hagame/ui/elements/label.h>
#include <hagame/core/assets.h>
#include "mainMenu.h"
#include "../common/ui.h"
#include "../common/actionMap.h"
#include "../common/gameState.h"

using namespace hg;
using namespace hg::graphics;

MainMenu::MainMenu(hg::graphics::Window *window):
    m_window(window),
    m_menu(Rect(Vec2::Zero(), window->size().cast<float>()))
{

}

void MainMenu::onInit() {
    m_menu.root()->style.margin = hg::ui::offset(1. / 3, 1. / 6, 1. / 3, 1. / 6, ui::Unit::Percent);
    m_menu.root()->style.padding = hg::ui::offset(25);
    m_menu.root()->style.backgroundColor = MENU_BG;
    struct MenuItem {
        std::string label;
        std::function<void()> onSelect;
    };

    std::vector<MenuItem> menuItems {

    };

#ifndef __EMSCRIPTEN__
    menuItems.push_back({
        "Quit to Desktop",
        [&]() {
            game()->running(false);
        }
    });
#endif

    std::vector rowSizes {0.15, 0.1};

    for (int i = 0; i < menuItems.size(); i++) {
        rowSizes.push_back(0.75 / menuItems.size());
    }

    auto menu = m_menu.addElement<ui::GridContainer>(ui::GridConfig::Custom(hg::Vec2i(1, menuItems.size() + 2), {1.0}, rowSizes));

    {
        auto gridEl = m_menu.addElementTo<ui::GridElement>(menu, menu->config(), Vec2i(0, 0));
        m_menu.addElementTo<ui::Label>(gridEl, Vec2::Zero(), getFont("8bit_lg"), "HaBan");
    }

    {
        auto gridEl = m_menu.addElementTo<ui::GridElement>(menu, menu->config(), Vec2i(0, 1));
        auto divider = m_menu.addElementTo<ui::Divider>(gridEl, 5);
        divider->style.foregroundColor = SECONDARY;
    }

    for (int i = 0; i < menuItems.size(); i++) {
        auto gridEl = m_menu.addElementTo<ui::GridElement>(menu, menu->config(), hg::Vec2i(0, i + 2));
        gridEl->style.margin = ui::offset(5);
        addButton(&m_menu, gridEl, menuItems[i].label, menuItems[i].onSelect);
    }

}


void MainMenu::onUpdate(double dt) {

    auto state = GameState::Get();

    state->input = m_window->input.player(ACTION_MAP, 0);

    if (state->input.buttonsPressed[Buttons::Select]) {
        m_menu.root()->trigger(ui::UITriggers::Select);
    }

    auto rawMousePos = m_window->input.devices.keyboardMouse()->mousePosition();
    rawMousePos[1] = m_window->size()[1] - rawMousePos[1];

    m_window->color(Color::black());
    m_window->clear();

    m_menu.render(dt);

    m_menu.update(rawMousePos, dt);
}