#ifdef LEXICALANALYZER_UNIT_TEST
#include "LexicalAnalyzer.h"
#include <iostream>

using namespace lexia;

int main(int argc, char* argv[])
{
	try{
		while(true){
			std::string line;
			std::getline(std::cin, line);
			LexicalAnalyzer lexical_analyzer(line);
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

	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
    return 0;
}

#endif
