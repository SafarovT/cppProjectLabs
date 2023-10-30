#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Eye.h"
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
void redrawFrame(sf::RenderWindow& window, Eye eye1, Eye eye2)
{
    window.clear();
    eye1.Draw(window);
    eye2.Draw(window);
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

    sf::Vector2f mousePosition;
    Eye eye1(200, 350);
    Eye eye2(300, 350);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        eye1.Update(mousePosition);
        eye2.Update(mousePosition);
        redrawFrame(window, eye1, eye2);
    }

    return 1;
}