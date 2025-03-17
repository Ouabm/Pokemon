#ifndef GAME_MASTER_HPP
#define GAME_MASTER_HPP

#include "Pokemon.hpp"
#include "Graphique.hpp"
#include <queue>
#include <functional>
#include <random>

// Forward declaration to resolve circular dependencys
class Window;

// Enum to define the current battle state
enum class BattleState {
    WAITING_FOR_INPUT,
    MOVE_SELECTION,
    TARGET_SELECTION,
    ANIMATION_PLAYING,
    TURN_EXECUTING,
    CHECKING_FAINT,
    GAME_OVER
};

// Structure to represent a turn action
struct TurnAction {
    Pokemon* attacker;
    Pokemon* target;
    move* selectedMove;
    int priority; // For priority moves
    
    // Constructor
    TurnAction(Pokemon* atk, Pokemon* tgt, move* mv, int pri = 0) 
        : attacker(atk), target(tgt), selectedMove(mv), priority(pri) {}
        
    // Comparison operator for priority queue
    bool operator<(const TurnAction& other) const {
        // First compare by priority
        if (priority != other.priority) {
            return priority < other.priority;
        }
        // Then by speed if priority is the same
        return attacker->getVit() < other.attacker->getVit();
    }
};

class GameMaster {
private:
    // Reference to the window for UI updates
    Window* window;
    
    // Battle state
    BattleState currentState;
    
    // Pointers to the active Pokémon
    Pokemon* team1Pokemon[2]; // [0] = active, [1] = backup
    Pokemon* team2Pokemon[2]; // [0] = active, [1] = backup
    
    // Turn queue for actions this turn
    std::priority_queue<TurnAction> turnQueue;
    
    // RNG for damage calculations
    std::mt19937 rng;
    
    // Currently selected move and target
    size_t selectedMoveIndex;
    int selectedTargetIndex;
    
    // Team turn flags
    bool team1TurnComplete;
    bool team2TurnComplete;
    
    // Game over flag
    bool isGameOver;
    int winningTeam; // 0 = no winner yet, 1 = team1, 2 = team2
    Pokemon* targetPokemon = nullptr;
    Pokemon* activePokemon=nullptr;
    bool team1hasattacked;
    bool team2hasattacked;
public:
    // Constructor
    GameMaster(Window* win);
    void updatePokemonPointers(Window* win);
    
    // Initialization methods
    void initializeBattle();
    
    // Game state methods
    void update(float deltaTime);
    void handleInput(sf::Event& event);
    
    // Battle mechanics
    void selectMove(int teamNumber, size_t moveIndex);
    void selectTarget(int teamNumber, int targetIndex);
    void confirmAction(int teamNumber);
    void executeTurn();
    
    // Damage calculation
    int calculateDamage(Pokemon* attacker, Pokemon* defender,  move* selectedMove);
    float calculateTypeEffectiveness(const std::string& moveType, const std::string& defenderType);
    
    // Check battle conditions
    bool checkFainted(Pokemon* pokemon);
    bool checkTeamDefeated(int teamNumber);
    void checkGameOver();
    
    // Switch Pokémon
    void switchPokemon(int teamNumber);
    
    // Getters
    BattleState getCurrentState() const { return currentState; }
    bool isActionReady(int teamNumber) const;
    
    // Utility
    void reset();
};

#endif // GAME_MASTER_HPP