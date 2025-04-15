//
//  AddNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#include "AddNode.h"
/*
 Constructor for AddNode to initialize the left and right input nodes.
 
 Parameters:
 - L: Shared Smart pointer to the left input node.
 - R: Shared Smart pointer to the right input node.
*/
AddNode::AddNode(NodePtr l, NodePtr r) : left(l), right(r) {}

/*
 Computes the sum of the input node values using the formula:
 value = left->value + right->value;
 
 No return value.
*/
void AddNode::forward() {
    left->forward();
    right->forward();
    value = left->value + right->value;
}

/*
 Propagates gradients from the output node to both input nodes:

 Gradients:
 d(x + y)/dx = 1
 d(x + y)/dy = 1

 No return value.
*/
void AddNode::backward(double topGrad) {
    left->backward(topGrad);
    right->backward(topGrad);
}
