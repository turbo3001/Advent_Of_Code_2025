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

  std::sort(Ranges.begin(), Ranges.end(), [](const auto& a, const auto& b) -> bool { return std::get<0>(a) < std::get<0>(b); });
}

void Day5Processor::PrintRanges() const
  {
  for (const auto &Range : Ranges)
    {
    std::cout << std::get<0>(Range) << "-" << std::get<1>(Range) << std::endl;
    }
  }

void Day5Processor::ReproduceInputFile()
{
  PrintRanges();

  std::cout << std::endl;

  for (const auto& ID : AvailableIDs)
  {
    std::cout << ID << std::endl;
  }

}
bool Day5Processor::IsFinished() const
{
  if (!Globals::Get().Part2Mode)
    return IsPart1Finished();
  return IsPart2Finished();
}


intmax_t Day5Processor::Step(const intmax_t LastValue)
{
  if (!Globals::Get().Part2Mode)
    return StepPart1(LastValue);
  return StepPart2(LastValue);
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
bool Day5Processor::IsPart1Finished() const
{
  return CurrentIndex >= AvailableIDs.size();
}

intmax_t Day5Processor::StepPart1(const intmax_t LastValue)
{
  const uint_fast64_t CurrentID = AvailableIDs[CurrentIndex++];
  DebugLog("Processing ID {}: {}", CurrentIndex, CurrentID);
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
bool Day5Processor::IsPart2Finished() const
{
  return CurrentIndex >= Ranges.size();
}
intmax_t Day5Processor::StepPart2(const intmax_t LastValue)
{
  const auto Range = Ranges[CurrentIndex++];
  const uint_fast64_t RangeStart = std::get<0>(Range);
  const uint_fast64_t RangeEnd = std::get<1>(Range);

  DebugLog("LastMax = {}", LastMax);
  DebugLog("Range: {} -> {}", RangeStart, RangeEnd);

  intmax_t NewValue = LastValue;
  if (RangeStart > LastMax)
  {
    const uint_fast64_t AdditionalIDCount = (RangeEnd - RangeStart) + 1;
    DebugLog("New Range: {} New IDs", AdditionalIDCount);
    NewValue += AdditionalIDCount;
    LastMax = RangeEnd;
  }
  else if (RangeEnd > LastMax)
  {
    const uint_fast64_t AdditionalIDCount = RangeEnd - LastMax;
    DebugLog("Overlapping Range: {} New IDs", AdditionalIDCount);
    NewValue += AdditionalIDCount;
    LastMax = RangeEnd;
  }
  else
  {
    DebugLog("Range Skipped, no new IDs", LastMax);
  }
  return NewValue;
}
