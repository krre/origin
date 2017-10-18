#pragma once
#include "Singleton.h"

class SDLWrapper : public Singleton<SDLWrapper> {

public:
    SDLWrapper();
    ~SDLWrapper();
    void init();
    const Size& getScreenSize() const { return screenSize; }
    std::string getError() const;
    void showErrorMessageBox(const char* message);
    bool isInited() const { return inited; }

private:
    Size screenSize;
    bool inited = false;
};
