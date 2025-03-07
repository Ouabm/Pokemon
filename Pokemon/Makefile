# Le compilateur
CC = g++

# Options du compilateur
CFLAGS = -std=c++11 -Wall -g 

# Bibliothèques SFML nécessaires
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Les fichiers source
SRC = pokemon.cpp graphique.cpp main.cpp move.cpp PokemonDB.cpp Game_master.cpp

# Les fichiers objets
OBJ = $(SRC:.cpp=.o)

# Le nom de l'exécutable
EXEC = jeu

# Règle par défaut
all: $(EXEC)

# Génération de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)

# Exécution avec vérification de DISPLAY
RUN_DISPLAY := $(if $(DISPLAY),$(DISPLAY),:0)

run: $(EXEC)
	@echo "Exécution de $(EXEC) avec DISPLAY=$(RUN_DISPLAY)"; \
	DISPLAY=$(RUN_DISPLAY) ./$(EXEC)

.PHONY: all clean run