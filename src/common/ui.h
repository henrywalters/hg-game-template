//
// Created by henry on 8/12/24.
//

#ifndef HABAN_UI_H
#define HABAN_UI_H

#include <hagame/ui/elements/gridContainer.h>
#include <hagame/ui/elements/checkbox.h>
#include <hagame/ui/frame.h>
#include <hagame/graphics/color.h>
#include <hagame/ui/elements/textButton.h>

const hg::graphics::Color MENU_BG {15, 15, 120, 150};
const hg::graphics::Color PRIMARY {230, 230, 230};
const hg::graphics::Color SECONDARY {237, 237, 0 };

hg::ui::Checkbox* addCheckbox(hg::ui::Frame* frame, hg::ui::Element* parent, std::string label, bool* ref);
hg::ui::TextButton* addButton(hg::ui::Frame* frame, hg::ui::Element* parent, std::string label, std::function<void()> onSelect);

#endif //HABAN_UI_H
