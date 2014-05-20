CC = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(WARN) $(INC) $(LIB)
EXE_NAME= exec

# List all your .cc files here (source files, excluding header files)
lip_SRC = ./*.cc 

# List corresponding compiled object files here (.o files)
lip_OBJ = ./*.o 
 
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
	./$(EXE_NAME) < input.txt

clean:
	rm -f *.o exec


# type "make clobber" to remove all .o files (leaves hgq binary)

clobber:
	rm -f *.o


