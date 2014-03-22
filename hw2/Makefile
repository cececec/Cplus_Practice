CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)

# List all your .cc files here (source files, excluding header files)
lip_SRC = main.cc 

# List corresponding compiled object files here (.o files)
lip_OBJ = main.o 
 
#################################

# default rule

all: hgq
	@echo "my work is done here..."


# rule for making hgq

hgq: $(lip_OBJ)
	$(CC) -o hgq $(CFLAGS) $(lip_OBJ) -lm
	@echo "-----------DONE WITH linking-----------"


# generic rule for converting any .cc file to any .o file
 
.cc.o:
	$(CC) $(CFLAGS)  -c $*.cc


# type "make clean" to remove all .o files plus the hgq binary

clean:
	rm -f *.o hgq


# type "make clobber" to remove all .o files (leaves hgq binary)

clobber:
	rm -f *.o


