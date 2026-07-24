#pragma once
#include <iostream>

class IRiskAIAnalysisService {
	
public:
	virtual ~IRiskAIAnalysisService() = default;
	virtual void Analysis(std::uint64_t vid) = 0;
};
