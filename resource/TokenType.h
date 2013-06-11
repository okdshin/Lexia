#pragma once
//TokenType:20130424
#include <iostream>

namespace lexia
{
class TokenType{
public:
	static auto LEXIA_EOF_TOKEN_TYPE() -> TokenType { return TokenType("LEXIA_EOF_TOKEN"); }
#ifndef LEXICALANALYZER_UNIT_TEST
{{ token_type_code }}
#else
	static auto INT() -> TokenType { return TokenType("INT"); }
	static auto SEMICOLON() -> TokenType { return TokenType("SEMICOLON"); }
	static auto EQUAL() -> TokenType { return TokenType("EQUAL"); }
	static auto CONSTANT() -> TokenType { return TokenType("CONSTANT"); }
	static auto IDENTIFIER() -> TokenType { return TokenType("IDENTIFIER"); }	
#endif

	bool operator==(const TokenType& pair)const { 
		return this->token_type_str == pair.token_type_str; }

	friend auto operator<<(
		std::ostream& os, const TokenType& token_type) -> std::ostream&;

private:
	TokenType(const std::string& token_type_str) : token_type_str(token_type_str){}
	std::string token_type_str;
};
auto operator<<(std::ostream& os, const TokenType& token_type) -> std::ostream& {
	os << "TokenType:" << token_type.token_type_str;	
	return os;	
}
}

