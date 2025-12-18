//
// Created by Luke on 13/12/2025.
//

#include "Day2Processor.h"

#include <cmath>
#include <sstream>
#include "../Common/Globals.h"
#include "../Common/StringUtils.h"

Day2Processor::Day2Processor(const std::string &InputFileName) : IDayProcessor(InputFileName)
{
	while (InputFile.HasLine()) {
		using namespace std;
		auto NextRanges = InputFile.GetNextLine<vector<Range>>([](const string_view& Line) -> vector<Range> {
			vector<Range> Result;
			stringstream LineStream(Line.data());
			string CurrentIDRange;
			while (getline(LineStream, CurrentIDRange, ','))
			{
				const int DashPos = CurrentIDRange.find('-');
				if (DashPos == string::npos)
					throw runtime_error("Invalid ID Range: " + CurrentIDRange);
				try {
					auto &[RangeStart, RangeEnd] = Result.emplace_back();
					std::string startPos = CurrentIDRange.substr(0, DashPos);
					std::string endPos = CurrentIDRange.substr(DashPos + 1);
					RangeStart = stoll(startPos);
					RangeEnd = stoll(endPos);
				}
				catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
			return Result;
		});
		IDRanges.reserve(NextRanges.size());
		copy(NextRanges.begin(), NextRanges.end(), back_inserter(IDRanges));
	}

	if (Globals::Get().VerboseMode)
		ReproduceInputFile();
}
bool Day2Processor::IsFinished() const { return CurrentRangeIndex >= IDRanges.size(); }

bool IsValidID(const intmax_t &ID) {
	const int IDLength = log10(ID) + 1;
	if (IDLength % 2 != 0)
		return true;

	const int HalfIDLength = IDLength / 2;
	const intmax_t HalfLengthPOT =  pow(10, HalfIDLength);
	const intmax_t FirstHalf =  ID / HalfLengthPOT;
	const intmax_t SecondHalf = ID - (FirstHalf * HalfLengthPOT);
	return FirstHalf != SecondHalf;
}

intmax_t Day2Processor::Step(const intmax_t LastValue) {
	int Result = LastValue;
	const auto &[RangeStart, RangeEnd] = IDRanges[CurrentRangeIndex++];
	for (intmax_t i = RangeStart; i <= RangeEnd; i++)
	{
		DebugLog("Checking {}", i);
		if (!IsValidID(i))
		{
			DebugLog("Found Invalid ID: {}", i);
			Result += i;
		}
	}
	return Result;
}

void Day2Processor::ReproduceInputFile()
{
	int i = 0;
	for (auto &[start, end] : IDRanges) {
		std::cout << (i++ == 0 ? "" : ",") << start << "-" << end;
	}
	std::cout << std::endl;
}
