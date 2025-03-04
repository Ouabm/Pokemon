CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude/core -Iinclude/ui

SRC = src/core/type.cpp src/core/pokemon_db.cpp src/core/pokemon.cpp src/core/move_db.cpp src/core/move.cpp src/core/trainer.cpp src/core/battle.cpp src/core/game.cpp src/core/main.cpp
OBJ_DIR = build
OBJ = $(SRC:src/core/%.cpp=$(OBJ_DIR)/%.o)
EXEC = pokepute

# Cible par défaut
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Compilation des fichiers sources dans le dossier build
$(OBJ_DIR)/%.o: src/core/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean
