#pragma once
#include "Singleton.h"

class SDLWrapper : public Singleton<SDLWrapper> {

public:
    SDLWrapper();
    void init();
    const Size& getScreenSize() const { return screenSize; }

private:
    Size screenSize;
};
