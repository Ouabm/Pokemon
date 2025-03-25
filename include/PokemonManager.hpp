#pragma once

#include "Pokemon.hpp"
#include <map> // Pour std::map

/**
 * @class PokemonManager
 * @brief Gestionnaire centralisé des données Pokémon (Singleton)
 *
 * Cette classe implémente le pattern Singleton pour fournir un accès global
 * et unique à l'ensemble des données Pokémon. Elle permet :
 * - Le chargement centralisé des données
 * - L'accès aux Pokémon par nom
 * - La récupération de la liste complète
 * 
 * @designpattern Singleton - Garantit une seule instance globale
 */
class PokemonManager
{
private:
    std::map<std::string, Pokemon> pokemonList; ///< Map des Pokémon indexés par nom

    /**
     * @brief Charge les données Pokémon dans pokemonList
     * 
     * Méthode interne appelée lors de la première initialisation.
     * Charge tous les Pokémon disponibles depuis la source de données.
     */
    void loadPokemonData();

    /**
     * @brief Constructeur privé
     * 
     * Empêche l'instanciation directe (partie du pattern Singleton).
     * Initialise et charge les données Pokémon.
     */
    PokemonManager();

public:
    // ========================== INTERFACE SINGLETON ========================== //

    /**
     * @brief Obtient l'instance unique du gestionnaire
     * @return Référence à l'instance unique de PokemonManager
     *
     * @note Premier appel initialise l'instance (initialisation paresseuse)
     */
    static PokemonManager& getInstance();

    // ========================== ACCES AUX DONNEES ========================== //

    /**
     * @brief Récupère un Pokémon par son nom
     * @param name Nom du Pokémon recherché
     * @return Pointeur vers le Pokémon ou nullptr si non trouvé
     *
     * @warning Le pointeur reste valide tant que le manager existe
     */
    Pokemon* getPokemonByName(const std::string &name);

    /**
     * @brief Obtient la liste de tous les noms de Pokémon disponibles
     * @return Vecteur des noms de Pokémon (triés alphabétiquement)
     */
    std::vector<std::string> getAllPokemonNames() const;

    // ========================== CONTROLE D'INSTANCE ========================== //

    /**
     * @brief Supprime le constructeur de copie
     * 
     * Partie essentielle du pattern Singleton - empêche la duplication
     */
    PokemonManager(const PokemonManager&) = delete;

    /**
     * @brief Supprime l'opérateur d'affectation
     * 
     * Partie essentielle du pattern Singleton - empêche la duplication
     */
    PokemonManager& operator=(const PokemonManager&) = delete;

    // -------------------------------------------------------------------------------------
    /**
     * @section Pourquoi le Singleton est adapté ici
     * 
     * 1. @b Accès global unique :
     *    Garantit une seule instance pour toute l'application, évitant
     *    la duplication des données Pokémon.
     * 
     * 2. @b Gestion centralisée :
     *    Toutes les données sont chargées une seule fois et accessibles
     *    globalement via PokemonManager::getInstance().
     * 
     * 3. @b Optimisation mémoire :
     *    Évite de multiples chargements des mêmes données.
     * 
     * 4. @b Cohérence des données :
     *    Toutes les parties de l'application travaillent sur la même
     *    instance des données Pokémon.
     */
    // -------------------------------------------------------------------------------------
};