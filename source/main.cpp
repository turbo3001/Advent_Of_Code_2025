#include <cstring>
#include <iostream>

#include "Common/StringUtils.h"
#include "Day_1/Day1Processor.h"

struct CommandLineArguments {
	int DayNumber = 0;
	int PartNumber = 1;
	std::string InputFileName = "";
	static CommandLineArguments Parse(const int argC, const char* argV[])
	{
		CommandLineArguments Args;
		for (int i = 1; i < argC; i++)
		{
			// ReSharper disable once CppTooWideScopeInitStatement (I don't like the way the if-init looks here XD)
			const std::string arg = argV[i];
			if ( StringEqualCaseInsensitive(arg,"-d") )
			{
				Args.DayNumber = atoi(argV[++i]);
			}
			else if ( StringEqualCaseInsensitive(arg,"-p") )
			{
				Args.PartNumber = atoi(argV[++i]);
			}
			else if ( StringEqualCaseInsensitive(arg, "-i") )
			{
				Args.InputFileName = std::string(argV[++i]);
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
	auto [DayNumber, PartNumber, InputFileName] = CommandLineArguments::Parse(ArgC, ArgV);
	if (DayNumber < 1 || PartNumber < 1) {
		PickDay(DayNumber, PartNumber);
	}

	if (InputFileName.empty()) {
		PickInputFile(InputFileName);
	}

	switch (DayNumber) {
		case 1:
			{
				Day1Processor Processor(InputFileName, PartNumber == 2);
				const int Result = Processor.RunDay();
				std::cout << "Result: " << Result << std::endl;
			}
			break;
		default:
			std::cerr << "Day number (" << DayNumber << ") is not yet handled!" << std::endl;
	}
}
