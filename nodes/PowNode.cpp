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
PowNode::PowNode(NodePtr b, double e) : base(b), exponent(e) {}

/*
 Computes the B^(exp) of the input node value using the formula:
 value = pow(base->getValue(), exponent)
 
 Throws:
 - std::runtime_error If the result overflows to infinity.
 
 No return value.
*/
void PowNode::forward() {
    base->forward();
    value = std::pow(base->value, exponent);
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
void PowNode::backward(double topGrad) {
    double dfdx = exponent * std::pow(base->value, exponent - 1.0);
    base->backward(topGrad * dfdx);
    if (std::isinf(base->grad))
    {throw std::overflow_error("Overflow as isinf for large exponent in PowNode::forward.");}
}
