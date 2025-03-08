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
#include "PokemonDB.hpp"

class GameMaster;
class Window {
    friend class GameMaster;
    private:
    
    
    PokemonDB Pokemondb;
    sf::Texture pokemon1_texture , pokemon2_texture , Arene_texture;
    sf::Sprite pokemon1_sprite;
    sf::Sprite pokemon2_sprite;
    sf::Sprite pokemon3_sprite;
    sf::Sprite pokemon4_sprite;
    sf::Sprite Arene_sprite;
    sf::Font font;
    sf::RectangleShape infoJ1;
    sf::RectangleShape infoJ2;
    sf::RectangleShape moveButtons[8];
    sf::Text moveButtonTexts[8];
    Pokemon* active;
    sf::Texture attackEffectTexture1;
    sf::Sprite attackEffectSprite1;
    sf::Texture attackEffectTexture2;
    sf::Sprite attackEffectSprite2;
    sf::Sprite attackEffectSprite3;
    sf::Texture attackEffectTexture3;
    sf::Sprite attackEffectSprite4;
    sf::Texture attackEffectTexture4;
   
    int attackFrame;
    float attackAnimationTimer;
    sf::Clock attackAnimClock;
    sf::Vector2f attackPosition;

    //move spe;
    void init_pokemon_positon();
    //void updatePokemoninfo(Joueur& J1, Joueur& J2);
    Pokemon pokemon1;
    Pokemon pokemon2;
    Pokemon pokemon3;
    Pokemon pokemon4;
    Pokemon* attacker;
    Pokemon* defender;

    // Animation states
    
    float animationProgress;
    sf::Clock animationClock;
    
    // Attack animation properties
    sf::Vector2f originalPos1;
    sf::Vector2f originalPos2;
    sf::Vector2f originalPos3;
    sf::Vector2f originalPos4;
    
    // Health bar properties
    sf::RectangleShape healthBar1;
    sf::RectangleShape healthBar2;
    sf::RectangleShape healthBarBackground1;
    sf::RectangleShape healthBarBackground2;
    sf::RectangleShape healthBar3;
    sf::RectangleShape healthBar4;
    sf::RectangleShape healthBarBackground3;
    sf::RectangleShape healthBarBackground4;
    sf::RectangleShape healthbg1;
    sf::RectangleShape healthbg2;
    sf::Text healthText1;
    sf::Text healthText2;
    sf::Text healthText3;
    sf::Text healthText4;
    
    //Switch 
    sf::RectangleShape switchButtons;     // Buttons to switch Pokemon
    sf::Text switchButtonTexts;           // Text for switch buttons
    sf::RectangleShape switchButtons2;     // Buttons to switch Pokemon
    sf::Text switchButtonTexts2;           // Text for switch buttons
    bool isSwapping;                         // Animation state for switching
    float swapProgress;                      // Progress of swap animation
    sf::Vector2f originalPosTeam1[2];        // Original positions for team 1 Pokemon
    sf::Vector2f originalPosTeam2[2];    
    bool animationFinished;
    int currentFrame;
    bool active1;
    bool active2;

    sf::Clock damageEffectClock;
    bool isDamageAnimating;
    float damageAnimationDuration;
    
    // Add to private section of Window class in Graphique.hpp
   
    sf::CircleShape targetIndicator;
    bool attackChosen = false;
    size_t selectedAttackIndex ;
    Pokemon* selectedAttackingPokemon;
    public :
    sf::RenderWindow* window;
    
    Window();
    virtual ~Window();
    //void setpokemon(const Pokemon&p1,const Pokemon& p2 ,const Pokemon& p3 , const Pokemon& p4 );
    void render();
    void setupUI();
    void setupSwitchButtons();
    void init();

    void initializeHealthBars();
    void updateHealthBars(float health1Percentage, float health2Percentage, float health3Percentage, float health4Percentage);
    void updatemovebutton(Pokemon* active);
    void updateAnimations();
    void updateSwapAnimation();
    void updateMoveButtons();
    

    void animateAttack(bool isFirstPokemonAttacking);
    void animateSwitch(bool isTeam1);
    void setAttackEffectSprite(const std::string& movePath);
    
    

    void handleinput();
    void processevent();
    bool isWindowopen()const{
        return window->isOpen();
    };
    void handleSwitching();
      // Methods for targeting
    void setupTargetingSystem();
    void renderTargetIndicator();
    void cycleTargets(bool isTeam1);
    Pokemon* getCurrentTarget(bool isTeam1);
    void confirmTargetAndAttack();
    int takeDammage();
    void init_game_over();
    void showPokemonSelection();

   // These are needed for the GameMaster to access
    bool isAnimating;
    bool isFirstPokemonAttaking;
    bool isSecondPokemonAttaking;
    bool isThirdPokemonAttaking;
    bool isFourthPokemonAttaking;
    bool isTargetingMode;
    int currentTargetTeam1;
    int currentTargetTeam2;
    int activeTeam1Index;                    // Current active Pokemon for team 1 (0 or 1)
    int activeTeam2Index;                    // Current active Pokemon for team 2 (0 or 1)


    std::vector<Pokemon> allPokemon = {
    Pokemondb.getPokemonByName("Pikachu"),
    Pokemondb.getPokemonByName("Charizard"),
    Pokemondb.getPokemonByName("Lugia"),
    Pokemondb.getPokemonByName("Reshiram"),
    Pokemondb.getPokemonByName("Zekrom"),
    Pokemondb.getPokemonByName("Mewtwo"),
    Pokemondb.getPokemonByName("Blastoise"),
    Pokemondb.getPokemonByName("Rayquaza"),
    Pokemondb.getPokemonByName("Giratina"),
    Pokemondb.getPokemonByName("Arceus"),
    Pokemondb.getPokemonByName("Palkia"),
    Pokemondb.getPokemonByName("Dialga"),
    };

   
    };
    


