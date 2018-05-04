.SUFFIXES: .cpp $(SUFFIXES)

CC = g++
CFLAGS = -g 
DEFINES = -DUNIX #-DOLD_GCC          Add DOLD_GCC if you are using GCC 3.0 
                                    #or lesser, or if using another compiler
RM = rm
DIR = `pwd`
LIB  = -lrt -lsocket -lnsl -lpthread -L../../src -lrmitgp \
       -L/research/ai/dylanm/server/rcsoccersim-9.0.3/rcssserver -lrcssserver \
       -lz

INCLUDE  = -I../../src \
           -I/research/ai/dylanm/server/rcsoccersim-9.0.3/rcssserver/src \
           -I/research/ai/dylanm/server/rcsoccersim-9.0.3/rcssbase

OUTPUT = robocupgp 

OBJS  = main.o ReturnAction.o ReturnPower.o ReturnAngle.o \
        Dash.o Turn.o Kick.o ExecTwo.o Power.o Angle.o RobocupFitness.o \
        SoccerPlayer.o Marker.o MovableObject.o SoccerField.o

SRCS=$(OBJS:.o=.cpp)

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
