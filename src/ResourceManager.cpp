#include "ResourceManager.hpp"
#include "PokemonManager.hpp" // Uniquement pour accéder aux noms des Pokémons

// Singleton
ResourceManager &ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

// Charger une police
bool ResourceManager::loadFont(const std::string &name, const std::string &filename)
{
    sf::Font font;
    if (!font.loadFromFile(filename))
        return false;
    fonts[name] = std::move(font);
    return true;
}

// Charger une texture
bool ResourceManager::loadTexture(const std::string &name, const std::string &filename)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename))
        return false;
    textures[name] = std::move(texture);
    return true;
}

// Charger une musique
bool ResourceManager::loadMusicResource(const std::string &name, const std::string &filename)
{
    auto newMusic = std::make_unique<sf::Music>();
    if (!newMusic->openFromFile(filename))
        return false;
    music[name] = std::move(newMusic);
    return true;
}

// Récupérer une police
const sf::Font &ResourceManager::getFont(const std::string &name) const
{
    return fonts.at(name);
}

// Récupérer une texture
const sf::Texture &ResourceManager::getTexture(const std::string &name) const
{
    return textures.at(name);
}

// Récupérer une musique
sf::Music &ResourceManager::getMusic(const std::string &musicKey) const
{
    auto it = music.find(musicKey);
    if (it == music.end())
    {
        throw std::runtime_error("Music not found: " + musicKey);
    }
    return *(it->second); // Déréférence le unique_ptr
}

// Jouer une musique
void ResourceManager::playMusic(const std::string &musicKey, float volume, bool loop)
{
    stopMusic(); // Arrête la musique précédente

    sf::Music &music = getMusic(musicKey);
    music.setVolume(volume);
    music.setLoop(loop);
    music.play();

    currentMusic = &music; // Garde une référence à la musique en cours
}

// Stopper la musique en cours
void ResourceManager::stopMusic()
{
    if (currentMusic)
    {
        currentMusic->stop();
        currentMusic = nullptr;
    }
}

// Charger toutes les ressources
void ResourceManager::loadAllResources()
{
    // Chargement des polices
    loadFont("MenuStateFont", "assets/fonts/arial.ttf");
    loadFont("SelectionStateFont", "assets/fonts/arial.ttf");
    loadFont("BattleStateFont", "assets/fonts/arial.ttf");
    loadFont("EndStateFont", "assets/fonts/arial.ttf");

    // Chargement des textures
    loadTexture("MenuStateBG", "assets/textures/menuBG.jpg");
    loadTexture("SelectionStateBG", "assets/textures/selectionBG.jpg");
    loadTexture("BattleStateBG", "assets/textures/battleBG.jpg");
    loadTexture("EndStateBG", "assets/textures/endBG.jpg");

    loadTexture("SelectionStateBG2", "assets/textures/SelectionBackground.jpg"); // TEST !

    // Chargement des musiques
    loadMusicResource("MenuStateMusic", "assets/musics/menuMusic.ogg");
    loadMusicResource("SelectionStateMusic", "assets/musics/selectionMusic.ogg");
    loadMusicResource("BattleStateMusic", "assets/musics/battleMusic.ogg");
    loadMusicResource("EndStateMusic", "assets/musics/menuMusic.ogg");

    loadAllPokemonTextures();
}

// Charger toutes les textures des Pokémons depuis le PokemonManager
void ResourceManager::loadAllPokemonTextures()
{
    PokemonManager &pokemonManager = PokemonManager::getInstance(); // Utiliser l'instance unique de PokemonManager
    std::vector<std::string> pokemonNames = pokemonManager.getAllPokemonNames(); // Récupère tous les noms de Pokémon

    for (const auto &name : pokemonNames)
    {
        // Recherche du Pokémon par son nom
        Pokemon *pokemon = pokemonManager.getPokemonByName(name);
        if (pokemon) // Si le Pokémon existe
        {
            std::string path = "assets/textures/pokemon/" + name + ".png";
            if (!loadTexture(name, path)) // Charge la texture pour ce Pokémon
            {
                std::cerr << "Avertissement : Texture manquante pour " << name << std::endl;
            }
        }
        else
        {
            std::cerr << "Avertissement : Pokémon non trouvé : " << name << std::endl;
        }
    }
}
