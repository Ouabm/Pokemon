CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Iinclude/states

SRCS = src/main.cpp src/GameStateManager.cpp src/ResourceManager.cpp src/ElementUI.cpp src/PokemonManager.cpp src/MoveManager.cpp src/Type.cpp  \
       src/states/MenuState.cpp src/states/SelectionState.cpp src/states/BattleState.cpp src/states/EndState.cpp

# On génère les .o dans le répertoire build
OBJS = $(SRCS:src/%.cpp=build/%.o)

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

EXEC = game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LIBS)

# La règle pour compiler chaque fichier .cpp en .o dans le répertoire build
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)  # Crée tous les répertoires nécessaires pour $@ (le chemin complet du .o)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(EXEC)
