//
// Created by Luke on 13/12/2025.
//

#include "Day1Processor.h"

int Day1Processor::Step(const int lastValue)
{
	std::string Line = InputFile.GetNextLine();
	switch (Line[0]) {
		case 'L':
			TurnDial(-atoi(Line.substr(1).c_str()));
			break;
		case 'R':
			TurnDial(atoi(Line.substr(1).c_str()));
			break;
		default:
			throw std::invalid_argument("Invalid input format!");
	}
	if (SafeDialValue == 0) {
		return lastValue+1;
	}
	return lastValue;
}
void Day1Processor::TurnDial(const int Amount)
{
	SafeDialValue += Amount;
	SafeDialValue %= 100;
	if (SafeDialValue < 0)
		SafeDialValue += 100;
}
