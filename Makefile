CPP=g++ --std=c++11 -Wall
CC= $(CPP) -c
OBJECTS= main.o Bord.o BordDomino.o Tuile.o

all : $(OBJECTS)
	$(CPP) -o go $(OBJECTS)
	

main.o: main.cpp main.hpp
	$(CC) -c main.cpp

Bord.o: Bord.cpp Bord.hpp
	$(CC) -c Bord.cpp

BordDomino.o: BordDomino.cpp BordDomino.hpp
	$(CC) -c BordDomino.cpp

Tuile.o: Tuile.cpp Tuile.hpp
	$(CC) -c Tuile.cpp

clean :
	rm *.o go