#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Cat.h"
#include "Pointer.h"
#include <iostream>
#include <algorithm>

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

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow& window, Cat const& cat, Pointer const& pointer)
{
    window.clear(sf::Color::White);
    cat.Draw(window);
    pointer.Draw(window);
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

    sf::Vector2f mousePosition;
    Cat cat({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
    Pointer pointer;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        const float time = clock.getElapsedTime().asSeconds();
        const float deltaTime = time - lastCycleTime;
        lastCycleTime = time;
        cat.Update(mousePosition, deltaTime);
        pointer.Update(mousePosition);
        redrawFrame(window, cat, pointer);
    }

    return 1;
}