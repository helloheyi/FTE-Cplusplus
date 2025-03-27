//
//  ConstantNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#include "ConstantNode.h"
/*
Constructor
param val initial value of the constant.
*/
ConstantNode::ConstantNode(double val) {
    value = val;
}
/*
 forward(): no operation
*/
void ConstantNode::forward() {}
/*
 backward(): no operation
*/
void ConstantNode::backward() {}

