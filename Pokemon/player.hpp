#include<string>
#include <iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include "Pokemon.hpp"

class Joueur{
    public:

        void Rajouterpokemon(Pokemon pokemon){
            if(equipe.size()<6){
                equipe.push_back(pokemon);
            }
        }
        std::vector<Pokemon> equipe;
        Pokemon* Pokemonactive=nullptr;

};