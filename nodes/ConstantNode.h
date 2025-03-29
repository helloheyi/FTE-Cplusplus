//
//  ConstantNode.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef ConstantNode_h
#define ConstantNode_h
#include "Node.h"

/*
 ConstantNode represents an Constant in the computational graph.
 
 ConstantNode stores a fixed value that remains unchanged during the forward and backward passes.
 */

class ConstantNode: public Node{
    public:
    /*
    Constructs a ConstantNode with a specified value.

    Parameters:
    - val: The constant value to be stored in the node.
    */
    ConstantNode(double val);
    
    //As this node represents a constant, no computation is performed.
    void forward() override;
   
    // Constants have no contribution to gradients, so no operation is performed.
    void backward() override;
};

#endif /* ConstantNode_h */
