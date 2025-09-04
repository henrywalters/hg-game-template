//
// Created by henry on 9/1/25.
//

#ifndef HGAMETEMPLATE_SETTINGS_H
#define HGAMETEMPLATE_SETTINGS_H

#include <hagame/common/console.h>
#include "../common/gameState.h"

struct SetVSyncCommand : public hg::Console::Command {
    SetVSyncCommand();
};

struct HelpCommand : public hg::Console::Command {
    HelpCommand();
};

#endif //HGAMETEMPLATE_SETTINGS_H
