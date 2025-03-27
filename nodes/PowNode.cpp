//
//  PowNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "PowNode.h"
/*
    constructor to initialize a base node and an exponent.
    param B Pointer to base node
    param exp The constant exponent
*/
PowNode::PowNode(std::shared_ptr<Node> B, double exp) : base(B), exponent(exp) {};
/*
    Forward pass: X^N
    throws std::runtime_error If the result overflows to infinity.
*/
void PowNode::forward() {
    value = std::pow(base->getValue(), exponent);
    if (std::isinf(value))
    {throw std::overflow_error("Overflow as isinf for large exponent in PowNode::forward.");}
};
/*
    Backward pass:
    ∂(x^n)/∂x = n * x^(n-1)
    throws std::runtime_error If the result overflows to infinity.
*/
void PowNode:: backward() {
    base->grad += grad * exponent * std::pow(base->getValue(), exponent - 1);
    if (std::isinf(base->grad))
    {throw std::overflow_error("Overflow as isinf for large exponent in PowNode::forward.");}
}
