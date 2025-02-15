CXX = g++ -std=c++23

all: my_program

my_program: main.o client.o
	$(CXX) client.o main.o -o prog

main.o: main.cpp
	$(CXX) -c main.cpp

client.o: client.cpp
	$(CXX) -c client.cpp

clean:
	rm -f prog *.o
