//
// Created by henry on 2/29/24.
//

#ifndef HABAN_GAMESTATE_H
#define HABAN_GAMESTATE_H

#include <hagame/utils/random.h>
#include <hagame/utils/enum.h>
#include <hagame/input/input.h>
#include <hagame/utils/variantMap.h>

#include "../constants.h"
#include "../common/enums/actions.h"
#include "../common/persistentSettings.h"

ENUM(DebugLevel)
ENUM_VALUE(DebugLevel, Disabled)
ENUM_VALUE(DebugLevel, Light)
ENUM_VALUE(DebugLevel, Heavy)

enum class EventType {
    MoveTo,
    MoveBack,
};

using Event = std::variant<>;

// Access GameState via the singleton Get function
class GameState {
public:

    struct Settings {
        bool running = true;
        bool editing = false;
    } settings;

    PersistentSettings persistentSettings;

    hg::Publisher<EventType, Event> events;

    hg::input::Actions<hg::utils::enum_t> input;
    hg::utils::Random random;

    static GameState* Get();

};

#endif //HABAN_GAMESTATE_H
