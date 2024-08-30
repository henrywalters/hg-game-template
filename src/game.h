//
// Created by henry on 4/12/23.
//

#ifndef HGAMETEMPLATE_GAME_H
#define HGAMETEMPLATE_GAME_H

#include <hagame/core/game.h>
#include "constants.h"

#if USE_CONSOLE
#include <hagame/common/console.h>
#endif

constexpr int FPS_HISTORY_SIZE = 100;

class Game : public hg::Game {
public:

#if HEADLESS
    Game(std::string name):
        hg::Game(name)
    {}
#else
    Game(std::string name, hg::Vec2i size):
        m_size(size),
        hg::Game(name)
    {}
#endif



protected:

    void onInit() override;
    void onBeforeUpdate() override;
    void onUpdate(double dt) override;
    void onAfterUpdate() override;
    void onDestroy() override;

private:

    double m_fpsSum;
    double m_fpsMean;
    float m_maxFps = std::numeric_limits<float>::min();
    std::deque<float> m_fpsHistory;

#if !HEADLESS
    hg::graphics::Window* m_window;
    hg::Vec2i m_size;
#endif

#if USE_CONSOLE
    std::unique_ptr<hg::Console> m_console;
#endif

};

#endif //HGAMETEMPLATE_GAME_H
