#pragma once
#include "Common.h"
#include <vector>

namespace Origin {

class Object {

public:
    Object(Object* parent = nullptr);
    virtual ~Object();

    void setName(const std::string& name) { this->name = name; }
    const std::string& getName() const { return name; }

    void setParent(Object* parent);
    Object* getParent() const { return parent; }

    void appendChild(Object* child);
    void insertChild(Object* child, int index);
    void removeChild(Object* child);
    void removeChild(int index);
    void removeChildren();
    const std::vector<Object*>& getChildren() const { return children; }

protected:
    virtual void notifyAddChild(Object* child [[maybe_unused]]) {}
    virtual void notifyRemoveChild(Object* child [[maybe_unused]]) {}

private:
    friend class Control;
    void polishAppendChild(Object* child);

    std::string name;
    Object* parent = nullptr;
    std::vector<Object*> children;
};

} // Origin
