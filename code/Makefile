#------------------------------------------------------------------------------
# Makefile for node.cpp
#------------------------------------------------------------------------------

ADT_NAME  = node
SOURCES   = $(ADT_NAME).cpp
OBJECTS   = $(ADT_NAME).o 
HEADERS   = $(ADT_NAME).h
EXEBIN    = $(ADT_NAME)
FLAGS     = 

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	g++ -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 


