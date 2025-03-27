//
//  AddNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#include "AddNode.h"
/*
constructor to initialize left and right input nodes.
param l Shared Smart Pointer to left node
param r Shared Smart Pointer to right node
*/
// Improve to smart pointer: std::shared_ptr
AddNode::AddNode(std::shared_ptr<Node> L,
                 std::shared_ptr<Node> R) : left(L), right(R) {}
/*
 Forward pass: x+y
 */

void AddNode::forward() {
    value = left->getValue() + right->getValue();
}
/*
 Backward pass: x+y
 ∂(x + y)/∂x = 1; ∂(x + y)/∂y = 1, both receive full gradient
 */

void AddNode::backward() {
    left->grad += grad;
    right->grad += grad;
}
