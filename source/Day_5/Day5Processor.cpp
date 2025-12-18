//
// Created by Luke on 18/12/2025.
//

#include "Day5Processor.hpp"
Day5Processor::Day5Processor(const std::string &InputFileName)
    : IDayProcessor(InputFileName)
{
  while (InputFile.HasLine())
  {
    const std::string Line = InputFile.GetNextLine();
    try
    {
      if (Line.empty())
        continue;

      if (Line.contains('-'))
      {
        const std::string Start = Line.substr(0, Line.find('-'));
        const std::string End = Line.substr(Line.find('-') + 1);
        if (Start.empty() || End.empty())
          throw std::invalid_argument("Invalid line: " + Line);

        Ranges.push_back({std::stoll(Start), std::stoll(End)});
      }
      else
      {
        AvailableIDs.push_back(std::stoll(Line));
      }
    }
    catch (...)
    {
      throw std::invalid_argument("Invalid line: " + Line);
    }
  }

  if (Globals::Get().VerboseMode)
    ReproduceInputFile();
}

void Day5Processor::ReproduceInputFile()
{
  for (const auto& Range : Ranges)
  {
    std::cout << std::get<0>(Range) << "-" << std::get<1>(Range) << std::endl;
  }

  std::cout << std::endl;

  for (const auto& ID : AvailableIDs)
  {
    std::cout << ID << std::endl;
  }

}
bool Day5Processor::IsFinished() const{ return CurrentIDIdx > AvailableIDs.size(); }


intmax_t Day5Processor::Step(const intmax_t LastValue)
{
  const uint_fast64_t CurrentID = AvailableIDs[CurrentIDIdx++];
  DebugLog("Processing ID {}: {}", CurrentIDIdx, CurrentID);
  intmax_t NewValue = LastValue;
  if (IsFreshIngredient(CurrentID))
  {
    //DebugLog("{} is Fresh!", CurrentID);
    NewValue++;
  }
  else
  {
    DebugLog("{} is Not Fresh!", CurrentID);
  }
  return NewValue;
}
bool Day5Processor::IsFreshIngredient(const uint_fast64_t ID) const
  {
  for (const auto &Range : Ranges)
  {
      const int_fast64_t RangeStart = std::get<0>(Range);
  if (const int_fast64_t RangeEnd = std::get<1>(Range);
      ID >= RangeStart && ID <= RangeEnd)
        return true;
  }
  return false;
}
