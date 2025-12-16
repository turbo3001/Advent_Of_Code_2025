//
// Created by Luke on 13/12/2025.
//

#include "Day1Processor.h"

#include "../Common/Globals.h"

#include <iostream>

intmax_t Day1Processor::Step(intmax_t lastValue)
{
	const std::string Line = InputFile.GetNextLine();
	int ZeroCount = 0;
	switch (Line[0]) {
		case 'L':
			ZeroCount = TurnDial(-atoi(Line.substr(1).c_str()));
			break;
		case 'R':
			ZeroCount = TurnDial(atoi(Line.substr(1).c_str()));
			break;
		default:
			throw std::invalid_argument("Invalid input format!");
	}

	if (Globals::Get().Part2Mode) {
		return lastValue + ZeroCount;
	}

	if (SafeDialValue == 0) {
		return lastValue+1;
	}
	return lastValue;

}
int Day1Processor::TurnDial(const int Amount)
{
	const int InitialDialValue = SafeDialValue;
	SafeDialValue += Amount;

	int ZeroCount = 0;
	while (SafeDialValue < 0 || SafeDialValue > 99)
	{
		SafeDialValue += SafeDialValue < 0 ? 100 : -100;
		ZeroCount++;
	}

	if (ZeroCount > 0 && InitialDialValue == 0)
		ZeroCount--;
	else if (ZeroCount == 0 && SafeDialValue == 0)
		ZeroCount = 1;


	DebugLog("{} {}{} {}", InitialDialValue, Amount >= 0 ? " R" : " L", abs(Amount), SafeDialValue);
	DebugLog("Passed Zero {} Time(s)\n", ZeroCount);

	return ZeroCount;
}
