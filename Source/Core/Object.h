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
    Object* getParent() const { return data.parent; }

    void addChild(Object* child);
    void insertChild(Object* child, int index);
    void removeChild(Object* child);
    void removeChild(int index);
    void removeChildren();
    const std::vector<Object*>& getChildren() const { return data.children; }

protected:
    virtual void notifyAddChild(Object* child) {}
    virtual void notifyRemoveChild(Object* child) {}

private:
    struct ObjectData {
        friend class Control;
        Object* parent = nullptr;
        std::vector<Object*> children;
    } data;

    void polishAddChild(Object* child);

    std::string name;
};

} // Origin
