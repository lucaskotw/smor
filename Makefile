CC = g++
OBJS = src/main.cpp
# executable name
OBJ_NAME = bin/main

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

clean:
	rm bin/main