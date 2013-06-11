#ifdef USERTEST_UNIT_TEST
#include "UserTest.h"
#include <iostream>
#include "LexicalAnalyzer.h"

using namespace user_test;

int main(int argc, char* argv[])
{
	while(true){
		std::string line;
		std::getline(std::cin, line);
		lexia::LexicalAnalyzer lexical_analyzer(line);
		while(true){
			const auto token = lexical_analyzer.GetNextToken(); 
			if(token->IsEof()){
				break;	
			}
			std::cout << "NextToken:" << *token << "\n" << std::endl;
			//std::string str;
			//std::cin >> str;
		}
	}

    return 0;
}

#endif
