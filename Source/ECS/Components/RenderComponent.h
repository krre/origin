#pragma once
#include "../Component.h"
#include "../Graphics/Drawable.h"

class RenderComponent : public Component {

public:
    RenderComponent();
    std::shared_ptr<Drawable> drawable;
};
