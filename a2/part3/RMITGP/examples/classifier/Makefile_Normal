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

OUTPUT = classifier 

OBJS  = main.o ClassificationFitness.o \
		Attribute.o \
        PlusDouble.o MinusDouble.o MultDouble.o DivideDouble.o \
        ReturnDouble.o ReturnBoolean.o ReturnInt.o \
		RandDouble.o RandInt.o \
        If.o LessThan.o GreaterThan.o Between.o Equal.o \
		Diff.o \
		AbsoluteDouble.o \
		ReturnTIndex.o \
		ReturnTOperation.o \
		RandSOperation.o ReturnSOperation.o \
		RandVIndex.o ReturnVIndex.o \
		VOI.o \
		Coordinate.o Rect.o \
		ReturnCoordinate.o ReturnRect.o \
		AOI.o Data.o\
		#TempDFunctionP.o TempDFunctionD.o \
		TempTerminalC.o TempTerminalD.o \
		RandTOperation.o RandTIndex.o
	
SRCS=$(OBJS:.o=.cpp)

INCLUDE = -I../../src/

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $(DEFINES) $(CXXINCLUDE) $(INCLUDE) -I. $*.cpp

clean:
	$(RM) -f $(OBJS) $(OUTPUT)

gclean:
	$(RM) -f *.gen.gz run-log.txt

objects:
	@for f in $(OBJS); do echo $(DIR)/$$f; done

depend: $(SRCS)
	@(sed <Makefile '/^#--DEPENDENCIES--$$/,$$d'; \
	echo '#--DEPENDENCIES--'; \
	$(CC) -c -MM $(CFLAGS) $(CXXINCLUDE) $(INCLUDE) $(SRCS) \
	) > Makefile.new
	mv Makefile.new Makefile

#--DEPENDENCIES--
main.o: main.cpp main.h ../../src/Population.h ../../src/GeneticProgram.h \
 ../../src/ReturnData.h ../../src/Node.h ../../src/Mutation.h ../../src/Crossover.h \
 ../../src/Selection.h ../../src/GPConfig.h ../../src/Random.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h ../../src/EMOPopulation.h ../../src/Fitness.h \
 ../../src/GeneticProgram.h ../../src/NodeSet.h ../../src/ProgramGenerator.h \
 ../../src/NodeVector.h Attribute.h ../../src/Terminal.h RandDouble.h RandInt.h \
 RandSOperation.h RandTIndex.h RandVIndex.h Coordinate.h Rect.h \
 PlusDouble.h ../../src/Function.h MinusDouble.h MultDouble.h DivideDouble.h \
 AbsoluteDouble.h If.h LessThan.h GreaterThan.h Equal.h Between.h Diff.h \
 ../../src/GPConfig.h ReturnDouble.h ../../src/ReturnData.h AOI.h \
 ReturnSOperation.h ReturnCoordinate.h ReturnRect.h VOI.h ReturnVIndex.h \
 ReturnBoolean.h ReturnInt.h ReturnTOperation.h ReturnTIndex.h \
 ClassificationFitness.h Testing.h Data.h
ClassificationFitness.o: ClassificationFitness.cpp \
 ClassificationFitness.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Fitness.h ../../src/GeneticProgram.h ReturnDouble.h \
 ../../src/ReturnData.h Attribute.h ../../src/Terminal.h ../../src/GPConfig.h \
 ../../src/Random.h ../../src/Crossover.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/Parsimony.h ../../src/Population.h ../../src/GPConfig.h \
 ../../src/CovariantTarpeian.h ../../src/DynamicDepthLimit.h
Attribute.o: Attribute.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h Attribute.h ../../src/Terminal.h ReturnDouble.h \
 ../../src/ReturnData.h
PlusDouble.o: PlusDouble.cpp PlusDouble.h ../../src/Function.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h
MinusDouble.o: MinusDouble.cpp MinusDouble.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h
MultDouble.o: MultDouble.cpp MultDouble.h ../../src/Function.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h
DivideDouble.o: DivideDouble.cpp DivideDouble.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h
ReturnDouble.o: ReturnDouble.cpp ReturnDouble.h ../../src/ReturnData.h
ReturnBoolean.o: ReturnBoolean.cpp ReturnBoolean.h ../../src/ReturnData.h
ReturnInt.o: ReturnInt.cpp ReturnInt.h ../../src/ReturnData.h
RandDouble.o: RandDouble.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h RandDouble.h ../../src/Terminal.h ReturnDouble.h \
 ../../src/ReturnData.h
RandInt.o: RandInt.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h RandInt.h ../../src/Terminal.h ReturnInt.h \
 ../../src/ReturnData.h
If.o: If.cpp If.h ../../src/Function.h ../../src/Node.h ../../src/ReturnData.h \
 ReturnDouble.h ../../src/ReturnData.h ReturnBoolean.h ../../src/GPConfig.h \
 ../../src/Random.h ../../src/Crossover.h ../../src/GeneticProgram.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h
LessThan.o: LessThan.cpp LessThan.h ../../src/Function.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/Parsimony.h ../../src/Population.h ../../src/GPConfig.h \
 ../../src/CovariantTarpeian.h ../../src/DynamicDepthLimit.h
GreaterThan.o: GreaterThan.cpp GreaterThan.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h \
 ReturnBoolean.h ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/Parsimony.h ../../src/Population.h ../../src/GPConfig.h \
 ../../src/CovariantTarpeian.h ../../src/DynamicDepthLimit.h
Between.o: Between.cpp Between.h ../../src/Function.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/Parsimony.h ../../src/Population.h ../../src/GPConfig.h \
 ../../src/CovariantTarpeian.h ../../src/DynamicDepthLimit.h
Equal.o: Equal.cpp Equal.h ../../src/Function.h ../../src/Node.h \
 ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/Parsimony.h ../../src/Population.h ../../src/GPConfig.h \
 ../../src/CovariantTarpeian.h ../../src/DynamicDepthLimit.h
Diff.o: Diff.cpp Diff.h ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h ReturnDouble.h ../../src/ReturnData.h \
 ../../src/Function.h ClassificationFitness.h ../../src/GeneticProgram.h \
 ../../src/Fitness.h
AbsoluteDouble.o: AbsoluteDouble.cpp AbsoluteDouble.h ../../src/Function.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h ../../src/ReturnData.h
RandTIndex.o: RandTIndex.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h RandTIndex.h ../../src/Terminal.h ReturnTIndex.h \
 ../../src/ReturnData.h
ReturnTIndex.o: ReturnTIndex.cpp ReturnTIndex.h ../../src/ReturnData.h
ReturnTOperation.o: ReturnTOperation.cpp ReturnTOperation.h \
 ../../src/ReturnData.h
RandSOperation.o: RandSOperation.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h RandSOperation.h ../../src/Terminal.h \
 ReturnSOperation.h ../../src/ReturnData.h
ReturnSOperation.o: ReturnSOperation.cpp ReturnSOperation.h \
 ../../src/ReturnData.h
RandVIndex.o: RandVIndex.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h RandVIndex.h ../../src/Terminal.h ReturnVIndex.h \
 ../../src/ReturnData.h
ReturnVIndex.o: ReturnVIndex.cpp ReturnVIndex.h ../../src/ReturnData.h
VOI.o: VOI.cpp VOI.h ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/ReturnData.h ../../src/Node.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h ../../src/Function.h ReturnDouble.h \
 ../../src/ReturnData.h ReturnSOperation.h ReturnVIndex.h \
 ClassificationFitness.h ../../src/GeneticProgram.h ../../src/Fitness.h
Coordinate.o: Coordinate.cpp ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h Coordinate.h ../../src/Terminal.h \
 ReturnCoordinate.h ../../src/ReturnData.h
Rect.o: Rect.cpp ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/ReturnData.h ../../src/Node.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h Rect.h ../../src/Terminal.h ReturnRect.h \
 ../../src/ReturnData.h
ReturnCoordinate.o: ReturnCoordinate.cpp ReturnCoordinate.h \
 ../../src/ReturnData.h
ReturnRect.o: ReturnRect.cpp ReturnRect.h ../../src/ReturnData.h
AOI.o: AOI.cpp AOI.h ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/ReturnData.h ../../src/Node.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/Terminal.h ../../src/Parsimony.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/CovariantTarpeian.h \
 ../../src/DynamicDepthLimit.h ../../src/Function.h ReturnDouble.h \
 ../../src/ReturnData.h ReturnSOperation.h ReturnCoordinate.h ReturnRect.h \
 ClassificationFitness.h ../../src/GeneticProgram.h ../../src/Fitness.h
Data.o: Data.cpp Data.h
