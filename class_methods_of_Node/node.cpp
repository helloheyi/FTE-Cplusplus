#include "node.h"
#include <cmath>
#include <memory>


/*
 Constructor of leaf nodes (constants or variables)
 */
Node::Node(double val)
    : value(val), grad(0.0), op(NodeType::CONSTANT),
      left(nullptr), right(nullptr), param(0.0)
{
}



/*
 Internal node constructor that performs the forward pass.
 operation The NodeType (ADD, SUB, MUL...).
 */
Node::Node(NodeType operation, NodePtr L, NodePtr R, double p)
    : op(operation), left(L), right(R), param(p), grad(0.0)
{
    switch (op) {
        case NodeType::ADD:
            value = left->value + (right ? right->value : 0.0);
            break;
        case NodeType::SUB:
            value = left->value - (right ? right->value : 0.0);
            break;
        case NodeType::MUL:
            value = left->value * (right ? right->value : 1.0);
            break;
        case NodeType::DIV:
            if (right && right->value == 0.0) {
            throw std::runtime_error("Division by zero in DivNode::forward()");
            }
            value = left->value / (right ? right->value : 1.0);
            break;
        case NodeType::POW:
            if (std::abs(p) > 1e6 || std::abs(left->value) > 1e100) {
                throw std::runtime_error("Exponentiation could cause overflow.");
            }
            value = std::pow(left->value, param);
            break;
        case NodeType::LOG:
            if (left->value <= 0.0) {
                throw std::runtime_error("Logarithm domain error: input must be > 0.");
           }
            value = std::log(left->value);
            break;
        case NodeType::VARIABLE:
        case NodeType::CONSTANT:
        default:
            break;
    }
}

/*
 Creates a leaf constant variable node.
 */
Node::NodePtr Node::constant(double val) {
    return std::make_shared<Node>(val);
}
Node::NodePtr Node::variable(double val) {
    auto node = std::make_shared<Node>(val);
    node->op = NodeType::VARIABLE;
    return node;
}



/*
 Builds a new node:Add, Sub, Mul, Div, Pow, Log
 */
Node::NodePtr Node::Add(const NodePtr& rhs) {
    return std::make_shared<Node>(NodeType::ADD, shared_from_this(), rhs);
}

Node::NodePtr Node::Sub(const NodePtr& rhs) {
    return std::make_shared<Node>(NodeType::SUB, shared_from_this(), rhs);
}

Node::NodePtr Node::Mul(const NodePtr& rhs) {
    return std::make_shared<Node>(NodeType::MUL, shared_from_this(), rhs);
}

Node::NodePtr Node::Div(const NodePtr& rhs) {
    return std::make_shared<Node>(NodeType::DIV, shared_from_this(), rhs);
}

Node::NodePtr Node::Pow(double exponent) {
    return std::make_shared<Node>(NodeType::POW, shared_from_this(), nullptr, exponent);
}

Node::NodePtr Node::Log() {
    return std::make_shared<Node>(NodeType::LOG, shared_from_this(), nullptr);
}

/*
 Performs the backward pass
 */
void Node::backward(double topGrad) {
    grad += topGrad;
    switch (op) {
        case NodeType::VARIABLE:
            break;
        case NodeType::CONSTANT:
            break;
        
        // df/dx (a + b) = 1
        case NodeType::ADD:
            if (left) left->backward(topGrad);
            if (right) right->backward(topGrad);
            break;
        
        // df/dx (a - b) = 1 (left), -1 (right)
        case NodeType::SUB:
            if (left) left->backward(topGrad);
            if (right) right->backward(-topGrad);
            break;
        
        // df/dx (a * b) = b (left), a (right)
        case NodeType::MUL:
            if (left && right) {
                left->backward(topGrad * right->value);
                right->backward(topGrad * left->value);
            }
            break;
        
        // df/dx (a / b) = 1/b (left), -a / b^2 (right)
        case NodeType::DIV:
            if (right && right->value == 0.0) {
                throw std::runtime_error("Backward pass error: Division by zero");
            }
            if (left && right) {
                left->backward(topGrad / right->value);
                right->backward(topGrad * (-left->value / (right->value * right->value)));
            }
            break;
        
        // df/dx (x^c) = c * x^(c - 1)
        case NodeType::POW:
            if (!std::isfinite(left->value)) {
                throw std::overflow_error("Backward pass error: overflow in pow gradient.");
            }
            if (left) {
                double e = param;
                left->backward(topGrad * e * std::pow(left->value, e - 1.0));
            }
            break;
            
        // d/dx (ln(x)) = 1 / x
        case NodeType::LOG:
            if (left && left->value <= 0.0) {
                throw std::runtime_error("Backward pass error: log(x) where x <= 0.");
            }
            if (left) {
                left->backward(topGrad * (1.0 / left->value));
            }
            break;
        default:
            break;
    }
}

