#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

float toRadians(float degrees)
{
    return float(double(degrees) * M_PI / 180);
}

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& pointer, float deltaTime, float maxSpeed)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float angle = std::atan2(delta.y, delta.x);
    double degrees = toDegrees(angle);
    if (degrees < 0)
    {
        degrees = 360 - abs(degrees);
    }

    double deltaAngle = degrees - pointer.getRotation();
    if (abs(deltaAngle) > 180)
    {
        deltaAngle = (360 - abs(deltaAngle)) * (deltaAngle > 0 ? -1 : 1);
    }
    deltaAngle = deltaAngle / deltaTime;
    if (std::abs(deltaAngle) > maxSpeed)
    {
        deltaAngle = deltaAngle > 0 ? maxSpeed * deltaTime : -maxSpeed * deltaTime;
    }

    pointer.rotate(float(deltaAngle));
}

void onMouseMove(sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = { float(event.x), float(event.y) };
}

// Опрашивает и обрабатывает доступные события в цикле.
void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void init(sf::ConvexShape& pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, { 40, 0 });
    pointer.setPoint(1, { -20, -20 });
    pointer.setPoint(2, { -20, 20 });
    pointer.setPosition({ 400, 300 });
    pointer.setFillColor(sf::Color(sf::Color(0xFF, 0x80, 0x00)));
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    constexpr float angleSpeedPerSecond = 15;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window
    (
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Pointer follows mouse", sf::Style::Default, settings
    );
    sf::Clock clock;
    float lastCycleTime = 0;

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        const float time = clock.getElapsedTime().asSeconds();
        const float deltaTime = time - lastCycleTime;
        lastCycleTime = time;
        update(mousePosition, pointer, deltaTime, angleSpeedPerSecond);
        redrawFrame(window, pointer);
    }

    return 1; 
}