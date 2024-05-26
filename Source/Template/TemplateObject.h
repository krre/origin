#pragma once
#include "Core/Object.h"

class TemplateObject : public Core::Object {

public:
    TemplateObject(Object* parent = nullptr);
    ~TemplateObject();
};
