//
//  DerivTest.cpp
//  test
//
//  Created by Barbara Grape on 11.12.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "tree.h"
#include "derivative.h"
#include "token_queue.h"
#include "parser.h"

TEST(DerivTest, deriv_var)
{
    Vertex* a = new VertVar('a');
    Vertex* c = new VertConst(1);
    Vertex* d = new VertConst(0);
    
    EXPECT_TRUE(Vertex::compare(deriv(a,'a'), c));
    EXPECT_FALSE(Vertex::compare(deriv(a,'b'), c));
    EXPECT_TRUE(Vertex::compare(deriv(a,'b'), d));
    
}
TEST (DerivTest, deriv_const)
{
    Vertex* a = new VertConst(23);
    Vertex* c = new VertConst(1);
    Vertex* d = new VertConst(0);
    
    EXPECT_TRUE(Vertex::compare(deriv(a, 'z'), d));
    EXPECT_FALSE(Vertex::compare(deriv(a, 'z'), c));
}
TEST (DerivTest, deriv_un_func)
{
    
    Vertex* x = new VertUnFunc(VertUnFunc::UnFunc::cos,new VertVar('x'));
    std::istringstream input1("(-sin(x))*1");
    TokenQueue tq1(input1);
    EXPECT_TRUE(Vertex::compare(deriv(x,'x'),parse(tq1)));
    
    Vertex* y = new VertUnFunc(VertUnFunc::UnFunc::sin,new VertVar('y'));
    std::istringstream input2("cos(y)*1");
    TokenQueue tq2(input2);
    EXPECT_TRUE(Vertex::compare(deriv(y,'y'),parse(tq2)));
    
    Vertex* c = new VertUnFunc(VertUnFunc::UnFunc::ctg ,new VertVar('c'));
    std::istringstream input3("((-1)/pow(sin(c),2))*1");
    TokenQueue tq3(input3);
    EXPECT_TRUE(Vertex::compare(deriv(c,'c'),parse(tq3)));
    
    Vertex* t = new VertUnFunc(VertUnFunc::UnFunc::tg,new VertVar('t'));
    std::istringstream input4("(1/pow(cos(t),2))*1");
    TokenQueue tq4(input4);
    EXPECT_TRUE(Vertex::compare(deriv(t,'t'),parse(tq4)));
    
    Vertex* m = new VertUnFunc(VertUnFunc::UnFunc::minus,new VertVar('m'));
    std::istringstream input5("-1");
    TokenQueue tq5(input5);
    EXPECT_TRUE(Vertex::compare(deriv(m,'m'),parse(tq5)));
    
}
TEST (DerivTest, deriv_bin_func)
{
    Vertex* div = new VertBinFunc(VertBinFunc::BinFunc::division,new VertVar('d'),new VertVar('i') );
    std::istringstream input11("(1*i-d*0)/pow(i,2)");
    TokenQueue tq11(input11);
    EXPECT_TRUE(Vertex::compare(deriv(div,'d'),parse(tq11)));
    
    std::istringstream input12("(0*i-d*1)/pow(i,2)");
    TokenQueue tq12(input12);
    EXPECT_TRUE(Vertex::compare(deriv(div,'i'),parse(tq12)));
    
    
    Vertex* mul = new VertBinFunc(VertBinFunc::BinFunc::multiplication,new VertVar('m'),new VertVar('u') );
    std::istringstream input21("1*u+m*0");
    TokenQueue tq21(input21);
    EXPECT_TRUE(Vertex::compare(deriv(mul,'m'),parse(tq21)));
    
    std::istringstream input22("0*u+m*1");
    TokenQueue tq22(input22);
    EXPECT_TRUE(Vertex::compare(deriv(mul,'u'),parse(tq22)));
    
    
    Vertex* sub = new VertBinFunc(VertBinFunc::BinFunc::substraction,new VertVar('s'),new VertVar('u') );
    std::istringstream input31("1-0");
    TokenQueue tq31(input31);
    EXPECT_TRUE(Vertex::compare(deriv(sub,'s'),parse(tq31)));
    
    std::istringstream input32("0-1");
    TokenQueue tq32(input32);
    EXPECT_TRUE(Vertex::compare(deriv(sub,'u'),parse(tq32)));
    
    
    Vertex* add = new VertBinFunc(VertBinFunc::BinFunc::addition,new VertVar('a'),new VertVar('d') );
    std::istringstream input41("1+0");
    TokenQueue tq41(input41);
    EXPECT_TRUE(Vertex::compare(deriv(add,'a'),parse(tq41)));
    
    std::istringstream input42("0+1");
    TokenQueue tq42(input42);
    EXPECT_TRUE(Vertex::compare(deriv(add,'d'),parse(tq42)));
    
    Vertex* log = new VertBinFunc(VertBinFunc::BinFunc::log,new VertVar('l'),new VertVar('o') );
    std::istringstream input51("((0*log(e,l))-(log(e,o)*((1/l)*1)))/pow(log(e,l),2)");
    TokenQueue tq51(input51);
    EXPECT_TRUE(Vertex::compare(deriv(log,'l'),parse(tq51)));
    
    std::istringstream input52("(1/o*1*log(e,l)-log(e,o)*0)/pow(log(e,l),2)");
    TokenQueue tq52(input52);
    EXPECT_TRUE(Vertex::compare(deriv(log,'o'),parse(tq52)));
    
    
    Vertex* inv = new VertBinFunc(VertBinFunc::BinFunc::involution,new VertVar('i'),new VertVar('n') );
    std::istringstream input61("n*pow(i,(n-1))*1");
    TokenQueue tq61(input61);
    EXPECT_TRUE(Vertex::compare(deriv(inv,'i'),parse(tq61)));
    
    std::istringstream input62("pow(e,(log(i,e)*n))*(0*n+log(i,e)*1)");
    TokenQueue tq62(input62);
    EXPECT_TRUE(Vertex::compare(deriv(inv,'n'),parse(tq62)));
    

}