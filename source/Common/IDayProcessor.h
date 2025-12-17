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
	virtual intmax_t Step(const intmax_t lastValue) = 0;
	virtual intmax_t RunDay(const intmax_t initialValue = 0);

protected:
	template<typename... _Args>
	void DebugLog(std::format_string<_Args...> format, _Args&&... arguments) const{
		if (Globals::Get().VerboseMode) {
			std::string DebugString;
			auto BackInserter = std::back_inserter(DebugString);
			std::format_to(BackInserter, format, std::forward<_Args>(arguments)...);
			std::cout << DebugString.c_str() << std::endl;
		}
	}

	FileReader InputFile;
	intmax_t StepCount = 0;
};

inline intmax_t IDayProcessor::RunDay(const intmax_t initialValue) {
	StepCount = 0;
	intmax_t result = initialValue;
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