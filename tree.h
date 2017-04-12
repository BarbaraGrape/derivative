//
//  tree.h
//  derivative_dz
//
//  Created by Barbara Grape on 29.10.16.
//  Copyright (c) 2016 Varvara Vinogradova. All rights reserved.
//

#ifndef derivative_dz_tree_h
#define derivative_dz_tree_h
#include <iostream>




class Vertex {
public:
    enum Type {
        unary_function, binary_function, constant, variable
    };
    virtual ~Vertex() {}
    virtual void print_tree(std::ostream& s) const =0;
    
    Type get_v_type() const {return type;}
    static Vertex* copy(Vertex*);
    static bool compare(Vertex*, Vertex*);

    
private:
    Type type;
    
protected:
    Vertex(Type t) :type(t) {}
};


class VertBinFunc : public Vertex {
public:
    enum BinFunc {
        none = 0,log, involution, division = '/', multiplication ='*', addition = '+', substraction = '-'
    };
    VertBinFunc(BinFunc f) :Vertex(Vertex::binary_function), left(nullptr), right(nullptr), func(f) { }
    VertBinFunc(BinFunc f, Vertex *l, Vertex *r ) :Vertex(Vertex::binary_function), left(l), right(r), func(f) { }
    ~VertBinFunc() {delete left; delete right;}
    
    BinFunc get_func() const {return func;}
    Vertex* get_left() const {return left;}
    Vertex* get_right() const {return right;}
    void print_tree(std::ostream& s) const;
private:
    Vertex *left;
    Vertex *right;
    BinFunc func;
};

class VertUnFunc : public Vertex {
public:
    enum UnFunc {
        cos = 0, sin = 1, tg = 2, ctg = 3, minus, none
    };
    VertUnFunc(UnFunc f) :Vertex(Vertex::unary_function), child(nullptr), func(none) { }
    VertUnFunc(UnFunc f, Vertex* ch) :Vertex(Vertex::unary_function), child(ch), func(f) { }
    ~VertUnFunc() {delete child;}
    
    UnFunc get_func() const {return func;}
    Vertex* get_child() const {return child;}
    void print_tree(std::ostream& s) const;
private:
    Vertex *child;
    UnFunc func;
};

class VertConst : public Vertex {
public:
    VertConst() :Vertex(Vertex::constant), constant(0) { }
    VertConst(double c) :Vertex(Vertex::constant), constant(c) { }
    
    double get_const() const {return constant;}
    void print_tree(std::ostream& s) const;
private:
    double constant;
};

class VertVar : public Vertex {
public:
    VertVar() :Vertex(Vertex::variable), var(0) { }
    VertVar(char ch) :Vertex(Vertex::variable), var(ch) { }
    
    char get_var() const {return var;}
    void print_tree(std::ostream& s) const;
private:
    char var;
};
void print_expression(std::ostream& os, Vertex* n);

#endif
