CXX=g++
CXXFLAGS=-std=c++11 -g
OBJECT=myString.o main.o
TARGET=main.exe

ALL:
	${CXX} src/*.hpp src/*.cpp main.cpp -o ${TARGET} ${CXXFLAGS}
