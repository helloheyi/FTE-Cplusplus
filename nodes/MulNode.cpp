//
//  MulNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "MulNode.h"

/*
 Constructor for MulNode to initialize the left and right input nodes.
 
 Parameters:
 - L: Shared Smart pointer to the left input node.
 - R: Shared Smart pointer to the right input node.
*/
MulNode:: MulNode(std::shared_ptr<Node> L, std::shared_ptr<Node> R) : left(L), right(R) {};

/*
 Computes the multiplication of the input node values using the formula:
 value = left->getValue() * right->getValue();

 No return value.
*/
void MulNode::forward() {
    
    value = left->getValue() * right->getValue();
}

/*
 Propagates gradients from the output node to both input nodes:

 Gradients:
 d(x * y)/dx = y
 d(x * y)/dy = x

 No return value.
*/
void MulNode::backward() {
    
    left->grad += grad * right->getValue();
    right->grad += grad * left->getValue();
}
