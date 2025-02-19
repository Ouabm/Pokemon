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
    sf::Texture pokemon1_texture , pokemon2_texture , Arene_texture;
    sf::Sprite pokemon1_sprite;
    sf::Sprite pokemon2_sprite;
    sf::Sprite pokemon3_sprite;
    sf::Sprite pokemon4_sprite;
    sf::Sprite Arene_sprite;
    sf::Font font;
    sf::RectangleShape infoJ1;
    sf::RectangleShape infoJ2;
    sf::RectangleShape moveButtons[4];
    sf::Text moveButtonTexts[4];
    Pokemon* active;


    //move spe;
    void init_pokemon_positon();
    //void updatePokemoninfo(Joueur& J1, Joueur& J2);
    Pokemon pokemon1;
    Pokemon pokemon2;
    Pokemon pokemon3;
    Pokemon pokemon4;
    // Animation states
    bool isAnimating;
    float animationProgress;
    bool isFirstPokemonAttaking;
    sf::Clock animationClock;
    
    // Attack animation properties
    sf::Vector2f originalPos1;
    sf::Vector2f originalPos2;
    
    // Health bar properties
    sf::RectangleShape healthBar1;
    sf::RectangleShape healthBar2;
    sf::RectangleShape healthBarBackground1;
    sf::RectangleShape healthBarBackground2;
    sf::RectangleShape healthBar3;
    sf::RectangleShape healthBar4;
    sf::RectangleShape healthBarBackground3;
    sf::RectangleShape healthBarBackground4;
    
    //Switch 
    sf::RectangleShape switchButtons;     // Buttons to switch Pokemon
    sf::Text switchButtonTexts;           // Text for switch buttons
    bool isSwapping;                         // Animation state for switching
    float swapProgress;                      // Progress of swap animation
    int activeTeam1Index;                    // Current active Pokemon for team 1 (0 or 1)
    int activeTeam2Index;                    // Current active Pokemon for team 2 (0 or 1)
    sf::Vector2f originalPosTeam1[2];        // Original positions for team 1 Pokemon
    sf::Vector2f originalPosTeam2[2];    

    public :
    
    Window();
    virtual ~Window();
    void render();
    void setupUI();
    void update();
    void initializeHealthBars();
    void updateHealthBars(float health1Percentage, float health2Percentage, float health3Percentage, float health4Percentage);
    void animateAttack(bool isFirstPokemonAttacking);
    void updateAnimations();
    void handleinput();
    void processevent();
    bool isWindowopen()const{
        return window->isOpen();
    };
    void updatemovebutton(Pokemon* active);
    void setupSwitchButtons();
    void handleSwitching();
    void animateSwitch(bool isTeam1);
    void updateSwapAnimation();

    };
    


