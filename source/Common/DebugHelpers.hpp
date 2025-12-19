//
// Created by Luke on 19/12/2025.
//

#pragma once
#include "Globals.h"

template <typename... _Args>
void DebugLog(std::format_string<_Args...> format, _Args &&...arguments)
{
  if (Globals::Get().VerboseMode)
  {
    std::string DebugString;
    auto BackInserter = std::back_inserter(DebugString);
    std::format_to(BackInserter, format, std::forward<_Args>(arguments)...);
    std::cout << DebugString.c_str() << std::endl;
  }
}