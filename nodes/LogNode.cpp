//
//  LogNode.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-27.
//

#include <stdio.h>
#include "LogNode.h"

/*
Constructor to initialize LogNode with an input node.
param I Pointer to the input node.
*/
LogNode::LogNode(Node* I) : input(I) {};

/*
Forward pass: ln(x)
throws std::runtime_error If the input value is non-positive.
*/
void LogNode::forward(){
    if (input->getValue() <= 0){
        {throw std::runtime_error("Log by non positive or very small value in LogNode::forward().");}
    }
    value = std::log(input->getValue());
    
};

/*
Backward pass:
 ∂(ln(x))/∂x = 1 / x
throws std::runtime_error If the input value is non-positive.
*/
void LogNode::backward(){
    if (input->getValue() == 0){
        {throw std::runtime_error("Division by zero in LogNode::backward().");}
    }
    input->grad += grad / input->getValue();
};
    

