CC = g++
OBJS = src/main.cpp
# executable name
OBJ_NAME = bin/main

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/usr/local/Cellar/eigen/3.2.4/include/eigen3/

all: $(OBJS)
	$(CC) $(INCLUDE_PATHS) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

clean:
	rm bin/main