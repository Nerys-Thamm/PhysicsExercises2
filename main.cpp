#include <iostream>
#include "CVector.h"
#include <vector>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

sf::VertexArray MakeTriangle(sf::Vector2f PointA, sf::Vector2f PointB, sf::Vector2f PointC, sf::Color Color)
{
    // create an array of 3 vertices that define a triangle primitive
    sf::VertexArray triangle(sf::Triangles, 3);

    // define the position of the triangle's points
    triangle[0].position = PointA;
    triangle[1].position = PointB;
    triangle[2].position = PointC;

    // define the color of the triangle's points
    triangle[0].color = Color;
    triangle[1].color = Color;
    triangle[2].color = Color;

    return triangle;
}

void PointInTriangle()
{
    //window
    sf::RenderWindow window(sf::VideoMode(300, 300), "Nerys Thamm Triangle Cutter", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    std::vector<sf::VertexArray> Triangles; //Vector of all triangles
    sf::Vector2f *Point = nullptr;
    bool isInsideTriangle = false;
    std::vector<sf::Vector2i> ClickBuffer; //Buffer of click input positions

    sf::Vertex line[3];

    //program loop
    while (window.isOpen())
    {

        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
                ClickBuffer.push_back(sf::Mouse::getPosition(window)); //Add clicks to buffer
                if (ClickBuffer.size() == 3 && Triangles.size() == 0)  //Make a triangle if there isnt already one, and there have been three clicks
                {
                    Triangles.push_back(MakeTriangle((sf::Vector2f)ClickBuffer[0], (sf::Vector2f)ClickBuffer[1], (sf::Vector2f)ClickBuffer[2], sf::Color::Red));

                    ClickBuffer.clear();
                }
                else if (ClickBuffer.size() == 1 && Triangles.size() == 1)
                {
                    Point = new sf::Vector2f((sf::Vector2f)ClickBuffer[0]);
                    CVector::Vector3 vec1 = CVector::ToVector3(Triangles[0][0].position) - CVector::ToVector3(*Point);
                    CVector::Vector3 vec2 = CVector::ToVector3(Triangles[0][1].position) - CVector::ToVector3(*Point);
                    CVector::Vector3 vec3 = CVector::ToVector3(Triangles[0][2].position) - CVector::ToVector3(*Point);
                    float f = (CVector::AngleBetween(vec1, vec2) +
                               CVector::AngleBetween(vec2, vec3) +
                               CVector::AngleBetween(vec3, vec1));
                    if ((f < 365 && f > 355) || (f > -365 && f < -355))
                    {
                        isInsideTriangle = true;
                    }
                    else
                    {
                        isInsideTriangle = false;
                    }
                }
                else if (ClickBuffer.size() > 1 && Triangles.size() >= 1) //Clear the buffer if nothing can be done
                {
                    ClickBuffer.clear();
                }

                break;
            case sf::Event::KeyPressed:

                switch (event.key.code)
                {
                case sf::Keyboard::R:
                    Triangles.clear();
                    Point = nullptr;
                    ClickBuffer.clear();
                    break;

                default:
                    window.close();
                    break;
                }
            default:
                break;
            }
        }
        //RENDER
        window.clear();

        for (int i = 0; i < Triangles.size(); i++)
        {
            window.draw(Triangles[i]);
        }

        if (ClickBuffer.size() == 1 && Triangles.size() == 0)
        {
            line[0].position = (sf::Vector2f)ClickBuffer[0];
            line[1].position = (sf::Vector2f)sf::Mouse::getPosition(window);
            line[2].position = (sf::Vector2f)sf::Mouse::getPosition(window);
            window.draw(line, 2, sf::Lines);
        }
        else if (ClickBuffer.size() >= 2)
        {
            line[0].position = (sf::Vector2f)ClickBuffer[0];
            line[1].position = (sf::Vector2f)ClickBuffer[1];
            line[2].position = (sf::Vector2f)sf::Mouse::getPosition(window);
            window.draw(line, 3, sf::LineStrip);
        }
        if (Point != nullptr)
        {
            sf::CircleShape shape(10.0f);
            shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
            shape.setPosition(*Point);
            shape.setFillColor(isInsideTriangle ? sf::Color::Green : sf::Color::Red);
            window.draw(shape);
        }

        window.display();
    }

    return;
}

void PointInTriangleBarycentric()
{
    //window
    sf::RenderWindow window(sf::VideoMode(300, 300), "Nerys Thamm Triangle Cutter", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    std::vector<sf::VertexArray> Triangles; //Vector of all triangles
    sf::Vector2f *Point = nullptr;
    bool isInsideTriangle = false;
    std::vector<sf::Vector2i> ClickBuffer; //Buffer of click input positions

    sf::Vertex line[3];

    //program loop
    while (window.isOpen())
    {

        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
                ClickBuffer.push_back(sf::Mouse::getPosition(window)); //Add clicks to buffer
                if (ClickBuffer.size() == 3 && Triangles.size() == 0)  //Make a triangle if there isnt already one, and there have been three clicks
                {
                    Triangles.push_back(MakeTriangle((sf::Vector2f)ClickBuffer[0], (sf::Vector2f)ClickBuffer[1], (sf::Vector2f)ClickBuffer[2], sf::Color::Red));

                    ClickBuffer.clear();
                }
                else if (ClickBuffer.size() == 1 && Triangles.size() == 1)
                {
                    Point = new sf::Vector2f((sf::Vector2f)ClickBuffer[0]);

                    isInsideTriangle = CVector::TestPointInTriBarycentric(CVector::ToVector3(*Point), CVector::ToVector3(Triangles[0][0].position), CVector::ToVector3(Triangles[0][1].position), CVector::ToVector3(Triangles[0][2].position));
                }
                else if (ClickBuffer.size() > 1 && Triangles.size() >= 1) //Clear the buffer if nothing can be done
                {
                    ClickBuffer.clear();
                }

                break;
            case sf::Event::KeyPressed:

                switch (event.key.code)
                {
                case sf::Keyboard::R:
                    Triangles.clear();
                    Point = nullptr;
                    ClickBuffer.clear();
                    break;

                default:
                    window.close();
                    break;
                }
            default:
                break;
            }
        }
        //RENDER
        window.clear();

        for (int i = 0; i < Triangles.size(); i++)
        {
            window.draw(Triangles[i]);
        }

        if (ClickBuffer.size() == 1 && Triangles.size() == 0)
        {
            line[0].position = (sf::Vector2f)ClickBuffer[0];
            line[1].position = (sf::Vector2f)sf::Mouse::getPosition(window);
            line[2].position = (sf::Vector2f)sf::Mouse::getPosition(window);
            window.draw(line, 2, sf::Lines);
        }
        else if (ClickBuffer.size() >= 2)
        {
            line[0].position = (sf::Vector2f)ClickBuffer[0];
            line[1].position = (sf::Vector2f)ClickBuffer[1];
            line[2].position = (sf::Vector2f)sf::Mouse::getPosition(window);
            window.draw(line, 3, sf::LineStrip);
        }
        if (Point != nullptr)
        {
            sf::CircleShape shape(10.0f);
            shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
            shape.setPosition(*Point);
            shape.setFillColor(isInsideTriangle ? sf::Color::Green : sf::Color::Red);
            window.draw(shape);
        }

        window.display();
    }

    return;
}

void Javelin(float _angle, float _speed, float _time, CVector::Vector3 &out_Pos, float &out_Angle)
{
    const float GRAVITY = 9.80665f;
    out_Pos = CVector::Vector3{0.0f, 0.0f, 0.0f};
    CVector::Vector3 startvelocity{_speed * cos(_angle * (M_PI / 180)), _speed * sin(_angle * (M_PI / 180)), 0.0f};
    out_Pos.x = startvelocity.x * _time;
    out_Pos.y = (startvelocity.y * _time) - (GRAVITY * (_time * _time) / 2);
    float currVelocityX = startvelocity.x;
    float currVelocityY = startvelocity.y - GRAVITY * _time;
    out_Angle = CVector::Angle(CVector::Vector3{currVelocityX, currVelocityY, 0.0f});
}

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
        std::cout << "Please input the Exercise number you would like to run\nAvailable Exercises are:\n[004.1] [004.2] [004.3] [005.2] [005.3]\nOr input [exit] to Close the program:" << std::endl;
        std::cin >> input;
        std::cin.ignore();
        if (input == "exit")
        {
            running = false;
            break;
        }
        else if (input == "004.1")
        {
            PointInTriangle();
        }
        else if (input == "004.2")
        {
            PointInTriangleBarycentric();
        }
        else if (input == "005.2")
        {
            std::cout << "Please enter the Javelin throw angle: ";
            std::string input;
            std::cin >> input;
            float inpangle = std::stof(input);
            std::cout << std::endl
                      << "Please enter Javelin throw speed: ";
            input = "";
            std::cin >> input;
            float inpspeed = std::stof(input);
            std::cout << std::endl
                      << "Please enter Time you would like to calculate: ";
            input = "";
            std::cin >> input;
            float inptime = std::stof(input);
            float outangle;
            CVector::Vector3 outvec;
            Javelin(inpangle, inpspeed, inptime, outvec, outangle);
            std::cout << std::endl
                      << "Pos [X: " + std::to_string(outvec.x) + " Y: " + std::to_string(outvec.y) + "] Angle: " + std::to_string(outangle) + "";
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
