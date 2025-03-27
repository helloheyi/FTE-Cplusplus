//
//  VariableNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#include "VariableNode.h"
/*
Constructor
param val initial value of the variable.
*/
VariableNode::VariableNode(double val) {
    value = val;
}
/*
 forward(): no operation
*/
void VariableNode::forward() {}
/*
 backward(): no operation
*/
void VariableNode::backward() {}

