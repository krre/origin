#include "Renderer.h"
#include "Core/Screen.h"
#include "Renderer2D.h"
#include "Renderer3D.h"
#include "Gui/Control.h"
#include "Gui/Batch2D.h"
#include "Graphics/Render/RenderContext.h"

namespace Origin {

Renderer::Renderer() {
    renderer2d = std::make_unique<Renderer2D>();
    renderer3d = std::make_unique<Renderer3D>();

    createShaderPrograms();
    createRenderStates();
}

Renderer::~Renderer() {

}

void Renderer::render(Screen* screen) {
    renderer2d->prepare(screen->getRootControl());
    renderer2d->render();

    for (auto view3d : renderer2d->getRenderViews()) {
        renderer3d->render(view3d);
    }

    renderQueue();
}

void Renderer::createShaderPrograms() {
    shaderPrograms[ShaderProgram::ProgamType::Base] = RenderContext::get()->createShaderProgram("Base");
    shaderPrograms[ShaderProgram::ProgamType::Sdf] = RenderContext::get()->createShaderProgram("Sdf");
    shaderPrograms[ShaderProgram::ProgamType::Voxel] = RenderContext::get()->createShaderProgram("Voxel");
}

void Renderer::createRenderStates() {
    // Shape2D
    std::shared_ptr<RenderState> shape2DRS = RenderContext::get()->createRenderState();
    shape2DRS->setShaderProgram(shaderPrograms[ShaderProgram::ProgamType::Base].get());
    shape2DRS->setBlendEnable(true);
    shape2DRS->create();
    renderStates[RenderState::Type::Shape2D] = shape2DRS;

    // Freetype text
    std::shared_ptr<RenderState> freeTypeTextRS = RenderContext::get()->createRenderState();
    shape2DRS->setBlendEnable(true);
    shape2DRS->create();
    renderStates[RenderState::Type::FreeTypeText] = freeTypeTextRS;

    // SDF text
    std::shared_ptr<RenderState> sdfTextRS = RenderContext::get()->createRenderState();
    sdfTextRS->setShaderProgram(shaderPrograms[ShaderProgram::ProgamType::Sdf].get());
    shape2DRS->setBlendEnable(true);
    shape2DRS->create();
    renderStates[RenderState::Type::SdfText] = sdfTextRS;

    // Voxel
    std::shared_ptr<RenderState> voxelRS = RenderContext::get()->createRenderState();
    voxelRS->setShaderProgram(shaderPrograms[ShaderProgram::ProgamType::Voxel].get());
    voxelRS->create();
    renderStates[RenderState::Type::Voxel] = voxelRS;
}

} // Origin
