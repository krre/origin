#pragma once
#include "../../Core/Object.h"

const string folder = "Data/Shader";

class Shader : public Object {

public:
    Shader();
    void load(const string& path);
private:
    string source;
};
