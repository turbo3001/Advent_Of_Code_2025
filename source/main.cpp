#include <cstring>
#include <iostream>

#include "Common/Globals.h"
#include "Common/StringUtils.h"
#include "Day_1/Day1Processor.h"
#include "Day_2/Day2Processor.h"

struct CommandLineArguments {
	int DayNumber = 0;
	int PartNumber = 1;
	std::string InputFileName = "";
	std::string OutputFileName = "";
	static CommandLineArguments Parse(const int argC, const char* argV[])
	{
		CommandLineArguments Args;
		for (int i = 1; i < argC; i++)
		{
			// ReSharper disable once CppTooWideScopeInitStatement (I don't like the way the if-init looks here XD)
			const std::string arg = argV[i];
			if ( StringEqualCaseInsensitive(arg,"-d") || StringEqualCaseInsensitive(arg,"-day") )
			{
				Args.DayNumber = atoi(argV[++i]);
			}
			else if ( StringEqualCaseInsensitive(arg,"-p") || StringEqualCaseInsensitive(arg,"-part") )
			{
				Args.PartNumber = atoi(argV[++i]);
			}
			else if ( StringEqualCaseInsensitive(arg, "-i") || StringEqualCaseInsensitive(arg,"-input") )
			{
				Args.InputFileName = std::string(argV[++i]);
			}
			else if (StringEqualCaseInsensitive(arg,"-o") || StringEqualCaseInsensitive(arg,"-output") )
			{
				Args.OutputFileName = std::string(argV[++i]);
			}
			else if (StringEqualCaseInsensitive(arg,"-v") || StringEqualCaseInsensitive(arg,"-verbose") )
			{
				Globals::Get().VerboseMode = true;
			}
			else
			{
				std::cerr << "Unknown Argument: " << arg << std::endl;
			}
		}
		return Args;
	}
};

void PickDay(int& Day, int& Part)
{
	using namespace std;
	Day = 0;
	Part = 0;
	while (Day == 0 || Day > 12)
	{
		cout << "Please enter an integer day solution (between 1 and 12) you wish to run:";
		cin >> Day;
	}
	while (Part == 0 || Part > 2)
	{
		cout << "Please enter a number of the part (1 or 2) you wish to run:";
		cin >> Part;
	}
}

void PickInputFile(std::string& inputFileName) {
	using namespace std;
	inputFileName = "";
	while (inputFileName == "") {
		cout << "Please enter a file name: ";
		getline(cin, inputFileName);
	}
}
int main(const int ArgC, const char* ArgV[]) {
	auto [DayNumber, PartNumber, InputFileName, OutputFileName] = CommandLineArguments::Parse(ArgC, ArgV);
	if (DayNumber < 1 || PartNumber < 1) {
		PickDay(DayNumber, PartNumber);
	}

	if (InputFileName.empty()) {
		PickInputFile(InputFileName);
	}

	// ReSharper disable once CppTooWideScope //I'm pretty sure moving this in-scope will destroy the buffer and cause runtime errors.
	std::ofstream OutputFile;
	if (!OutputFileName.empty()) {
		OutputFile.open(OutputFileName, std::ios::out | std::ios::trunc);
		if (!OutputFile.is_open()) {
			throw std::invalid_argument("Unable to open output file ("+OutputFileName+") for writing!");
		}
		std::cout.rdbuf(OutputFile.rdbuf());
	}

	Globals::Get().Part2Mode = PartNumber == 2;

	switch (DayNumber) {
		case 1:
		{
			Day1Processor Processor(InputFileName);
			const int Result = Processor.RunDay();
			std::cout << "Result: " << Result << std::endl;
		}
			break;
		case 2:
		{
			Day2Processor Processor(InputFileName);
			const int Result = Processor.RunDay();
			std::cout << "Result: " << Result << std::endl;
		}
			break;
		default:
			std::cerr << "Day number (" << DayNumber << ") is not yet handled!" << std::endl;
	}
}
