//
// Created by Luke on 18/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"

class Day6Processor : public IDayProcessor
{
public:
  explicit Day6Processor(const std::string& InputFileName);
  inline void ReproduceInputFile() override;
  bool IsFinished() const override;
  intmax_t Step(intmax_t LastValue) override;

private:
  struct Problem
  {
    std::vector<uintmax_t> Operands;
    bool Multiply;
  };
  std::vector<Problem> Problems;
  size_t CurrentProblemIndex = 0;
};
