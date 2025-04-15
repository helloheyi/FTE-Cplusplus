//
//  DivNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef DivNode_h
#define DivNode_h
#include "Node.h"
#include <stdio.h>
#include <memory>

/*
 DivNode represents a division operation in the computational graph.

 It computes numerator / denominator in the forward pass and propagates gradients by the chain rule.
 */
class DivNode: public Node{
public:
    NodePtr left, right;
    /*
     Constructs a DivNode that divides 'L' by 'R'.

     Parameters:
     - L: Shared Smart pointer to the numerator node
     - R: Shared Smart pointer to the denominator node
    */
    DivNode(NodePtr l, NodePtr r);

    /*
     Computes x / y in the forward pass.

     Throws:
     - std::runtime_error if 'y' is zero.
    */
    void forward() override;
    
    /*
     Performs the backward pass for x / y.

     Gradients:
     d(x / y)/dx = 1 / y
     d(x / y)/dy = -x / (y^2)

     Throws:
     - std::runtime_error if 'y' is zero.
    */
    void backward(double topGrad) override;

};

#endif /* DivNode_h */
