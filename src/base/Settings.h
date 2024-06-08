#pragma once
#include <core/SingleObject.h>
#include <json/json.hpp>

using json = nlohmann::json;

class Settings : public Core::SingleObject<Settings> {

public:
    Settings(Object* parent = nullptr);
    ~Settings();
    static void saveAll();
    static json& storage() { return get()->m_storage; }

private:
    void setDefaultSettings();

    std::string m_path;
    json m_storage;
};
