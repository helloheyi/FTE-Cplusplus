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
     variable value in the graph.
     param val initial value of the variable.
     forward(): no operation
     backward(): no operation

 */
class VariableNode : public Node {
public:
    /*
    Constructor
    param val initial value of the variable.
    */
    VariableNode(double val);
    /*
     forward(): no operation 
    */
    void forward() override;
    /*
     backward(): no operation
    */
    void backward() override;
};

#endif /* VariableNode_h */
