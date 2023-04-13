#include <iostream>

#include <hagame/core/hg.h>
#include "src/game.h"

// The main function simply initializes the game and starts running it

// The main entrypoint of the game is found in src/game.h
// For global configurables, checkout src/constants.h

#if HEADLESS
Game game(GAME_NAME);
#else
Game game(GAME_NAME, GAME_SIZE);
#endif

void emscripten_tick() {
    game.tick();
}

int main() {
#ifdef __EMSCRIPTEN__
    game.initialize();
    emscripten_set_main_loop(emscripten_tick, 0, false);
    // clickVenture.destroy();
#else
    hg::HG::Run(&game);
#endif
    return 0;
}
