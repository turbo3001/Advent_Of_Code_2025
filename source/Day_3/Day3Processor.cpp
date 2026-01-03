//
// Created by Luke on 16/12/2025.
//

#include "Day3Processor.hpp"

#include "../Common/Globals.h"

std::string GetJoltageString(const std::string_view& Line, const int RemainingDepth)
{
	if (RemainingDepth <= 0 || Line.length() == 0)
		return "";

	int LastJoltage = 0;
	int CurrentIndex = 0;
	for (int i = 0; i < Line.length() - (RemainingDepth - 1); ++i)
	{
		const std::string_view Character = Line.substr(i, 1);
		int Joltage;
		std::from_chars(Character.data(), Character.data() + Character.length(), Joltage);
		if (Joltage > LastJoltage)
		{
			LastJoltage = Joltage;
			CurrentIndex = i;
		}
	}
	return Line[CurrentIndex] + GetJoltageString(Line.substr(CurrentIndex+1), RemainingDepth-1);
}

intmax_t Day3Processor::Step(const intmax_t LastValue)
{
	const std::string& Line = InputFile.GetNextLine();
	const std::string JoltageString = GetJoltageString(Line, Globals::Get().Part2Mode ? 12 : 2);
	const intmax_t Joltage = std::stoll(JoltageString);
	const intmax_t NextValue = LastValue + Joltage;
	return NextValue;
}
