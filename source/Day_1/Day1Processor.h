//
// Created by Luke on 13/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"


class Day1Processor : public IDayProcessor
{
public:
	explicit Day1Processor(const std::string& InputFileName) : IDayProcessor(InputFileName) {};
	intmax_t Step(intmax_t lastValue) override;
private:
	int TurnDial(int Amount);
	int SafeDialValue = 50;
};
