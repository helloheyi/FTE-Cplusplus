//
//  Node.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef Node_h
#define Node_h

/*
 Node is an abstract base class representing a generic node in a computational graph.

 Each node stores:
 - value: The result of the forward pass.
 - grad:  The accumulated gradient during the backward pass.

 Derived classes must implement:
 - forward(): Computes this node’s output value.
 - backward(): Propagates gradients to upstream nodes.
*/

class Node{
    public:
    double value = 0.0;
    double grad = 0.0;
    
    /*
     Computes this node's output value based on its inputs.
     Pure virtual function and must be implemented by derived classes.
    */
    virtual void forward () = 0;
    
    /*
     Backpropagates gradients backward to input nodes.
     Pure virtual function and must be implemented by derived classes.
    */
    virtual void backward () = 0;
    
    /*
     Retrieves the node's current value (result of the forward pass).

     Returns:
     - The node's current value.
    */
    double getValue() const { return value; }
    
    /*
     Retrieves the node's current gradient (accumulated from the backward pass).

     Returns:
     - The node's current gradient.
    */
    double getGrad() const { return grad; }
    
    /*
     Virtual destructor to ensure proper cleanup of derived classes.
    */
    virtual ~Node() {}
};

#endif /* Node_h */
