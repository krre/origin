#pragma once
#include "Common.h"
#include <vector>

namespace Core {

class Object {
public:
    Object(Object* parent = nullptr);
    virtual ~Object();

    void setName(const std::string& name) { m_name = name; }
    const std::string& name() const { return m_name; }

    void setParent(Object* parent);
    Object* parent() const { return m_parent; }

    void appendChild(Object* child);
    void insertChild(Object* child, int index);
    void removeChild(Object* child);
    void removeChild(int index);
    void removeChildren();
    const std::vector<Object*>& children() const { return m_children; }

protected:
    virtual void notifyAddChild(Object* child [[maybe_unused]]) {}
    virtual void notifyRemoveChild(Object* child [[maybe_unused]]) {}

private:
    friend class Control;
    void polishAppendChild(Object* child);

    std::string m_name;
    Object* m_parent = nullptr;
    std::vector<Object*> m_children;
};

}
