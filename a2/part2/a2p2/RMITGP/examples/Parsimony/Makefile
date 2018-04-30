.SUFFIXES: .cpp $(SUFFIXES)

CC = g++
#CC = cxx                           #FOR VPAC
#CFLAGS = -g -std gnu               #FOR VPAC
CFLAGS = -g -pedantic -Wall
DEFINES = -DUNIX #-DOLD_GCC          Add DOLD_GCC if you are using GCC 3.0 
                                    #or lesser, or if using another compiler

RM = rm
DIR = `pwd`
LIB = -L../../src/ -lrmitgp

OUTPUT = parsimony_symbolicgp

OBJS  = main.o SymbolicFitness.o \
        DivideInt.o MinusInt.o MultInt.o PlusInt.o XInt.o RandInt.o \
        ReturnInt.o 

SRCS=$(OBJS:.o=.cpp)

INCLUDE = -I../../src/

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $(DEFINES) $(CXXINCLUDE) $(INCLUDE) -I. $*.cpp

clean:
	$(RM) -f $(OBJS) $(OUTPUT)

objects:
	@for f in $(OBJS); do echo $(DIR)/$$f; done

depend: $(SRCS)
	@(sed <Makefile '/^#--DEPENDENCIES--$$/,$$d'; \
	echo '#--DEPENDENCIES--'; \
	$(CC) -c -MM $(CFLAGS) $(CXXINCLUDE) $(INCLUDE) $(SRCS) \
	) > Makefile.new
	mv Makefile.new Makefile

#--DEPENDENCIES--
main.o: main.cpp ../../src/Population.h ../../src/GeneticProgram.h \
  ../../src/ReturnData.h ../../src/Node.h ../../src/Mutation.h \
  ../../src/Crossover.h ../../src/Selection.h ../../src/GPConfig.h \
  ../../src/Random.h ../../src/Fitness.h ../../src/NodeSet.h \
  ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
  ../../src/Population.h ../../src/Fitness.h SymbolicFitness.h \
  ../../src/GeneticProgram.h ParallelFitness.h \
  ../../src/TournamentSelection.h ReturnInt.h ../../src/ReturnData.h \
  RandInt.h ../../src/Terminal.h XInt.h PlusInt.h ../../src/Function.h \
  MinusInt.h MultInt.h DivideInt.h ../../src/NodeSet.h \
  ../../src/ProgramGenerator.h ../../src/NodeVector.h \
  ../../src/GPConfig.h ../../src/SinParsimony.h \
  ../../src/LinearParsimony.h ../../src/ConstantParsimony.h \
  ../../src/LimitParsimony.h
SymbolicFitness.o: SymbolicFitness.cpp SymbolicFitness.h \
  ../../src/GeneticProgram.h ../../src/ReturnData.h ../../src/Node.h \
  ../../src/Fitness.h ../../src/GeneticProgram.h ReturnInt.h \
  ../../src/ReturnData.h XInt.h ../../src/Terminal.h ../../src/GPConfig.h \
  ../../src/Random.h ../../src/Crossover.h ../../src/Mutation.h \
  ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
  ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
  ../../src/Population.h ../../src/GPConfig.h
DivideInt.o: DivideInt.cpp DivideInt.h ../../src/Function.h \
  ../../src/Node.h ../../src/ReturnData.h ReturnInt.h \
  ../../src/ReturnData.h ../../src/GPConfig.h ../../src/Random.h \
  ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/Mutation.h \
  ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
  ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
  ../../src/Population.h ../../src/GPConfig.h
MinusInt.o: MinusInt.cpp MinusInt.h ../../src/Function.h ../../src/Node.h \
  ../../src/ReturnData.h ReturnInt.h ../../src/ReturnData.h \
  ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
  ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
  ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
  ../../src/Terminal.h ../../src/Parsimony.h ../../src/Population.h \
  ../../src/GPConfig.h
MultInt.o: MultInt.cpp MultInt.h ../../src/Function.h ../../src/Node.h \
  ../../src/ReturnData.h ReturnInt.h ../../src/ReturnData.h \
  ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
  ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
  ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
  ../../src/Terminal.h ../../src/Parsimony.h ../../src/Population.h \
  ../../src/GPConfig.h
PlusInt.o: PlusInt.cpp PlusInt.h ../../src/Function.h ../../src/Node.h \
  ../../src/ReturnData.h ReturnInt.h ../../src/ReturnData.h \
  ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
  ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
  ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
  ../../src/Terminal.h ../../src/Parsimony.h ../../src/Population.h \
  ../../src/GPConfig.h
XInt.o: XInt.cpp XInt.h ../../src/Terminal.h ../../src/Node.h \
  ../../src/ReturnData.h ReturnInt.h ../../src/ReturnData.h \
  ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
  ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
  ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
  ../../src/Terminal.h ../../src/Parsimony.h ../../src/Population.h \
  ../../src/GPConfig.h
RandInt.o: RandInt.cpp RandInt.h ../../src/Terminal.h ../../src/Node.h \
  ../../src/ReturnData.h ReturnInt.h ../../src/ReturnData.h \
  ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
  ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
  ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
  ../../src/Terminal.h ../../src/Parsimony.h ../../src/Population.h \
  ../../src/GPConfig.h
ReturnInt.o: ReturnInt.cpp ReturnInt.h ../../src/ReturnData.h
