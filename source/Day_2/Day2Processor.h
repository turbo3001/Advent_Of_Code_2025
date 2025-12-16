//
// Created by Luke on 13/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"


class Day2Processor : public IDayProcessor
{
public:
	explicit Day2Processor(const std::string& InputFileName, bool Part2Mode = false);
	bool IsFinished() const override;
	intmax_t Step(intmax_t lastValue) override;
	void ReproduceInputFile() override;

private:
	struct Range {
		intmax_t start;
		intmax_t end;
	};
	std::vector<Range> IDRanges;
	int CurrentRangeIndex = 0;
};
