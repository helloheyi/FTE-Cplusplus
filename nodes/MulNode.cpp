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
MulNode::MulNode(NodePtr l, NodePtr r) : left(l), right(r) {}

/*
 Computes the multiplication of the input node values using the formula:
 value = left->value * right->value;
 
 No return value.
*/
void MulNode::forward() {
    left->forward();
    right->forward();
    value = left->value * right->value;
}
/*
 Propagates gradients from the output node to both input nodes:

 Gradients:
 d(x * y)/dx = y
 d(x * y)/dy = x

 No return value.
*/
void MulNode::backward(double topGrad) {
    left->backward(topGrad * right->value);
    right->backward(topGrad * left->value);
}
