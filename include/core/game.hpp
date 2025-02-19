#ifndef GAME_HPP
#define GAME_HPP

#include "trainer.hpp"
#include "battle.hpp"

class Game
{
public:
    void start();

private:
    Trainer player1;
    Trainer player2;
    Battle battle;
};

#endif // GAME_HPP
