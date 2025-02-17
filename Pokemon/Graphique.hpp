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


class Window {
    private:
    
    sf::RenderWindow* window;
    sf::Texture pokemon1_texture , pokemon2_texture ;
    sf::Sprite pokemon1_sprite;
    sf::Sprite pokemon2_sprite;
    sf::Font font;
    sf::RectangleShape infoJ1;
    sf::RectangleShape infoJ2;
    sf::RectangleShape moveButtons[4];

    //move spe;
    void init_pokemon_positon();
    void drawPokemonSprites();
    //void updatePokemoninfo(Joueur& J1, Joueur& J2);
    void updateMoveButton(Pokemon* pokemon);
    void handleinput();
    Pokemon pokemon1;
    Pokemon pokemon2;
    
    

    public :
    
    Window();
    virtual ~Window();
    void setupUI();
    //void update(Joueur& J1,Joueur& J2);
    void render();
    };
 



