#include <iostream>
#include <cmath>
#include "ConstantNode.h"
#include "VariableNode.h"
#include "AddNode.h"
#include "SubNode.h"
#include "MulNode.h"
#include "DivNode.h"
#include "PowNode.h"
#include "LogNode.h"
#include "Tape.hpp"
#include <functional>
#include <vector>

/*
 central finiteDifference method
 param f as function variable used for finiteDifference
 param x variable
 param h shocked value
 return double df/dx
 */
double finiteDifference(std::function<double(double)> f, double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}


/*
 f(x) = 5 + x^3 + ln((x^2 - 5) * (4 - 3x)) / (x - 4) as test case 1
 param double x
 return f(x)
 
 */
double f1(double x) {
    return 5.0 + std::pow(x, 3) + std::log((std::pow(x, 2) - 5.0) * (4.0 - 3.0 * x)) / (x - 4.0);
}

/*
 f(x) = 5 + x^3 + ln((x^2 - 5) * (4 - 3x)) / (x - 4) as test case 1
 param double x_0: initial value of the variable
 return: a vector
 f(x) value
 Gradient df/dx
 */
auto runGraphTest1(double x_0) {
    Tape tape;
    // variable node for x
    auto x = tape.create<VariableNode>(x_0);
    // x^2 using PowNode
    auto x2 = tape.create<PowNode>(x, 2.0);
    // (x^2 - 5) using SubNode
    auto c5 = tape.create<ConstantNode>(5.0);
    auto left = tape.create<SubNode>(x2, c5);
    // Perform (3 * x) using MulNode
    auto c3 = tape.create<ConstantNode>(3.0);
    auto tmp = tape.create<MulNode>(c3, x);
    // (4 - 3 * x) using SubNode
    auto c4 = tape.create<ConstantNode>(4.0);
    auto right = tape.create<SubNode>(c4, tmp);
    // (x^2 - 5) * (4 - 3 * x) using MulNode
    auto mult = tape.create<MulNode>(left, right);
    // ln((x^2 - 5) * (4 - 3 * x)) using LogNode
    auto ln_part = tape.create<LogNode>(mult);
    // (x - 4) using SubNode
    auto denom = tape.create<SubNode>(x, c4);
    //  ln_part / denom using DivNode
    auto fraction = tape.create<DivNode>(ln_part, denom);
    // x^3 using PowNode
    auto x3 = tape.create<PowNode>(x, 3.0);
    // 5 + x^3 using AddNode
    auto tmp2 = tape.create<AddNode>(c5, x3);
    // computation: (5 + x^3) + (ln_part / denom) using AddNode
    auto final = tape.create<AddNode>(tmp2, fraction);
    // forward and backward pass
    tape.forward();
    tape.backward();
    return std::vector<double>{final->getValue(), x->getGrad()};
}


/*
 f(x,y) = x^3 * y+ln(x) * y
 param double x_0: initial value of the variable
 return: a vector
 f(x) value
 Gradient df/dx
 */
auto runGraphTest2(double x_0, double y_0) {
    std::cout << "\nRunning Graph Test2 with x_0 = " << x_0 << " and y_0 = " << y_0 << std::endl;
    Tape tape;
    auto x = tape.create<VariableNode>(x_0);
    auto y = tape.create<VariableNode>(y_0);
    // x^3 using PowNode
    auto x3 = tape.create<PowNode>(x, 3.0);
    // ln(x) using LogNode
    auto ln_x = tape.create<LogNode>(x);
    // x^3 * y using MulNode
    auto x3y = tape.create<MulNode>(x3, y);
    // ln(x) * y using MulNode
    auto ln_xy = tape.create<MulNode>(ln_x, y);
    // computation: x^3 * y + ln(x) * y using AddNode
    auto final = tape.create<AddNode>(x3y, ln_xy);
    // forward and backward pass
    tape.forward();
    tape.backward();
    return std::vector<double>{final->getValue(), x->getGrad(), y->getGrad()};
    
}

int main() {
    //one variable test case
    // f(x) = 5 + x^3 + ln((x^2 - 5) * (4 - 3x)) / (x - 4)
    double x_0 = 2;
    auto f1_result =runGraphTest1(x_0);
    std::cout << "\nRunning Graph Test 1 with x_0 = " << x_0 << std::endl;
    std::cout << "Numerical f1'(2.0) ≈ " << finiteDifference(f1, x_0,0.001) << std::endl;
    std::cout << "f1(" << x_0 << ") = " << f1_result[0] << std::endl;
    std::cout << "f1'(" << x_0 << ") = " << f1_result[1] << std::endl;
    
    
    // two variables test case
    // f(x,y) = x^3 * y+ln(x) * y
    double test2_x_0 = 2.0;
    double test2_y_0 = 3.0;
    auto f2_result =runGraphTest2(test2_x_0,test2_y_0);
    std::cout << "f(" << test2_x_0 << ", " << test2_y_0 << ") = " << f2_result[0] << std::endl;
    std::cout << "df/dx(" << test2_x_0 << ", " << test2_y_0 << ") = " << f2_result[1] << std::endl;
    std::cout << "df/dy(" << test2_x_0 << ", " << test2_y_0 << ") = " << f2_result[2] << std::endl;
    
    
    // run for edge case as x = -1, x = 0, x = 0.0001, x= pow(10,1000000) and empty Tape
    std::cout << "run for edge cases \n" << std::endl;
    std::vector<double> arr = {-1, 0, 0.00001, std::pow(10, 100000)};
    for (int i = 0; i < arr.size(); ++i){
        try {
                std::cout << "f1(" << arr[i] << ") = " << runGraphTest1(arr[i])[0] << std::endl;
                std::cout << "f1'(" << arr[i] << ") = " << runGraphTest1(arr[i])[1] << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Exception caught during edge case testing: " << e.what() << std::endl;
            }
       
    }
    Tape tape;
    // a warning: No nodes in tape to run forward.
    tape.forward();
    return 0;
}


