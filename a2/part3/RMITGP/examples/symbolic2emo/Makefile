
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
        DivideDouble.o MinusDouble.o MultDouble.o PlusDouble.o XDouble.o RandDouble.o \
        ReturnDouble.o 

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

#depend: $(SRCS)
#	@(sed <Makefile '/^#--DEPENDENCIES--$$/,$$d'; \
#	echo '#--DEPENDENCIES--'; \
#	$(CC) -c -MM $(CFLAGS) $(CXXINCLUDE) $(INCLUDE) $(SRCS) \
#	) > Makefile.new
#	mv Makefile.new Makefile
#
#all:
#	g++ -g -I ../../src/ *.cpp -o symbolic2 ../../src/*.o
#clean:
#	rm symbolic2

