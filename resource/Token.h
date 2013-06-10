#pragma once
//Token:20130424
#include <iostream>
#include "TokenType.h"
#include "SharedPtr.h"
#include "Word.h"

namespace lexia
{
class Token{
public:
	using Ptr = SharedPtr<Token>;
	static auto Create(const TokenType& type, const Word& word) -> Ptr {
		return Ptr(new Token(type, word));	
	}

	static auto EOF_TOKEN() -> Ptr {
		return Token::Create(TokenType::EOF_TOKEN_TYPE(), Word("EOF_CHARACTOR"));	
	}

	auto IsEof()const -> bool {
		return type_ == TokenType::EOF_TOKEN_TYPE();		
	}

	auto GetType()const -> TokenType {
		return type_;
	}

	auto GetWord()const -> Word {
		return word_;
	}
	
private:
	Token(const TokenType& type, const Word& word) 
		: type_(type), word_(word){}
	
	TokenType type_;
	Word word_;
};
auto operator<<(std::ostream& os, const Token& token) -> std::ostream& {
	os << "Token:" << "\"" << token.GetType() << "\"" << ", \"" << token.GetWord() << "\"";
	return os;	
}
}

