//
// Created by Luke on 19/12/2025.
//

#include "Day7Processor.hpp"

#include "../Common/DebugHelpers.hpp"

Day7Processor::Day7Processor(const std::string &InputFileName)
    : IDayProcessor(InputFileName), StartNode(-1,0)
  {
  if (Globals::Get().Part2Mode)
    {
    const std::string FirstLine = InputFile.GetNextLine();
    for (int Column = 0; Column < FirstLine.length(); Column++)
      {
      if (FirstLine[Column] == 'S')
        {
        StartNode.X = Column;
        }
      }
    }
  }

intmax_t Day7Processor::RunDay(const intmax_t InitialValue)
{
  if (!Globals::Get().Part2Mode)
    return IDayProcessor::RunDay(InitialValue);

  if (Globals::Get().VerboseMode)
    ReproduceInputFile();
  return InitialValue + GetPathCount(&StartNode);
}
intmax_t Day7Processor::Step(const intmax_t LastValue)
{
//Part 1 fits into the Framework I've written, Part 2 is recursive within the RunDay function!
  if (LastLine.empty())
  {
    LastLine = InputFile.GetNextLine();
    DebugLog("{}", LastLine);
    return LastValue;
  }

  intmax_t NewValue = LastValue;
  const std::string CurrentLine = InputFile.GetNextLine();
  std::string NewLine = CurrentLine;
  for (int Column =0; Column < CurrentLine.length(); Column++)
  {
    if (LastLine[Column] == 'S' || LastLine[Column] == '|')
    {
      if (CurrentLine[Column] == '^')
      {
        NewValue++;
        if (Column > 0)
          NewLine[Column-1] = '|';
        if (Column < CurrentLine.length() - 1)
          NewLine[Column+1] = '|';
      }
      else
      {
        NewLine[Column] = '|';
      }
    }
  }
  DebugLog("{}", NewLine);
  LastLine = NewLine;
  return NewValue;
}

intmax_t Day7Processor::GetPathCount(PathNode *CurrentNode)
{
  intmax_t PathCount = 0;
  InputFile.SetLineNumber(CurrentNode->Y);
  DebugLog("Node x={}, y={}", CurrentNode->X, CurrentNode->Y);
  while (InputFile.HasLine())
  {
    if (const std::string CurrentLine = InputFile.GetNextLine();
        CurrentLine[CurrentNode->X] == '^')
    {
      const int CurrentY = InputFile.GetLineNumber();
      if (CurrentNode->X > 0)
      {
        if (CurrentNode->LeftPath == nullptr)
        {
          CurrentNode->LeftPath = new PathNode(CurrentNode->X-1, CurrentY);
        }

        DebugLog("Checking Left Node: <{}, {}>", CurrentNode->LeftPath->X, CurrentNode->LeftPath->Y);
        PathCount += GetPathCount(CurrentNode->LeftPath);
        InputFile.SetLineNumber(CurrentY);
      }
      if (CurrentNode->X < CurrentLine.length() - 1)
      {
        if (CurrentNode->RightPath == nullptr)
        {
          CurrentNode->RightPath = new PathNode(CurrentNode->X+1, CurrentY);
        }

        DebugLog("Checking Right Node: <{}, {}>", CurrentNode->RightPath->X, CurrentNode->RightPath->Y);
        PathCount += GetPathCount(CurrentNode->RightPath);
        InputFile.SetLineNumber(CurrentY);
      }
    }
  }
  return PathCount+1;
}