//
//  token_queue.h
//  derivative_dz
//
//  Created by Barbara Grape on 29.10.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#ifndef __derivative_dz__token_queue__
#define __derivative_dz__token_queue__

#include <stdio.h>
#include <queue>
#include <iostream>
#include "token.h"

class TokenQueue {
public:
    TokenQueue(std::istream &);
    
    void pop();
    void push(Token *t);
    Token* front() const;
    ~TokenQueue();
private:
    std::queue<Token*> tq;
    
    TokenQueue(const TokenQueue&);
    TokenQueue& operator=(const TokenQueue&);
};

#endif /* defined(__derivative_dz__token_queue__) */
