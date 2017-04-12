//
//  token_queue.cpp
//  derivative_dz
//
//  Created by Barbara Grape on 29.10.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//


#include <queue>
#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "token_queue.h"
#include "token.h"

std::unordered_map<std::string, TokenFunc::Func> mapFunc =
{
    {"cos", TokenFunc::cos},
    {"sin", TokenFunc::sin},
    {"tg",  TokenFunc::tg},
    {"ctg", TokenFunc::ctg},
    {"log", TokenFunc::log},
    {"pow", TokenFunc::involution}
};

void TokenQueue::pop(){
    if (tq.empty())
        return;
    
    Token *t = front();
    tq.pop();
    delete t;
};

void TokenQueue::push(Token *t){
    tq.push(t);
};
Token* TokenQueue::front() const {
    return (tq.empty()) ? nullptr : tq.front();
};
TokenQueue:: ~TokenQueue() {
    while (!tq.empty())
        pop();
};

TokenQueue::TokenQueue(std::istream &stream) {
    char ch = 0;
    while (stream.get(ch) && !stream.eof())
    {
        stream.putback(ch);
        while (stream.get(ch) && ch != '\n')
        {
            if (!std::isspace(ch))
                break;
        }
        switch (ch)
        {
            case '\n':
                push(new Token(Token::end));
                return;
                
            case '+':
                push(new TokenOper(TokenOper::addition));
                break;
            case '-':
                push(new TokenOper(TokenOper::substraction));
                break;
            case '*':
                push(new TokenOper(TokenOper::multiplication));
                break;
            case '/':
                push(new TokenOper(TokenOper::division));
                break;
            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9': case '.':
            {
                stream.putback(ch);
                double d;
                stream >> d;
                push(new TokenNum(d));
                break;
            }
            case '(':
                push(new TokenOper(TokenOper::open_bracket));
                break;
            case ')':
                push(new TokenOper(TokenOper::close_bracket));
                break;
            case ',':
                push(new TokenOper(TokenOper::comma));
                break;
                
            default:
            {
                if (!std::isalpha(ch))
                    throw std::runtime_error("Bad token!");
                std::string str(1, ch);
                
                while(stream.get(ch) && std::isalpha(ch))
                    str += ch;
                
                if (str.size() == 1)
                {
                    if (!std::isalpha(ch))
                        stream.putback(ch);
                    push(new TokenVar(str[0]));
                    break;
                }
                std::unordered_map<std::string, TokenFunc::Func>::const_iterator cit = mapFunc.find(str);
                if (cit == mapFunc.end())
                    throw std::runtime_error("Bad name!");
                
                TokenFunc::Func f = cit->second;
                
                if (ch != '(')
                    throw std::runtime_error("'(' not found'");
                
                push(new TokenFunc(f));
                break;
            }
        }
    }
    push(new Token(Token::end));
}