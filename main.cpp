#include <iostream>
#include "CVector.h"
#include <vector>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

//-----------------------
//Main loop, has Menu
//-----------------------
int main()
{
    bool running = true;
    do
    {
        //Clear the console window using a different command based on Platform compiled for. This allows for cross-platform use.
#if _WIN32 || _WIN64
        system("cls");
#else
        system("clear");
#endif

        std::string input;
        std::cout << "Please input the Exercise number you would like to run\nAvailable Exercises are:\n[001.1] [001.2] [001.3] [001.4] [001.5]\nOr input [exit] to Close the program:" << std::endl;
        std::cin >> input;
        std::cin.ignore();
        if (input == "exit")
        {
            running = false;
            break;
        }
        else
        {
            std::cout << "Invalid input, please try again!" << std::endl;
        }
        std::cout << "Input anything to continue..." << std::endl;
        std::string temp;
        std::cin >> temp;

    } while (running);
}
