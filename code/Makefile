#------------------------------------------------------------------------------
# Makefile for node.c 
#------------------------------------------------------------------------------

ADT     = node
EXEBIN  = $(ADT)Client
SOURCES = $(ADT).cpp $(EXEBIN).cpp Makefile node.h 
OBJECTS = $(ADT).o $(EXEBIN).o
HEADERS = $(ADT).h

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	g++ -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 
