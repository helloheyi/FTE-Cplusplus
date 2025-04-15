#include <iostream>
#include <cmath>
#include "nodes/ConstantNode.h"
#include "nodes/VariableNode.h"
#include "nodes/AddNode.h"
#include "nodes/SubNode.h"
#include "nodes/MulNode.h"
#include "nodes/DivNode.h"
#include "nodes/PowNode.h"
#include "nodes/LogNode.h"
#include <functional>
#include <vector>
#include <fstream>
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
    
    using NodePtr = std::shared_ptr<Node>;
    auto x = std::make_shared<VariableNode>(x_0);

    NodePtr expr = std::make_shared<AddNode>(
            std::make_shared<ConstantNode>(5.0),
            std::make_shared<AddNode>(
                std::make_shared<PowNode>(x, 3.0),
                std::make_shared<DivNode>(
                    std::make_shared<LogNode>(
                        std::make_shared<MulNode>(
                            std::make_shared<SubNode>(
                                std::make_shared<PowNode>(x, 2.0),
                                std::make_shared<ConstantNode>(5.0)
                            ),
                            std::make_shared<SubNode>(
                                std::make_shared<ConstantNode>(4.0),
                                std::make_shared<MulNode>(
                                    std::make_shared<ConstantNode>(3.0), x)
                            )
                        )
                    ),
                    std::make_shared<SubNode>(x, std::make_shared<ConstantNode>(4.0))
                )
            )
        );
    
    expr->forward();
    expr->backward(1.0);
    outfile << "The f(x) = 5 + x^3 + ln((x^2 - 5) * (4 - 3x)) / (x - 4)"  << ":\n";
    outfile << "For x = " << x_0 << ":\n";
    outfile << "f1(x)  = " <<  expr->value << "\n";
    outfile << "f1'(x) (Back-propagation) = " << x->grad << "\n";
    outfile << "f1'(x) (Finite Diff)  = " << finiteDifference(f1, x_0, 0.001) << "\n";
    outfile << "\n";
    

    // Test 2: Multi-variable function
    // f(x, y) = x^3 * y + ln(x) * y
    std::cout << "\n For the second test:\n"
                    " f(x, y) = x^3 * y + ln(x) * y\n"
                    "We need two values for x and y.\n";
    
    double test2_x_0, test2_y_0;
    if (argc >= 3) {
        test2_x_0 = std::stod(argv[1]);
        test2_y_0 = std::stod(argv[2]);
        std::cout << "Using command-line arguments: x_0 = " << test2_x_0
        << ", y_0 = " << test2_y_0 << std::endl;
    }
    else {
        // Prompt the user
        std::cout << "Please enter x_0 for test2: ";
        std::cin >> test2_x_0;
        if (!std::cin) {
            std::cerr << "Invalid x_0. Exiting.\n";
            return 1;
            }

        std::cout << "Please enter y_0 for test2: ";
        std::cin >> test2_y_0;
        if (!std::cin) {
            std::cerr << "Invalid y_0. Exiting.\n";
            return 1;
            }
    }
    
    
    using NodePtr_test2 = std::shared_ptr<Node>;
    auto test2_x = std::make_shared<VariableNode>(test2_x_0);
    auto test2_y = std::make_shared<VariableNode>(test2_y_0);

    NodePtr_test2 expr_test2 = std::make_shared<AddNode>(
        std::make_shared<MulNode>(
            std::make_shared<PowNode>(test2_x, 3.0),test2_y
        ),
        std::make_shared<MulNode>(
            std::make_shared<LogNode>(test2_x), test2_y
        )
    );

    expr_test2->forward();
    expr_test2->backward(1.0);
    
    outfile << "The f(x, y) = x^3 * y + ln(x) * y"  << ":\n";
    outfile << "For x = " << test2_x_0 << " y = " << test2_y_0 <<":\n";
    outfile << "f2(x, y)  = " << expr_test2 -> value << "\n";
    outfile << "df/dx(2, 3)  = " << test2_x -> grad << "\n";
    outfile << "df/dy(2, 3) = " << test2_y -> grad << "\n";
    outfile.close();
    std::cout << "Results are saved in results.txt" << std::endl;
    return 0;

//
//       {
//           Tape tape;
//           auto x = tape.create<VariableNode>(test2_x_0);
//           auto y = tape.create<VariableNode>(test2_y_0);
//
//           auto final = tape.create<AddNode>(
//               tape.create<MulNode>(
//                   tape.create<PowNode>(x, 3.0),
//                   y
//               ),
//               tape.create<MulNode>(
//                   tape.create<LogNode>(x),
//                   y
//               )
//           );
//
//           tape.forward();
//           tape.backward();
//           outfile << "The f(x, y) = x^3 * y + ln(x) * y"  << ":\n";
//           outfile << "For x = " << test2_x_0 << " y = " << test2_y_0 <<":\n";
//           outfile << "f2(x, y)  = " << final->getValue() << "\n";
//           outfile << "df/dx(2, 3)  = " << x->getGrad() << "\n";
//           outfile << "df/dy(2, 3) = " << y->getGrad() << "\n";
//       }
//
//    outfile.close();
//
//    std::cout << "Results are saved in results.txt" << std::endl;
//    return 0;

//    // Edge-case tests:
//    //   x = -1, x = 0, x = 0.00001, x = 10^100000
//    //   and an empty Tape usage example
//    std::cout << "\nRunning edge case tests...\n" << std::endl;
//    std::vector<double> arr = {-1, 0, 0.00001, std::pow(10, 100000)};
//
//    for (double x_val : arr) {
//        try {
//            auto results = runGraphTest1(x_val);
//            std::cout << "f1(" << x_val << ") = " << results[0] << std::endl;
//            std::cout << "f1'(" << x_val << ") = " << results[1] << std::endl;
//        } catch (const std::exception& e) {
//            std::cerr << "Exception caught during edge-case testing: " << e.what() << std::endl;
//        }
//    }
//
//    // Demonstration of an empty Tape
//    Tape tape;
//    // This should emit a warning like "No nodes in tape to run forward."
//    tape.forward();
//
}
