//
//  tree.cpp
//  derivative_dz
//
//  Created by Barbara Grape on 29.10.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <stdexcept>
#include <iostream>
#include "tree.h"



void VertBinFunc::print_tree(std::ostream &s) const
{
    switch(func)
    {
        case VertBinFunc::addition:
        case VertBinFunc::substraction:
        case VertBinFunc::division:
        case VertBinFunc::multiplication:
            s << static_cast<char>(func) << '[';
            left->print_tree(s);
            s << ',';
            right->print_tree(s);
            s << ']';
            break;
            
        case VertBinFunc::log:
            s << "log(";
            left->print_tree(s);
            s << ',';
            right->print_tree(s);
            s << ')';
            break;
        case VertBinFunc::involution:
            s << "^[";
            left -> print_tree(s);
            s << ',';
            right -> print_tree(s);
            s << ']';
            break;
        case VertBinFunc::none:
            break;
    }
}

const char* functToStr[] = { "cos", "sin", "tg", "ctg", "", ""};
void VertUnFunc::print_tree(std::ostream &s) const
{
    switch(func)
    {
        case VertUnFunc::cos:
        case VertUnFunc::sin:
        case VertUnFunc::tg:
        case VertUnFunc::ctg:
            s << functToStr[func] << '(';
            child->print_tree(s);
            s << ')';
            break;
            
        case VertUnFunc::minus:
            s << "-(";
            child->print_tree(s);
            s << ')';
            break;
            
    }
}

void VertVar::print_tree(std::ostream &s) const
{
    s << var;
}

void VertConst::print_tree(std::ostream &s) const
{
    s << constant;
}

bool Vertex::compare (Vertex* f, Vertex* s )
{
#define CAST(a, b, c) c* f1 = static_cast<c*>(a); c* s1 = static_cast<c*>(b)
    if (f->get_v_type() != s->get_v_type())
        return false;
    switch (f->get_v_type()) {
        case Vertex::unary_function:
        {
            CAST(f, s, VertUnFunc);
            if (f1->get_func() != s1->get_func())
                return false;
            else
                return compare (f1->get_child(), s1->get_child());
            break;
        }
        case Vertex::binary_function:
        {
            CAST(f, s, VertBinFunc);
            if (f1->get_func() != s1->get_func())
                return false;
            else
            {
                return compare (f1->get_left(), s1->get_left()) &&
                compare (f1->get_right(), s1->get_right());
            }
            break;
        }
        case Vertex::variable:
        {
            CAST(f, s, VertVar);
            if (f1->get_var() != s1->get_var())
                return false;
            return true;
        }
        case Vertex::constant:
        {
            CAST(f, s, VertConst);
            if (f1->get_const() != s1->get_const())
                return false;
            return true;
        }
            
        default:
            throw std::runtime_error("There is no such type");
            break;
    }
    return true;
#undef CAST
}

Vertex* Vertex::copy(Vertex* t)
{
#define CAST(a, b) b* t1 = static_cast<b*>(a)
    switch (t->get_v_type()) {
        case Vertex::unary_function:
        {
            CAST(t, VertUnFunc);
            return new VertUnFunc( t1->get_func(), copy(t1->get_child()));
        }
        case Vertex::binary_function:
        {
            CAST(t,VertBinFunc);
            return new VertBinFunc( t1->get_func(), copy(t1->get_left()), copy(t1->get_right()));
        }
        case Vertex::variable:
        {
            CAST(t,VertVar);
            return new VertVar( t1->get_var());
        }
        case Vertex::constant:
        {
            CAST(t,VertConst);
            return new VertConst( t1->get_const());
        }
            
        default:
            throw std::runtime_error("There is no such type");
            break;
    }
#undef CAST
}
bool need_brackets (Vertex* t)
{
#define CAST(a, b)  b* t1 = static_cast<b*>(a)
    switch (t->get_v_type())
    {
        case Vertex::unary_function:
        {
            CAST(t, VertUnFunc);
            switch (t1->get_func())
            {
                case VertUnFunc::UnFunc::cos:
                case VertUnFunc::UnFunc::sin:
                case VertUnFunc::UnFunc::tg:
                case VertUnFunc::UnFunc::ctg:
                    return false;
                    break;
                    
                default:
                    break;
            }
        }
        case Vertex::binary_function:
            {
                CAST(t, VertBinFunc);
                switch (t1->get_func())
                {
                    case VertBinFunc::BinFunc::division:
                    case VertBinFunc::BinFunc::multiplication:
                    case VertBinFunc::BinFunc::log:
                    case VertBinFunc::BinFunc::involution:
                        return false;
                        
                    case VertBinFunc::BinFunc::substraction:
                    case VertBinFunc::BinFunc::addition:
                        return true;

                    default:
                        return false;
                }
            }
        default:
            return false;
        }
   
#undef CAST
}
int property (VertBinFunc* t)
{
    switch (t->get_func()) {
        case VertBinFunc::BinFunc::addition:
        case VertBinFunc::BinFunc::substraction:
            return 0;
        case VertBinFunc::BinFunc::multiplication:
        case VertBinFunc::BinFunc::division:
            return 1;
        case VertBinFunc::BinFunc::involution:
            return 2;
            
        default: throw std::runtime_error("Problems with property");
            break;
    }
}

static void _print_expression(std::ostream& os,  Vertex* t, int prec, bool isNewExpr =false)
{
#define CAST(a, b)  b* t1 = static_cast< b*>(a)
    switch (t->get_v_type())
    {
        case Vertex::unary_function:
        {
            CAST(t, VertUnFunc);
            
            switch (t1->get_func())
            {
                case VertUnFunc::UnFunc::minus:
                {
                    if (!isNewExpr)
                        os << '(';
                    os << '-';
                    
                    if (need_brackets(t1->get_child()))
                    {
                        os << '(';
                        _print_expression(os, t1->get_child(), prec, true);
                        os << ')';
                    }
                    else
                        _print_expression(os, t1->get_child(), prec);
                    
                    if (!isNewExpr)
                        os<< ')';
                    break;
                }
                    
                default:
                    break;
                
                case VertUnFunc::UnFunc::cos:
                case VertUnFunc::UnFunc::sin:
                case VertUnFunc::UnFunc::tg:
                case VertUnFunc::UnFunc::ctg:
                {
                    os << functToStr[t1->get_func()] << '(';
                    _print_expression(os, t1->get_child(), prec, true);
                    os << ')';
                    break;
                }
            }
            break;
        }
        case Vertex::binary_function:
        {
            CAST(t, VertBinFunc);
         
            if (t1->get_func() == VertBinFunc::BinFunc::log)
            {
                os << "log(";
                _print_expression(os, t1->get_left(), prec, true);
                os<<",";
                _print_expression(os, t1->get_right(), prec, true);
                os <<")";
                break;
            }
            
            if (prec > property(t1))
            {
                os << '(';
                _print_expression(os, t1->get_left(), property(t1), true);
            }
            else
            {
                _print_expression(os, t1->get_left(), property(t1), false);
            }
            
          //  os << it->second;
            switch (t1->get_func()) {
                case VertBinFunc::addition:
                case VertBinFunc::substraction:
                case VertBinFunc::division:
                case VertBinFunc::multiplication:
                    os << static_cast<char>(t1->get_func());
                    break;
                
                case VertBinFunc::involution:
                    os << "^";
                    break;
            }

            _print_expression(os, t1->get_right(), property(t1));
            if (prec > property(t1))
                os << ')';
            break;
        }
        case Vertex::variable:
        {
            CAST(t,VertVar);
            os << t1->get_var();
            break;
        }
            
        case Vertex::constant:
        {
            CAST(t,VertConst);
            os << t1->get_const();
            break;
        }
            
        default:
            throw std::runtime_error("Print_expression error!");
    }
    
}
void print_expression(std::ostream& os, Vertex* n)
{
    _print_expression(os, n, 0, true);
}

