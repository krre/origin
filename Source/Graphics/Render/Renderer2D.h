#pragma once
#include "Core/Common.h"
#include "Gui/Batch2D.h"

namespace Origin {

class Control;
class View3D;
class GpuBuffer;
class ShaderProgram;

class Renderer2D {

public:
    Renderer2D();
    virtual ~Renderer2D();
    void render();
    void prepare(Control* control);
    std::vector<View3D*> getRenderViews() const { return renderViews; }

private:
    void getBatches(Control* control, std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices);

    std::vector<Batch2D> batches;
    std::vector<Batch2D::Vertex> vertices;
    std::vector<View3D*> renderViews;
    std::shared_ptr<GpuBuffer> vertexBuffer;
    std::shared_ptr<ShaderProgram> baseShaderProgram;
};

} // Origin
