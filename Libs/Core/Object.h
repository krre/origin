#pragma once
#include "Common.h"

namespace Origin {

class Object {

public:
    Object(Object* parent = nullptr);
    virtual ~Object();

    void setName(const std::string& name) { this->name = name; }
    const std::string& getName() const { return name; }

    void setParent(Object* parent);
    Object* getParent() const { return parent; }

    void addChild(Object* child);
    void insertChild(Object* child, int index);
    void removeChild(Object* child);
    void removeChild(int index);
    void removeChildren();
    const std::vector<Object*>& getChildren() const { return children; }

protected:
    virtual void notifyAddChild(Object* child) {}
    virtual void notifyRemoveChild(Object* child) {}

private:
    friend class Control;
    void polishAddChild(Object* child);

    std::string name;
    Object* parent = nullptr;
    std::vector<Object*> children;
};

} // Origin
