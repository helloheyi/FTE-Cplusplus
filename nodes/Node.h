//
//  Node.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef Node_h
#define Node_h
#include <memory>

/*
 Node is an abstract base class representing a generic node in a computational graph.

 Each node stores:
 - value: The result of the forward pass.
 - grad:  The accumulated gradient during the backward pass.

 Derived classes must implement:
 - forward(): Computes this node’s output value.
 - backward(): Propagates gradients to upstream nodes.
*/

class Node : public std::enable_shared_from_this<Node> {
public:
    using NodePtr = std::shared_ptr<Node>;
    double value = 0.0;
    double grad = 0.0;    

    virtual void forward() = 0;
    virtual void backward(double topGrad) = 0;
    virtual ~Node() = default;
};

#endif /* Node_h */
