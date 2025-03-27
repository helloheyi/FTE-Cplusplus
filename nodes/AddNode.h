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
    addition of two nodes.
    param l Shared Smart Pointer to left node
    param r Shared Smart Pointer to right node
 
 */
class AddNode:public Node{
public:

    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    /*
     Constructor
     */
    AddNode(std::shared_ptr<Node> L, std::shared_ptr<Node> R);
    /*
     Forward pass
     */
    void forward() override;
    /*
     Backward pass
     */
    void backward() override;
};

#endif /* AddNode_h */
