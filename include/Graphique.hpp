#include "utile.hpp"
#include "Pokemon.hpp"
#include "PokemonDB.hpp"

class GameMaster;

class Window
{
    friend class GameMaster;

private:
    // =================== MUSIQUE ===================
    sf::Music music;
    std::string currentMusic;
    void playMusic(const std::string &filename, float volume = 50.0f, bool loop = true);

    // =================== POKÉMON & BASE DE DONNÉES ===================
    PokemonDB Pokemondb;
    Pokemon *pokemon1, *pokemon2, *pokemon3, *pokemon4;
    Pokemon *active, *attacker, *defender;

    std::vector<Pokemon *> allPokemon = {
        Pokemondb.getPokemonByName("Pikachu"),
        Pokemondb.getPokemonByName("Charizard"),
        Pokemondb.getPokemonByName("Lugia"),
        Pokemondb.getPokemonByName("Reshiram"),
        Pokemondb.getPokemonByName("Zekrom"),
        Pokemondb.getPokemonByName("Mewtwo"),
        Pokemondb.getPokemonByName("Dialga"),
        Pokemondb.getPokemonByName("Rayquaza"),
        Pokemondb.getPokemonByName("Giratina"),
        Pokemondb.getPokemonByName("Arceus"),
        Pokemondb.getPokemonByName("Palkia"),
        Pokemondb.getPokemonByName("Zapdos"),
        Pokemondb.getPokemonByName("Articuno"),
        Pokemondb.getPokemonByName("Raikou"),
        Pokemondb.getPokemonByName("Entei"),
        Pokemondb.getPokemonByName("Suicune"),
        Pokemondb.getPokemonByName("Kyogre"),
        Pokemondb.getPokemonByName("Groudon"),
        Pokemondb.getPokemonByName("Ho-Oh"),
        Pokemondb.getPokemonByName("Moltres"),
    };

    // =================== INTERFACE UTILISATEUR ===================
    sf::Font font;
    sf::Texture BGTexture;
    sf::Sprite BGSprite;
    void loadResources(const std::string &fontFile, const std::string &bgTextureFile);

    // --- Arène et fonds ---
    sf::Texture ArenaTexture, backgroundm, backgroundfin;
    sf::Sprite ArenaSprite, background_spritem, background_spritefin;

    // --- Pokémon Sprites et textures ---
    sf::Texture pokemon1_texture, pokemon2_texture;
    sf::Sprite pokemonSprite[4];

    // --- Barres de vie et affichage des PV ---
    sf::RectangleShape healthBar[4];
    sf::RectangleShape healthBarBackground[4];
    sf::Text healthText[4];

    // --- Boutons de mouvement et changement ---
    sf::RectangleShape moveButtons[8];
    sf::Text moveButtonTexts[8];

    sf::RectangleShape switchButtons, switchButtons2;
    sf::Text switchButtonTexts, switchButtonTexts2;

    // =================== MÉTHODES D'INITIALISATION ===================
    void initPokemonPostion();

    void initializeHealthBars();
    void initHealthBarElement(sf::RectangleShape &healthElement, const sf::Vector2f &position, const sf::Vector2f &size,
                              const sf::Color &fillColor, const sf::Color &outlineColor = sf::Color::Black, float outlineThickness = 5.f);

    void initMoveButton(sf::RectangleShape &button, sf::Text &text, sf::Vector2f position);
    void setupSwitchButtons();
    void setupUI();
    void init();

    // =================== ANIMATIONS ===================
    int attackFrame;
    float attackAnimationTimer;
    sf::Clock attackAnimClock;
    sf::Vector2f attackPosition;
    float animationProgress;
    sf::Clock animationClock;
    sf::Vector2f originalPos[4];
    bool isDamageAnimating;
    float damageAnimationDuration;
    sf::Clock damageEffectClock;

    // =================== CHANGEMENT DE POKÉMON ===================
    bool isSwapping;
    float swapProgress;
    bool animationFinished;
    int currentFrame;
    bool active1, active2;
    sf::Vector2f originalPosTeam1[2], originalPosTeam2[2];

    // =================== CIBLAGE & ATTAQUE ===================
    sf::CircleShape targetIndicator;
    bool attackChosen = false;
    size_t selectedAttackIndex;
    Pokemon *selectedAttackingPokemon;

    sf::Texture attackEffectTexture[4];
    sf::Sprite attackEffectSprite[4];

    // =================== MÉTHODES D'ACTION ===================
    void updateHealthBars(float health1Percentage, float health2Percentage, float health3Percentage, float health4Percentage);
    void updatemovebutton(Pokemon *active);
    void updateAnimations();
    void updateSwapAnimation();
    void updateMoveButtons();
    void animateAttack(bool isFirstPokemonAttacking);
    void animateSwitch(bool isTeam1);
    void setAttackEffectSprite(const std::string &movePath);

    void handleSwitching();
    void processevent();
    void cycleTargets(bool isTeam1);
    Pokemon *getCurrentTarget(bool isTeam1);

    void showPokemonSelection();
    void handleSelection(bool &jConfirmed, size_t &selectedIndex, std::vector<int> &team, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key confirmKey);
    void drawHighlight(size_t i, const std::vector<int> &teamJ1, const std::vector<int> &teamJ2, size_t selectedIndexJ1, size_t selectedIndexJ2, bool j1Confirmed, bool j2Confirmed, int col, int row, sf::RenderWindow &window);
    void displayHealthNames(sf::RenderWindow &window);
    
    void setupTargetingSystem(void);

    sf::Text createText(const std::string &textContent, unsigned int fontSize);
    sf::RectangleShape createButton(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    void showHelpWindow();

public:
    // =================== CONSTRUCTEUR / DESTRUCTEUR ===================
    Window();
    virtual ~Window();

    // =================== ÉTAT DU JEU ===================
    bool debut = false;
    bool isAnimating;
    bool isFirstPokemonAttaking;
    bool isSecondPokemonAttaking;
    bool isThirdPokemonAttaking;
    bool isFourthPokemonAttaking;
    bool isTargetingMode;
    int currentTargetTeam1;
    int currentTargetTeam2;
    int activeTeam1Index; // Pokémon actif équipe 1 (0 ou 1)
    int activeTeam2Index; // Pokémon actif équipe 2 (0 ou 1)

    // =================== AFFICHAGE ===================
    void render();
    void showMainMenu();
    void showEndGameMenu(int winningTeam);
    void renderTargetIndicator();
    void updatePokemonSprites();

    sf::RenderWindow *window;

    void handleinput();
};
