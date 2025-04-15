//
//  AddNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef AddNode_h
#define AddNode_h
#include "Node.h"
#include <memory>

/*
 AddNode represents an addition operation in the computational graph.
 
 Computes the sum of two input nodes and propagates gradients.
*/

class AddNode:public Node{
public:

    NodePtr left, right;
    /*
     Constructs an AddNode with two input nodes.

     Parameters:
     - L: Shared Smart pointer to the left input node.
     - R: Shared Smart pointer to the right input node.
    */
    AddNode(NodePtr l, NodePtr r);

    /*
     Computes x + y in the forward pass.
    */
    void forward() override;
    
    /*
     Performs the backward pass for x + y.

     Gradients:
     d(x + y)/dx = 1
     d(x + y)/dy = 1
    */
    void backward(double topGrad) override;
};

#endif /* AddNode_h */
