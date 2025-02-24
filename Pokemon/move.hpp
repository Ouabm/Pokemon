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
    private:
    int power;
   

public:
    move(std::string nom, int puissance, int precision, std::string type,  std::string texturepath);
    std::string nom;
    int puissance;
    int precision;
    std::string type;
    std::string texturepath;
    bool isSpecial; // For special attacks like Spacial Rend
    std::string getmovestype(){return type;};
    std::string getmovename(){return nom;};
    std::string& getmovepath(){
    return texturepath;};

};


