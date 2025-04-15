//
//  VariableNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef VariableNode_h
#define VariableNode_h
#include "Node.h"
#include <stdio.h>

/*
 VariableNode represents an variable in the computational graph.
 
 VariableNode stores a value that remains change during the forward and backward passes.
 */

class VariableNode : public Node {
public:
    /*
    Constructs a VariableNode with a specified value.

    Parameters:
    - val: The constant value to be stored in the node.
    */
    explicit VariableNode(double val);

    /*
     The forward pass just sets 'value' to the variable's current value.
    */
    void forward() override;
    
    /*
     The backward pass just sets 'value' to the variable's current value.
    */
    void backward(double topGrad) override;  
};

#endif /* VariableNode_h */
