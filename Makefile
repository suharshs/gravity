#Makefile for gravity program
#Author : Suharsh Sivakumar
#Date : 2/10/2012

CFLAGS = -c -g -Wall
LFLAGS = -lm -lopengl32 -lglu32 glut32.lib

BINARIES = gravity

all : $(BINARIES)

clean : 
	DEL *.o $(BINARIES)
	
gravity : ball.o field.o gravity.o
	g++ ball.o field.o gravity.o $(LFLAGS) -o gravity
	
gravity.o : gravity.cpp field.h ball.h
	g++ $(CFLAGS) gravity.cpp
	
field.o : field.cpp field.h ball.h
	g++ $(CFLAGS) field.cpp
	
ball.o : ball.cpp ball.h
	g++ $(CFLAGS) ball.cpp