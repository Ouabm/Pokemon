#include "Pokemon.hpp"
#include"player.hpp"


class combat{
    private:
    void executeMove(move& spe, Pokemon& attaqauant, Pokemon& defenseur);
    Joueur& Joueur1;
    Joueur& Joueur2;
    int tour_actuelle;


    public:
    combat(Joueur& Joueur1,Joueur& Joueur2);
    void init_combat();
    void Tour(move& speJ1, move& speJ2);

};