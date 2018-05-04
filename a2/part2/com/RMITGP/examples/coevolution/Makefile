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

OUTPUT = pred-prey

OBJS  = PredatorPreyFitness.o \
        ReturnMove.o ReturnCoord.o ReturnBoolean.o \
        MoveUp.o MoveDown.o MoveLeft.o MoveRight.o \
        GetPredX.o GetPredY.o GetPreyX.o GetPreyY.o \
        If.o LessThan.o GreaterThan.o And.o Or.o \
        main.o

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
	$(CC) -c -M $(CFLAGS) $(CXXINCLUDE) $(INCLUDE) $(SRCS) \
	) > Makefile.new
	mv Makefile.new Makefile

#--DEPENDENCIES--
PredatorPreyFitness.o: PredatorPreyFitness.cpp /usr/include/float.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 PredatorPreyFitness.h ../../src/GeneticProgram.h \
 ../../src/ReturnData.h ../../src/Node.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/CoEvolutionFitness.h ../../src/Fitness.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/Terminal.h ../../src/NodeVector.h \
 ../../src/NodeVector.cpp
ReturnMove.o: ReturnMove.cpp ReturnMove.h ../../src/ReturnData.h
ReturnCoord.o: ReturnCoord.cpp ReturnCoord.h ../../src/ReturnData.h
ReturnBoolean.o: ReturnBoolean.cpp ReturnBoolean.h \
 ../../src/ReturnData.h
MoveUp.o: MoveUp.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 MoveUp.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
MoveDown.o: MoveDown.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 MoveDown.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
MoveLeft.o: MoveLeft.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 MoveLeft.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
MoveRight.o: MoveRight.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 MoveRight.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
GetPredX.o: GetPredX.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 GetPredX.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnCoord.h \
 PredatorPreyFitness.h ../../src/GeneticProgram.h \
 ../../src/CoEvolutionFitness.h ../../src/Fitness.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/NodeVector.h ../../src/NodeVector.cpp
GetPredY.o: GetPredY.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 GetPredY.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnCoord.h \
 PredatorPreyFitness.h ../../src/GeneticProgram.h \
 ../../src/CoEvolutionFitness.h ../../src/Fitness.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/NodeVector.h ../../src/NodeVector.cpp
GetPreyX.o: GetPreyX.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 GetPreyX.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnCoord.h \
 PredatorPreyFitness.h ../../src/GeneticProgram.h \
 ../../src/CoEvolutionFitness.h ../../src/Fitness.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/NodeVector.h ../../src/NodeVector.cpp
GetPreyY.o: GetPreyY.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 GetPreyY.h ../../src/Terminal.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnCoord.h \
 PredatorPreyFitness.h ../../src/GeneticProgram.h \
 ../../src/CoEvolutionFitness.h ../../src/Fitness.h ReturnMove.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/Mutation.h ../../src/Selection.h ../../src/NodeSet.h \
 ../../src/Function.h ../../src/NodeVector.h ../../src/NodeVector.cpp
If.o: If.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 If.h ../../src/Function.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnMove.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
LessThan.o: LessThan.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 LessThan.h ../../src/Function.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnCoord.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
GreaterThan.o: GreaterThan.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 GreaterThan.h ../../src/Function.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnCoord.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
And.o: And.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 And.h ../../src/Function.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
Or.o: Or.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 Or.h ../../src/Function.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Node.h ../../src/ReturnData.h ReturnBoolean.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
 ../../src/GeneticProgram.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp
main.o: main.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 ../../src/CoEvolutionPopulation.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/fstream \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/fstream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/string \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstddef \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/straits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cctype \
 /usr/include/ctype.h /usr/include/iso/ctype_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstring \
 /usr/include/string.h /usr/include/iso/string_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_alloc.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 ../../src/GeneticProgram.h ../../src/ReturnData.h ../../src/Node.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/vector \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_algobase.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_pair.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/type_traits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/syslimits.h \
 /usr/include/limits.h /usr/include/iso/limits_iso.h \
 /usr/include/sys/int_limits.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/new \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/exception \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_construct.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_uninitialized.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_vector.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_bvector.h \
 ../../src/Mutation.h ../../src/Crossover.h ../../src/Selection.h \
 ../../src/Population.h ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Fitness.h ../../src/NodeSet.h ../../src/Function.h \
 ../../src/Terminal.h ../../src/NodeVector.h ../../src/NodeVector.cpp \
 PredatorPreyFitness.h ../../src/CoEvolutionFitness.h ReturnMove.h \
 ../../src/ProgramGenerator.h If.h LessThan.h GreaterThan.h And.h Or.h \
 GetPredX.h GetPredY.h GetPreyX.h GetPreyY.h MoveUp.h MoveDown.h \
 MoveLeft.h MoveRight.h ReturnCoord.h ReturnBoolean.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdio \
 /usr/include/stdio.h /usr/include/iso/stdio_iso.h \
 /usr/include/sys/va_list.h /usr/include/stdio_tag.h \
 /usr/include/stdio_impl.h
