.SUFFIXES: .cpp $(SUFFIXES)

CC = g++
#CC = /usr/local/pkg/gcc-3-1/bin/g++
#CC = cxx                           #FOR VPAC
#CFLAGS = -g -std gnu               #FOR VPAC
CFLAGS = -g -pedantic -Wall
DEFINES = -DUNIX #-DOLD_GCC          Add DOLD_GCC if you are using GCC 3.0 
                                    #or lesser, or if using another compiler

RM = rm
DIR = `pwd`
LIB = -L../../src/ -lrmitgp

OUTPUT = maxgp

OBJS  = MaxFitness.o ReturnDouble.o \
        MultDouble.o PlusDouble.o PointFive.o main.o


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
MaxFitness.o: MaxFitness.cpp MaxFitness.h ../../src/GeneticProgram.h \
  ../../src/ReturnData.h ../../src/Node.h ../../src/Fitness.h \
  ../../src/GeneticProgram.h ../../src/GPConfig.h ../../src/Random.h \
  ../../src/Crossover.h ../../src/Mutation.h ../../src/Selection.h \
  ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
  ../../src/Terminal.h ReturnDouble.h ../../src/ReturnData.h
ReturnDouble.o: ReturnDouble.cpp ReturnDouble.h ../../src/ReturnData.h
MultDouble.o: MultDouble.cpp MultDouble.h ../../src/Function.h \
  ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
  ../../src/ReturnData.h
PlusDouble.o: PlusDouble.cpp PlusDouble.h ../../src/Function.h \
  ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
  ../../src/ReturnData.h
PointFive.o: PointFive.cpp ../../src/GPConfig.h ../../src/Random.h \
  ../../src/Crossover.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
  ../../src/Node.h ../../src/Mutation.h ../../src/Selection.h \
  ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
  ../../src/Terminal.h PointFive.h ../../src/Terminal.h ReturnDouble.h \
  ../../src/ReturnData.h
main.o: main.cpp ../../src/Population.h ../../src/GeneticProgram.h \
  ../../src/ReturnData.h ../../src/Node.h ../../src/Mutation.h \
  ../../src/Crossover.h ../../src/Selection.h ../../src/GPConfig.h \
  ../../src/Random.h ../../src/Fitness.h ../../src/NodeSet.h \
  ../../src/Function.h ../../src/Terminal.h ../../src/Fitness.h \
  ../../src/GeneticProgram.h ../../src/NodeSet.h \
  ../../src/ProgramGenerator.h ../../src/NodeVector.h PlusDouble.h \
  ../../src/Function.h MultDouble.h PointFive.h ../../src/Terminal.h \
  ReturnDouble.h ../../src/ReturnData.h MaxFitness.h ../../src/GPConfig.h
