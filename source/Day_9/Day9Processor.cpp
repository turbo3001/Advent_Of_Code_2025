//
// Created by Luke on 03/01/2026.
//

#include "Day9Processor.hpp"

#include "../Common/DebugHelpers.hpp"
#include "../Common/Globals.h"

void Day9Processor::ReproduceInputFile()
{
  for (const VectorType& TileLocation : TileLocations)
  {
    std::cout << TileLocation[0] << "," << TileLocation[1] << std::endl;
  }
}

bool Day9Processor::IsFinished() const { return LastIndex >= TileLocations.size(); }

Day9Processor::Day9Processor(const std::string &InputFileName) : IDayProcessor(InputFileName)
{
  while (InputFile.HasLine())
  {
    auto NewLocation = InputFile.GetNextLine<VectorType>(VectorType::ParseFromString);
    TileLocations.push_back(NewLocation);
  }

  if (Globals::Get().VerboseMode)
    ReproduceInputFile();
}

intmax_t Day9Processor::Step(const intmax_t LastValue)
{
  const VectorType& StartLocation = TileLocations[LastIndex++];
  //DebugLog("Checking {} = {}", LastIndex-1, StartLocation.ToString());
  intmax_t LargestArea = LastValue;
  for (int i = LastIndex; i < TileLocations.size(); ++i)
  {
    const VectorType& EndLocation = TileLocations[i];
    const intmax_t Length = std::abs(EndLocation[0] - StartLocation[0]) + 1;
    const intmax_t Height = std::abs(EndLocation[1] - StartLocation[1]) + 1;
    if (const intmax_t Area = Length * Height; Area > LargestArea)
    {
      DebugLog("Largest Area between {} and {} = {}", StartLocation.ToString(), EndLocation.ToString(), Area);
      LargestArea = Area;
    }
  }
  return LargestArea;
}