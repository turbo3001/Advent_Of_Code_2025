//
// Created by Luke on 16/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"


class Day3Processor : public IDayProcessor {
public:
	explicit Day3Processor(const std::string& InputFileName) : IDayProcessor(InputFileName) {};

	intmax_t Step(intmax_t LastValue) override;
};
