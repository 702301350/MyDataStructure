CXX=g++
CXXFLAGS=-std=c++11 -g
OBJECT=myString.o main.o
TARGET=main.exe

ALL:
	${CXX} src/*.cpp main.cpp -I ./src/ -o ${TARGET} ${CXXFLAGS}