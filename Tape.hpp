//
//  Tape.hpp
//  autoDiff_Oop
//
//  Created by Yi He on 2025-03-26.
//

#ifndef Tape_hpp
#define Tape_hpp
#include "nodes/Node.h"
#include <vector>

/*
 Tape class representing a computational graph for automatic differentiation.
 
 This class holds a sequence of nodes and coordinates the forward and backward passes to compute output values and gradients.
*/

class Tape {
public:
    std::vector<std::shared_ptr<Node>> nodes;
   
    /*
     Create a template declaration
     
     Template Parameters:
      - T:  type of node to create (must inherit from Node).
     
     Parameters:
      - Args...: number of arguments of different types for the node's constructor.

     Returns:
      - std::shared_ptr<T>: Pointer to the newly created node.
     
     Example:
        auto addNode = tape.create<AddNode>(leftNode, rightNode);
     
     std::make_shared<T> creates a std::shared_ptr<T> instead of raw pointers to use new and delete
    
     */
    template<typename T, typename... Args>
    std::shared_ptr<T> create(Args... args) {
        std::shared_ptr<T> node = std::make_shared<T> (args...);
        nodes.push_back(node);
        return node;
    }
    
    /*
     Performs the forward pass for all nodes in the computational graph.
     Each node's forward() function is called to compute its output value.

     If the tape is empty, a warning is printed.
    */
    void forward();
    
    
    /*
     Performs the backward pass for all nodes in the computational graph.
     Each node's backward() function is called to compute gradients using proporgation differentiation.
     
     The gradient of the final node is initialized to 1.0, representing the derivative of the output itself.

     If the tape is empty, a warning is printed.
    */
    
    void backward();
    // No longer needed becuase of std::shared_ptr handle memory automatically by reference counting.
    // ~Tape();
};


#endif /* Tape_hpp */
