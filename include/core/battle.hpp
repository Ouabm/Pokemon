#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "trainer.hpp"

class Battle {
public:
    Battle(Trainer& player1, Trainer& player2);
    
    void start();
    void performTurn();

private:
    Trainer& player1;
    Trainer& player2;
};

#endif // BATTLE_HPP
