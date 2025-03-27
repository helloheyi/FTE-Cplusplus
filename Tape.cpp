//
//  Tape.cpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//
#include "Tape.hpp"
#include <iostream>

/*
 forward pass for all nodes in the computational graph.
 node's forward() function is called to compute its output value.
 // or use auto& node : nodes
 print a warning if no nodes are available for computation.
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
 backward pass for all nodes in the computational graph.
 node's backward() function is called to compute its output gradient.
 print a warning if no nodes are available for computation.
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
