//
//  parser.cpp
//  derivative_dz
//
//  Created by Barbara Grape on 29.10.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <stdexcept>
#include "parser.h"
#include "tree.h"
#include "token_queue.h"

bool expect_oper(TokenQueue& t, TokenOper::Oper op)
{
    Token *tt = t.front();
    if (tt->get_type() != Token::operation)
        return false;
    TokenOper *top = static_cast<TokenOper*>(tt);
    if (top->get_op() != op)
        return false;
    return true;
}
void pop_oper(TokenQueue& t, TokenOper::Oper op, const char* msg)
{
    if (!expect_oper(t, op))
        throw std::runtime_error (msg);
    t.pop();
}
Vertex *exp ( TokenQueue &t);
Vertex *term ( TokenQueue &t);
Vertex *prim ( TokenQueue &t)
{
    Token *tok = t.front();
    switch (tok->get_type())
    {
        case Token::number :
        {
            TokenNum *n = static_cast<TokenNum*>(tok);
            Vertex *v = new VertConst(n->get_double());
            t.pop();
            return v;
        }
        case Token::operation :
        {
            TokenOper::Oper op = static_cast<TokenOper*>(tok)->get_op();
            switch (op) {
                case TokenOper::open_bracket:
                {
                    t.pop();
                    Vertex *e = exp(t);
                    pop_oper(t, TokenOper::close_bracket, "Oops, some problems with brackets, check it out please");
                    return e;
                }
                case TokenOper::substraction:
                    t.pop();
                    return new VertUnFunc(VertUnFunc::minus, term(t));
                    
                default:
                    throw std::runtime_error("Sorry, you may make a mistake with sign, cheсk it please");
            }
        }
        case Token::variable :
        {
            TokenVar *n = static_cast<TokenVar*>(tok);
            Vertex *v = new VertVar(n->get_var());
            t.pop();
            return v;
        }
        case Token::function :
        {
            
            TokenFunc::Func f = static_cast<TokenFunc*>(tok)->get_func();
            Vertex *arg1 = nullptr, *arg2 = nullptr;
            t.pop();
            arg1 = exp(t);
            switch (f)
            {
                case TokenFunc::sin :
                    pop_oper(t, TokenOper::close_bracket, "Sorry, you may make a mistake in sin, cheсk it please");
                    return new VertUnFunc(VertUnFunc::UnFunc::sin, arg1);
                case TokenFunc::cos:
                    pop_oper(t, TokenOper::close_bracket, "Sorry, you may make a mistake in cos, cheсk it please");
                    return new VertUnFunc(VertUnFunc::UnFunc::cos, arg1);
                case TokenFunc::tg :
                    pop_oper(t, TokenOper::close_bracket, "Sorry, you may make a mistake in tg, cheсk it please");
                    return new VertUnFunc(VertUnFunc::UnFunc::tg, arg1);
                case TokenFunc::ctg :
                    pop_oper(t, TokenOper::close_bracket, "Sorry, you may make a mistake in ctg, cheсk it please");
                    return new VertUnFunc(VertUnFunc::UnFunc::ctg, arg1);
                case TokenFunc::log :
                {
                    pop_oper(t, TokenOper::comma, "Sorry, you may make a mistake in log, cheсk it please");
                    arg2 = exp(t);
                    pop_oper(t, TokenOper::close_bracket, "Sorry, you may make a mistake in log, cheсk it please");
                    return new VertBinFunc(VertBinFunc::BinFunc::log, arg1, arg2);
                }
                case TokenFunc::involution :
                {
                    pop_oper (t, TokenOper::comma, "Sorry, you may make a mistake in pow, cheсk it please");
                    arg2 = exp(t);
                    pop_oper(t, TokenOper::close_bracket, "Sorry, you may make a mistake in pow, cheсk it please");
                    return new VertBinFunc(VertBinFunc::BinFunc::involution, arg1, arg2);
                }
                default:
                    throw std::runtime_error ("Sorry, you may make a mistake with some math function, cheсk it out please");
            }
        }
        default:
            throw std::runtime_error ("Sorry, you may make a mistake in your expression, cheсk it out please");
    }
}

Vertex *term ( TokenQueue &t)
{
    Vertex *first = prim(t);
    while (t.front()) {
        Token *tok = t.front();
        
        if (tok->get_type()!= Token::operation)
            return first;
        
        TokenOper *op = static_cast<TokenOper*>(tok);
        
        switch (op->get_op()) {
            case TokenOper::multiplication :
            {
                t.pop();
                Vertex *second = prim(t);
                first = new VertBinFunc (VertBinFunc::multiplication, first, second);
                break;
            }
            case TokenOper::division :
            {
                t.pop();
                Vertex *second = prim(t);
                first = new VertBinFunc (VertBinFunc::division, first, second);
                break;
            }
                
            default:
                return first;
        }
    }
    return first;
    
}
Vertex *exp ( TokenQueue &t)
{
    Vertex *first = term(t);
    while (t.front()) {
        Token *tok = t.front();
        
        if (tok->get_type()!= Token::operation)
            return first;
        
        TokenOper *op = static_cast<TokenOper*>(tok);
        
        switch (op->get_op()) {
            case TokenOper::addition :
            {
                t.pop();
                Vertex *second = term(t);
                first = new VertBinFunc (VertBinFunc::addition, first, second);
                break;
            }
            case TokenOper::substraction :
            {
                t.pop();
                Vertex *second = term(t);
                first = new VertBinFunc (VertBinFunc::substraction, first, second);
                break;
            }
                
            default:
                return first;
        }
    }
    return first;
}


Vertex *parse ( TokenQueue &t)
{
    Vertex *v = exp(t);
    if (t.front()->get_type() != Token::Type::end)
        throw std::runtime_error("Sorry, you may make a mistake, check it out please");
    return v;
}
