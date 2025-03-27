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
    Log of a node.
    param I Pointer to the input node
    forward(): calcuate In(x), with running time error  checks.
    backward(): backpropagate gradients, with running time error  checks.
 */
class LogNode: public Node {
public:
    Node* input;
    /*
    Constructor to initialize LogNode with an input node.
    param I Pointer to the input node.
    */
    LogNode(Node* I);
    /*
    Forward pass: ln(x)
    */
    void forward() override;
    /*
    Backward pass:
     ∂(ln(x))/∂x = 1 / x
    */
    void backward() override;
};

#endif /* LogNode_h */
