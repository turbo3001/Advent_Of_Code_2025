//
// Created by Luke on 19/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"

class Day7Processor : public IDayProcessor
{
public:
  explicit Day7Processor(const std::string& InputFileName);
  inline intmax_t RunDay(const intmax_t InitialValue) override;
  intmax_t Step(intmax_t LastValue) override;
private:
  std::string LastLine = "";

  struct PathNode
  {
    int X;
    int Y;
    PathNode(const int X, const int Y) : X(X), Y(Y) {}
    PathNode* LeftPath = nullptr;
    PathNode* RightPath = nullptr;
  };
  PathNode StartNode;

  intmax_t GetPathCount(PathNode* CurrentNode);
};
