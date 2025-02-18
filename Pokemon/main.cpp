#include"Graphique.hpp"


int main() {
    Window battleScene;
    
    // Game loop
    while (battleScene.isWindowopen()) {
        battleScene.processevent();
        battleScene.handleinput();
        battleScene.render();
    }
    
    return 0;
}