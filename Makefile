# smso: subspace optimazation
# smno: thesis layout, node overlap removal

CC = g++
SMSO_OBJS = mmio.o load_graph.o graph.o all_pair.o hde.o smso.o lap.o g_bound.o ortho.o subspace_iter.o two_d_stress.o
SMOR_OBJS = mmio.o load_graph.o graph.o smor.o
# executable name
OBJ_NAME = bin/main
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -framework OpenGL -lglfw3
I_E_PATHS = -I/usr/local/Cellar/eigen/3.2.4/include/eigen3/
IPATHS = -I/usr/local/Cellar/eigen/3.2.4/include/eigen3/ -I/usr/local/include -I/opt/X11/include
LPATHS = -L/usr/local/lib -L/opt/X11/lib


all: smso smor

mmio.o: src/mmio.h src/mmio.c
	gcc $(CFLAGS) src/mmio.c

load_graph.o: src/mmio.h src/load_graph.hpp src/load_graph.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/load_graph.cpp

graph.o: src/graph.hpp src/graph.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/graph.cpp

all_pair.o: src/all_pair.hpp src/graph.hpp src/all_pair.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/all_pair.cpp

hde.o: src/hde.hpp src/graph.hpp src/hde.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/hde.cpp

lap.o: src/lap.hpp src/graph.hpp src/lap.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/lap.cpp

g_bound.o: src/g_bound.hpp src/g_bound.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/g_bound.cpp

ortho.o: src/ortho.hpp src/ortho.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/ortho.cpp

subspace_iter.o: src/g_bound.hpp src/ortho.hpp src/subspace_iter.hpp src/subspace_iter.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/subspace_iter.cpp

two_d_stress.o: src/two_d_stress.hpp src/two_d_stress.cpp
	$(CC) $(CFLAGS) $(I_E_PATHS) src/two_d_stress.cpp

smso.o: src/all_pair.hpp src/hde.hpp src/subspace_iter.hpp src/two_d_stress.hpp src/smso.cpp
	$(CC) $(CFLAGS) $(IPATHS) src/smso.cpp

smor.o: src/smso.cpp
	$(CC) $(CFLAGS) $(IPATHS) src/smor.cpp



smso: $(SMSO_OBJS)
	$(CC) $(SMSO_OBJS) $(LPATHS) $(LFLAGS) -o bin/smso

smor: $(SMOR_OBJS)
	$(CC) $(SMOR_OBJS) $(LPATHS) $(LFLAGS) -o bin/smor

clean:
	rm bin/smso bin/smor *.o