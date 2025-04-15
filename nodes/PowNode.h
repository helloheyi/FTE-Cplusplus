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
 PowNode represents an power operation in the computational graph.
 
 Computes the PowNode of an input node and propagates gradients.
*/
class PowNode: public Node {
public:
    NodePtr base;
    double exponent;
    
    /*
     Constructs an PowNode with one input node and a constant exponent.

     Parameters:
     - B: Shared Smart pointer to to base node.
     - exp: The constant exponent
    */
    PowNode(NodePtr b, double e);

    /*
    Computes B^(exp) in the forward pass.

    Throws:
    - std::runtime_error If the result overflows to infinity.
    */
    void forward() override;
    
    /*
     Performs the backward pass for X^(exp).

     Gradients:
     d(B^(exp))/dB = exp * B^(exp - 1)
     
     Throws:
     - std::runtime_error If the result overflows to infinity.
    */
    void backward(double topGrad) override;
};
#endif /* PowNode_h */
