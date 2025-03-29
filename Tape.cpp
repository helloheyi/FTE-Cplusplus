//
//  Tape.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//
#include "Tape.hpp"
#include <iostream>

/*
 Performs the forward pass for all nodes in the computational graph.
 Each node's `forward()` function is called to compute its output value.

 If no nodes are available in the tape, a warning is printed.
*/
void Tape::forward() {
    if (nodes.empty()) {
        std::cerr << "Warning: No nodes in tape to run Tape::forward." << std::endl;
        return;
    }
    for (std::shared_ptr<Node> node : nodes) {
        node->forward();
    }
    
}

/*
 Performs the backward pass for all nodes in the computational graph.
 Each node's `backward()` function is called to compute gradients using back proporgation.

 The gradient of the final node is initialized to 1.0 as (d(output)/d(output) = 1), representing the derivative of the output itself

 If no nodes are available in the tape, a warning is printed.
*/
void Tape::backward() {
    if (nodes.empty()) {
        std::cerr << "Warning: No nodes in tape to run Tape::backward." << std::endl;
        return;
    }
    // final node gradient to 1.0
    nodes.back()->grad = 1.0;
    for (int i = static_cast<int>(nodes.size()) - 1; i >= 0; --i) {
        nodes[i]->backward();
    }
}

// No longer needed becuase of std::shared_ptr handle memory automatically by reference counting.

//Tape::~Tape() {
//    for (Node* node : nodes) {
//        delete node;
//    }
//}
