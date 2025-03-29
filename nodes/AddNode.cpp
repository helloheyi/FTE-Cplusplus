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
AddNode::AddNode(std::shared_ptr<Node> L,
                 std::shared_ptr<Node> R) : left(L), right(R) {}

/*
 Computes the sum of the input node values using the formula:
 value = left->getValue() + right->getValue();

 No return value.
*/
void AddNode::forward() {
    
    value = left->getValue() + right->getValue();
}

/*
 Propagates gradients from the output node to both input nodes:

 Gradients:
 d(x + y)/dx = 1
 d(x + y)/dy = 1

 No return value.
*/
void AddNode::backward() {
    left->grad += grad;
    right->grad += grad;
}
