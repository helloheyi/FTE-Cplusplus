//
//  SubNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef SubNode_h
#define SubNode_h
#include "Node.h"
#include <stdio.h>
#include <memory>


/*
    substract of two nodes.
    param l Pointer to left node
    param r Pointer to right node
    forward(): calcuate x - y
    backward(): backpropagate gradients

 */
class SubNode:public Node{
    public:
        Node* left;
        Node* right;
       
    SubNode(Node* L, Node* R);
    void forward() override;
    void backward() override;
};

#endif /* SubNode_h */
