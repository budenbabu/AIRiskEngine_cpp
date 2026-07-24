#pragma once

#include <nlohmann\json.hpp>



class JsonSerializer
{
public:
    template<typename T>
    static std::string Serialize(const T& value){
        nlohmann::json json=value;
        return json.dump(4);
    }
    template<typename T>
    static T Deserialize(const std::string& text){
        return nlohmann::json::parse(text).template get<T>();
    }
};


