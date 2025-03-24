# Compiler et options
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Iinclude/states -MMD -MP

# Répertoires sources et inclusions
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
STATES_DIR = include/states

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/states/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Bibliothèques
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Nom de l'exécutable
EXEC = pokemon

# Règle par défaut : construire l'exécutable
all: $(EXEC)

# Génération de l'exécutable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LIBS)

# Compilation des fichiers .cpp en .o et génération des dépendances .d
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)  # Crée tous les répertoires nécessaires pour $@
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Inclure les dépendances générées
-include $(DEPS)

# Nettoyage des fichiers générés
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

# Cibles supplémentaires
.PHONY: all clean
