# Email: yedidea9@gmail.com

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g
SOURCES = Graph.cpp Algorithms.cpp Queue.cpp PriorityQueue.cpp UnionFind.cpp
OBJECTS = Graph.o Algorithms.o Queue.o PriorityQueue.o UnionFind.o

.PHONY: Main test valgrind clean

Main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o Main main.o $(OBJECTS)
	./Main

test: test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o test test.o $(OBJECTS)
	./test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o Main test
