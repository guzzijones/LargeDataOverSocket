###########
#add new depend files below 
#add new ones here object files relating to .cpp files
DEPS=client.o 

EXE=driver

#######################
#DO NOT EDIT BELOW
#######################

###########
#variables
###########
CC=g++
CPPFLAGS= -Wall -c -I./include/
CPPFLAGS+= -MD -MP -std=c++0x
LFLAGS= -Wall 
VPATH=src

all: $(EXE)

debug: CC+= -DDEBUG -g 
debug: $(EXE)
###########
#linker
###########
$(EXE): $(DEPS)
	$(CC) $(LFLAGS) $(DEPS) -o $(EXE).exe

##########
#implicit calls for all object file builds
#########

###########
#include dependency files 
###########
-include $(DEPS:%.o=%.d)

