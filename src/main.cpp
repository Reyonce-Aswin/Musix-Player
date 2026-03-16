#include "Player.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

// Main entry point for the audio player application
int main()
{
    // Create a Player object with the specified audio file
    Player player("assets/test.wav");

    // Attempt to start playback, exit if failed
    if (!player.play())
        return -1;

    // Display control instructions to the user
    std::cout << "Controls:\n";
    std::cout << "p = play/pause\n";
    std::cout << "l = toggle loop\n";
    std::cout << "m = mute/unmute\n";
    std::cout << "q = quit\n\n";

    // Hide the cursor for cleaner output
    std::cout << "\033[?25l";
    
    // Main control loop
    while (true)
    {
        // Check for keyboard input
        if (_kbhit())
        {
            char cmd = _getch();

            // Handle play/pause toggle
            if (cmd == 'p')
                player.togglePause();

            // Handle loop toggle
            else if (cmd == 'l')
                player.toggleLoop();

            // Handle mute toggle
            else if (cmd == 'm')
                player.toggleMute();

            // Handle quit command
            else if (cmd == 'q')
            {
                player.stop();
                break;
            }
        }

        // Update and display playback status
        player.printStatus();

        // Sleep for half a second before next iteration
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Show the cursor again
    std::cout << "\033[?25h";
    std::cout << std::endl;

    return 0;
}