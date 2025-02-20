CXX = g++ -std=c++23

all: my_program test

my_program: main.o restclient.o
	$(CXX) restclient.o main.o -o prog

main.o: main.cpp
	$(CXX) -c main.cpp

test: test.o restclient.o
	$(CXX) restclient.o test.o -o test

test.o: test.cpp
	$(CXX) -c test.cpp

restclient.o: restclient.cpp
	$(CXX) -c restclient.cpp

clean:
	rm -f prog test *.o
