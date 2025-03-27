//
//  DivNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef DivNode_h
#define DivNode_h
#include "Node.h"
#include <stdio.h>
#include <memory>

/*
    divide of two nodes.
    param l Pointer to numerator
    param r Pointer to denominator
    forward(): calcuate x / y, with running time error  checks.
    backward(): backpropagate gradients, with running time error  checks.
 
 */
class DivNode: public Node{
public:
    Node* left;
    Node* right;
    /*
    constructor to initialize numerator and denominator
    param l Pointer to left node -- numerator
    param r Pointer to right node -- denominator
    */
    DivNode(Node* L, Node* R);
    /*
    Forward pass
    */
    void forward() override;
    /*
    Backward pass
    */
    void backward() override;
    
};

#endif /* DivNode_h */
