#include "utile.hpp"
#include "Pokemon.hpp"
#include "PokemonDB.hpp"

class GameMaster;

class Window
{
  friend class GameMaster;

private:
  // --- Musique ---
  sf::Music music_Arriere_plan;
  sf::Music music;

  // --- Pokémon et DB ---
  PokemonDB Pokemondb;
  Pokemon *pokemon1, *pokemon2, *pokemon3, *pokemon4;
  Pokemon *active, *attacker, *defender;

  // --- Interface utilisateur ---
  sf::Texture pokemon1_texture, pokemon2_texture, Arene_texture;
  sf::Sprite Arene_sprite;
  sf::Font font;
  sf::RectangleShape infoJ1, infoJ2;
  sf::RectangleShape moveButtons[8];
  sf::Text moveButtonTexts[8];
  sf::RectangleShape healthBar[4];
  sf::RectangleShape healthBarBackground[4];
  sf::RectangleShape healthbg[2];
  sf::Text healthText[4];
  sf::RectangleShape switchButtons, switchButtons2;
  sf::Text switchButtonTexts, switchButtonTexts2;

  // --- Animation ---
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

  // --- Switching Pokémon ---
  bool isSwapping;
  float swapProgress;
  bool animationFinished;
  int currentFrame;
  bool active1, active2;
  sf::Vector2f originalPosTeam1[2], originalPosTeam2[2];

  // --- Backgrounds ---
  sf::Texture backgroundm, backgroundfin;
  sf::Sprite background_spritem, background_spritefin;

  // --- Ciblage et Attaque ---
  sf::CircleShape targetIndicator;
  bool attackChosen = false;
  size_t selectedAttackIndex;
  Pokemon *selectedAttackingPokemon;

  // A voir
  sf::Texture attackEffectTexture[4];
  sf::Sprite attackEffectSprite[4];
  sf::Sprite pokemonSprite[4];

  // move spe;
  void init_pokemon_positon();

public:
  sf::RenderWindow *window;

  bool debut = false;
  Window();
  virtual ~Window();
  void showMainMenu();
  void showEndGameMenu(int winningTeam);

  void render();
  void setupUI();
  void setupSwitchButtons();
  void init();

  void initializeHealthBars();
  void updateHealthBars(float health1Percentage, float health2Percentage, float health3Percentage, float health4Percentage);
  void updatemovebutton(Pokemon *active);
  void updateAnimations();
  void updateSwapAnimation();
  void updateMoveButtons();

  void animateAttack(bool isFirstPokemonAttacking);
  void animateSwitch(bool isTeam1);
  void setAttackEffectSprite(const std::string &movePath);

  void handleinput();
  void processevent();
  bool isWindowopen() const
  {
    return window->isOpen();
  };
  void handleSwitching();
  // Methods for targeting
  void setupTargetingSystem();
  void renderTargetIndicator();
  void updatePokemonSprites();
  void cycleTargets(bool isTeam1);
  Pokemon *getCurrentTarget(bool isTeam1);
  void showPokemonSelection();
  void init_music();
  void playMusic(const std::string &filename);
  // These are needed for the GameMaster to access
  bool isAnimating;
  bool isFirstPokemonAttaking;
  bool isSecondPokemonAttaking;
  bool isThirdPokemonAttaking;
  bool isFourthPokemonAttaking;
  bool isTargetingMode;
  int currentTargetTeam1;
  int currentTargetTeam2;
  int activeTeam1Index; // Current active Pokemon for team 1 (0 or 1)
  int activeTeam2Index; // Current active Pokemon for team 2 (0 or 1)

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
};
