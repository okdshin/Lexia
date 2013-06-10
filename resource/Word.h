#pragma once
//Word:20130610
#include <iostream>
#include <string>

namespace lexia
{
class Word{
public:
    Word(const std::string& word_str) : word_str_(word_str){}

	auto ToString()const -> std::string {
		return word_str_;	
	}

private:
	std::string word_str_;
};

auto operator<<(std::ostream& os, const Word& word) -> std::ostream& {
	os << "Word:" << word.ToString();
	return os;
}
}

