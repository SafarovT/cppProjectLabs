#define _USE_MATH_DEFINES
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <cmath>


namespace
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
}

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Wave moving ball");
    sf::Clock clock;

    // const sf::Vector2f position = { 10, 350 };
    float x = 50;
    const float y = 350;
    float prevCycleTime = 0;
    int directionSign = 1;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        constexpr float speedX = 100.f;
        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float time = clock.getElapsedTime().asSeconds();
        const float deltaTime = time - prevCycleTime;
        prevCycleTime = time;
        const float wavePhase = time * float(2 * M_PI);
        x += speedX * directionSign * deltaTime;
        const float yOffset = amplitudeY * std::sin(wavePhase / periodY);

        ball.setPosition({ x, y + yOffset });

        if (x + BALL_SIZE * 2 >= WINDOW_WIDTH || x <= 0)
        {
            directionSign *= -1;
        }

        window.clear();
        window.draw(ball);
        window.display();
    }
    
    return EXIT_SUCCESS;
}
