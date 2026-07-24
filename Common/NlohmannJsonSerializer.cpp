#include "NlohmannJsonSerializer.h"

std::string NlohmannJsonSerializer::Serialize(const nlohmann::json &json) const
{
    return json.dump(4);
}

nlohmann::json NlohmannJsonSerializer::Deserialize(std::string_view json) const
{
    return nlohmann::json::parse(json);
}
