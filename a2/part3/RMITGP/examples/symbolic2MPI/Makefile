
.SUFFIXES: .cpp $(SUFFIXES)

all:
	mpiCC -D MPI_ENABLED -g -I ../../src/ *.cpp -L/usr/local/openmpi/1.6.3-gcc/lib/ -o symbolic2 ../../src/*.o
clean:
	rm symbolic2
	rm core*

