//
//  main.cpp
//  derivative_dz
//
//  Created by Barbara Grape on 29.10.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#include <iostream>
#include "token_queue.h"
#include "token.h"
#include "tree.h"
#include "parser.h"
#include "derivative.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>



void _main(std::ifstream& in, std::ofstream& of, const std::string& c)
try
{
    while (!in.eof())
    {
        TokenQueue t (in);
        Vertex* root = parse(t);
        Vertex* result = deriv(root, c[0]);
        of << "Expression entered: ";
        root->print_tree(of);
        of << '\n' << "Derivative tree: ";
        result->print_tree(of);
        of << '\n' << "Derivative expression: ";
        print_expression(of, result);
        of << '\n' << '\n';
        delete root;
        delete result;
    }
        
}
catch (std::exception& t)
{
    of << t.what() << std::endl;
}
        
int main(int argc, char* argv[])
{
    if (argc != 4)
        return 0;
    std::ifstream in_file(argv[1]);
    std::ofstream out_file(argv[2]);
    const std::string& c(argv[3]);
    if (!in_file || !out_file || c.length() != 1)
    {
        std::cerr << "Problems with arguments!\n";
        return 0;
    }
    _main(in_file, out_file, c);
    return 0;
}
        

