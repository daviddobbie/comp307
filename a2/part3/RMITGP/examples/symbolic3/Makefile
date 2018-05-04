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

OUTPUT = symbolicgp

OBJS  = main.o SymbolicFitness.o \
        DivideDouble.o MinusDouble.o MultDouble.o PlusDouble.o XDouble.o \
        RandDouble.o ReturnDouble.o ReturnBoolean.o \
        If.o LessThan.o GreaterThan.o

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
 ../../src/Population.h ../../src/Fitness.h ../../src/GeneticProgram.h \
 ../../src/NodeSet.h ../../src/ProgramGenerator.h ../../src/NodeVector.h \
 PlusDouble.h ../../src/Function.h MinusDouble.h MultDouble.h \
 DivideDouble.h If.h LessThan.h GreaterThan.h XDouble.h \
 ../../src/Terminal.h RandDouble.h ReturnDouble.h ../../src/ReturnData.h \
 ReturnBoolean.h SymbolicFitness.h ../../src/GPConfig.h
SymbolicFitness.o: SymbolicFitness.cpp SymbolicFitness.h \
 ../../src/GeneticProgram.h ../../src/ReturnData.h ../../src/Node.h \
 ../../src/Fitness.h ../../src/GeneticProgram.h ReturnDouble.h \
 ../../src/ReturnData.h XDouble.h ../../src/Terminal.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/Parsimony.h ../../src/Population.h ../../src/GPConfig.h
DivideDouble.o: DivideDouble.cpp DivideDouble.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
 ../../src/ReturnData.h
MinusDouble.o: MinusDouble.cpp MinusDouble.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
 ../../src/ReturnData.h
MultDouble.o: MultDouble.cpp MultDouble.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
 ../../src/ReturnData.h
PlusDouble.o: PlusDouble.cpp PlusDouble.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
 ../../src/ReturnData.h
XDouble.o: XDouble.cpp XDouble.h ../../src/Terminal.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h
RandDouble.o: RandDouble.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
 ../../src/Terminal.h ../../src/Parsimony.h ../../src/Population.h \
 ../../src/GPConfig.h RandDouble.h ../../src/Terminal.h ReturnDouble.h \
 ../../src/ReturnData.h
ReturnDouble.o: ReturnDouble.cpp ReturnDouble.h ../../src/ReturnData.h
ReturnBoolean.o: ReturnBoolean.cpp ReturnBoolean.h ../../src/ReturnData.h
If.o: If.cpp If.h ../../src/Function.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h \
 ReturnBoolean.h ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/Mutation.h \
 ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h
LessThan.o: LessThan.cpp LessThan.h ../../src/Function.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h \
 ReturnBoolean.h ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/Mutation.h \
 ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h
GreaterThan.o: GreaterThan.cpp GreaterThan.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
 ../../src/ReturnData.h ReturnBoolean.h ../../src/GPConfig.h \
 ../../src/Random.h ../../src/Crossover.h ../../src/GeneticProgram.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/Parsimony.h ../../src/Population.h ../../src/GPConfig.h
