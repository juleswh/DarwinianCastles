
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
OBJ = $(B_DIR)/CApp.o $(B_DIR)/Physics.o $(B_DIR)/Brick.o

########
#   Objects

$(B_DIR)/CApp.o : $(S_DIR)/CApp.cpp $(S_DIR)/CApp.h $(S_DIR)/Global.h $(S_DIR)/Physics.h
	$(CC) $(CC_OPTS) $(S_DIR)/CApp.cpp -o $(B_DIR)/CApp.o

$(B_DIR)/Physics.o : $(S_DIR)/Physics.cpp $(S_DIR)/Physics.h
	$(CC) $(CC_OPTS) $(S_DIR)/Physics.cpp -o $(B_DIR)/Physics.o

$(B_DIR)/Brick.o : $(S_DIR)/Brick.cpp $(S_DIR)/Brick.h
	$(CC) $(CC_OPTS) $(S_DIR)/Brick.cpp -o $(B_DIR)/Brick.o

########
#   Main build rule     
Build : $(OBJ) Makefile
	$(CC) $(LN_OPTS) -o $(EXEC) $(OBJ) $(LN_LIB)

all : Build

clean:
	rm -f $(OBJ) $(EXEC)
