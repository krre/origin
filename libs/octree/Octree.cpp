#include "Octree.h"
#include "JsonStorage.h"
#include <fstream>

namespace Octree {

Octree::Octree(Substance substance, Object* parent) : Object(parent) {
    m_storage = {};
    m_storage["substance"] = substance.id();
    build();
}

void Octree::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed open file: " + path);
    }

    std::string text = std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    m_storage = json::parse(text);
}

void Octree::save(const std::string& path) {
    std::ofstream out(path);
    out << m_storage.dump(4);
    out.close();
}

void Octree::build(Octree::SurfaceFlags flags) {
    m_vertices.clear();

    Vertex vertex = {};
    vertex.color =  { 1.0f, 0.0f, 0.0f, 1.0f };

    if (flags & SurfaceFlags::Front) {
        vertex.pos = { -1.0, 1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 0.0, -1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, 1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 0.0, -1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 0.0, -1.0 }; m_vertices.push_back(vertex);

        vertex.pos = { 1.0, 1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 0.0, -1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 0.0, -1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 0.0, -1.0 }; m_vertices.push_back(vertex);

    }

    if (flags & SurfaceFlags::Back) {
        vertex.pos = { 1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 0.0, 1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 0.0, 1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, -1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 0.0, 1.0 }; m_vertices.push_back(vertex);

        vertex.pos = { -1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 0.0, 1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, -1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 0.0, 1.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, -1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 0.0, 1.0 }; m_vertices.push_back(vertex);
    }

    if (flags & SurfaceFlags::Top) {
        vertex.pos = { -1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, 1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 1.0, 0.0 }; m_vertices.push_back(vertex);

        vertex.pos = { 1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 0.0, 1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, 1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, 1.0, 1.0, 1.0f }; vertex.normal = { 0.0, 1.0, 0.0 }; m_vertices.push_back(vertex);
    }

    if (flags & SurfaceFlags::Bottom) {
        vertex.pos = { 1.0, -1.0, -1.0, 1.0f }; vertex.normal = { 0.0, -1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, -1.0, -1.0, 1.0f }; vertex.normal = { 0.0, -1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 0.0, -1.0, 0.0 }; m_vertices.push_back(vertex);

        vertex.pos = { -1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 0.0, -1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 0.0, -1.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, -1.0, -1.0, 1.0f }; vertex.normal = { 0.0, -1.0, 0.0 }; m_vertices.push_back(vertex);
    }

    if (flags & SurfaceFlags::Left) {
        vertex.pos = { -1.0, 1.0, -1.0, 1.0f }; vertex.normal = { -1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, 1.0, 1.0, 1.0f }; vertex.normal = { -1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, -1.0, 1.0, 1.0f }; vertex.normal = { -1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);

        vertex.pos = { -1.0, -1.0, 1.0, 1.0f }; vertex.normal = { -1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, -1.0, -1.0, 1.0f }; vertex.normal = { -1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { -1.0, 1.0, -1.0, 1.0f }; vertex.normal = { -1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
    }

    if (flags & SurfaceFlags::Right) {
        vertex.pos = { 1.0, 1.0, 1.0, 1.0f }; vertex.normal = { 1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);

        vertex.pos = { 1.0, -1.0, 1.0, 1.0f }; vertex.normal = { 1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, 1.0, -1.0, 1.0f }; vertex.normal = { 1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
        vertex.pos = { 1.0, -1.0, -1.0, 1.0f }; vertex.normal = { 1.0, 0.0, 0.0 }; m_vertices.push_back(vertex);
    }
}

void Octree::split(const Path& path) {
    json::object_t* parentNode = findNode(path);
    json nodes;
    for (int i = 0; i < 8; i++) {
        nodes[std::to_string(i)] = json::object();
    }

    (*parentNode)["nodes"] = nodes;
}

const std::vector<Octree::Vertex>& Octree::vertices() const {
    return m_vertices;
}

void Octree::setSubstance(const Substance& substance) {
    m_substance = substance;
}

json::object_t* Octree::findNode(const Path& path) {
    json::object_t* node = m_storage.get_ptr<json::object_t*>();
    for (const Pos& pos : path) {
        int number = posToNumber(pos);
        node = m_storage[std::to_string(number)].get_ptr<json::object_t*>();
    }

    return node;
}

int Octree::posToNumber(const Octree::Pos& pos) {
    int number = 0;
    number |= pos.x & 0x1;
    number |= pos.y & 0x2;
    number |= pos.z & 0x4;

    return number;
}

}
