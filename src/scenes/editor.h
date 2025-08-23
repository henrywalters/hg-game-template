//
// Created by henry on 8/13/25.
//

#ifndef HGAMETEMPLATE_EDITOR_H
#define HGAMETEMPLATE_EDITOR_H

#include <hagame/core/scene.h>
#include <hagame/graphics/window.h>
#include <hagame/ui/frame.h>
#include <hge/editor.h>

class Editor : public hg::Scene {
public:

    Editor(hg::graphics::Window* window);

protected:

    void onInit() override;
    void onUpdate(double dt) override;

    hg::graphics::Window* m_window;
    std::unique_ptr<hge::Editor> m_editor;

private:

    void resize();

};

#endif //HGAMETEMPLATE_EDITOR_H
