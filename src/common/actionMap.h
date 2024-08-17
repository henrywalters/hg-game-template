//
// Created by henry on 2/29/24.
//

#ifndef HABAN_ACTIONMAP_H
#define HABAN_ACTIONMAP_H

#include <hagame/input/action.h>
#include <hagame/input/devices/keyboardMouseEnums.h>
#include <hagame/input/devices/gamepad.h>
#include "enums/actions.h"

const hg::input::ActionMapper<hg::utils::enum_t> ACTION_MAP {
        {
                { Buttons::Select, {hg::input::devices::MouseButtons::Left, hg::input::devices::GamepadButtons::A}},
                { Buttons::Deselect, {hg::input::devices::MouseButtons::Right, hg::input::devices::GamepadButtons::B}},
        },
        {
                { Axes::MoveX, {hg::input::devices::KeyboardAxes::WASD_X, hg::input::devices::GamepadAxes::LAxisX}},
                { Axes::MoveY, {hg::input::devices::KeyboardAxes::WASD_Y, hg::input::devices::GamepadAxes::LAxisY}}
        }
};

#endif //HABAN_ACTIONMAP_H
