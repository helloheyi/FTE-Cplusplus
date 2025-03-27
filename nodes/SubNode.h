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
    param l Shared Smart Pointer to left node
    param r Shared Smart Pointer to right node
    forward(): calcuate x - y
    backward(): backpropagate gradients

 */
class SubNode:public Node{
    public:
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
       
    SubNode(std::shared_ptr<Node> L, std::shared_ptr<Node> R);
    void forward() override;
    void backward() override;
};

#endif /* SubNode_h */
