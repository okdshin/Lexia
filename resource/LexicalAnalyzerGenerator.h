#pragma once
//LexicalAnalyzerGenerator:20130608
#include <iostream>

namespace lexia
{
class LexicalAnalyzerGenerator{
public:
    LexicalAnalyzerGenerator(const String& definition_code) : 
		definition_code_(definition_code){}

	
private:
	const String definition_code_;
};
}

