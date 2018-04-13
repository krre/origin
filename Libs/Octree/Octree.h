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
    struct Pos {
        uint8_t x;
        uint8_t y;
        uint8_t z;
    };

    typedef std::vector<Octree::Pos> Path;

    struct Vertex {
        glm::vec4 pos;
        glm::vec4 color;
        glm::vec3 normal;
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

    Octree(Substance substance = Substance(), Object* parent = nullptr);
    ~Octree();

    void load(const std::string& path);
    void save(const std::string& path);
    void build(SurfaceFlags flags = SurfaceFlags::All);

    void split(const Path& path = Path());

    const std::vector<Vertex>& getVertices() const;

    void setSubstance(const Substance& substance);

private:
    json::object_t* findNode(const Path& path);
    int posToNumber(const Pos& pos);

    json storage = {};
    std::vector<Vertex> vertices;
    Substance substance;
};

DEFINE_ENUM_CLASS_BITWISE_OPERATOR(Octree::SurfaceFlags)

} // Origin
