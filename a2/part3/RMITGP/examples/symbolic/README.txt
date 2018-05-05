This directory contains an example simple symbolic regression problem.

type these commands to build the program

make clean
make depend
make
 
type ./symbolicgp to run

There is also an example of using MPI to evolve a population on 
multiple processors. You will need to modify the file Makefile.mpi
to suit your MPI environment.

To build the mpi version type

make -f Makefile.mpi clean
make -f Makefile.mpi depend
make -f Makefile.mpi
