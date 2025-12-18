//
// Created by Luke on 18/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"

class Day5Processor : public IDayProcessor
{
public:
  explicit Day5Processor(const std::string &InputFileName);
  void PrintRanges() const;
  inline void ReproduceInputFile() override;
  bool IsFinished() const override;
  intmax_t Step(intmax_t LastValue) override;

private:

  bool IsFreshIngredient(const uint_fast64_t ID) const;
  bool IsPart1Finished() const;
  intmax_t StepPart1(intmax_t LastValue);
  bool IsPart2Finished() const;
  intmax_t StepPart2(intmax_t LastValue);

  std::vector<std::tuple<uint_fast64_t, uint_fast64_t>> Ranges;
  std::vector<uint_fast64_t> AvailableIDs;
  size_t CurrentIndex = 0;
  uint_fast64_t LastMax = 0;
};
