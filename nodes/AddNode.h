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
    param l Pointer to left node
    param r Pointer to right node
 
 */
class AddNode:public Node{
public:
    Node* left;
    Node* right;
    /*
     Constructor
     */
    AddNode(Node* L, Node* R);
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
