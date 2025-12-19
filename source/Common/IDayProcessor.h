//
// Created by Luke on 13/12/2025.
//

#pragma once

#include <cstdint>
#include <format>
#include <iostream>
#include "FileReader.h"
#include "Globals.h"

static_assert(sizeof(intmax_t) == sizeof(int64_t), "This platform doesn't support integers of the correct size for the numbers used in AoC");

class IDayProcessor
{
	public:
	explicit IDayProcessor(const std::string& InputFile) : InputFile(InputFile) {}
	virtual ~IDayProcessor() = default;

	virtual void ReproduceInputFile();

	virtual bool IsFinished() const { return !InputFile.HasLine(); };
	virtual intmax_t Step(intmax_t LastValue) = 0;
	virtual intmax_t RunDay(const intmax_t InitialValue = 0);

protected:
	FileReader InputFile;
	intmax_t StepCount = 0;
};

inline intmax_t IDayProcessor::RunDay(const intmax_t InitialValue) {
	StepCount = 0;
	intmax_t result = InitialValue;
	while (!IsFinished()) {
		result = Step(result);
		StepCount++;
	}
	return result;
}

inline void IDayProcessor::ReproduceInputFile() {
	const int InitialPosition = InputFile.GetLineNumber();
	InputFile.SetLineNumber(0);
	while (InputFile.HasLine())
	{
		std::cout << InputFile.GetNextLine().c_str() << std::endl;
	}
	InputFile.SetLineNumber(InitialPosition);
};