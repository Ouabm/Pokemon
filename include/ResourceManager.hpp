#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>

/**
 * @class ResourceManager
 * @brief Gestionnaire centralisé des ressources (Singleton)
 *
 * Cette classe implémente le pattern Singleton pour fournir un accès global
 * aux ressources du jeu (textures, polices, musiques). Elle permet :
 * - Le chargement et le stockage des ressources
 * - L'accès sécurisé aux ressources
 * - La gestion de la musique en cours
 * 
 * @designpattern Singleton - Garantit une seule instance globale
 */
class ResourceManager
{
public:
    /**
     * @brief Obtient l'instance unique du gestionnaire
     * @return Référence à l'instance unique de ResourceManager
     */
    static ResourceManager& getInstance();

    // ========================== CHARGEMENT DES RESSOURCES ========================== //

    /**
     * @brief Charge une police depuis un fichier
     * @param name Clé d'accès pour la police
     * @param filename Chemin du fichier .ttf/.otf
     * @return true si chargement réussi, false sinon
     */
    bool loadFont(const std::string& name, const std::string& filename);

    /**
     * @brief Charge une texture depuis un fichier
     * @param name Clé d'accès pour la texture
     * @param filename Chemin du fichier image
     * @return true si chargement réussi, false sinon
     */
    bool loadTexture(const std::string& name, const std::string& filename);

    /**
     * @brief Charge une musique depuis un fichier
     * @param name Clé d'accès pour la musique
     * @param filename Chemin du fichier audio
     * @return true si chargement réussi, false sinon
     */
    bool loadMusicResource(const std::string& name, const std::string& filename);

    // ========================== ACCES AUX RESSOURCES ========================== //

    /**
     * @brief Récupère une police chargée
     * @param name Clé de la police
     * @return Référence constante à la police
     * @throw std::out_of_range si la clé n'existe pas
     */
    const sf::Font& getFont(const std::string& name) const;

    /**
     * @brief Récupère une texture chargée
     * @param name Clé de la texture
     * @return Référence constante à la texture
     * @throw std::out_of_range si la clé n'existe pas
     */
    const sf::Texture& getTexture(const std::string& name) const;

    /**
     * @brief Récupère une musique chargée
     * @param musicKey Clé de la musique
     * @return Référence à la musique (pour contrôle playback)
     * @throw std::out_of_range si la clé n'existe pas
     */
    sf::Music& getMusic(const std::string& musicKey) const;

    // ========================== CHARGEMENT GROUPÉ ========================== //

    /**
     * @brief Charge toutes les ressources globales du jeu
     * 
     * Méthode centrale qui charge l'ensemble des ressources
     * nécessaires au fonctionnement de base du jeu.
     */
    void loadAllResources();

    /**
     * @brief Charge toutes les textures des Pokémon
     * 
     * Charge les sprites de tous les Pokémon disponibles
     * dans le jeu.
     */
    void loadAllPokemonTextures();

    // ========================== GESTION MUSICALE ========================== //

    /**
     * @brief Joue une musique
     * @param musicKey Clé de la musique à jouer
     * @param volume Volume (0-100)
     * @param loop true pour lecture en boucle
     */
    void playMusic(const std::string& musicKey, float volume = 50.0f, bool loop = true);

    /**
     * @brief Arrête la musique en cours
     */
    void stopMusic();

private:
    ResourceManager() = default; ///< Constructeur privé (Singleton)

    // Désactivation de la copie
    ResourceManager(const ResourceManager&) = delete;            ///< Empêche la copie
    ResourceManager& operator=(const ResourceManager&) = delete; ///< Empêche l'affectation

    ~ResourceManager(); ///< Destructeur gérant la libération des ressources

    // Stockage des ressources
    std::unordered_map<std::string, sf::Font> fonts; ///< Dictionnaire des polices
    std::unordered_map<std::string, sf::Texture> textures; ///< Dictionnaire des textures
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> music; ///< Musiques (unique_ptr)
    sf::Music* currentMusic = nullptr; ///< Pointeur vers la musique actuellement jouée
};