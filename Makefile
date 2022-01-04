
CC=g++
CXX=g++
AR=ar -crs
INCLUDES=-Iinclude/
CXXFLAGS=-g -std=c++98 -m64 -fPIC -falign-functions=16
LDFLAGS=-rdynamic
LIBS=-ldl

all: libcpphook.a example/example1 example/example2

libcpphook.a: src/cpphook.cpp
	$(CXX) -c src/cpphook.cpp -o src/cpphook.o $(CXXFLAGS) $(INCLUDES)
	$(AR) libcpphook.a src/cpphook.o

example/example1: example/example1.cpp libcpphook.a
	$(CXX) -c example/example1.cpp -o example/example1.o $(CXXFLAGS) $(INCLUDES)
	$(CXX) example/example1.o -o example/example1 libcpphook.a $(LDFLAGS) $(LIBS)

example/example2: example/example2.cpp libcpphook.a
	$(CXX) -c example/example2.cpp -o example/example2.o $(CXXFLAGS) $(INCLUDES)
	$(CXX) example/example2.o -o example/example2 libcpphook.a $(LDFLAGS) $(LIBS) 

clean:
	rm -rf src/*.o example/*.o libcpphook.a example/example1 example/example2
