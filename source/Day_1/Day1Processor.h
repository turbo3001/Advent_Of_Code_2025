//
// Created by Luke on 13/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"


class Day1Processor : public IDayProcessor
{
public:
	explicit Day1Processor(const std::string& InputFile) : IDayProcessor(InputFile) {};

	int Step(int lastValue) override;

private:
	void TurnDial(int Amount);

	int SafeDialValue = 50;
};
