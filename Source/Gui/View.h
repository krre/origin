#pragma once
#include "Control.h"

namespace Origin {

class View : public Control {

public:

    enum class Dimension {
        View2D,
        View3D
    };

    View();
    ~View();
    virtual Dimension getDimension() const = 0;
    void update(float dt);
    void render();

protected:

private:
};

} // Origin
