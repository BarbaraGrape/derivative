//
//  token.h
//  derivative_dz
//
//  Created by Barbara Grape on 29.10.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#ifndef derivative_dz_token_h
#define derivative_dz_token_h
#include <queue>

class Token {
public:
    enum Type {
        number, function, operation, variable, end
    };
    Token(Type t) :type(t) {}
    Type get_type () const {return type;}
private:
    Type type;
    
protected:
};

class TokenNum : public Token {
public:
    TokenNum() :Token(Token::number), num(0) { }
    TokenNum(double d) :Token(Token::number), num(d) { }
    double get_double() const { return num;}
private:
    double num;
};

class TokenFunc : public Token {
public:
    enum Func {
        cos, sin, tg, ctg, involution, log, none
    };
    TokenFunc() :Token(Token::function), f(none) { }
    TokenFunc(TokenFunc::Func t) :Token(Token::function), f(t) { }
    Func get_func() const {return f;}
private:
    Func f;
};

class TokenOper : public Token {
public:
    enum Oper {
        division = 0, multiplication, addition, substraction, open_bracket, close_bracket, comma, none
    };
    TokenOper() :Token(Token::operation), o(none) { }
    TokenOper(Oper t) :Token(Token::operation), o(t) { }
    Oper get_op() const {return o;}
private:
    Oper o;
};

class TokenVar : public Token {
public:
    TokenVar() :Token(Token::variable), v(0) { }
    TokenVar(char c) :Token(Token::variable), v(c) { }
    char get_var() const {return v;}
private:
    char v;
};
#endif
