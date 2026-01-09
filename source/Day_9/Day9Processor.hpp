//
// Created by Luke on 03/01/2026.
//

#pragma once
#include "../Common/DimensionalVector.hpp"
#include "../Common/IDayProcessor.h"

class Day9Processor : public IDayProcessor
{
  using VectorType = IntVector2D;
public:
  explicit Day9Processor(const std::string& InputFileName);
  void ReproduceInputFile() override;
  bool IsFinished() const override;
  intmax_t Step(intmax_t LastValue) override;
  static void CheckLargestArea_Part1(const VectorType& StartLocation, const VectorType& EndLocation, intmax_t& LargestArea);
  void CheckLargestArea_Part2(const VectorType& StartLocation, const VectorType& EndLocation, intmax_t& LargestArea);

private:
  std::vector<VectorType> TileLocations;
  int LastIndex = 0;
  struct TileMap
  {
    TileMap() = default;
    TileMap(const size_t& Width, const size_t& Height);

    void SetTile(const size_t& x, const size_t& y, const bool& value) { MapData[y][x] = value; }
    bool HasTile(const size_t& x, const size_t& y) const { return MapData[y][x]; }

    void DebugLogTiles() const;

  private:
    std::vector<std::vector<bool>> MapData;
    size_t _Width, _Height;
  } PossibleTileMap;
};
