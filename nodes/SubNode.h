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
 SubNode represents an subtract operation in the computational graph.
 
 Computes the subtract of two input nodes and propagates gradients.
*/


class SubNode:public Node{
    public:
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    /*
     Constructs an SubNode with two input nodes.

     Parameters:
     - L: Shared Smart pointer to the left input node.
     - R: Shared Smart pointer to the right input node.
    */
    SubNode(std::shared_ptr<Node> L, std::shared_ptr<Node> R);
    
    /*
     Computes x - y in the forward pass.
    */
    void forward() override;
    
    /*
     Performs the backward pass for x - y.

     Gradients:
     d(x - y)/dx = 1
     d(x - y)/dy = 1
    */
    void backward() override;
};

#endif /* SubNode_h */
