# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
Main: Main.o MasterMind.o Board.o EColor.o
	$(CC) $(CFLAGS) -o Main Main.o MasterMind.o Board.o EColor.o
 
# The main.o target can be written more simply
 
Main.o: Main.cpp MasterMind.hpp
	$(CC) $(CFLAGS) -c Main.cpp
 
MasterMind.o: MasterMind.hpp
 
Board.o: Board.hpp

EColor.o: EColor.hpp

run:
	./Main

clean:
	rm -rf *.o
	rm -rf Main
