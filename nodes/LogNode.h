//
//  LogNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef LogNode_h
#define LogNode_h
#include "Node.h"
#include <stdio.h>
#include <memory>

/*
 LogNode represents IN in the computational graph.
 
 Computes the In of input node and propagates gradients.
*/
class LogNode: public Node {
    
public:
    
    NodePtr input;
    /*
     Constructs a LogNode with a input node.

     Parameters:
     - I: Shared Smart to the node used as the input to ln(x).
    */
    LogNode(NodePtr in);

    /*
     Performs the forward pass by computing ln(x).
     
     Throws:
     - std::runtime_error if x <= 0.
    */
    void forward() override;
    
    /*
     Performs the backward pass for In(x)

     Gradients:
     d(In(x))/dx = 1/x

     Throws:
     - std::runtime_error if x == 0.
    */
    void backward(double topGrad) override;

};

#endif /* LogNode_h */

