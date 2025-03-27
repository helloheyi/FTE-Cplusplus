//
//  MulNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "MulNode.h"
/*
     constructor to initialize left and right input nodes.
     param l Pointer to left node
     param r Pointer to right node
*/

MulNode:: MulNode(Node* L, Node* R) : left(L), right(R) {};
/*
     Forward pass: x * y
*/
void MulNode::forward() {
    value = left->getValue() * right->getValue();
}
/*
     Backward pass: x+y
     ∂(x * y)/∂x = y; ∂(x * y)/∂y = x, both receive full gradient
*/
void MulNode::backward() {
    left->grad += grad * right->getValue();
    right->grad += grad * left->getValue();
}
