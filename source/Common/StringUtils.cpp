//
// Created by Luke on 14/12/2025.
//

#include "StringUtils.h"

#include <algorithm>

bool StringEqualCaseInsensitive(const std::string_view &lhs, const std::string_view &rhs) {
	auto caseInsensitive = [](const char a, const char b) -> bool { return tolower(a) == tolower(b); };
	return std::ranges::equal(lhs, rhs, caseInsensitive);
}
bool IsRepeatedSubstring(const std::string_view string, const int substringLength) {
	if (string.length() % substringLength != 0)
		return false;
	const std::string_view substring = string.substr(0, substringLength);
	for (int i = substringLength; i < string.length(); i += substringLength) {
		if (string.substr(i, substringLength) != substring)
			return false;
	}
	return true;
}
