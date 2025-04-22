# Compiler and Flags
CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g -O3
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
DEPS =
OBJECTS = main.o
PROGRAM = ps7

.PHONY: all clean lint

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIB)


# Compile source files into object files
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

# Run cpplint
lint:
	cpplint *.cpp *.hpp

# Clean compiled files
clean:
	rm -f *.o $(PROGRAM) test $(PROGRAM).a massif.out.*
	