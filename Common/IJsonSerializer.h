#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

class IJsonSerializer{
public:
    virtual ~IJsonSerializer()=default;
    virtual std::string Serialize(const nlohmann::json& json)const=0;
    virtual nlohmann::json Deserialize(std::string_view json)const=0;

    template<typename T>
    std::string SerializeObject(const T& object)const{
        return nlohmann::json(object).dump(4);
    }
    template<typename T>
    T DeserializeObject(std::string json)const{
        return nlohmann::json::parse(json).get<T>();
    }
};