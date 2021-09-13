#include <iostream>
#include "CVector.h"
#include <vector>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <cstdarg>

////////////////////////////////    11
////////////////////////////////  1111
////////////////////////////////    11
////////////////////////////////    11
////////////////////////////////  111l11
////////////////////////////////////////////////////////////////////////////////////////////////
// WEEK 4 EX 1: Point In Triangle Application
////////////////////////////////////////////////////////////////////////////////////////////////

//Makes a Vertex array of a triangle from Points
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

//SFML loop
void PointInTriangle()
{
    //window
    sf::RenderWindow window(sf::VideoMode(300, 300), "Nerys Thamm point in triangle tester", sf::Style::Titlebar);
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
                else if (ClickBuffer.size() == 1 && Triangles.size() == 1) //If there is one triangle and one click in the buffer
                {
                    Point = new sf::Vector2f((sf::Vector2f)ClickBuffer[0]);                                            //Store the point where the click occurred
                    CVector::Vector3 vec1 = CVector::ToVector3(Triangles[0][0].position) - CVector::ToVector3(*Point); //Vector from Click to first corner
                    CVector::Vector3 vec2 = CVector::ToVector3(Triangles[0][1].position) - CVector::ToVector3(*Point); //Vector from Click to second corner
                    CVector::Vector3 vec3 = CVector::ToVector3(Triangles[0][2].position) - CVector::ToVector3(*Point); //Vector from Click to third corner
                    //Store the Sum of angles between the three vectors
                    float f = (CVector::AngleBetween(vec1, vec2) +
                               CVector::AngleBetween(vec2, vec3) +
                               CVector::AngleBetween(vec3, vec1));
                    if ((f < 365 && f > 355) || (f > -365 && f < -355)) //if they add up to ~360
                    {
                        isInsideTriangle = true; //The click occured inside the triangle
                    }
                    else
                    {
                        isInsideTriangle = false; //The click occured outside the triangle
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
                case sf::Keyboard::R: //Reset the scene
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

////////////////////////////////   22
////////////////////////////////  2  2
////////////////////////////////    2
////////////////////////////////   2
////////////////////////////////  2222
////////////////////////////////////////////////////////////////////////////////////////////////
// WEEK 4 EX 2: Barycentric Coordinate Calculator
////////////////////////////////////////////////////////////////////////////////////////////////
void PointInTriangleBarycentric()
{
    //window
    sf::RenderWindow window(sf::VideoMode(300, 300), "Nerys Thamm Barycentric Point in triangle tester", sf::Style::Titlebar);
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

                    isInsideTriangle = CVector::TestPointInTriBarycentric(CVector::ToVector3(*Point), CVector::ToVector3(Triangles[0][0].position), CVector::ToVector3(Triangles[0][1].position), CVector::ToVector3(Triangles[0][2].position)); //Use Barycentric coordinates to test if it is inside the triangle
                }
                else if (ClickBuffer.size() > 1 && Triangles.size() >= 1) //Clear the buffer if nothing can be done
                {
                    ClickBuffer.clear();
                }

                break;
            case sf::Event::KeyPressed:

                switch (event.key.code)
                {
                case sf::Keyboard::R: //Reset the scene
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

////////////////////////////////  333
////////////////////////////////     3
////////////////////////////////   33
////////////////////////////////     3
////////////////////////////////  333
///////////////////////////////////////////////////////////////
// WEEK 4 EX 3: Seperating Axis Theorem
///////////////////////////////////////////////////////////////

//Gets all axes adjacent to polygon edges
std::vector<CVector::Vector3> GetAxes(sf::VertexArray _vertices)
{
    std::vector<CVector::Vector3> out;
    for (int i = 0; i < _vertices.getVertexCount(); i++) //Get edges from vertex array
    {
        out.push_back(CVector::ToVector3(_vertices[i].position - _vertices[i + 1 == _vertices.getVertexCount() ? 0 : i + 1].position));
    }

    for (auto edge : out) //Get adjacent vector to edges
    {
        edge = CVector::Vector3{edge.y, -edge.x, 0.0f};
    }
    return out;
}

//Returns a VertexArray containing a polygon
sf::VertexArray MakePolygon(std::vector<sf::Vector2i> _vertices)
{
    sf::VertexArray poly(sf::TrianglesFan, _vertices.size());
    for (int i = 0; i < _vertices.size(); i++)
    {
        poly[i].position = (sf::Vector2f)_vertices[i];
    }
    return poly;
}

typedef std::tuple<float, float> Projection; //Stores the Min and Max projection value

//Returns a projection of the polygon onto the provided plane
Projection ProjectOnAxis(const sf::VertexArray &_vertices, const CVector::Vector3 &_axis)
{
    float min = std::numeric_limits<float>::infinity();
    float max = -std::numeric_limits<float>::infinity();
    for (int i = 0; i < _vertices.getVertexCount(); i++) //For every vertex
    {
        float proj = CVector::Dot(CVector::ToVector3(_vertices[i].position), _axis); //Get the dot product of the vertex and axis
        if (proj < min)                                                              //If lower than current min
            min = proj;                                                              //Set as min
        if (proj > max)                                                              //If higher than current max
            max = proj;                                                              //Set as max
    }
    return Projection(min, max); //Return min and max values
}

//Checks if two convex polygons overlap
bool IsOverlapping(sf::VertexArray _a, sf::VertexArray _b)
{
    std::vector<CVector::Vector3> axesA = GetAxes(_a); //Get the Axes for each shape
    std::vector<CVector::Vector3> axesB = GetAxes(_b);
    //Define a Lambda to compare overlap between projections
    auto overlap = [](Projection a, Projection b) -> bool
    { return std::get<0>(a) <= std::get<1>(b) && std::get<1>(a) >= std::get<0>(b); };

    //For each shape, project both shapes onto every axis, and check if they overlap
    for (auto axis : axesA)
    {
        if (!overlap(ProjectOnAxis(_a, axis), ProjectOnAxis(_b, axis)))
            return false; //If there is no overlap, the shapes do not intersect
    }
    for (auto axis : axesB)
    {
        if (!overlap(ProjectOnAxis(_a, axis), ProjectOnAxis(_b, axis)))
            return false; //If there is no overlap, the shapes do not intersect
    }
    return true; //If every test results in overlap, then the shapes must intersect
}

//SFML loop
void SeperatingAxisTheorem()
{
    //window
    sf::RenderWindow window(sf::VideoMode(300, 300), "Nerys Thamm Triangle Cutter", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    std::vector<sf::VertexArray> Polygons; //Vector of all triangles

    std::vector<sf::Vector2i> ClickBuffer; //Buffer of click input positions

    bool overlap = false;

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
                if (Polygons.size() >= 2)                              //If two polygons have been made nothing further can be done
                    ClickBuffer.clear();
                break;
            case sf::Event::KeyPressed:

                switch (event.key.code)
                {
                case sf::Keyboard::R: //Reset the Scene
                    Polygons.clear();
                    overlap = false;
                    ClickBuffer.clear();
                    break;
                case sf::Keyboard::P:           //Place a polygon
                    if (ClickBuffer.size() > 2) //At least three vertices are needed to make a polygon
                    {
                        Polygons.push_back(MakePolygon(ClickBuffer));
                        if (Polygons.size() == 2) //If there are two polygons, check if they overlap
                        {
                            overlap = IsOverlapping(Polygons[0], Polygons[1]);
                        }
                        ClickBuffer.clear();
                    }
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
        sf::Color colorlist[] = {sf::Color::Blue,
                                 sf::Color::Green};

        for (int i = 0; i < Polygons.size(); i++) //Draw the polygons
        {
            for (int j = 0; j < Polygons[i].getVertexCount(); j++)
            {
                Polygons[i][j].color = (overlap ? sf::Color::Red : colorlist[i]); //Make the polygons red if they overlap
            }

            window.draw(Polygons[i]);
        }
        sf::Vertex line[ClickBuffer.size() + 1];
        for (int i = 0; i < ClickBuffer.size(); i++)
        {
            line[i].position = (sf::Vector2f)ClickBuffer[i];
        }
        line[ClickBuffer.size()].position = (sf::Vector2f)sf::Mouse::getPosition(window);
        window.draw(line, ClickBuffer.size() + 1, sf::LineStrip);

        window.display();
    }

    return;
}

////////////////////////////////  4  4
////////////////////////////////  4  4
////////////////////////////////  4444
////////////////////////////////     4
////////////////////////////////     4
///////////////////////////////////////////////////////////////
// WEEK 5 EX 2: Where is the Javelin?
///////////////////////////////////////////////////////////////
void Javelin(float _angle, float _speed, float _time, CVector::Vector3 &out_Pos, float &out_Angle)
{
    const float GRAVITY = 9.80665f; //Gravity constant
    out_Pos = CVector::Vector3{0.0f, 0.0f, 0.0f};
    CVector::Vector3 startvelocity{_speed * cos(_angle * (M_PI / 180.0f)), _speed * sin(_angle * (M_PI / 180.0f)), 0.0f}; //Start velocity is in the direction of the throw angle with magnitude determined by throw speed
    out_Pos.x = startvelocity.x * _time;                                                                                  // Distance = Velocity * Time
    out_Pos.y = (startvelocity.y * _time) - (GRAVITY * (_time * _time) / 2);                                              //apply gravity acceleration to initial vertical velocity
    float currVelocityX = startvelocity.x;
    float currVelocityY = startvelocity.y - GRAVITY * _time;
    out_Angle = CVector::Angle(CVector::Vector3{currVelocityX, currVelocityY, 0.0f}); //Angle of the Javelin is in the direction of its velocity
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
        std::cout << "Please input the Exercise number you would like to run\nAvailable Exercises are:\n[004.1] [004.2] [004.3] [005.2]\nOr input [exit] to Close the program:" << std::endl;
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
        else if (input == "004.3")
        {
            SeperatingAxisTheorem();
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
