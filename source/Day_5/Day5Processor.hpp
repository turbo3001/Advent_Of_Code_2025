//
// Created by Luke on 18/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"

class Day5Processor : public IDayProcessor
{
public:
  explicit Day5Processor(const std::string &InputFileName);
  inline void ReproduceInputFile() override;
  bool IsFinished() const override;
  intmax_t Step(intmax_t LastValue) override;

private:

  bool IsFreshIngredient(const uint_fast64_t ID) const;

  std::vector<std::tuple<uint_fast64_t, uint_fast64_t>> Ranges;
  std::vector<uint_fast64_t> AvailableIDs;
  size_t CurrentIDIdx = 0;
};
