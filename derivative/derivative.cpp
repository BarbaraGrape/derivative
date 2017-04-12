//
//  derivative.cpp
//  derivative_dz
//
//  Created by Barbara Grape on 10.12.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include "derivative.h"
#include "tree.h"

bool is_such_el(Vertex* tree, char c)
{
#define CAST(a, b) b* t1 = static_cast<b*>(a)
    switch (tree->get_v_type()) {
        case Vertex::constant:
            return false;
        case Vertex::unary_function:
        {
            CAST(tree, VertUnFunc);
            return is_such_el(Vertex::copy(t1->get_child()), c);
        }
        case Vertex::binary_function:
        {
            CAST(tree, VertBinFunc);
            return is_such_el(Vertex::copy(t1->get_left()), c) || is_such_el(Vertex::copy(t1->get_right()), c);
        }
        case Vertex::variable:
        {
            CAST(tree, VertVar);
            if (t1->get_var() == c)
                return true;
            else
                return false;
        }
            
        default:
            throw std::runtime_error("Impossible error");
            
    }
}




Vertex* deriv_un_func(Vertex* t, char c)
{
#define CAST(a, b) b* t1 = static_cast<b*>(a)
    CAST(t, VertUnFunc);
    if (!is_such_el(t, c))
        return new VertConst(0);
    switch (t1->get_func()) {
        case VertUnFunc::UnFunc::minus:
            return new VertUnFunc(VertUnFunc::UnFunc::minus,deriv(t1->get_child(), c));
            
        case VertUnFunc::UnFunc::sin:
            return new VertUnFunc(VertUnFunc::UnFunc::cos,Vertex::copy(t1->get_child()));
            
        case VertUnFunc::UnFunc::cos:
            return new VertUnFunc(VertUnFunc::UnFunc::minus,
                                  new VertUnFunc(VertUnFunc::UnFunc::sin,
                                                 Vertex::copy(t1->get_child())
                                                 )
                                  );
            
        case VertUnFunc::UnFunc::tg:
        {
            Vertex* left = new VertConst(1);
            Vertex* right = new VertUnFunc(VertUnFunc::UnFunc::cos, Vertex::copy(t1->get_child()));
            return new VertBinFunc(VertBinFunc::BinFunc::division,
                                   left, new VertBinFunc(VertBinFunc::BinFunc::involution,
                                        right, new VertConst(2))
                                   );
        }
            
        case VertUnFunc::UnFunc::ctg:
        {
            Vertex* left = new VertUnFunc(VertUnFunc::UnFunc::minus, new VertConst(1));
            Vertex* right = new VertUnFunc(VertUnFunc::UnFunc::sin, Vertex::copy(t1->get_child()));
            return new VertBinFunc(VertBinFunc::BinFunc::division,
                                   left, new VertBinFunc(VertBinFunc::BinFunc::involution,
                                                         right, new VertConst(2))
                                   );
        }
        default:
            throw std::runtime_error("Impossible error");
    }
#undef CAST
}

Vertex* deriv_bin_func(Vertex* t, char c)
{
#define CAST(a, b) b* t1 = static_cast<b*>(a)
    CAST(t, VertBinFunc);
    if (!is_such_el(t, c))
        return new VertConst(0);
        
    switch (t1->get_func()) {
        case VertBinFunc::BinFunc::division:
        {
            Vertex* min = new VertBinFunc(VertBinFunc::BinFunc::multiplication, deriv(t1->get_left(), c), Vertex::copy(t1->get_right()));
            Vertex* sub = new VertBinFunc(VertBinFunc::BinFunc::multiplication, Vertex::copy(t1->get_left()), deriv(t1->get_right(), c));
            Vertex *numer = new VertBinFunc(VertBinFunc::BinFunc::substraction, min, sub);
            Vertex *denom = new VertBinFunc(VertBinFunc::BinFunc::involution, Vertex::copy(t1->get_right()), new VertConst(2));
            return new VertBinFunc(VertBinFunc::BinFunc::division, numer, denom);
        }
        case VertBinFunc::BinFunc::multiplication:
        {
            Vertex* fir = new VertBinFunc(VertBinFunc::BinFunc::multiplication, deriv(t1->get_left(), c), Vertex::copy(t1->get_right()));
            Vertex* sec = new VertBinFunc(VertBinFunc::BinFunc::multiplication,Vertex::copy(t1->get_left()) ,deriv(t1->get_right(), c));
            return new VertBinFunc(VertBinFunc::BinFunc::addition, fir, sec);
        }
        case VertBinFunc::BinFunc::addition:
        {
            Vertex* fir = deriv(t1->get_left(), c);
            Vertex* sec = deriv(t1->get_right(), c);
            return new VertBinFunc(VertBinFunc::BinFunc::addition, fir, sec);
        }
        case VertBinFunc::BinFunc::substraction:
        {
            Vertex* fir = deriv(t1->get_left(), c);
            Vertex* sec = deriv(t1->get_right(), c);
            return new VertBinFunc(VertBinFunc::BinFunc::substraction, fir, sec);
        }
        case VertBinFunc::BinFunc::log:
        {
            if (is_such_el(t1->get_left(), 'e'))
                return new VertBinFunc(VertBinFunc::BinFunc::multiplication,
                            new VertBinFunc(VertBinFunc::BinFunc::division,
                                new VertConst(1), Vertex::copy(t1->get_right())),
                            deriv(t1->get_right (), c)) ;
            
            Vertex* num = new VertBinFunc(VertBinFunc::BinFunc::log, new VertVar('e'),Vertex::copy(t1->get_right()));
            Vertex* denom = new VertBinFunc(VertBinFunc::BinFunc::log, new VertVar('e'), Vertex::copy(t1->get_left()));
            
            return deriv(new VertBinFunc(VertBinFunc::BinFunc::division, num,denom), c);
        }
      /*  case VertBinFunc::BinFunc::log:
        {
            if (is_such_el(t1->get_right(), 'e'))
                return new VertBinFunc(VertBinFunc::BinFunc::multiplication,
                                       new VertBinFunc(VertBinFunc::BinFunc::division,
                                                       new VertConst(1), Vertex::copy(t1->get_left())),
                                       deriv(t1->get_left(), c)) ;
            (1/b*1*log(a,e)-log(b,e)*0)/log(a,e)^2
            Vertex* denom = new VertBinFunc(VertBinFunc::BinFunc::log, Vertex::copy(t1->get_right()), new VertVar('e'));
            Vertex* num = new VertBinFunc(VertBinFunc::BinFunc::log, Vertex::copy(t1->get_left()), new VertVar('e'));
            return deriv(new VertBinFunc(VertBinFunc::BinFunc::division, num,denom), c);
        }*/
        case VertBinFunc::BinFunc::involution:
            if (is_such_el(t1->get_right(), c))
            {
                Vertex* temp = new VertBinFunc(VertBinFunc::BinFunc::multiplication,
                                    new VertBinFunc(VertBinFunc::BinFunc::log, Vertex::copy(t1->get_left()),
                                            new VertVar('e')), Vertex::copy(t1->get_right()));
                Vertex* temp_d = deriv(temp, c);
                Vertex* help_t = new VertBinFunc(VertBinFunc::BinFunc::involution, new VertVar ('e'), temp );
                return new VertBinFunc(VertBinFunc::BinFunc::multiplication, help_t, temp_d);
            }
            else
            {
                Vertex* help_t_low = new VertBinFunc(VertBinFunc::BinFunc::substraction, Vertex::copy(t1->get_right()), new VertConst(1));
                Vertex* help_t_up = new VertBinFunc(VertBinFunc::BinFunc::involution, Vertex::copy(t1->get_left()), help_t_low);
                Vertex* help = new VertBinFunc(VertBinFunc::BinFunc::multiplication, Vertex::copy(t1->get_right()), help_t_up);
                return new VertBinFunc(VertBinFunc::BinFunc::multiplication, help, deriv(t1->get_left(), c));
            }
        default:
            throw std::runtime_error("Impossible error");
    }
#undef CAST
}

Vertex* deriv_var (Vertex* t, char c)
{
#define CAST(a, b) b* t1 = static_cast<b*>(a)
    CAST(t, VertVar);
    if (t1->get_var() == c)
        return new VertConst(1);
    return new VertConst(0);
#undef CAST
}

Vertex* deriv_dif_func(Vertex*t , char c)
{
#define CAST(a, b) b* t1 = static_cast<b*>(a)
    CAST(t, VertUnFunc);
    return new VertBinFunc(VertBinFunc::BinFunc::multiplication, deriv_un_func(t1, c), deriv(t1->get_child(), c) );
#undef CAST
}

Vertex* deriv (Vertex* t, char c)
{
#define CAST(a, b) b* t1 = static_cast<b*>(a)
    switch (t->get_v_type()) {
        case Vertex::binary_function:
            return deriv_bin_func(t, c);
        case Vertex::unary_function:
        {
            CAST(t, VertUnFunc);
           if (is_such_el(t1->get_child(), c))
           {
               if (t1->get_func()==VertUnFunc::UnFunc::minus)
                   return deriv_un_func(t, c);
               return deriv_dif_func(t, c);
           }
            return deriv_un_func(t, c);
        }
        case Vertex::variable:
            return deriv_var(t, c);
        case Vertex::constant:
            return new VertConst(0);
            
        default:
            throw std::runtime_error("Impossible error");
            break;
    }
    
#undef CAST

}
