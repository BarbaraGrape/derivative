//
//  ParserTest.cpp
//  test
//
//  Created by Barbara Grape on 10.12.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"
#include "tree.h"
#include "parser.h"
#include <sstream>

TEST(ParserTest, parse_bin_func)
{
    Vertex* a = new VertBinFunc(VertBinFunc::BinFunc::addition, new VertConst(5), new VertVar('x'));
    std::istringstream input1("5+x");
    TokenQueue tq1(input1);
    EXPECT_TRUE(Vertex::compare(a,parse(tq1)));
    
    Vertex* b = new VertBinFunc(VertBinFunc::BinFunc::involution, new VertVar('x'), new VertConst(2));
    std::istringstream input2("pow(x,2)");
    TokenQueue tq2(input2);
    EXPECT_TRUE(Vertex::compare(b,parse(tq2)));
    
    std::istringstream input3("pow(2,x)");
    TokenQueue tq3(input3);
    EXPECT_FALSE(Vertex::compare(b,parse(tq3)));
}
TEST(ParserTest, parse_un_func)
{
    Vertex* c = new VertUnFunc(VertUnFunc::UnFunc::cos, new VertVar('x'));
    std::istringstream input1("cos(x)");
    TokenQueue tq1(input1);
    EXPECT_TRUE(Vertex::compare(c,parse(tq1)));
    
    Vertex* d = new VertUnFunc(VertUnFunc::UnFunc::minus, new VertConst(2));
    std::istringstream input2("-2");
    TokenQueue tq2(input2);
    EXPECT_TRUE(Vertex::compare(d,parse(tq2)));
    
        std::istringstream input3("2");
    TokenQueue tq3(input3);
    EXPECT_FALSE(Vertex::compare(d,parse(tq3)));

}
TEST(ParserTest, parse_var)
{
    Vertex* e = new VertVar('x');
    std::istringstream input1("x");
    TokenQueue tq1(input1);
    EXPECT_TRUE(Vertex::compare(e,parse(tq1)));
    
    std::istringstream input2("y");
    TokenQueue tq2(input2);
    EXPECT_FALSE(Vertex::compare(e,parse(tq2)));
    
    
}
TEST(ParserTest, parse_const)
{
    Vertex* f = new VertConst(5);
    std::istringstream input1("5");
    TokenQueue tq1(input1);
    EXPECT_TRUE(Vertex::compare(f,parse(tq1)));
    
    std::istringstream input2("2");
    TokenQueue tq2(input2);
    EXPECT_FALSE(Vertex::compare(f,parse(tq2)));
}
TEST(ParserTest, parse_non)
{
    std::istringstream input1("\n");
    TokenQueue tq1(input1);
    EXPECT_ANY_THROW(parse(tq1));
    
    std::istringstream input2("");
    TokenQueue tq2(input2);
    EXPECT_ANY_THROW(parse(tq2));
}
TEST(ParserTest, parse_error)
{
    std::istringstream input1("2+");
    TokenQueue tq1(input1);
    EXPECT_ANY_THROW(parse(tq1));
    
    std::istringstream input2("pow(x, )");
    TokenQueue tq2(input2);
    EXPECT_ANY_THROW(parse(tq2));
    
    std::istringstream input3("cos(x(");
    TokenQueue tq3(input3);
    EXPECT_ANY_THROW(parse(tq3));
    
    std::istringstream input4("3/)");
    TokenQueue tq4(input4);
    EXPECT_ANY_THROW(parse(tq4));
    
    std::istringstream input5("+5");
    TokenQueue tq5(input5);
    EXPECT_ANY_THROW(parse(tq5));
    
    std::istringstream input6("2z");
    TokenQueue tq6(input6);
    EXPECT_ANY_THROW(parse(tq6));
    
}