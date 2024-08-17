//
// Created by henry on 8/12/24.
//
#include <hagame/ui/elements/label.h>
#include <hagame/core/assets.h>
#include <hagame/ui/elements/textButton.h>
#include "ui.h"

using namespace hg;
using namespace hg::graphics;
using namespace hg::ui;

Checkbox* addCheckbox(Frame *frame, Element *parent, std::string label, bool* ref) {
    auto config = GridConfig::Custom(hg::Vec2i(2, 1), {0.8, 0.2}, {1.});
    auto grid = frame->addElementTo<GridContainer>(parent, config);

    auto labelGridEl = frame->addElementTo<GridElement>(grid, config, Vec2i(0, 0));
    frame->addElementTo<Label>(labelGridEl, Vec2::Zero(), getFont("8bit"), label)
            ->getBuffer()
            ->hAlignment(TextHAlignment::Left);

    auto checkboxGridEl = frame->addElementTo<GridElement>(grid, config, Vec2i(1, 0));
    auto cbox = frame->addElementTo<ui::Checkbox>(checkboxGridEl, ref, hg::Vec2(30, 30), 5);
    cbox->style.backgroundColor = PRIMARY;
    cbox->style.foregroundColor = Color::transparent();
    cbox->style.focusForegroundColor = Color::transparent();
    cbox->style.focusBackgroundColor = SECONDARY;
    cbox->checkedColor = Color::green();

    cbox->events.subscribe([cbox](const auto& event) {
        if (event == ui::UIEvents::MouseEnter) {
            cbox->focus();
        } else if (event == ui::UIEvents::MouseLeave) {
            cbox->unFocus();
        }
    });

    return cbox;
}

hg::ui::TextButton *addButton(hg::ui::Frame *frame, hg::ui::Element *parent, std::string label, std::function<void()> onSelect) {
    auto container = frame->addElementTo<Container>(parent);
    container->style.borderColor = PRIMARY;
    container->style.borderThickness = 5;
    auto button = frame->addElementTo<TextButton>(container, Vec2::Zero(), getFont("8bit"), label);
    button->style.foregroundColor = PRIMARY;
    button->style.focusForegroundColor = SECONDARY;
    button->events.subscribe([button, container, onSelect](const auto& event) {
        if (event == ui::UIEvents::MouseEnter) {
            button->focus();
            container->style.borderColor = SECONDARY;
        } else if (event == ui::UIEvents::MouseLeave) {
            button->unFocus();
            container->style.borderColor = PRIMARY;
        } else if (event == ui::UIEvents::Selected) {
            onSelect();
        }
    });
    return button;
}
