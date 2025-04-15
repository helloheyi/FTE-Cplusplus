//
//  DivNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "DivNode.h"


/*
 Constructor for DivNode to initialize the numerator and denominator input nodes.

 Parameters:
 - L: Shared Smart pointer to the numerator node.
 - R: Shared Smart pointer to the denominator node.
*/
DivNode::DivNode(NodePtr l, NodePtr r) : left(l), right(r) {}

/*
 Computes the divide operation of two input nodes using the formula:
 value = left->getValue() / right->getValue()

 Throws:
 - std::runtime_error If division by zero is detected.
 
 No return value.
*/
void DivNode::forward() {
    
    left->forward();
    right->forward();
    
    if (right->value == 0.0)
    {throw std::runtime_error("Division by zero in DivNode::forward()");}
    
    value = left->value / right->value;
};

/*
 Propagates gradients from the output node to both input nodes:

 Gradients:
   d(x / y)/dx = 1 / y
   d(x / y)/dy = -x / (y^2)
 We apply these, multiplied by grad.
 
 Throws:
 - std::runtime_error If division by zero is detected.
 
 No return value.
*/
void DivNode::backward(double topGrad) {
    
    
    if (right->value == 0.0) {throw std::runtime_error("Division by zero in DivNode::backward().");}
    double denom = right->value * right->value;
    left->backward(topGrad / right->value);
    right->backward(-topGrad * left->value / denom);
}
