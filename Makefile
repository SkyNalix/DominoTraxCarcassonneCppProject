SRC_DIRS :=  src/DominoCarre src
# ajouter les repertoires ici ^ 

.SILENT:
CPP_FILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst %.cpp,%.o,$(CPP_FILES))
OBJECTS_IN_OBJ_DIR = $(addprefix obj/, $(notdir $(OBJECTS)))
OBJ_DIR = ./obj

CPP = g++ --std=c++11 -Wall
SFML_ARGS = -lsfml-graphics -lsfml-window -lsfml-system
EXE_NAME = go

all: $(OBJECTS)
	$(CPP) -o $(EXE_NAME) $(OBJECTS_IN_OBJ_DIR) $(SFML_ARGS)
	echo "Lancez avec ./$(EXE_NAME)"

%.o: %.cpp %.hpp
	mkdir -p $(OBJ_DIR)
	$(CPP) $(addprefix -I,$(SRC_DIRS)) -c $*.cpp -o $(OBJ_DIR)/$(notdir $@)


clean :
	rm -rf $(EXE_NAME) $(OBJ_DIR) 