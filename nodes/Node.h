//
//  Node.h
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef Node_h
#define Node_h
class Node{
    public:
    double value = 0.0;
    double grad = 0.0;
    /*
     output value during the forward pass.
     pure virtual function
     */
    virtual void forward () = 0;
    /*
     backpropagates gradients during the backward pass.
     pure virtual function
     */
    virtual void backward () = 0;
    /*
     returns the current forward
     */
    double getValue() const { return value; }
    /*
     returns the current gradient
     */
    double getGrad() const { return grad; }
    virtual ~Node() {}
};

#endif /* Node_h */
