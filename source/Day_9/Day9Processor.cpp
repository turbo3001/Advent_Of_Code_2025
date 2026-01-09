//
// Created by Luke on 03/01/2026.
//

#include "Day9Processor.hpp"

#include "../Common/DebugHelpers.hpp"
#include "../Common/Globals.h"

Day9Processor::Day9Processor(const std::string &InputFileName) : IDayProcessor(InputFileName)
{
  while (InputFile.HasLine())
  {
    auto NewLocation = InputFile.GetNextLine<VectorType>(VectorType::ParseFromString);
    TileLocations.push_back(NewLocation);
  }

  if (Globals::Get().VerboseMode)
    ReproduceInputFile();

  if (Globals::Get().Part2Mode)
  {
    std::sort(TileLocations.begin(), TileLocations.end(), [](const VectorType& A, const VectorType& B)
    {
      if (A[0] == B[0])
      {
        return A[1] < B[1];
      }
      return A[0] < B[0];
    }
    );

    DebugLog("--------Part 2-------");

    DebugLog("Determining Width & Height");

    int Width = 0, Height = 0;
    for (const VectorType& TileLocation : TileLocations)
    {
      if (TileLocation[0] > Width)
        Width = TileLocation[0];
      if (TileLocation[1] > Height)
        Height = TileLocation[1];
    }
    PossibleTileMap = TileMap(Width+1, Height+1);

   for (int y = 0; y <= Height; ++y)
   {
     size_t StartLocationIndex = -1;
     size_t EndLocationIndex = -1;
     for (int i = 0; i < TileLocations.size(); i++)
     {
       if (const VectorType &TileLocation = TileLocations[i];
           TileLocation[1] < y) continue;
       else if (TileLocation[1] > y) break;

       if (StartLocationIndex == -1)
         StartLocationIndex = i;
       else if (EndLocationIndex == -1)
         EndLocationIndex = i;
     }

     if (StartLocationIndex != -1 && EndLocationIndex != -1)
     {
       const VectorType& StartLocation = TileLocations[StartLocationIndex];
       const VectorType& EndLocation = TileLocations[EndLocationIndex];
       for (int x = StartLocation[0]; x <= EndLocation[0]; ++x)
       {
         PossibleTileMap.SetTile(x, y, true);
       }
     }
   }

    DebugLog("Horizontal");
    PossibleTileMap.DebugLogTiles();

    std::sort(TileLocations.begin(), TileLocations.end(), [](const VectorType& A, const VectorType& B)
    {
      if (A[1] == B[1])
      {
        return A[0] < B[0];
      }
      return A[1] < B[1];
    }
    );

    for (int x = 0; x <= Width; ++x)
    {
      size_t StartLocationIndex = -1;
      size_t EndLocationIndex = -1;
      for (int i = 0; i < TileLocations.size(); i++)
      {
        if (const VectorType &TileLocation = TileLocations[i];
            TileLocation[0] < x) continue;
        else if (TileLocation[0] > x) break;

        if (StartLocationIndex == -1)
          StartLocationIndex = i;
        else if (EndLocationIndex == -1)
          EndLocationIndex = i;
      }

      if (StartLocationIndex != -1 && EndLocationIndex != -1)
      {
        const VectorType& StartLocation = TileLocations[StartLocationIndex];
        const VectorType& EndLocation = TileLocations[EndLocationIndex];
        for (int y = StartLocation[1]; y <= EndLocation[1]; ++y)
        {
          PossibleTileMap.SetTile(x, y, true);
        }
      }
    }

    DebugLog("Vertical");
    PossibleTileMap.DebugLogTiles();

    for (int y = 0; y <= Height; ++y)
    {
      bool InPolygon = false;
      for (int x = 0; x <= Width; ++x)
      {
        if (!InPolygon && PossibleTileMap.HasTile(x, y))
        {
          InPolygon = !InPolygon;
        }
        else if (InPolygon)
        {
          PossibleTileMap.SetTile(x, y, true);
        }
      }
    }

    DebugLog("Filled");
    PossibleTileMap.DebugLogTiles();
  }
}

void Day9Processor::ReproduceInputFile()
{
  for (const VectorType& TileLocation : TileLocations)
  {
    std::cout << TileLocation[0] << "," << TileLocation[1] << std::endl;
  }
}

bool Day9Processor::IsFinished() const { return LastIndex >= TileLocations.size(); }

void Day9Processor::CheckLargestArea_Part1(const VectorType& StartLocation, const VectorType& EndLocation, intmax_t& LargestArea)
{
  const intmax_t Length = std::abs(EndLocation[0] - StartLocation[0]) + 1;
  const intmax_t Height = std::abs(EndLocation[1] - StartLocation[1]) + 1;
  if (const intmax_t Area = Length * Height; Area > LargestArea)
    {
    DebugLog("Largest Area between {} and {} = {}", StartLocation.ToString(),
             EndLocation.ToString(), Area);
    LargestArea = Area;
    }
}
void Day9Processor::CheckLargestArea_Part2(const VectorType &StartLocation, const VectorType &EndLocation, intmax_t &LargestArea)
{
  const int StartX = std::min(StartLocation[0], EndLocation[0]);
  const int StartY = std::min(StartLocation[1], EndLocation[1]);
  const int EndX = std::max(StartLocation[0], EndLocation[0]);
  const int EndY = std::max(EndLocation[1], EndLocation[1]);
  const intmax_t Length = std::abs(EndLocation[0] - StartLocation[0]) + 1;
  const intmax_t Height = std::abs(EndLocation[1] - StartLocation[1]) + 1;
  const intmax_t Area = Length * Height;
  if (Area < LargestArea)
    return;

  for (int x = StartX; x < EndX; ++x)
  {
    for (int y = StartY; y < EndY; ++y)
    {
      if (!PossibleTileMap.HasTile(x,y))
      {
        return;
      }
    }
  }

  DebugLog("Largest Area between {} and {} = {}", StartLocation.ToString(),
               EndLocation.ToString(), Area);
  LargestArea = Area;
}

intmax_t Day9Processor::Step(const intmax_t LastValue)
{
  const VectorType& StartLocation = TileLocations[LastIndex++];
  //DebugLog("Checking {} = {}", LastIndex-1, StartLocation.ToString());
  intmax_t LargestArea = LastValue;
  for (int i = LastIndex; i < TileLocations.size(); ++i)
  {
    const VectorType& EndLocation = TileLocations[i];
    if (!Globals::Get().Part2Mode)
    {
      CheckLargestArea_Part1(StartLocation, EndLocation, LargestArea);
    }
    else
    {
      CheckLargestArea_Part2(StartLocation, EndLocation, LargestArea);
    }
  }
  return LargestArea;
}

Day9Processor::TileMap::TileMap(const size_t &Width, const size_t &Height)
  : MapData(Height, std::vector(Width, false)), _Width(Width), _Height(Height)
{
}
void Day9Processor::TileMap::DebugLogTiles() const
{
  for (const std::vector<bool>& Line : MapData)
  {
    std::string LineBuffer = "";
    for ( const bool& IsTile : Line)
    {
      LineBuffer += IsTile ? "X" : ".";
    }
    DebugLog("{}", LineBuffer);
  }
}
