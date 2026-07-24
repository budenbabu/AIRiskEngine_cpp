#include "IJsonSerializer.h"
class NlohmannJsonSerializer final :public IJsonSerializer{
public:
    std::string Serialize(const nlohmann::json& json)const override;
    nlohmann::json Deserialize(std::string_view json)const override;
    
};