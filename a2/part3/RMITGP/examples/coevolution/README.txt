This directory contains a simple predator prey co-evolution example.
The problem is grid based, at each time step players can move up, down, left,
or right one grid position. The goal for the predator is to occupy the 
same square as the prey (capture it), the goal for the prey is to avoid
the predator.

The fitness for the predator is (1 / (1 + number of caught prey))
The fitness for the prey is (0.01 * (number of time caught)^2)

The fitness object inherets from a new class CoEvolutionFitness which 
allows two populations to be passed to the assignFitness method.

The population is an instance of a new class CoEvolutionPopulation
which contains a reference to the other population.

type...

make clean
make depend
make

to build the program

./pred-prey to run the program

You can view two populations interacting by running
./pred-prey PREDPOPFILE PREYPOPFILE 

The program will load the two populations and display the behaviour of
the programs on the grid.

Some extensions to this simple example could be:-
 a) More than one predator, more than one prey.
 b) Include the concept of a facing direction for the players.
 c) Make the prey faster
 d) Include the concept of a catch area rather than saying the
    predator has to occupy the same square as the prey.

