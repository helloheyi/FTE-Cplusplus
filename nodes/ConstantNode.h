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
 constant value in the graph.
 param val initial value of the variable.
 forward(): no operation
 backward(): no operation

 */

class ConstantNode: public Node{
    public:
    /*
    Constructor
    param val initial value of the constant.
    */
    ConstantNode(double val);
    /*
     forward(): no operation
    */
    void forward() override;
    /*
     backward(): no operation
    */
    void backward() override;
};

#endif /* ConstantNode_h */
