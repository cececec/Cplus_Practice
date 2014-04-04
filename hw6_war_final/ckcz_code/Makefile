CC = g++
OPT = -O3
OPT = -g
WARN = -Wall
CFLAGS = $(WARN) $(INC) $(LIB)
CFLAGSGDB = $(OPT) $(WARN) $(INC) $(LIB)
EXE_NAME= main

# List all your .cc files here (source files, excluding header files)
lip_SRC = main.cpp 

# List corresponding compiled object files here (.o files)
lip_OBJ = main.o 
 
#################################

# default rule

all: sim
	@echo ""
	@echo ""
	@echo "======================="
	@echo "my work is done here..."


# rule for making hgq

hgq:  clean $(lip_OBJ)
	$(CC) -o $(EXE_NAME) $(CFLAGS) $(lip_OBJ) -lm
	@echo "-----------DONE WITH linking-----------"
	@echo "=========BEGIN========="


# generic rule for converting any .cc file to any .o file
 
.cc.o:
	$(CC) $(CFLAGS)  -c $*.cc


# type "make clean" to remove all .o files plus the hgq binary

sim: hgq
	time ./$(EXE_NAME) < final_input.txt

clean:
	rm -f *.o main


# type "make clobber" to remove all .o files (leaves hgq binary)

clobber:
	rm -f *.o

hgqgdb: clean $(lip_OBJ)
	$(CC) -g $(lip_SRC) -o $(EXE_NAME)

gdb: hgqgdb
	gdb $(EXE_NAME)
	
