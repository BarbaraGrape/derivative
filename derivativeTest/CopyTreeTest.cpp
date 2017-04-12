//
//  CopyTreeTest.cpp
//  test
//
//  Created by Barbara Grape on 10.12.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"
#include "tree.h"

TEST(CopyTreeTest, copy_ver)
{
    
    Vertex* a = new VertConst(5);
    Vertex* b = new VertVar('b');
    VertUnFunc* c = new VertUnFunc(VertUnFunc::UnFunc::cos, new VertVar('c'));
    VertBinFunc* d = new VertBinFunc(VertBinFunc::BinFunc::multiplication, new VertVar('d'), new VertConst(5));
 
    Vertex* a1 = Vertex::copy(a);
    Vertex* b1 = Vertex::copy(b);
    Vertex* c1 = Vertex::copy(c);
    Vertex* d1 = Vertex::copy(d);
    
    EXPECT_NE(a, a1);// проверка на разные адреса
    EXPECT_NE(b, b1);
    EXPECT_NE(c, c1);
    EXPECT_NE(d, d1);
    
    EXPECT_NE(c->get_child(), static_cast<VertUnFunc*>(c1)->get_child());
    EXPECT_NE(d->get_left(), static_cast<VertBinFunc*>(d1)->get_left());
    EXPECT_NE(d->get_right(), static_cast<VertBinFunc*>(d1)->get_right());
    
    EXPECT_TRUE(Vertex::compare(a,a1));
    EXPECT_TRUE(Vertex::compare(b,b1));
    EXPECT_TRUE(Vertex::compare(c,c1));
    EXPECT_TRUE(Vertex::compare(d,d1));
    
    EXPECT_FALSE(Vertex::compare(a1, b1));
    EXPECT_FALSE(Vertex::compare(a1, b));
    
    
  
}




