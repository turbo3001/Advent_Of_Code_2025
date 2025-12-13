//
// Created by Luke on 13/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"


class Day1Processor : public IDayProcessor
{
public:
	Day1Processor(const std::string& InputFile, bool Part2Mode = false) : IDayProcessor(InputFile), Part2Mode(Part2Mode) {};

	int Step(int lastValue) override;

private:
	int TurnDial(int Amount);

	int SafeDialValue = 50;
	bool Part2Mode;
};
