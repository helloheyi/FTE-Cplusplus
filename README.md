
## Project Structure
 - main.cpp: The main entry point where computations and function evaluations are tested.

- nodes/: Contains all the node classes representing operations (`AddNode`, `ConstantNode`, `DivNode`, `LogNode`, `MulNode`, `PowNode`, `SubNode`, `VariableNode`).


## Node Class Overview

- Node (base) Class: is an abstract class with pure virtual functions `forward()` and `backward()` that derived classes override to perform specific operations.
- Each node handles its own `forward()` and `backward()` logic. No tape or operation registry required.
- Polymorphism: Derived classes (`AddNode`, `ConstantNode`, `DivNode`, `LogNode`, `MulNode`, `PowNode`, `SubNode`, `VariableNode`) implement their own operation logic for Value and Gradient, supporting the computational graph.
- Memory-Safe: Uses `std::shared_ptr<Node>` for managing computation graph ownership.


## Script Implementation:
### Compile and Run
To compile and run in the terminal,  please ensure you are in the correct directory containing the following files:
by `g++`
```bash
g++ -std=c++14     main.cpp     nodes/ConstantNode.cpp     nodes/VariableNode.cpp     nodes/AddNode.cpp     nodes/SubNode.cpp     nodes/MulNode.cpp     nodes/DivNode.cpp     nodes/PowNode.cpp     nodes/LogNode.cpp     -o autoDiff
./autoDiff
```
by `clang++`
```bash
clang++  -std=c++14     main.cpp     nodes/ConstantNode.cpp     nodes/VariableNode.cpp     nodes/AddNode.cpp     nodes/SubNode.cpp     nodes/MulNode.cpp     nodes/DivNode.cpp     nodes/PowNode.cpp     nodes/LogNode.cpp     -o autoDiff
./autoDiff
```
Then enter a number for `x` when prompted.

### Examples of Computational Graph Breakdown for one variable and two variables:
#### One Variable: 
```
f(x) = 5 + x^3 + ln((x^2 - 5)*(4 - 3x)) / (x - 4)
```
 ```cpp
using NodePtr = std::shared_ptr<Node>;
auto x = std::make_shared<VariableNode>(2.0);

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
 ```


## Results 
Test cases results are all acceptable and saved in the `results.txt`and please refer the screenshot: 
![Test Case Results](images/autoDiff_Oop_Result.png)


