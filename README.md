This project implements automatic differentitation by backpropagation and build center different method as a benchmark. 

1. Taple Class
 - Stores a list of nodes of  mathematical operations (add, sub, mul, div, pow, log).
   - Each node holds:
     - operation type (e.g., add, sub, mul, div, pow, log).
     - indexes to its child nodes (left, right).
     - Value (forward evaluation result).
     - Gradient (computed in backward pass).
     - Additional parameter (e.g., the exponent in pow).
   - After constructing the entire expression, we can run forward and backward passes to get:
     - getValue(index) → the numeric value of the sub-expression.
     - getGrad(index) → the partial derivative of that sub-expression with respect to x.

2. Differentiator Class  
   - Executes two key processes:
     1. forwardPass(Tape&)  
        - Iterates through each node in order, computing its value from its children’s values.
     2. backwardPass(Tape&, outputIndex)
        - Sets the gradient of final node as 1.0 (since  d f / d f = 1).
        - Iterates backwards, applying the chain rule for each operation:
     - There is also a finiteDifference utility to approximate the derivative numerically (for validation).

3. Compile code and Function Evaluated

f(x) = 5 + x^3 - In((x^2-5)*(4-3*x)/(x-4)
create an object: Tape tape;
Create a variable node for x = 2.
e.g: int xIdx = tape.variable(2.0);
e.g: x^2 is a pow node as int x2 = tape.pow(xIdx, 2.0);
e.g. x^2 - 5 as int left = tape.sub(x2, tape.constant(5.0));
other operations can be referred in main function
Differentiator diff;
diff.forwardPass(tape);           
diff.backwardPass(tape, final);    

4. Future extension for other operations: dd support for more mathematical operations such as sin, cos, exp, and beyond.

a. In tape class,add a new entry to the NodeType emun and add method to create a node for the new operation.
c. In Differentiator class extend forwardPass() logic and backwardPass() logic

