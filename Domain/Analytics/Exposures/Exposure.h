#pragma once
#include <string>
#include <nlohmann/json.hpp>


namespace ns {
	struct Exposure
	{
		std::string symbol;
		double marketValue{};
		double percentage{};
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Exposure, symbol, marketValue, percentage)
	};
}