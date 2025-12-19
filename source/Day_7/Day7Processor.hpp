//
// Created by Luke on 19/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"

class Day7Processor : public IDayProcessor
{
public:
  explicit Day7Processor(const std::string& InputFileName) : IDayProcessor(InputFileName) {}
  intmax_t Step(intmax_t LastValue) override;
private:
  std::string LastLine = "";
};
