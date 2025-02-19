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

class move {
public:
    move(std::string nom, int puissance, int precision, std::string type);
    std::string nom;
    int puissance;
    int precision;
    std::string type;
    bool isSpecial; // For special attacks like Spacial Rend
};

