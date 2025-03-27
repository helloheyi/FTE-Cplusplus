//
//  DivNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "DivNode.h"
/*
constructor to initialize numerator and denominator
param l Shared Smart Pointer to left node -- numerator
param r Shared Smart Pointer to right node -- denominator
*/
DivNode:: DivNode(std::shared_ptr<Node> L,std::shared_ptr<Node> R) : left(L), right(R) {};

/*
Forward pass: x / y
throws std::runtime_error If division by zero is detected.
*/
void DivNode::forward() {
    double rv = right->getValue();
    if (rv == 0.0)
    {throw std::runtime_error("Division by zero in DivNode::forward()");}
    value = left->getValue() / rv;
};

/*
Backward pass:
 numerator: ∂(x / y)/∂x = 1 / y
 denominator: ∂(x / y)/∂y = -x / (y^2)
throws std::runtime_error If division by zero is detected.
*/
void DivNode::backward() {
    double lv = left->getValue(), rv = right->getValue();
    if (right->getValue() == 0.0) {throw std::runtime_error("Division by zero in DivNode::backward().");}
    left->grad += grad / rv;
    right->grad -= grad * lv / (rv * rv);
}
