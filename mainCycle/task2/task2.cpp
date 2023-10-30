#define _USE_MATH_DEFINES
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <cmath>
#include <vector>

namespace
{
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    std::vector<sf::ConvexShape> GetShapes(sf::Vector2f center)
    {
        const sf::Vector2f ellipseRadius = { 100.f, 5.f };
        constexpr int pointCount = 200;
        std::vector<sf::ConvexShape> shapes;

        float drawingItemAngle = 2 * M_PI / 12;
        while (drawingItemAngle < 2 * M_PI)
        {
            sf::ConvexShape ellipse;
            ellipse.setPosition({ center.x, center.y });
            ellipse.rotate(drawingItemAngle * 180 / M_PI);
            ellipse.setFillColor(sf::Color(0xFF, 0x09, 0x80));

            ellipse.setPointCount(pointCount);
            for (int pointNo = 0; pointNo < pointCount; ++pointNo)
            {
                float angle = float(2 * M_PI * pointNo) / float(pointCount);
                sf::Vector2f point = {
                    ellipseRadius.x * std::sin(angle),
                    ellipseRadius.y * std::cos(angle),
                };
                ellipse.setPoint(pointNo, point);
            }

            shapes.push_back(ellipse);
            drawingItemAngle += 2 * M_PI / 12;
        }

        return shapes;
    }
}

int main()
{
    const sf::Vector2f windowCenter = { double(WINDOW_WIDTH) / 2, double(WINDOW_HEIGHT) / 2 };
    const float movingRadius = 50;
    const float angleSpeed = M_PI;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Ellipse",
        sf::Style::Default, settings
    );

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

        const float time = clock.getElapsedTime().asSeconds();
        sf::Vector2f centerPoint = {
            windowCenter.x + movingRadius * std::cos(angleSpeed * time),
            windowCenter.y + movingRadius * std::sin(angleSpeed * time),
        };
        auto shapes = GetShapes(centerPoint);


        window.clear();
        for (auto& shape : shapes)
        {
            window.draw(shape);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
