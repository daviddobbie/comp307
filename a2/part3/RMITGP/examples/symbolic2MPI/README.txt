This example is another symbolic regression example with MPI functionality. 

It uses double values to try to discover the function
  1.5X^3 + 3.2X^2 + 4.0X - 127.2
To change the function modify the targetFunc values in SymbolicFitness.cpp

To build type

bash MPI_make.sh

To run on an standard MPI machine, type:

qsub pbs-symbolic

Edit the pbs script as necessary for requesting extra time, processors, etc.

