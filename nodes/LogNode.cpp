//
//  LogNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "LogNode.h"

/*
 Constructor for LogNode to initialize the input node.

 Parameters:
 - I: Shared Smart pointer to the input node.
*/
LogNode::LogNode(NodePtr in) : input(in) {}

/*
 Computes the In(x) of the input node values using the formula:
 value = log(input->getValue())
 
 Throws:
 - std::runtime_error if input->getValue() <= 0,
   to avoid taking a logarithm of zero or negative values.

 No return value.
*/
void LogNode::forward(){
    input->forward();
    if (input->value <= 0.0){
        
        {throw std::runtime_error("Log by non positive or very small value in LogNode::forward().");}
    }
    
    value = std::log(input->value);

};

/*
 Propagates gradients from the output node to input node:

 Gradients:
 d(In(x)) = 1/x
 
 Throws:
 - std::runtime_error if input->getValue() == 0,
   to avoid dividing zero
 
 No return value.
*/
void LogNode::backward(double topGrad){
    
    if (input->value <= 0.0){
        {throw std::runtime_error("Division by zero in LogNode::backward().");}
    }
    
    input->backward(topGrad / input->value);
};
    

