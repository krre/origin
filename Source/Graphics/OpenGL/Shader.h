#pragma once
#include "../../Core/Object.h"

const string folder = "Data/Shader";

class Shader : public Object {

public:
    Shader();
    bool load(const string& path);
private:
    string source;
};
