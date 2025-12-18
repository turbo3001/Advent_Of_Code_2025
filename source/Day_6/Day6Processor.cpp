//
// Created by Luke on 18/12/2025.
//

#include "Day6Processor.hpp"
#include <sstream>

Day6Processor::Day6Processor(const std::string &InputFileName) : IDayProcessor(InputFileName)
{
  while (InputFile.HasLine())
  {
    auto StringStream = std::stringstream(InputFile.GetNextLine());

    int ProblemNumber = 0;
    std::string Token;
    while (StringStream >> Token)
    {
      if (Problems.size() <= ProblemNumber)
      {
        Problems.push_back({});
      }
      auto &[Operands, Multiply] = Problems[ProblemNumber++];
      if (Token != "*" && Token != "+")
      {
        Operands.push_back(std::stoll(Token));
      }
      else
      {
        Multiply = Token == "*";
      }
    }
  }

  if (Globals::Get().VerboseMode)
    ReproduceInputFile();
}
void Day6Processor::ReproduceInputFile()
{
  std::vector<std::string> OutputLines;
  for (const auto &[Operands, Multiply] : Problems)
  {
    int OperandNumber = 0;
    for (const auto &Operand : Operands)
    {
      if (OutputLines.size() <= OperandNumber)
      {
        OutputLines.push_back(std::format("{}", Operand));
      }
      else
      {
        OutputLines[OperandNumber] += std::format("\t{}", Operand);
      }
      OperandNumber++;
    }
  }
  OutputLines.push_back("");
  for (const auto &[Operands, Multiply] : Problems)
  {
    std::string& OperatorsLine = OutputLines[OutputLines.size()-1];
    if (!OperatorsLine.empty())
      OperatorsLine += "\t";
    OperatorsLine += Multiply ? "*" : "+";
  }

  for (const auto& OutputLine : OutputLines)
  {
    std::cout << OutputLine << std::endl;
  }
}
bool Day6Processor::IsFinished() const
{
  return CurrentProblemIndex >= Problems.size();
}

intmax_t Day6Processor::Step(const intmax_t LastValue)
{
  const auto &[Operands, Multiply] = Problems[CurrentProblemIndex++];
  intmax_t Result = Multiply ? 1 : 0;
  for (const auto& Operand : Operands)
  {
    if (Multiply)
    {
      Result = Result * Operand;
    }
    else
    {
      Result = Result + Operand;
    }
  }
  return LastValue + Result;
}