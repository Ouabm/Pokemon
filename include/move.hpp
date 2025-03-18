#include "utile.hpp"

class move
{
private:
    int power;

public:
    move(std::string nom, int puissance, int precision, std::string type, std::string texturepath);
    std::string nom;
    int puissance;
    int precision;
    std::string type;
    std::string texturepath;
    bool isSpecial; // For special attacks like Spacial Rend
    std::string getmovetype() { return type; };
    std::string getmovename() { return nom; };
    const int getmovepower() { return puissance; };
    std::string &getmovepath()
    {
        return texturepath;
    };
};
