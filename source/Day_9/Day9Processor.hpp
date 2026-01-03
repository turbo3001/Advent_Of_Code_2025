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

private:
  std::vector<VectorType> TileLocations;
  int LastIndex = 0;
};
