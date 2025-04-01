#include "../include/game/Game.hpp"
#include <iostream> 

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
