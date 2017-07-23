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
    bool getIsInited() const { return isInited; }

private:
    Size screenSize;
    bool isInited = false;
};
