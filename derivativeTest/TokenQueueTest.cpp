//
//  TokenQueueTest.cpp
//  test
//
//  Created by Barbara Grape on 10.12.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <sstream>
#include "gtest/gtest.h"
#include "token.h"
#include "token_queue.h"

TEST(TokenQueueTest, long_token_queue)
{
    std::istringstream input("2+v/x*(a)-pow(a)+sin(a)");
    TokenQueue q(input);
    Token* curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::number);
    EXPECT_EQ(static_cast<TokenNum*>(curT)->get_double(), 2);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::addition);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::variable);
    EXPECT_EQ(static_cast<TokenVar*>(curT)->get_var(), 'v');
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::division);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::variable);
    EXPECT_EQ(static_cast<TokenVar*>(curT)->get_var(), 'x');
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::multiplication);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::open_bracket);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::variable);
    EXPECT_EQ(static_cast<TokenVar*>(curT)->get_var(), 'a');
    
    q.pop();
    curT = q.front();

    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::close_bracket);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::substraction);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::function);
    EXPECT_EQ(static_cast<TokenFunc*>(curT)->get_func(), TokenFunc::involution);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::variable);
    EXPECT_EQ(static_cast<TokenVar*>(curT)->get_var(), 'a');
    
    q.pop();
    curT = q.front();
    
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::close_bracket);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::addition);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::function);
    EXPECT_EQ(static_cast<TokenFunc*>(curT)->get_func(), TokenFunc::sin);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::variable);
    EXPECT_EQ(static_cast<TokenVar*>(curT)->get_var(), 'a');
    
    q.pop();
    curT = q.front();
    
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::close_bracket);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::end);

    
}
TEST(TokenQueueTest, short_token_queue)
{
    std::istringstream input("2+v\n");
    TokenQueue q(input);
    Token* curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::number);
    EXPECT_EQ(static_cast<TokenNum*>(curT)->get_double(), 2);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::operation);
    EXPECT_EQ(static_cast<TokenOper*>(curT)->get_op(), TokenOper::addition);
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::variable);
    EXPECT_EQ(static_cast<TokenVar*>(curT)->get_var(), 'v');
    
    q.pop();
    curT = q.front();
    
    ASSERT_EQ(curT->get_type(), Token::end);
}
TEST(TokenQueueTest, token_error)
{
    std::istringstream tan("tan");
    EXPECT_ANY_THROW(TokenQueue tq1(tan));
    
    std::istringstream qwe("qwe");
    EXPECT_ANY_THROW(TokenQueue tq2(qwe));
    
    std::istringstream cos("COs");
    EXPECT_ANY_THROW(TokenQueue tq3(cos));
    
    std::istringstream pow("pow");
    EXPECT_ANY_THROW(TokenQueue tq4(pow));
    
    std::istringstream none(" ");
    EXPECT_ANY_THROW(TokenQueue tq5(none));
    
    
}

