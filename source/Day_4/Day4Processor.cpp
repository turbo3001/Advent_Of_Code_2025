//
// Created by Luke on 17/12/2025.
//

#include "Day4Processor.hpp"



Day4Processor::Day4Processor(const std::string &InputFileName) : IDayProcessor(InputFileName)
{
	while (InputFile.HasLine())
	{
		auto CurrentRow = InputFile.GetNextLine<std::vector<bool>>([](const std::string_view& Line) -> MapRow
			{
				MapRow Row;
				for (const auto& Column : Line) {
					Row.push_back(Column == '@');
				}
			return Row;
			});

		Map.rows.emplace_back(CurrentRow);
	}
	if (Globals::Get().VerboseMode)
		ReproduceInputFile();
	DebugLog("");
}

bool Day4Processor::IsFinished() const {
	if (!Globals::Get().Part2Mode)
		return CurrentY >= Map.rows.size();

	return Finished;
}

intmax_t Day4Processor::Step(const intmax_t lastValue) {
	if (!Globals::Get().Part2Mode) {
		MapRow NewMapRow;
		const intmax_t NextValue = lastValue + ProcessRow(NewMapRow);
		CurrentY++;
		return NextValue;
	}

	CurrentY = 0;
	PaperMap NewMap;
	intmax_t MovablePaper = 0;
	for (const auto& Row : Map.rows) {
		MapRow NewMapRow;
		MovablePaper += ProcessRow(NewMapRow);
		NewMap.rows.emplace_back(NewMapRow);
		CurrentY++;
	}
	if (Globals::Get().VerboseMode)
		NewMap.Print();
	Finished = (MovablePaper == 0);
	Map = NewMap;
	return lastValue + MovablePaper;
}

intmax_t Day4Processor::ProcessRow(MapRow &NewRow) const {
	const MapRow Row = Map.rows[CurrentY];
	NewRow.clear();
	NewRow.reserve(Row.size());
	std::string CalculatedRow = "";
	intmax_t RemoveCount = 0;
	for (int CurrentX = 0; CurrentX < Row.size(); ++CurrentX)
	{
		if (!Map.GetPos(CurrentX, CurrentY)) {
			NewRow.push_back(Row[CurrentX]);
			CalculatedRow += ".";
			continue;
		}

		int PaperCount = 0;
		if (CurrentY > 0) {
			if (CurrentX > 0 && Map.GetPos(CurrentX-1, CurrentY-1))
				PaperCount++;

			if (Map.GetPos(CurrentX, CurrentY-1))
				PaperCount++;

			if (CurrentX < Row.size() -1 && Map.GetPos(CurrentX+1, CurrentY-1))
				PaperCount++;
		}

		if (CurrentX > 0 && Map.GetPos(CurrentX-1, CurrentY))
			PaperCount++;
		if (CurrentX < Row.size() -1 && Map.GetPos(CurrentX +1, CurrentY))
			PaperCount++;

		if (CurrentY < Map.rows.size() -1)
		{
			if (CurrentX > 0 && Map.GetPos(CurrentX-1, CurrentY+1))
				PaperCount++;

			if (Map.GetPos(CurrentX, CurrentY+1))
				PaperCount++;

			if (CurrentX < Row.size() -1 && Map.GetPos(CurrentX+1, CurrentY+1))
				PaperCount++;
		}
		if (PaperCount < 4) {
			RemoveCount++;
			CalculatedRow += "X";
		}
		else {
			CalculatedRow += "@";
		}
		NewRow.push_back(PaperCount >= 4);
	}
	DebugLog("{}", CalculatedRow);
	return RemoveCount;
}

void Day4Processor::ReproduceInputFile() {
	Map.Print();
}
