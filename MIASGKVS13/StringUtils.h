#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

template<typename Out>
inline void Split(const std::string &s, char delim, Out result)
{
	std::stringstream stringStream(s);
	std::string item;
	while (std::getline(stringStream, item, delim))
	{
		*(result++) = item;
	}
}

inline std::vector<std::string> Split(const std::string &str, char delim)
{
	std::vector<std::string> splitted;
	Split(str, delim, std::back_inserter(splitted));
	return splitted;
}

inline bool StartsWith(std::string str, std::string characters)
{
	if (str.substr(0, characters.length()) == characters)
	{
		return true;
	}
	else
	{
		return false;
	}
}