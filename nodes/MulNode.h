//
//  MulNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef MulNode_h
#define MulNode_h
#include "Node.h"
#include <stdio.h>
#include <memory>

/*
    multiply of two nodes.
    param l Pointer to left node
    param r Pointer to right node
    forward(): calcuate x + y
    backward(): backpropagate gradients
 
 */
class MulNode:public Node{
public:
    Node* left;
    Node* right;
    /*
     constructor to initialize left and right input nodes.
     param l Pointer to left node
     param r Pointer to right node
    */
    MulNode(Node* L, Node* R);
    /*
     Forward pass: x * y
     */
    void forward() override;
    /*
     Backward pass: x+y
     ∂(x * y)/∂x = y; ∂(x * y)/∂y = x, both receive full gradient
     */
    void backward() override;
};

#endif /* MulNode_h */
