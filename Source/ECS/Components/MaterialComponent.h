#pragma once
#include "../Component.h"
#include "../Graphics/Material.h"

class MaterialComponent : public Component {

public:
    MaterialComponent() { type = ComponentType::Material; }
    std::shared_ptr<Material> material;
};
