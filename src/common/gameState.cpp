//
// Created by henry on 2/29/24.
//
#include <memory>
#include "gameState.h"

GameState *GameState::Get() {
    static std::unique_ptr<GameState> gameState;
    if (!gameState) {
        gameState = std::make_unique<GameState>();
    }
    return gameState.get();
}

