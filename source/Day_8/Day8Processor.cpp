//
// Created by Luke on 02/01/2026.
//

#include "Day8Processor.hpp"

#include "../Common/DebugHelpers.hpp"

Day8Processor::Day8Processor(const std::string &InputFileName)
    : IDayProcessor(InputFileName)
  {
  while (InputFile.HasLine())
    {
    const VectorType3D Junction = InputFile.GetNextLine<VectorType3D>(VectorType3D::ParseFromString);
    JunctionBoxes.emplace_back(Junction);
    }

  RemainingJunctionBoxCount =
      InputFileName.find("Example") != std::string::npos ? 10 : 1000;

  for (int i = 0; i < JunctionBoxes.size(); ++i)
    {
    for (int j = i+1; j < JunctionBoxes.size(); ++j)
      {
        const intmax_t Distance = JunctionBoxes[j] % JunctionBoxes[i];
        JunctionPairs.emplace_back(i, j, Distance);
      }
    }

  std::sort(JunctionPairs.begin(), JunctionPairs.end());

  // if (Globals::Get().VerboseMode)
  //   ReproduceInputFile();

  DebugLogJunctionPairs();
}
void Day8Processor::ReproduceInputFile()
{
  for (auto& JunctionBox : JunctionBoxes)
  {
    std::cout << JunctionBox[0] << "," << JunctionBox[1] << "," << JunctionBox[2] << std::endl;
  }
}

bool Day8Processor::IsFinished() const { return RemainingJunctionBoxCount < 0; }

intmax_t Day8Processor::Step(const intmax_t LastValue)
{
  DebugLog("RemainingJunctionBoxCount: {}", RemainingJunctionBoxCount);
  const auto& Pair = JunctionPairs.front();
  DebugLogJunctionPair(Pair);
  bool CircuitFound = false;
  for (auto& Indices : Circuits)
  {
    const bool HasAIndex = std::ranges::find(Indices, Pair.AIndex) != Indices.end();
    const bool HasBIndex = std::ranges::find(Indices, Pair.BIndex) != Indices.end();
    if (HasAIndex && HasBIndex)
    {
      CircuitFound = true;
      break;
    }
    if (HasAIndex)
    {
      Indices.push_back(Pair.BIndex);
      CircuitFound = true;
      break;
    }
    if (HasBIndex)
    {
      Indices.push_back(Pair.AIndex);
      CircuitFound = true;
      break;
    }
  }
  if (!CircuitFound)
  {
    std::vector NewCircuitIndices = {Pair.AIndex, Pair.BIndex};
    Circuits.emplace_back(NewCircuitIndices);
  }
  JunctionPairs.pop_front();
  RemainingJunctionBoxCount--;
  if (IsFinished())
  {
    std::sort(Circuits.begin(), Circuits.end(), [](const std::vector<int>& A, const std::vector<int> &B) { return A.size() > B.size(); });
    DebugLogCircuits();
    if (Circuits.size() >= 3)
      return Circuits[0].size() * Circuits[1].size() * Circuits[2].size();

    intmax_t Result = 1;
    for (const std::vector<int>& Circuit : Circuits)
    {
      Result *= Circuit.size();
    }
  }
  return LastValue;
}
void Day8Processor::DebugLogJunctionPair(const JunctionPair &Pair) const
{
  const int& AIndex = Pair.AIndex;
  const int& BIndex = Pair.BIndex;
  const VectorType3D& AJunction = JunctionBoxes[AIndex];
  const VectorType3D& BJunction = JunctionBoxes[BIndex];
  DebugLog("({}) {} -> ({}) {} - Distance (Squared): {}", AIndex, AJunction.ToString(), BIndex, BJunction.ToString(), Pair.Distance);
}

void Day8Processor::DebugLogJunctionPairs() const
{
  for (auto& Pair : JunctionPairs)
  {
    DebugLogJunctionPair(Pair);
  }
}

void Day8Processor::DebugLogCircuits() const {
  DebugLog("Number of non-trivial Circuits: {}", Circuits.size());
  for (const std::vector<int>& CircuitIndices : Circuits)
  {
    std::string CircuitMap = "";
    for (int i = 0; i < CircuitIndices.size(); ++i)
    {
      const int& JunctionIndex = CircuitIndices[i];
      if (i != 0) CircuitMap += " -> ";
      CircuitMap += std::format("({}) {}", JunctionIndex, JunctionBoxes[JunctionIndex].ToString());
    }
    CircuitMap += " - size: " + std::to_string(CircuitIndices.size());
    DebugLog("{}", CircuitMap);
  }
}