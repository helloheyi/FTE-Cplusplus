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
 MulNode represents a multiplication operation in the computational graph.
 
 Computes the multiplication of two input nodes and propagates gradients.
*/

class MulNode:public Node{
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    /*
     Constructs a MulNode with two input nodes.

     Parameters:
     - L: Shared pointer to the left input node.
     - R: Shared pointer to the right input node.
    */
    MulNode(std::shared_ptr<Node> L, std::shared_ptr<Node> R);
    
    /*
     Computes x * y in the forward pass.
   */
    void forward() override;
    
    /*
     Performs the backward pass for x * y.

     Gradients:
     d(x * y)/dx = y
     d(x * y)/dy = x
    */
    void backward() override;
};

#endif /* MulNode_h */
