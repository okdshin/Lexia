#pragma once
//TokenType:20130424
#include <iostream>

namespace lexia
{
class TokenType{
public:
	static auto EOF_TOKEN_TYPE() -> TokenType { return TokenType("EOF_TOKEN"); }
	static auto INT() -> TokenType { return TokenType("INT"); }
	static auto INT_CONSTANT() -> TokenType { return TokenType("INT_CONSTANT"); }
	static auto IDENTIFIER() -> TokenType { return TokenType("IDENTIFIER"); }

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

