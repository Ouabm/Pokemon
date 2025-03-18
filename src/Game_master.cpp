#include "Game_master.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>

GameMaster::GameMaster(Window *win) : window(win), currentState(BattleState::WAITING_FOR_INPUT),
                                      selectedMoveIndex(-1), selectedTargetIndex(-1), team1TurnComplete(false),
                                      team2TurnComplete(false), isGameOver(false), winningTeam(0), team1hasattacked(false), team2hasattacked(false)
{

    // Initialize RNG
    rng.seed(static_cast<unsigned int>(std::time(nullptr)));

    updatePokemonPointers(win);
    initializeBattle();
}
void GameMaster::updatePokemonPointers(Window *win)
{
    // Mettre à jour les pointeurs des Pokémon
    team1Pokemon[0] = win->pokemon1;
    team1Pokemon[1] = win->pokemon3;
    team2Pokemon[0] = win->pokemon2;
    team2Pokemon[1] = win->pokemon4;
}
void GameMaster::initializeBattle()
{
    // Set initial state
    currentState = BattleState::WAITING_FOR_INPUT;

    // Reset turn flags
    team1TurnComplete = false;
    team2TurnComplete = false;

    // Reset game over flags
    isGameOver = false;
    winningTeam = 0;

    // Make sure all Pokémon have their moves initialized
    team1Pokemon[0]->initializeMoves();
    team1Pokemon[1]->initializeMoves();
    team2Pokemon[0]->initializeMoves();
    team2Pokemon[1]->initializeMoves();

    // Update the UI to show the correct health bars
    window->updateHealthBars(
        team1Pokemon[0]->getHpRestant() / static_cast<float>(team1Pokemon[0]->getHp()),
        team2Pokemon[0]->getHpRestant() / static_cast<float>(team2Pokemon[0]->getHp()),
        team1Pokemon[1]->getHpRestant() / static_cast<float>(team1Pokemon[1]->getHp()),
        team2Pokemon[1]->getHpRestant() / static_cast<float>(team2Pokemon[1]->getHp()));
    window->updateMoveButtons();

    std::cout << "Battle initialized with Pokemon: " << std::endl;
    std::cout << "Team 1: " << team1Pokemon[0]->getName() << " and " << team1Pokemon[1]->getName() << std::endl;
    std::cout << "Team 2: " << team2Pokemon[0]->getName() << " and " << team2Pokemon[1]->getName() << std::endl;
}

void GameMaster::update(float deltaTime)
{
    // State machine for battle flow

    switch (currentState)
    {
    case BattleState::WAITING_FOR_INPUT:
        // Wait for player input, handled in handleInput
        break;

    case BattleState::ANIMATION_PLAYING:
        // Check if animation is complete
        if (!window->isAnimating)
        {
            // Animation is done, proceed with next action or back to input
            if (!turnQueue.empty())
            {
                currentState = BattleState::TURN_EXECUTING;
            }
            else
            {
                currentState = BattleState::CHECKING_FAINT;
            }
        }
        break;

    case BattleState::TURN_EXECUTING:
        executeTurn();
        break;

    case BattleState::CHECKING_FAINT:
        // Check if any Pokémon have fainted
        for (int i = 0; i < 2; i++)
        {
            checkFainted(team1Pokemon[i]);
            checkFainted(team2Pokemon[i]);
        }

        // Check if the battle is over
        checkGameOver();

        if (isGameOver)
        {
            currentState = BattleState::GAME_OVER;
            std::cout << "Game over! Team " << winningTeam << " wins!" << std::endl;
        }
        else
        {
            // Reset for next turn
            team1TurnComplete = false;
            team2TurnComplete = false;
            currentState = BattleState::WAITING_FOR_INPUT;
        }
        break;

    case BattleState::GAME_OVER:
        std::cout << "Game over! Team " << winningTeam << " wins!" << std::endl;
        window->showEndGameMenu(winningTeam);
        isGameOver = false;

        reset();
        break;

    default:
        break;
    }
}

void GameMaster::handleInput(sf::Event &event)
{
    // Don't process input if we're not waiting for it
    if (currentState != BattleState::WAITING_FOR_INPUT &&
        currentState != BattleState::MOVE_SELECTION &&
        currentState != BattleState::TARGET_SELECTION)
    {
        return;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code != sf::Keyboard::Tab && event.key.code != sf::Keyboard::Return && event.key.code != sf::Keyboard::Escape && !team1TurnComplete)
    {
        std::cout << "Attendez que le joueur 1 choisisse son action !" << std::endl;
        return;
    }
    if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && team1TurnComplete) ||
        (event.type == sf::Event::KeyPressed && team2TurnComplete))
    {
        std::cout << "Cette équipe a déjà terminé son tour." << std::endl;
        return;
    }

    // Mouse position for UI interaction
    sf::Vector2f mousePos;
    if (window->window)
    {
        mousePos = window->window->mapPixelToCoords(sf::Mouse::getPosition(*window->window));
    }

    // Check for move button clicks (Team 1)
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        // Handle Team 1 move selection
        for (int i = 0; i < 4; i++)
        {
            if (window->moveButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                window->handleinput();
                selectMove(1, i); // Team 1, move index i

                currentState = BattleState::TARGET_SELECTION;

                window->isTargetingMode = true;

                // Set up which Pokémon is attacking based on active index
                if (window->activeTeam1Index == 0)
                {
                    window->isFirstPokemonAttaking = true;
                    window->isThirdPokemonAttaking = false;
                }
                else
                {
                    window->isFirstPokemonAttaking = false;
                    window->isThirdPokemonAttaking = true;
                }

                return;
            }
        }

        // Handle Team 1 switch button
        if (window->switchButtons.getGlobalBounds().contains(mousePos.x, mousePos.y) && !window->isSwapping)
        {
            switchPokemon(1);
            return;
        }
    }

    // Team 2 keyboard controls
    if (event.type == sf::Event::KeyPressed)
    {
        // Move selection for Team 2

        if (event.key.code == sf::Keyboard::Z)
            selectMove(2, 0);
        else if (event.key.code == sf::Keyboard::Q)
            selectMove(2, 1);
        else if (event.key.code == sf::Keyboard::S)
            selectMove(2, 2);
        else if (event.key.code == sf::Keyboard::D)
            selectMove(2, 3);

        // Switch Pokémon for Team 2
        if (event.key.code == sf::Keyboard::P && !window->isSwapping)
        {
            switchPokemon(2);
            return;
        }

        // If a move was selected, enter targeting mode
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Q ||
            event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D)
        {
            window->handleinput();
            currentState = BattleState::TARGET_SELECTION;
            window->isTargetingMode = true;
            // Set up which Pokémon is attacking based on active index
            if (window->activeTeam2Index == 0)
            {
                window->isSecondPokemonAttaking = true;
                window->isFourthPokemonAttaking = false;
            }
            else
            {
                window->isSecondPokemonAttaking = false;
                window->isFourthPokemonAttaking = true;
            }

            return;
        }
    }

    // Target selection and confirmation
    if (window->isTargetingMode)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // Cycle targets with Tab
            if (event.key.code == sf::Keyboard::Tab)
            {
                if (window->isFirstPokemonAttaking || window->isThirdPokemonAttaking)
                {
                    window->cycleTargets(true); // Team 1 targeting
                }
                else if (window->isSecondPokemonAttaking || window->isFourthPokemonAttaking)
                {
                    window->cycleTargets(false); // Team 2 targeting
                }
            }

            // Confirm target with Enter/Return
            if (event.key.code == sf::Keyboard::Return)
            {
                // Determine which team is targeting
                int teamNumber = (window->isFirstPokemonAttaking || window->isThirdPokemonAttaking) ? 1 : 2;
                // Get the current target index
                int targetIndex = (teamNumber == 1) ? window->currentTargetTeam1 : window->currentTargetTeam2;

                // Confirm action
                selectTarget(teamNumber, targetIndex);
                confirmAction(teamNumber);

                window->isTargetingMode = false;
                window->isFirstPokemonAttaking = false;
                window->isSecondPokemonAttaking = false;
                window->isThirdPokemonAttaking = false;
                window->isFourthPokemonAttaking = false;
                currentState = BattleState::WAITING_FOR_INPUT;

                // Check if both teams have acted
                if (team1TurnComplete && team2TurnComplete)
                {
                    currentState = BattleState::TURN_EXECUTING;
                    executeTurn();
                }
            }

            // Cancel targeting with Escape
            if (event.key.code == sf::Keyboard::Escape)
            {
                window->isTargetingMode = false;
                window->isFirstPokemonAttaking = false;
                window->isSecondPokemonAttaking = false;
                window->isThirdPokemonAttaking = false;
                window->isFourthPokemonAttaking = false;
                currentState = BattleState::WAITING_FOR_INPUT;
            }
        }
    }
}

void GameMaster::selectMove(int teamNumber, size_t moveIndex)
{
    std::cout << "Team " << teamNumber << " selected move index " << moveIndex << std::endl;
    selectedMoveIndex = moveIndex;

    // Vérifier si le Pokémon est K.O.

    if (teamNumber == 1)
    {
        activePokemon = team1Pokemon[window->activeTeam1Index];
    }
    else
    {
        activePokemon = team2Pokemon[window->activeTeam2Index];
    }

    if (activePokemon->getHpRestant() <= 0)
    {
        std::cout << "Ce Pokémon est K.O. ! Sélectionne un autre Pokémon." << std::endl;
        return;
    }

    // Debug info
    if (activePokemon)
    {
        std::vector<move *> moves = activePokemon->getMoves();
        if (moveIndex < moves.size())
        {
            std::cout << "Selected move: " << moves[moveIndex]->getmovename() << std::endl;
        }
        else
        {
            std::cout << "Error: Move index out of bounds" << std::endl;
        }
    }
}

void GameMaster::selectTarget(int teamNumber, int targetIndex)
{

    std::cout << "Team " << teamNumber << " selected target index " << targetIndex << std::endl;
    selectedTargetIndex = targetIndex;

    // For now, Team 1 targets Team 2 and vice versa

    if (teamNumber == 1)
    {
        targetPokemon = team2Pokemon[targetIndex];
    }
    else
    {
        targetPokemon = team1Pokemon[targetIndex];
        std::cout << "Team " << teamNumber << std::endl;
    }
    if (targetPokemon->getHpRestant() <= 0)
    {
        std::cout << "Ce Pokémon est K.O. ! Sélectionne un autre Pokémon." << std::endl;
        return;
    }

    if (targetPokemon)
    {
        std::cout << "Selected target: " << targetPokemon->getName() << std::endl;
    }
    // Vérifier si le Pokémon est K.O.
}

void GameMaster::confirmAction(int teamNumber)
{

    if ((teamNumber == 1 && team1TurnComplete) || (teamNumber == 2 && team2TurnComplete))
    {
        std::cout << "Cette équipe a déjà confirmé une action ce tour." << std::endl;
        return;
    }
    if (teamNumber == 2 && !team1TurnComplete)
    {
        std::cout << "Attendez que le joueur 1 choisisse son action !" << std::endl;
        return;
    }

    // Vérifier si l'équipe a déjà confirmé une action ce tour
    if ((teamNumber == 1 && team1TurnComplete) || (teamNumber == 2 && team2TurnComplete))
    {
        std::cout << "Cette équipe a déjà confirmé une action ce tour." << std::endl;
        return;
    }

    // Get the active Pokémon for this team

    Pokemon *activePokemon = (teamNumber == 1) ? team1Pokemon[window->activeTeam1Index]
                                               : team2Pokemon[window->activeTeam2Index];
    Pokemon *targetPokemon = (teamNumber == 1) ? team2Pokemon[selectedTargetIndex]
                                               : team1Pokemon[selectedTargetIndex];

    int activeIndex = 0;

    if (teamNumber == 1)
    {
        activeIndex = window->activeTeam1Index;
        activePokemon = team1Pokemon[activeIndex];
        targetPokemon = team2Pokemon[selectedTargetIndex];
        team1TurnComplete = true;
    }
    else
    {
        activeIndex = window->activeTeam2Index;
        activePokemon = team2Pokemon[activeIndex];
        targetPokemon = team1Pokemon[selectedTargetIndex];
        team2TurnComplete = true;
    }
    if (targetPokemon->getHpRestant() <= 0)
    {
        std::cout << "Impossible d'attaquer " << targetPokemon->getName() << " car il est déjà K.O. !" << std::endl;
        return;
    }

    if (activePokemon && targetPokemon)
    {
        // Get the selected move
        std::vector<move *> moves = activePokemon->getMoves();
        if (selectedMoveIndex < moves.size())
        {
            move *selectedMove = moves[selectedMoveIndex];

            // Create a turn action and add it to the queue
            int priority = 0; // Could be derived from move properties
            turnQueue.push(TurnAction(activePokemon, targetPokemon, selectedMove, priority));

            std::cout << "Action confirmed: " << activePokemon->getName()
                      << " will use " << selectedMove->getmovename()
                      << " on " << targetPokemon->getName() << std::endl;
        }
    }
}

void GameMaster::executeTurn()
{
    // Process all queued turn actions in priority order
    if (turnQueue.empty())
    {
        currentState = BattleState::CHECKING_FAINT;
        return;
    }

    // Get the next action
    TurnAction action = turnQueue.top();
    turnQueue.pop();
    if (action.attacker->getHpRestant() <= 0)
    {
        return;
    }

    // Execute the move
    int damage = calculateDamage(action.attacker, action.target, action.selectedMove);

    // Apply damage to the target
    int currentHP = action.target->getHpRestant();
    int newHP = std::max(0, currentHP - damage);
    action.target->setHpRestant(newHP);

    std::cout << action.attacker->getName() << " used " << action.selectedMove->getmovename()
              << " on " << action.target->getName() << " for " << damage << " damage!" << std::endl;

    // Update health bars
    window->updateHealthBars(
        team1Pokemon[0]->getHpRestant() / static_cast<float>(team1Pokemon[0]->getHp()),
        team2Pokemon[0]->getHpRestant() / static_cast<float>(team2Pokemon[0]->getHp()),
        team1Pokemon[1]->getHpRestant() / static_cast<float>(team1Pokemon[1]->getHp()),
        team2Pokemon[1]->getHpRestant() / static_cast<float>(team2Pokemon[1]->getHp()));

    // Set up the attack animation
    if (action.attacker == team1Pokemon[0])
    {
        window->isFirstPokemonAttaking = true;
        window->currentTargetTeam1 = (action.target == team2Pokemon[0]) ? 0 : 1;
    }
    else if (action.attacker == team1Pokemon[1])
    {
        window->isThirdPokemonAttaking = true;
        window->currentTargetTeam1 = (action.target == team2Pokemon[0]) ? 0 : 1;
    }
    else if (action.attacker == team2Pokemon[0])
    {
        window->isSecondPokemonAttaking = true;
        window->currentTargetTeam2 = (action.target == team1Pokemon[0]) ? 0 : 1;
    }
    else if (action.attacker == team2Pokemon[1])
    {
        window->isFourthPokemonAttaking = true;
        window->currentTargetTeam2 = (action.target == team1Pokemon[0]) ? 0 : 1;
    }

    // Start the attack animation and set the attack effect sprite
    window->setAttackEffectSprite(action.selectedMove->getmovepath());
    window->animateAttack(window->isFirstPokemonAttaking || window->isThirdPokemonAttaking);
    currentState = BattleState::ANIMATION_PLAYING;
}

int GameMaster::calculateDamage(Pokemon *attacker, Pokemon *defender, move *selectedMove)
{
    // Basic formula: damage = ((2 * level / 5 + 2) * power * attack / defense) / 50 + 2
    // Simplified for this implementation

    // Get base damage from move
    int power = selectedMove->getmovepower();

    // Get attacker's attack stat
    int attackStat = attacker->getAtk();

    // Get defender's defense stat
    int defenseStat = defender->getDef();

    // Calculate base damage
    float level = 50; // Assuming all Pokémon are level 50
    float baseDamage = ((2 * level / 5 + 2) * power * attackStat / defenseStat) / 50 + 2;

    // Apply type effectiveness multiplier
    float typeEffectiveness = calculateTypeEffectiveness(selectedMove->getmovetype(), defender->getType());

    // Apply random factor (85-100%)
    std::uniform_int_distribution<int> dist(85, 100);
    float randomFactor = dist(rng) / 100.0f;

    // Same Type Attack Bonus (STAB)
    float stab = 1.0f;
    if (selectedMove->getmovetype() == attacker->getType())
    {
        stab = 1.5f;
    }

    // Calculate final damage
    int finalDamage = static_cast<int>(baseDamage * typeEffectiveness * randomFactor * stab);

    std::cout << "Damage calculation:" << std::endl;
    std::cout << "Base: " << baseDamage << " * Type: " << typeEffectiveness
              << " * Random: " << randomFactor << " * STAB: " << stab << std::endl;
    std::cout << "Final damage: " << finalDamage << std::endl;

    return finalDamage;
}

float GameMaster::calculateTypeEffectiveness(const std::string &moveType, const std::string &defenderType)
{
    // Define a type effectiveness chart
    // This is a simplified version - a real implementation would be more complex

    // Super effective (2x damage)
    if (moveType == "Water" && defenderType == "Fire")
        return 2.0f;
    if (moveType == "Fire" && defenderType == "Grass")
        return 2.0f;
    if (moveType == "Grass" && defenderType == "Water")
        return 2.0f;
    if (moveType == "Electric" && defenderType == "Water")
        return 2.0f;
    if (moveType == "Ground" && defenderType == "Electric")
        return 2.0f;
    if (moveType == "Psychic" && defenderType == "Fighting")
        return 2.0f;
    if (moveType == "Dragon" && defenderType == "Dragon")
        return 2.0f;

    // Not very effective (0.5x damage)
    if (moveType == "Water" && defenderType == "Water")
        return 0.5f;
    if (moveType == "Fire" && defenderType == "Water")
        return 0.5f;
    if (moveType == "Grass" && defenderType == "Fire")
        return 0.5f;
    if (moveType == "Electric" && defenderType == "Grass")
        return 0.5f;
    if (moveType == "Electric" && defenderType == "Ground")
        return 0.0f; // Immune

    // Normal effectiveness
    return 1.0f;
}

bool GameMaster::checkFainted(Pokemon *pokemon)
{
    if (pokemon->getHpRestant() <= 0)
    {
        std::cout << pokemon->getName() << " has fainted!" << std::endl;
        pokemon->setHpRestant(0);
        return true;
    }
    return false;
}

bool GameMaster::checkTeamDefeated(int teamNumber)
{
    if (teamNumber == 1)
    {
        return checkFainted(team1Pokemon[0]) && checkFainted(team1Pokemon[1]);
    }
    else
    {
        return checkFainted(team2Pokemon[0]) && checkFainted(team2Pokemon[1]);
    }
}

void GameMaster::checkGameOver()
{
    if (checkTeamDefeated(1))
    {
        isGameOver = true;
        winningTeam = 2;
    }
    else if (checkTeamDefeated(2))
    {
        isGameOver = true;
        winningTeam = 1;
    }
}

void GameMaster::switchPokemon(int teamNumber)
{
    if (teamNumber == 1)
    {
        window->activeTeam1Index = 1 - window->activeTeam1Index;
        std::cout << "Team 1 switched to " << team1Pokemon[window->activeTeam1Index]->getName() << std::endl;
    }
    else
    {
        window->activeTeam2Index = 1 - window->activeTeam2Index;
        std::cout << "Team 2 switched to " << team2Pokemon[window->activeTeam2Index]->getName() << std::endl;
    }

    window->animateSwitch(teamNumber == 1);
    window->updateMoveButtons();
}

bool GameMaster::isActionReady(int teamNumber) const
{
    return (teamNumber == 1) ? team1TurnComplete : team2TurnComplete;
}

void GameMaster::reset()
{
    isGameOver = false;

    // Reset battle state
    currentState = BattleState::WAITING_FOR_INPUT;

    // Reset turn queue
    while (!turnQueue.empty())
    {
        turnQueue.pop();
    }

    // Reset turn flags
    team1TurnComplete = false;
    team2TurnComplete = false;

    // Reset game over flags
    isGameOver = false;
    winningTeam = 0;

    // Reset Pokémon HP
    PokemonDB db;
    for (int i = 0; i < 2; i++)
    {
        team1Pokemon[i]->setHpRestant(team1Pokemon[i]->getHp());
        team2Pokemon[i]->setHpRestant(team2Pokemon[i]->getHp());

        // Réinitialiser les attaques de chaque Pokémon
        team1Pokemon[i]->resetMoves();
        team2Pokemon[i]->resetMoves();

        // Ajouter à nouveau les attaques depuis PokemonDB
        PokemonDB db;
        Pokemon *newPokemon1 = db.getPokemonByName(team1Pokemon[i]->getName());
        Pokemon *newPokemon2 = db.getPokemonByName(team2Pokemon[i]->getName());

        if (newPokemon1 && newPokemon2)
        {
            *team1Pokemon[i] = *newPokemon1;
            *team2Pokemon[i] = *newPokemon2;
        }
    }

    // Met à jour les barres de vie
    window->updateHealthBars(1.0f, 1.0f, 1.0f, 1.0f);

    // Réinitialise le combat
    initializeBattle();

    std::cout << "Battle reset!" << std::endl;
}