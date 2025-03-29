//
//  PowNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "PowNode.h"

/*
 Constructor for PowNode to initialize the base node
 
 Parameters:
 - B: Shared Smart pointer to the base node
 - exp: A constant value
*/
PowNode::PowNode(std::shared_ptr<Node> B, double exp) : base(B), exponent(exp) {};

/*
 Computes the B^(exp) of the input node value using the formula:
 value = pow(base->getValue(), exponent)
 
 Throws:
 - std::runtime_error If the result overflows to infinity.
 
 No return value.
*/
void PowNode::forward() {
    value = std::pow(base->getValue(), exponent);
    
    if (std::isinf(value))
    {throw std::overflow_error("Overflow as isinf for large exponent in PowNode::forward.");}
};

/*
 Propagates gradients from the output node to input node:

 Gradients:
 d(B^(exp))/dB = exp * B^(exp - 1)
 
 Throws:
 - std::runtime_error If the result overflows to infinity.
 
 No return value.
*/
void PowNode:: backward() {
    base->grad += grad * exponent * std::pow(base->getValue(), exponent - 1);
    if (std::isinf(base->grad))
    {throw std::overflow_error("Overflow as isinf for large exponent in PowNode::forward.");}
}
