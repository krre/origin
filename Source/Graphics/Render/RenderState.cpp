#include "RenderState.h"

namespace Origin {

RenderState::RenderState() {

}

RenderState::~RenderState() {

}

void RenderState::setShaderProgram(ShaderProgram* shaderProgram) {
    this->shaderProgram = shaderProgram;
}

} // Origin
