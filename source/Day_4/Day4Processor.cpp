//
// Created by Luke on 17/12/2025.
//

#include "Day4Processor.hpp"



Day4Processor::Day4Processor(const std::string &InputFileName) : IDayProcessor(InputFileName)
{
	while (InputFile.HasLine())
	{
		auto CurrentRow = InputFile.GetNextLine<std::vector<bool>>([](const std::string_view& Line) -> std::vector<bool>
			{
				std::vector<bool> Row;
				for (const auto& Column : Line) {
				Row.push_back(Column == '@');
				}
			return Row;
			});

		PaperMap.rows.emplace_back(CurrentRow);
	}
	if (Globals::Get().VerboseMode)
		ReproduceInputFile();
	DebugLog("");
}

bool Day4Processor::IsFinished() const {
	return CurrentY >= PaperMap.rows.size();
}

intmax_t Day4Processor::Step(const intmax_t lastValue) {
	const auto [Row] = PaperMap.rows[CurrentY];
	intmax_t NextValue = lastValue;
	std::string CalculatedRow = "";
	for (int CurrentX = 0; CurrentX < Row.size(); ++CurrentX)
	{
		if (!PaperMap.GetPos(CurrentX, CurrentY)) {
			CalculatedRow += ".";
			continue;
		}

		int PaperCount = 0;
		if (CurrentY > 0) {
			if (CurrentX > 0 && PaperMap.GetPos(CurrentX-1, CurrentY-1))
				PaperCount++;

			if (PaperMap.GetPos(CurrentX, CurrentY-1))
				PaperCount++;

			if (CurrentX < Row.size() -1 && PaperMap.GetPos(CurrentX+1, CurrentY-1))
				PaperCount++;
		}

		if (CurrentX > 0 && PaperMap.GetPos(CurrentX-1, CurrentY))
			PaperCount++;
		if (CurrentX < Row.size() -1 && PaperMap.GetPos(CurrentX +1, CurrentY))
			PaperCount++;

		if (CurrentY < PaperMap.rows.size() -1)
		{
			if (CurrentX > 0 && PaperMap.GetPos(CurrentX-1, CurrentY+1))
				PaperCount++;

			if (PaperMap.GetPos(CurrentX, CurrentY+1))
				PaperCount++;

			if (CurrentX < Row.size() -1 && PaperMap.GetPos(CurrentX+1, CurrentY+1))
				PaperCount++;
		}
		if (PaperCount < 4) {
			NextValue++;
			CalculatedRow += "X";
		}
		else {
			CalculatedRow += "@";
		}
	}
	DebugLog("{}", CalculatedRow);
	CurrentY++;
	return NextValue;
}

void Day4Processor::ReproduceInputFile() {
	for (const auto &[columns] : PaperMap.rows) {
		for (const bool& Column : columns) {
			std::cout << (Column ? "@" : ".");
		}
		std::cout << std::endl;
	}
}
