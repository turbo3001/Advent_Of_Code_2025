//
// Created by Luke on 02/01/2026.
//

#pragma once
#include "../Common/DimensionalVector.hpp"
#include "../Common/IDayProcessor.h"

#include <queue>

class Day8Processor : public IDayProcessor
{
  using VectorType3D = IntMaxVector3D;
public:
  explicit Day8Processor(const std::string& InputFileName);
  void ReproduceInputFile() override;
  bool IsFinished() const override;
  intmax_t Step(intmax_t LastValue) override;

private:
  struct JunctionPair
  {
    int AIndex;
    int BIndex;
    intmax_t Distance;
    JunctionPair(const int& _AIndex, const int& _BIndex, const double& _Distance) : AIndex(_AIndex), BIndex(_BIndex), Distance(_Distance) {}
    auto operator<=>(const JunctionPair& Other) const { return Distance <=> Other.Distance; }
    bool operator==(const JunctionPair& Other) const { return Distance == Other.Distance; }
  };

  void DebugLogJunctionPair(const JunctionPair& Pair) const;
  void DebugLogJunctionPairs() const;
  void DebugLogCircuits() const;

  std::deque<JunctionPair> JunctionPairs;
  std::vector<VectorType3D> JunctionBoxes;
  std::vector<std::vector<int>> Circuits;

  int RemainingJunctionBoxCount;
};
