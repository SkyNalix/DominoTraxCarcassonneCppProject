CPP=g++ --std=c++11 -Wall
CC= $(CPP) -c
OBJECTS= main.o Bord.o BordDomino.o Tuile.o Terrain.o
.SILENT: clean

all : clean $(OBJECTS)
	$(CPP) -o go $(OBJECTS) -lsfml-graphics -lsfml-window -lsfml-system
	./go

main.o: main.cpp main.hpp
	$(CC) main.cpp

Bord.o: Bord.cpp Bord.hpp
	$(CC) Bord.cpp

BordDomino.o: BordDomino.cpp BordDomino.hpp
	$(CC) BordDomino.cpp

Tuile.o: Tuile.cpp Tuile.hpp
	$(CC) Tuile.cpp

Terrain.o: Terrain.cpp Terrain.hpp
	$(CC) Terrain.cpp

clean :
	rm -f *.o go