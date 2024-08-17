//
// Created by henry on 8/16/24.
//

#ifndef HGAMETEMPLATE_MAINMENU_H
#define HGAMETEMPLATE_MAINMENU_H

#include <hagame/core/scene.h>
#include <hagame/graphics/window.h>
#include <hagame/ui/frame.h>

class MainMenu : public hg::Scene {
public:

    MainMenu(hg::graphics::Window* window);

protected:

    void onInit() override;
    void onUpdate(double dt) override;

    hg::graphics::Window* m_window;
    hg::ui::Frame m_menu;

};

#endif //HGAMETEMPLATE_MAINMENU_H
