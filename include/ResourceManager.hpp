#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>

class ResourceManager
{
public:
    static ResourceManager &getInstance();

    // Chargement des ressources
    bool loadFont(const std::string &name, const std::string &filename);
    bool loadTexture(const std::string &name, const std::string &filename);
    bool loadMusicResource(const std::string &name, const std::string &filename);

    // Accès aux ressources
    const sf::Font &getFont(const std::string &name) const;
    const sf::Texture &getTexture(const std::string &name) const;
    sf::Music &getMusic(const std::string &musicKey) const; // Retourne une référence correcte

    // Chargement groupé
    void loadAllResources();       // Charge toutes les ressources globales
    void loadAllPokemonTextures(); // Charge toutes les textures des Pokémon

    // Gestion de la musique
    void playMusic(const std::string &musicKey, float volume = 50.0f, bool loop = true);
    void stopMusic();

private:
    // Constructeur privé
    ResourceManager() = default;

    // Désactivation des méthodes de copie et d'affectation
    ResourceManager(const ResourceManager&) = delete;            // Empêche la copie
    ResourceManager& operator=(const ResourceManager&) = delete; // Empêche l'affectation

    ~ResourceManager() = default;

    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> music; // Stocké en unique_ptr
    sf::Music *currentMusic = nullptr;                                 // Pointeur vers la musique en cours
};
