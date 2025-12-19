//
// Created by Luke on 18/12/2025.
//

#include "Day6Processor.hpp"
#include <sstream>
#include "../Common/DebugHelpers.hpp"

Day6Processor::ProblemsType ParsePart1Problems(FileReader* InputFile)
{
  Day6Processor::ProblemsType Problems;
  while (InputFile->HasLine())
  {
    auto StringStream = std::stringstream(InputFile->GetNextLine());

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
  return Problems;
}

Day6Processor::ProblemsType ParsePart2Problems(FileReader* InputFile)
{
  Day6Processor::ProblemsType Problems;
  std::vector<std::string> InputLines;
  while (InputFile->HasLine())
  {
    std::string Line = InputFile->GetNextLine();

    if (Line.empty())
      throw std::runtime_error(std::format("Empty Line found on Line {}",InputFile->GetLineNumber()));

    if (InputLines.size() > 0 && Line.size() != InputLines[0].size())
    {
      DebugLog("Next Line length ({}) doesn't match length of previous lines ({}), extending previous lines", Line.size(), InputLines[0].size());
      for (std::string& InputLine : InputLines)
      {
        for (int i = InputLine.size(); i < Line.size(); ++i)
        {
          InputLine += " ";
        }
        for (int i = Line.size(); i < InputLine.size(); ++i)
        {
          Line += " ";
        }
      }
    }

    InputLines.emplace_back(Line);
  }

  std::vector<uintmax_t> Operands;
  Operands.reserve(InputLines.size()-1);
  for (int Column = InputLines[0].size()-1; Column >= 0; --Column)
  {
    std::string CurrentDigit = "";
    for (int Row = 0; Row < InputLines.size() - 1; ++Row)
    {
      const std::string& Line = InputLines[Row];
      if (Line[Column] == ' ')
        continue;
      CurrentDigit += Line[Column];
    }

    if (CurrentDigit.size() <= 0)
      continue;

    Operands.push_back(std::stoll(CurrentDigit));

    if (const std::string CurrentOperand =
            InputLines[InputLines.size() - 1].substr(Column, 1);
        CurrentOperand != " ")
    {
      Problems.push_back({Operands, CurrentOperand == "*"});
      Operands.clear();
    }
  }
  return Problems;
}

Day6Processor::Day6Processor(const std::string &InputFileName) : IDayProcessor(InputFileName)
{
  if (!Globals::Get().Part2Mode)
    Problems = InputFile.ParseWholeFile<ProblemsType>(&ParsePart1Problems);
  else
    Problems = InputFile.ParseWholeFile<ProblemsType>(&ParsePart2Problems);

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