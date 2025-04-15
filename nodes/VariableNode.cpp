//
//  VariableNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#include "VariableNode.h"

/*
 Constructor for ConstantNode to initialize a constant value.
 
 Parameters:
 - val: The constant value to be stored.
*/
VariableNode::VariableNode(double val) {
    value = val;
}

/*
 Performs the forward pass a VariableNode.
 
 No operation is required. The stored value remains as is.
*/
void VariableNode::forward() {}

/*
 Performs the backward pass a VariableNode.
 */
void VariableNode::backward(double topGrad) { grad += topGrad; }

