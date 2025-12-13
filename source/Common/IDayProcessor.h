//
// Created by Luke on 13/12/2025.
//

#pragma once
#include "FileReader.h"

class IDayProcessor
{
	public:
	explicit IDayProcessor(const std::string& InputFile) : InputFile(InputFile) {}
	virtual ~IDayProcessor() = default;
	virtual bool IsFinished() const { return !InputFile.HasLine(); };
	virtual int Step(int lastValue) = 0;

	virtual int RunDay(const int initialValue = 0) {
		int result = initialValue;
		while (!IsFinished()) {
			result = Step(result);
		}
		return result;
	};

protected:
	FileReader InputFile;
};