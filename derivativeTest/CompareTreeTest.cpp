//
//  CompareTreeTest.cpp
//  test
//
//  Created by Barbara Grape on 10.12.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"
#include "tree.h"



TEST(CompareTreeTest, compare_num)
{
    
    Vertex* t = new VertConst(5);
    Vertex* s = new VertConst(1);
    Vertex* z = new VertConst(5);
    Vertex* q = new VertVar('s');
    
    EXPECT_TRUE(Vertex::compare (t, t));
    EXPECT_FALSE(Vertex::compare (t,s));
    EXPECT_FALSE(Vertex::compare(s, t));
    EXPECT_FALSE(Vertex::compare(t, q));
    EXPECT_FALSE(Vertex::compare(q, t));
    EXPECT_TRUE(Vertex::compare(z, t));
    EXPECT_TRUE(Vertex::compare(t, z));
}
TEST(CompareTreeTest, compare_var)
{
    Vertex* t = new VertVar('t');
    Vertex* s = new VertVar('s');
    Vertex* z = new VertVar('t');
    Vertex* q = new VertConst(5);
    
    EXPECT_TRUE(Vertex::compare (t, t));
    EXPECT_FALSE(Vertex::compare (t,s));
    EXPECT_FALSE(Vertex::compare(s, t));
    EXPECT_FALSE(Vertex::compare(t, q));
    EXPECT_FALSE(Vertex::compare(q, t));
    EXPECT_TRUE(Vertex::compare(z, t));
    EXPECT_TRUE(Vertex::compare(t, z));
}
TEST(CompareTreeTest, compare_un_func)
{
    Vertex* t = new VertUnFunc(VertUnFunc::UnFunc::cos, new VertVar('t'));
    Vertex* s = new VertUnFunc(VertUnFunc::UnFunc::sin, new VertVar('t'));
    Vertex* z = new VertUnFunc(VertUnFunc::UnFunc::cos, new VertVar('t'));
    Vertex* q = new VertUnFunc(VertUnFunc::UnFunc::cos, new VertVar('q'));
    Vertex* a = new VertConst(5);
    
    EXPECT_TRUE(Vertex::compare(t,t));
    EXPECT_TRUE(Vertex::compare(t,z));
    EXPECT_TRUE(Vertex::compare(z,t));
    EXPECT_FALSE(Vertex::compare(t,s));
    EXPECT_FALSE(Vertex::compare(s,t));
    EXPECT_FALSE(Vertex::compare(t,q));
    EXPECT_FALSE(Vertex::compare(q,t));
    EXPECT_FALSE(Vertex::compare(t,a));
    EXPECT_FALSE(Vertex::compare(a,t));
}
TEST(CompareTreeTest, compare_bin_func)
{
    Vertex* t = new VertBinFunc(VertBinFunc::BinFunc::multiplication, new VertVar('t'), new VertConst(5));
    Vertex* s = new VertBinFunc(VertBinFunc::BinFunc::division, new VertVar('t'), new VertConst(5));//разные функции, одинаковые дети
    Vertex* z = new VertBinFunc(VertBinFunc::BinFunc::multiplication, new VertVar('t'), new VertConst(5));// разные имена, все остальное одинаковое
    Vertex* q = new VertBinFunc(VertBinFunc::BinFunc::multiplication, new VertVar('q'), new VertConst(5));// разные левые дети
    Vertex* w = new VertBinFunc(VertBinFunc::BinFunc::multiplication, new VertVar('t'), new VertConst(2));// разные правые дети
    Vertex* a = new VertConst(5);
    
    EXPECT_TRUE(Vertex::compare(t,t));
    EXPECT_TRUE(Vertex::compare(t,z));
    EXPECT_TRUE(Vertex::compare(z,t));
    EXPECT_FALSE(Vertex::compare(t,s));
    EXPECT_FALSE(Vertex::compare(s,t));
    EXPECT_FALSE(Vertex::compare(t,q));
    EXPECT_FALSE(Vertex::compare(q,t));
    EXPECT_FALSE(Vertex::compare(t,w));
    EXPECT_FALSE(Vertex::compare(w,t));
    EXPECT_FALSE(Vertex::compare(t,a));
    EXPECT_FALSE(Vertex::compare(a,t));
}