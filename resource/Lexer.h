#ifndef LEXER_H
#define LEXER_H
//Lexer:20130416
#include <iostream>
#include <string>
#include <exception>
#include <boost/regex.hpp>
#include <boost/format.hpp>

namespace lexia
{
class TokenType{
public:
	static auto LEXIA_UNINITIALIZED_TOKEN_TYPE() -> TokenType { 
		return TokenType("LEXIA_UNINITIALIZED_TOKEN"); }
	static auto LEXIA_EOF_TOKEN_TYPE() -> TokenType { return TokenType("LEXIA_EOF_TOKEN"); }
#ifndef LEXER_UNIT_TEST
{{ token_type_code }}
#else
	static auto INT() -> TokenType { return TokenType("INT"); }
	static auto SEMICOLON() -> TokenType { return TokenType("SEMICOLON"); }
	static auto EQUAL() -> TokenType { return TokenType("EQUAL"); }
	static auto CONSTANT() -> TokenType { return TokenType("CONSTANT"); }
	static auto IDENTIFIER() -> TokenType { return TokenType("IDENTIFIER"); }	
#endif

	auto ToString()const -> std::string {
		return token_type_str;	
	}

	auto operator==(const TokenType& pair)const -> bool { 
		return this->token_type_str == pair.token_type_str; 
	}

	auto operator!=(const TokenType& pair)const -> bool { 
		return !(*this == pair); 
	}

private:
	explicit TokenType(const std::string& token_type_str) : token_type_str(token_type_str){}
	std::string token_type_str;
};
auto operator<<(std::ostream& os, const TokenType& token_type) -> std::ostream& {
	os << "TokenType:" << token_type.ToString();	
	return os;	
}

class Word{
public:
	Word() : word_str_(){}
    explicit Word(const std::string& word_str) : word_str_(word_str){}

	auto ToString()const -> std::string {
		return word_str_;	
	}

private:
	std::string word_str_;
};
auto operator<<(std::ostream& os, const Word& word) -> std::ostream& {
	os << "Word:" << "\"" << word.ToString() << "\"";
	return os;
}
auto operator <(const Word& left, const Word& right) -> bool {
	return left.ToString() < right.ToString();	
}

class Token{
public:
	Token():type_(TokenType::LEXIA_UNINITIALIZED_TOKEN_TYPE()), word_(){}
	Token(const TokenType& type, const Word& word) 
		: type_(type), word_(word){}
	
	static auto EOF_TOKEN() -> Token{
		return Token(TokenType::LEXIA_EOF_TOKEN_TYPE(), Word("EOF_CHARACTOR"));	
	}
	
#ifndef LEXER_UNIT_TEST
{{ syntax_token_code }}
#endif
	auto IsEof()const -> bool {
		return type_ == TokenType::LEXIA_EOF_TOKEN_TYPE();		
	}
	
	auto IsUninitialized()const -> bool {
		return type_ == TokenType::LEXIA_UNINITIALIZED_TOKEN_TYPE();		
	}

	auto GetType()const -> TokenType {
		return type_;
	}

	auto GetWord()const -> Word {
		return word_;
	}
	
private:
	TokenType type_;
	Word word_;
};
auto operator<<(std::ostream& os, const Token& token) -> std::ostream& {
	os << "Token:" << token.GetType() << ", " << token.GetWord();
	return os;	
}

class InvalidCharactorError : public std::exception {
public:
	InvalidCharactorError(const std::string& message) : 
		message_(message) {}
	virtual ~InvalidCharactorError() throw() {}
	virtual const char* what() const throw() {
		return message_.c_str();
	}
private:
	const std::string message_;
};

class Lexer{
public:
    Lexer(const std::string& code) : 
		code_(code){}


	auto GetNextToken() -> Token {	
		std::cout << code_ << std::endl;
		{
#ifndef LEXER_UNIT_TEST
			boost::regex ignore_reg("\\A{{ ignore_regular_expression }}");
#else
			boost::regex ignore_reg("\\A[ \\t\\n]*");
#endif
			boost::smatch matched;
			boost::regex_search(code_, matched, ignore_reg);
			auto matched_str = matched.str();
			std::cout << matched_str.length() << std::endl;
			code_.erase(0, matched_str.length());
		}
		if(code_.empty()){
			return Token::EOF_TOKEN();
		}

		std::vector<Token> regular_expression_token_list;
#ifndef LEXER_UNIT_TEST
{{ regular_expression_code }}
#else
		std::cout << "!!!UNIT TEST SAMPLE!!!" << std::endl;
		regular_expression_token_list.push_back(
			Token(TokenType::INT(), Word("\\Aint")));
		regular_expression_token_list.push_back(
			Token(TokenType::SEMICOLON(), Word("\\A;")));
		regular_expression_token_list.push_back(
			Token(TokenType::EQUAL(), Word("\\A=")));
		regular_expression_token_list.push_back(
			Token(TokenType::CONSTANT(), Word("\\A[0-9]+")));
		regular_expression_token_list.push_back(
			Token(TokenType::IDENTIFIER(), Word("\\A[a-zA-Z_][a-zA-Z0-9_]*")));	
#endif
		std::vector<Token> matched_token_list;
		for(const auto reg_token : regular_expression_token_list){
			const boost::regex reg(reg_token.GetWord().ToString());
			boost::smatch matched;
			if(boost::regex_search(code_, matched, reg)){
				std::cout << "matched:" << matched.str() 
					<< " as " << reg_token.GetType() << std::endl;
				matched_token_list.push_back(
					Token(reg_token.GetType(), matched.str()));	
			}
		}

		if(matched_token_list.empty()){
			const auto invalid_char = std::string(1, code_.front());
			auto message_format = boost::format("InvalidCharactorError: \"%1%\"(CharCode: %2%) is invalid charactor.") % invalid_char % int(code_.front());
			throw InvalidCharactorError(message_format.str());
		}

		const auto longest_matched_token = 
			*std::max_element(matched_token_list.begin(), matched_token_list.end(),
				[](const Token& left, const Token& right) -> bool {
					return left.GetWord().ToString().length() 
						< right.GetWord().ToString().length();
				}
			);
		
		std::cout << "before:" << code_ << std::endl;
		code_.erase(0, longest_matched_token.GetWord().ToString().length());
		std::cout << "after:" << code_ << std::endl;
		return longest_matched_token; 
	}

private:
	std::string code_;
};
}
#endif
