//
//  PowNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef PowNode_h
#define PowNode_h
#include "Node.h"
#include <stdio.h>
#include <memory>
/*
    power of a node.
    param B Pointer to base node
    param exp The constant exponent
    forward(): calcuate X^N, with running time error  checks.
    backward(): backpropagate gradients, with running time error  checks.
 
 */
class PowNode: public Node {
public:
    Node* base;
    double exponent;
    /*
    constructor to initialize a base node and an exponent.
    param B Pointer to base node
    param exp The constant exponent
    */
    PowNode(Node* B, double exp);
    /*
    Forward pass: X^N
    throws std::runtime_error If the result overflows to infinity.
    */
    void forward() override;
    /*
    Backward pass:
    ∂(x^n)/∂x = n * x^(n-1)
    throws std::runtime_error If the result overflows to infinity.
    */
    void backward() override;
};
#endif /* PowNode_h */
