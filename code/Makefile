#------------------------------------------------------------------------------
# Makefile for any ADT and its test client
#------------------------------------------------------------------------------

ADT_NAME  = node
SOURCES   = $(ADT_NAME).cpp $(ADT_NAME)Client.cpp
OBJECTS   = $(ADT_NAME).o $(ADT_NAME)Client.o
HEADERS   = $(ADT_NAME).h
EXEBIN    = $(ADT_NAME)Client
FLAGS     = -std=c++11

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	g++ -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 


