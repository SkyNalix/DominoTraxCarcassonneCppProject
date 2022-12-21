SRC_DIRS := src/common src/DominoCarre src/Trax src
# ajouter les repertoires ici ^ 

.SILENT:
OBJ_DIR = ./obj
EXE_NAME = go

CPP_FILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst %.cpp,%.o,$(CPP_FILES))
OBJECTS_IN_OBJ_DIR = $(addprefix $(OBJ_DIR)/, $(notdir $(OBJECTS)))

CPP = g++ --std=c++11 -Wall
SFML_ARGS = -lsfml-graphics -lsfml-window -lsfml-system

all: clean init $(OBJECTS)
	$(CPP) -o $(EXE_NAME) $(OBJECTS_IN_OBJ_DIR) $(SFML_ARGS)
	echo "Lancez avec ./$(EXE_NAME)"
	./go

%.o: %.cpp %.hpp
	$(CPP) $(addprefix -I,$(SRC_DIRS)) -c $*.cpp -o $(OBJ_DIR)/$(notdir $@)

init:
	mkdir -p $(OBJ_DIR)

clean :
	rm -rf $(EXE_NAME) $(OBJ_DIR) 