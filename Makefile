
#
#   Default make file
#

########
#   Directories
S_DIR=src
B_DIR=build

########
#   Output
EXEC=bin/out

# default build settings
##  debug setup
CC_OPTS=-c -Wall 
LN_OPTS=
CC=g++
LN_LIB=-lsfml-graphics -lsfml-window -lsfml-system -lBox2D
##  release setup
#C_OPTS=-c -pipe
#LN_OPTS=
#CC=g++

########
#   This is the default action
all:build

########
#   Object list
#
OBJ = $(B_DIR)/Test.o $(B_DIR)/Object.o $(B_DIR)/Physics.o $(B_DIR)/ObjectManager.o $(B_DIR)/RandomGen.o

########
#   Objects

$(B_DIR)/Test.o : $(S_DIR)/Test.cpp $(S_DIR)/Test.h $(S_DIR)/Global.h $(S_DIR)/Physics.h
	$(CC) $(CC_OPTS) $(S_DIR)/Test.cpp -o $(B_DIR)/Test.o

$(B_DIR)/Physics.o : $(S_DIR)/Physics.cpp $(S_DIR)/Physics.h
	$(CC) $(CC_OPTS) $(S_DIR)/Physics.cpp -o $(B_DIR)/Physics.o

$(B_DIR)/Object.o : $(S_DIR)/Object.cpp $(S_DIR)/Object.h
	$(CC) $(CC_OPTS) $(S_DIR)/Object.cpp -o $(B_DIR)/Object.o

$(B_DIR)/ObjectManager.o : $(S_DIR)/ObjectManager.cpp $(S_DIR)/ObjectManager.h
	$(CC) $(CC_OPTS) $(S_DIR)/ObjectManager.cpp -o $(B_DIR)/ObjectManager.o

$(B_DIR)/RandomGen.o : $(S_DIR)/RandomGen.cpp $(S_DIR)/RandomGen.h
	$(CC) $(CC_OPTS) $(S_DIR)/RandomGen.cpp -o $(B_DIR)/RandomGen.o

########
#   Main build rule     
Build : $(OBJ) Makefile
	$(CC) $(LN_OPTS) -o $(EXEC) $(OBJ) $(LN_LIB)

all : Build

clean:
	rm -f $(OBJ) $(EXEC)
