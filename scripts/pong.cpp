//
// Created by henry on 9/2/25.
//
#include "pong.h"

void Pong::onUpdate(double dt) {
    std::cout << dt << "\n";
}

hg::ScriptDef Pong::getDef() const {
    return hg::ScriptDef{
        "a",
        "Pong",
        "scripts",
        "cmake-build-debug"
    };
}
