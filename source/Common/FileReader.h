//
// Created by Luke on 13/12/2025.
//

#pragma once

#include <fstream>
#include <functional>
#include <string_view>

class FileReader
{
public:
	explicit FileReader(const std::string& FileName);
	~FileReader() { FileToRead.close(); };

	bool HasLine() const { return FileToRead.is_open() && !FileToRead.eof(); };

	std::string GetNextLine();

	template<typename LineType>
	LineType GetNextLine(std::function<LineType(const std::string_view&)> ParseFunction) {
		if (!HasLine()) return LineType();

		const std::string Line = GetNextLine();
		return ParseFunction(Line);
	}

private:
	std::ifstream FileToRead;
};
