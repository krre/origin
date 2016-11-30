#pragma once
#include "../Resource/Resource.h"

class Font : public Resource {

public:
    Font();
    void setSize(int size);
    int getSize() const { return size; }

private:
    int size;
};
