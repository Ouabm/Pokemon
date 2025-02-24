#include "move.hpp"

move::move(std::string nom, int puissance, int precision, std::string type, std::string texturepath)
    : nom(nom), type(type), puissance(puissance), precision(precision), texturepath(texturepath) {
}
