//
// Created by henry on 10/13/24.
//

#ifndef HGEDITOR_RENDERER_H
#define HGEDITOR_RENDERER_H

#include <deque>

#include <hagame/core/system.h>
#include <hagame/core/scene.h>
#include <hagame/core/assets.h>

#include <hagame/graphics/window.h>
#include <hagame/graphics/resolution.h>
#include <hagame/graphics/camera.h>
#include <hagame/graphics/renderPasses.h>
#include <hagame/graphics/primitives/quad.h>
#include <hagame/graphics/primitives/light.h>
#include <hagame/graphics/mesh.h>
#include <hagame/graphics/color.h>
#include <hagame/graphics/debug.h>
#include <hagame/graphics/components/sprite.h>
#include <hagame/graphics/components/particleEmitterComponent.h>
#include <hagame/graphics/tilemap.h>
#include <hagame/graphics/textBuffer.h>
#include <hagame/graphics/batchRenderer.h>

#include "../common/enums/renderModes.h"
#include "../common/gameState.h"

class Runtime;

class Renderer : public hg::System {
public:

    friend class Runtime;

    Renderer(hg::graphics::Window* window);

    void onInit() override;

    void onBeforeUpdate() override;
    void onRender(double dt) override;
    void onUpdate(double dt) override;

    // Render a tile from the spritesheet at an index to a position
    void renderTile(hg::Vec2i index, hg::Vec3 position);

    hg::graphics::RenderPasses<hg::utils::enum_t> m_renderPasses;

    hg::Vec3 camPos;
    hg::Mat4 view;
    hg::Mat4 projection;

private:
    GLuint m_depthTextures;
    GLuint m_depthFBO;

    std::vector<std::unique_ptr<hg::graphics::Camera>> m_cameras;

    hg::graphics::Window* window;

    hg::Vec2 m_mousePos;

    hg::graphics::BatchRenderer m_batchRenderer;

    hg::graphics::primitives::Quad m_animQuad;
    hg::graphics::MeshInstance m_anim;

    hg::graphics::primitives::Quad m_displayQuad;
    hg::graphics::MeshInstance m_display;

    struct Renderable {
        std::function<void(hg::graphics::ShaderProgram*)> render;
        hg::Vec3 pos;
    };

    std::vector<Renderable> m_geometry;

    void prepareGeometry();

    void colorPass(double dt);
    void lightPass(double dt);
    void debugPass(double dt);
    void uiPass(double dt);
    void combinedPass(double dt);

};


#endif //HGEDITOR_RENDERER_H
