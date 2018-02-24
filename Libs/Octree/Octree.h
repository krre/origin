#pragma once
#include "Core/Object.h"
#include "Substance.h"
#include <json/json.hpp>
#include <glm/glm.hpp>
#include <type_traits>

namespace Origin {

using json = nlohmann::json;

class Octree : public Object {

public:
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 color;
    };

    enum class SurfaceFlags : uint32_t {
        Top = 1 << 0,
        Bottom = 1 << 1,
        Front = 1 << 2,
        Back = 1 << 3,
        Left = 1 << 4,
        Right = 1 << 5,
        All = Top | Bottom | Front | Back | Left | Right
    };

    Octree(Object* parent = nullptr);
    ~Octree();

    void create();
    void load(const std::string& path);
    void build(SurfaceFlags flags = SurfaceFlags::All);

    const std::vector<Vertex>& getVertices() const;

    void setSubstance(const Substance& substance);

private:
    json storage = {};
    std::vector<Vertex> vertices;
    Substance substance;
};

DEFINE_ENUM_CLASS_BITWISE_OPERATOR(Octree::SurfaceFlags)

} // Origin
