//
// Created by Luke on 13/12/2025.
//

#include "FileReader.h"

FileReader::FileReader(const std::string& FileName)
{
  if (FileName.empty())
	  throw std::invalid_argument("Invalid file name!");

  FileToRead = std::ifstream(FileName);
  if (!FileToRead.is_open())
	  throw std::runtime_error("Unable to open file: " + FileName);
}

void FileReader::SetLineNumber(const int NewLineNumber)
{
    if (NewLineNumber < LineNumber)
    {
      FileToRead.seekg(0);
      LineNumber = 0;
    }

    while (HasLine() && LineNumber < NewLineNumber)
    {
      GetNextLine();
    }

    if (!HasLine() && LineNumber != NewLineNumber)
      throw std::invalid_argument("Invalid line number!");
}

std::string FileReader::GetNextLine()
{
  if (!HasLine())
	  throw std::logic_error("No Line Available in FileReader::GetNextLine");

  std::string nextLine;
  std::getline(FileToRead, nextLine);
  LineNumber++;
  return nextLine;
}