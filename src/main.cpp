#include "Player.h"
#include <iostream>

int main() {
    Player player("assets/test.wav");

    player.setLoop(true);
    player.play();

    std::cout << "Controls:\n";
    std::cout << "p = play/pause\n";
    std::cout << "l = toggle loop\n";
    std::cout << "m = mute/unmute\n";
    std::cout << "i = stop & exit\n";

    char cmd;

    while (true) {
        std::cin >> cmd;

        if (cmd == 'p') {
            player.togglePause();
            std::cout << "Play/Pause toggled\n";
        }
        else if (cmd == 'l') {
            player.toggleLoop();
            std::cout << "Loop toggled\n";
        }
        else if (cmd == 'm') {
            player.toggleMute();
            std::cout << "Mute toggled\n";
        }
        else if (cmd == 'i') {
            player.stop();
            std::cout << "Stopped\n";
            break;
        }
    }

    return 0;
}