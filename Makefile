# Compilateur + options
CC = g++
CFLAGS = -std=c++11 -Wall -g -Iinclude

# Bibliothèques SFML nécessaires
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Dossiers
SRC_DIR = src
BUILD_DIR = build

# Les fichiers source & objet
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Le nom de l'exécutable
EXEC = pokemon

# Règle par défaut
all: $(EXEC)

# Génération de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier build si inexistant
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)