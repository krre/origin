#pragma once
#include "../Component.h"
#include "../Graphics/Material.h"

class MaterialComponent : public Component {

public:
    MaterialComponent();
    Material* material;
};
