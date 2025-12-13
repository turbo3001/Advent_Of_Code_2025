//
// Created by Luke on 13/12/2025.
//

#pragma once
#include <algorithm>
#include <string>

bool StringEqualCaseInsensitive(const std::string_view& lhs, const std::string_view& rhs) {
	auto caseInsensitive = [](const char a, const char b) -> bool {
		return tolower(a) == tolower(b);
	};
	return std::ranges::equal(lhs, rhs, caseInsensitive);
}