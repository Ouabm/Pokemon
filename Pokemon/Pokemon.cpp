#ifndef POKEMON_HPP
#define POKEMON_HPP
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

class move{
    public:
    move(std::string nom,int power, int precision , std::string type ,sf::Texture& Texture): nom(nom),puissance(puissance),precision(precision),type(type){}
    std::string nom;
    int puissance;
    int precision;
    std::string type;

};

class Pokemon {
    public:
    Pokemon(std::string nom,std::string type,int hp,int atk, int def , int vit): nom(nom),type(type),hp(hp),atk(atk),def(def),vit(vit){}
    void rajoutspe(move spe){
        if(spes.size()<4){
        spes.push_back(spe);
        }
    }
    bool mort()const{
        return hprestant<=0;
    }

    std::string nom;
    int hp;
    int hprestant;
    int def;
    std::string type;
    int atk; 
    int vit;
    std::vector<move> spes ;
};

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

class combat{
    public:
    combat(Joueur& Joueur1,Joueur& Joueur2):Joueur1(Joueur1),Joueur2(Joueur2){}
     void init_combat() {
        Joueur1.Pokemonactive = &Joueur1.equipe[0];
        Joueur2.Pokemonactive = &Joueur2.equipe[0];
        tour_actuelle = 1;
    }
    
    void Tour(move& speJ1, move& speJ2) {
        // Determine who goes first based on speed
        Pokemon* Pokemon1 = Joueur1.Pokemonactive;
        Pokemon* Pokemon2 = Joueur2.Pokemonactive;
        move* spe1 = &speJ1;
        move* spe2 = &speJ2;
        
        if (Joueur2.Pokemonactive->vit > Joueur1.Pokemonactive->vit) {
            std::swap(Pokemon1, Pokemon2);
            std::swap(speJ1, speJ2);
        }
        
        // Execute moves
        executeMove(speJ1, *Pokemon1, *Pokemon2);
        if (!Pokemon2->mort()) {
            executeMove(speJ2, *Pokemon2, *Pokemon1);
        }
        
        tour_actuelle++;
    }
    
    private:
    void executeMove(move& spe, Pokemon& attaqauant, Pokemon& defenseur) {
        // Simple damage calculation
        int damage = (spe.puissance * attaqauant.atk) / defenseur.def;
        defenseur.hprestant -= damage;
        if (defenseur.hprestant < 0) defenseur.hprestant = 0;
    }
    Joueur& Joueur1;
    Joueur& Joueur2;
    int tour_actuelle;

};
#endif