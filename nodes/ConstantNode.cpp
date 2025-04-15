//
//  ConstantNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#include "ConstantNode.h"

/*
 Constructor for ConstantNode to initialize a constant value.
 The value is stored in the node and remains unchanged.

 Parameters:
 - val: The constant value to be stored.
*/
ConstantNode::ConstantNode(double val) {
    value = val;
}

/*
 Performs the forward pass a ConstantNode.
 
 As this node represents a constant, no computation is performed.
*/
void ConstantNode::forward() {}

/*
 Performs the backward pass for a ConstantNode.

 As constant values do not influence gradients, no operations are required.
*/
void ConstantNode::backward(double) {}

