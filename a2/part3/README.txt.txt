To execute the genetically programmed classification on the dataset.

Compilation:

This is C++ code, utilising the RMITGP package. My implemetation of implementing adapts symbolic2 and allows for loading the file where the exectuable is. I have adapted the symbolic2 code to build up the classifier code, hence why it is called that. Operationally, it acts differently 

To compile on the Linux ECS machines:

got to 
RMITGP/src
run 'make'

go to 
RMITGP/examples/symbolic2
run 'make'

Execution:

Run symbolic2 in RMITGP/examples/symbolic2

It will ask to load the training file and the test file in the execution file system. These are called testing.data and training.data. These files must be in the same folder as where the application is running. Testing must be 100 lines long and training must be 599 lines long.


It will post parsing diagnostic information. At each generation, it posts the smallest fitness value. After finishing, it will post the learned program with the lowest fitness value (lower is better).