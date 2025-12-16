//
// Created by Luke on 16/12/2025.
//

#include "Day3Processor.hpp"
intmax_t Day3Processor::Step(const intmax_t lastValue)
{
	const std::string& Line = InputFile.GetNextLine();
	int LastJoltage = 0;
	for (int TensIndex = 0; TensIndex < Line.length(); ++TensIndex)
	{
		const std::string TensLine = Line.substr(TensIndex, 1);
		const int TensValue = std::stoi(TensLine) * 10;
		if (TensValue < LastJoltage)
			continue;

		for (int UnitsValue = TensIndex+1; UnitsValue < Line.length(); ++UnitsValue)
		{
			const std::string UnitsLine = Line.substr(UnitsValue, 1);
			const int Joltage = TensValue + std::stoi(UnitsLine);
			if (Joltage > LastJoltage)
				LastJoltage = Joltage;
		}
	}
	return lastValue + LastJoltage;
}
