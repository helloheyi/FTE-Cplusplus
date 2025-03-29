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
DivNode:: DivNode(std::shared_ptr<Node> L,std::shared_ptr<Node> R) : left(L), right(R) {};

/*
 Computes the divide operation of two input nodes using the formula:
 value = left->getValue() / right->getValue()

 Throws:
 - std::runtime_error If division by zero is detected.
 
 No return value.
*/
void DivNode::forward() {
    
    double rv = right->getValue();
    
    if (rv == 0.0)
    {throw std::runtime_error("Division by zero in DivNode::forward()");}
    
    value = left->getValue() / rv;
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
void DivNode::backward() {
    
    double lv = left->getValue(), rv = right->getValue();
    
    if (right->getValue() == 0.0) {throw std::runtime_error("Division by zero in DivNode::backward().");}
    
    left->grad += grad / rv;
    right->grad -= grad * lv / (rv * rv);
}
