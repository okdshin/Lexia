#pragma once
//LexicalAnalyzer:20130416
#include <iostream>
#include <exception>
#include <boost/regex.hpp>
#include "Token.h"

namespace lexia
{

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

class LexicalAnalyzer{
public:
    LexicalAnalyzer(const std::string& code) : 
		code_(code){}


	auto GetNextToken() -> Token::Ptr {	
		std::cout << code_ << std::endl;
		if(code_.empty()){
			return Token::EOF_TOKEN();
		}
		{
			boost::regex ignore_reg("^[ \t\n]*");
			boost::smatch matched;
			boost::regex_search(code_, matched, ignore_reg);
			auto matched_str = matched.str();
			std::cout << matched_str.length() << std::endl;
			code_.erase(0, matched_str.length());
		}
		std::vector<Token::Ptr> regular_expression_token_list;
		regular_expression_token_list.push_back(
			Token::Create(TokenType::INT(), Word("^int")));
		regular_expression_token_list.push_back(
			Token::Create(TokenType::INT_CONSTANT(), Word("^[0-9]+")));
		regular_expression_token_list.push_back(
			Token::Create(TokenType::IDENTIFIER(), Word("^[a-zA-Z_][a-zA-Z_0-9]*")));
		//{%regular_expression_code%}

		std::vector<Token::Ptr> matched_token_list;
		for(const auto reg_token : regular_expression_token_list){
			const boost::regex reg(reg_token->GetWord().ToString());
			boost::smatch matched;
			if(boost::regex_search(code_, matched, reg)){
				std::cout << "matched:" << matched.str() 
					<< " as " << reg_token->GetType() << std::endl;
				matched_token_list.push_back(
					Token::Create(reg_token->GetType(), matched.str()));	
			}
		}

		if(matched_token_list.empty()){
			const auto invalid_char = std::string(1, code_.front());
			throw InvalidCharactorError("InvalidCharactorError: \""+invalid_char+"\"");
		}

		const auto longest_matched_token = 
			*std::max_element(matched_token_list.begin(), matched_token_list.end(),
				[](const Token::Ptr& left, const Token::Ptr& right) -> bool {
					return left->GetWord().ToString().length() 
						< right->GetWord().ToString().length();
				}
			);
		
		std::cout << "before:" << code_ << std::endl;
		code_.erase(0, longest_matched_token->GetWord().ToString().length());
		std::cout << "after:" << code_ << std::endl;
		return longest_matched_token; 
	}

private:
	std::string code_;
};
}

