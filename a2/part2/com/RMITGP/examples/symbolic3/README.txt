This directory contains a symbolic regression problem which also
supports conditional execution. The terminals and functions are the
same for the symbolic2 example except for the addition of the following
functions.

Functions
if         and if function
d<         less than function for doubles
d>         greater than function for doubles 

type these commands to build the program

make clean
make depend
make
 
type ./symbolicgp to run


symbolic3 is an example of using strongly typed genetic programming (STGP).
There are 2 different returns types present in this example, doubles
and booleans. The less than and greater than functions accept two 
doubles and returns a boolean. The if function accepts a boolean and
2 doubles and returns a double. See the code for the details on how 
to use multiple data types. 
