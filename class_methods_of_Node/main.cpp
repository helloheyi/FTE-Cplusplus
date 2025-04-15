#include "node.h"
#include <iostream>
#include <fstream>
#include <string>
/*
 Central finite difference method to approximate the derivative of a function.
 
 Parameters:
  - f: Function to differentiate (std::function<double(double)>)
  - x: Point at which to evaluate the derivative
  - h: Small increment value for finite difference approximation

  Returns:
  - Approximation of the derivative df/dx
 */
double finiteDifference(std::function<double(double)> f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

/*
 Function definition: f(x) = 5 + x^3 + ln((x^2 - 5) * (4 - 3x)) / (x - 4)
 Used as a test case for automatic differentiation.

 Parameters:
 - x: Input value

 Returns:
 - Result of f(x)
*/
double f1(double x) {
    return 5.0 + std::pow(x, 3) + std::log((std::pow(x, 2) - 5.0) * (4.0 - 3.0 * x)) / (x - 4.0);
}


int main(int argc, char* argv[]) {
    
    // Test 1: Single-variable function
    // f(x) = 5 + x^3 + ln((x^2 - 5) * (4 - 3x)) / (x - 4)
    std::cout << "The f(x) = 5 + x^3 "
    "+ ln((x^2 - 5) * (4 - 3x)) / (x - 4)\n";
    double x_0;
    // If user provided an argument, parse it:
    if (argc >= 2) {
        x_0 = std::stod(argv[1]);
        std::cout << "Using command-line argument x_0 = " << x_0 << std::endl;
    }
    // Otherwise, prompt the user to enter the value:
    else {
        std::cout << "Please enter x_0 for the function f(x): ";
        std::cin >> x_0;
        if (!std::cin) {
        std::cerr << "Invalid input. Exiting.\n";
        return 1;
        }
    }
    // Prepare file to write results
    const std::string filename = "results.txt";
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: could not open " << filename << " for writing.\n";
        return 1;
    }
    
    
    
    // variable "x" with an initial value from user
    Node::NodePtr x = Node::variable(x_0);

    // Construct the expression of f
    Node::NodePtr expr =
        Node::constant(5.0)
        ->Add(
            x->Pow(3.0)
        )
        ->Add(
             ( x->Pow(2.0)->Sub(Node::constant(5.0)) )
             ->Mul( Node::constant(4.0)->Sub(Node::constant(3.0)->Mul(x)) )
             ->Log()
             ->Div( x->Sub(Node::constant(4.0)) )
        );
    expr->backward();
    outfile << "For x = " << x_0 << ":\n";
    outfile << "f1(x)  = " << expr->value << "\n";
    outfile << "f1'(x) (Back-propagation) = " << x->grad << "\n";
    outfile << "f1'(x) (Finite Diff)  = " << finiteDifference(f1, x_0, 0.001) << "\n";
    outfile.close();

    std::cout << "Results are saved in results.txt" << std::endl;
    return 0;
}

