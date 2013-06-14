#ifdef USERTEST_UNIT_TEST
#include "UserTest.h"
#include <iostream>
#include "Lexer.h"

using namespace user_test;

int main(int argc, char* argv[])
{
	while(true){
		std::string line;
		if(!std::getline(std::cin, line)){ break; }
		lexia::Lexer lexer(line);
		while(true){
			const auto token = lexer.GetNextToken(); 
			if(token.IsEof()){
				break;	
			}
			std::cout << "NextToken:" << token << "\n" << std::endl;
			//std::string str;
			//std::cin >> str;
		}
	}

    return 0;
}

#endif
