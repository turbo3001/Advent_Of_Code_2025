//
// Created by Luke on 19/12/2025.
//

#include "Day7Processor.hpp"

#include "../Common/DebugHelpers.hpp"

intmax_t Day7Processor::Step(const intmax_t LastValue)
{
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