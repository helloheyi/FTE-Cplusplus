#ifndef NODE_H
#define NODE_H

#include <memory>
#include <cmath>

/*
 An enumeration of operation types that a Node may represent.
 */
enum class NodeType {
    CONSTANT,
    VARIABLE,
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    LOG
};

/*
 A node in an autodiff computational graph that supports forward evaluation and backward pass.
 
 Each Node holds:
    - A NodeType 
    - A forward value,
    - A gradient for backprop,
    - A NodeType to identify which operation it represents,
    - Pointers to left and right child nodes,
    - A parameter used by operations like exponentiation.
 
 Backpropagation is handled recursively via the backward() function.
 */
class Node : public std::enable_shared_from_this<Node> {
   
public:
    using NodePtr = std::shared_ptr<Node>;
    NodeType op;
    double value;
    double grad;
    NodePtr left;
    NodePtr right;
    double param;
    
    /*
     Constructor of leaf nodes (constants or variables)
     Parameters:
     - val: numerical value to assign to the node.
     */
    explicit Node(double val);

    
    /*
     Internal node constructor that performs the forward pass.
     operation The NodeType (ADD, SUB, MUL...).
     Parameters:
     - operation: ADD, SUB, MUL ...
     - L: Pointer to the left operand node.
     - R: Pointer to the right operand node.
     - p: An extra parameter for operations like POW.
     */
    Node(NodeType operation, NodePtr L, NodePtr R = nullptr, double p = 0.0);

    
    /*
     Creates a leaf constant node.
     Parameters:
     - numeric value.
     Return A Node pointer with op set to CONSTANT.
     */
    static NodePtr constant(double val);

    
    /*
     Creates a leaf variable node.
     Parameters:
     - val: numeric value.
     Return A Node pointer with op set to VARIABLE.
     */
    static NodePtr variable(double val);

    
    /*
     Builds a new node representing (this + rhs).
     Parameters:
     - rhs: A NodePtr referring to the node to be added (right-hand).
     - Return: A NodePtr pointing to the newly created node that represents the sum.
     */
    NodePtr Add(const NodePtr& rhs);

    
    /*
     Builds a new node representing (this - rhs).
     Parameters:
     - rhs: A NodePtr referring to the node to be subtract (right-hand).
     - Return: A NodePtr pointing to the newly created node that represents the subtraction.
     */
    NodePtr Sub(const NodePtr& rhs);

    
    /*
     Builds a new node representing (this * rhs).
     Parameters:
     - rhs: A NodePtr referring to the node to be multiply (right-hand).
     - Return: A NodePtr pointing to the newly created node that represents the multiplication.
     */
    NodePtr Mul(const NodePtr& rhs);

    
    /*
     Builds a new node representing (this / rhs).
     - rhs: A NodePtr referring to the node to be divided (right-hand).
     - Return: A NodePtr pointing to the newly created node that represents the divide.
     */
    NodePtr Div(const NodePtr& rhs);

    
    /*
     Builds a new node representing (this ^ exponent).
     - exponent: A referring exponent value
     - Return: A NodePtr pointing to the newly created node that represents the power.
     */
    NodePtr Pow(double exponent);

    
    /*
     Builds a new node representing ln(this).
     - Return: A NodePtr pointing to the newly created node that represents the LN.
     */
    NodePtr Log();

    /*
     Performs the backward pass
     Parameters:
      - topGrad: The initial gradient to be propagated (seed, typically 1.0).
     */
    void backward(double topGrad = 1.0);
    
    
//    /*
//     Retrieves the node's current value (result of the forward pass).
//
//     Returns:
//     - The node's current value.
//    */
//    double getValue() const { return value; }
//    
//    /*
//     Retrieves the node's current gradient (accumulated from the backward pass).
//
//     Returns:
//     - The node's current gradient.
//    */
//    double getGrad() const { return grad; }
};

#endif // NODE_H

