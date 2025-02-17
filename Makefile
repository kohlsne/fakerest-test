CXX = g++ -std=c++23

all: my_program

my_program: main.o restclient.o
	$(CXX) restclient.o main.o -o prog

main.o: main.cpp
	$(CXX) -c main.cpp

restclient.o: restclient.cpp
	$(CXX) -c restclient.cpp

clean:
	rm -f prog *.o
