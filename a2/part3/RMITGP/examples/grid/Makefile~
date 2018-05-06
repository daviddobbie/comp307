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

OUTPUT = symbolicgp

OBJS  = SymbolicFitness.o \
        DivideDouble.o MinusDouble.o MultDouble.o PlusDouble.o XDouble.o \
        RandDouble.o ReturnDouble.o main.o


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
SymbolicFitness.o: SymbolicFitness.cpp /usr/include/float.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/math.h \
 /usr/include/math.h /usr/include/iso/math_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/fstream \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/fstream.h \
 SymbolicFitness.h ../../src/GeneticProgram.h ../../src/ReturnData.h \
 ../../src/Node.h \
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
 ../../src/Fitness.h ../../src/GPConfig.h ../../src/Random.h \
 ../../src/Crossover.h ../../src/Mutation.h ../../src/Selection.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp ReturnDouble.h \
 XDouble.h
DivideDouble.o: DivideDouble.cpp \
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
 DivideDouble.h ../../src/Function.h \
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
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h \
 /usr/include/float.h
MinusDouble.o: MinusDouble.cpp \
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
 MinusDouble.h ../../src/Function.h \
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
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h
MultDouble.o: MultDouble.cpp \
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
 MultDouble.h ../../src/Function.h \
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
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h
PlusDouble.o: PlusDouble.cpp \
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
 PlusDouble.h ../../src/Function.h \
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
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h
XDouble.o: XDouble.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdio \
 /usr/include/stdio.h /usr/include/iso/stdio_iso.h \
 /usr/include/sys/va_list.h /usr/include/stdio_tag.h \
 /usr/include/stdio_impl.h \
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
 XDouble.h ../../src/Terminal.h \
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
 ../../src/Node.h ../../src/ReturnData.h ReturnDouble.h
RandDouble.o: RandDouble.cpp \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdio \
 /usr/include/stdio.h /usr/include/iso/stdio_iso.h \
 /usr/include/sys/feature_tests.h /usr/include/sys/isa_defs.h \
 /usr/include/sys/va_list.h /usr/include/stdio_tag.h \
 /usr/include/stdio_impl.h \
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
 /usr/include/stdlib.h /usr/include/iso/stdlib_iso.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/assert.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iterator \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_relops.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/stl_iterator.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/std/bastring.cc \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Crossover.h \
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
 ../../src/Mutation.h ../../src/Selection.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp RandDouble.h \
 ReturnDouble.h
ReturnDouble.o: ReturnDouble.cpp ReturnDouble.h ../../src/ReturnData.h
main.o: main.cpp ../../src/GridPopulation.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/iostream.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/streambuf.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/libio.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../sparc-sun-solaris2.8/include/_G_config.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/include/stddef.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/fstream \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/fstream.h \
 ../../src/Population.h ../../src/GeneticProgram.h \
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
 ../../src/Mutation.h ../../src/Crossover.h ../../src/Selection.h \
 ../../src/GPConfig.h ../../src/Random.h ../../src/Fitness.h \
 ../../src/NodeSet.h ../../src/Function.h ../../src/Terminal.h \
 ../../src/NodeVector.h ../../src/NodeVector.cpp \
 ../../src/ProgramGenerator.h PlusDouble.h MinusDouble.h MultDouble.h \
 DivideDouble.h XDouble.h RandDouble.h ReturnDouble.h \
 SymbolicFitness.h \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdlib \
 /usr/local/pkg/gcc-2.95.2/lib/gcc-lib/sparc-sun-solaris2.8/2.95.2/../../../../include/g++-3/cstdio \
 /usr/include/stdio.h /usr/include/iso/stdio_iso.h \
 /usr/include/sys/va_list.h /usr/include/stdio_tag.h \
 /usr/include/stdio_impl.h
