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
class Tape {
public:
    std::vector<std::shared_ptr<Node>> nodes;
    /*
     Create a template declaration that to create a generic function.
     param T:  type of node to create (must inherit from Node).
     param Args...: number of arguments of different types for the node's constructor.
     e.g.AddNode: tape.create<AddNode>(leftNode, rightNode);
     std::make_shared<T> creates a std::shared_ptr<T>
     instead of tranditional point to use new
     return Pointer to the newly created node of type T.
     */
    template<typename T, typename... Args>
    std::shared_ptr<T> create(Args... args) {
        std::shared_ptr<T> node = std::make_shared<T> (args...);
        nodes.push_back(node);
        return node;
    }
    /*
     forward pass for all nodes in the computational graph.
     */
    void forward();
    /*
     backward pass for all nodes in the computational graph.
     */
    void backward();
    // No longer needed becuase of std::shared_ptr handle memory automatically by reference counting.
    // ~Tape();
};


#endif /* Tape_hpp */
