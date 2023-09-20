#pragma once
#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"

namespace
{
	const sf::Color BACKGROUND_COLOR = sf::Color::White;

	using Shapes = std::vector<std::shared_ptr<sf::Shape>>;
}

void CreateShapesTask1(Shapes& shapes)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(125, 124, 124));
	rect.setSize(sf::Vector2f(200, 650));
	rect.setPosition(sf::Vector2f(20, 20));
	shapes.push_back(std::make_shared<sf::RectangleShape>(rect));

	sf::CircleShape circle1;
	circle1.setFillColor(sf::Color::Green);
	circle1.setRadius(90);
	circle1.setPosition(sf::Vector2f(30, 55));
	shapes.push_back(std::make_shared<sf::CircleShape>(circle1));

	circle1.setFillColor(sf::Color::Yellow);
	circle1.setPosition(sf::Vector2f(30, 255));
	shapes.push_back(std::make_shared<sf::CircleShape>(circle1));

	circle1.setFillColor(sf::Color::Red);
	circle1.setPosition(sf::Vector2f(30, 455));
	shapes.push_back(std::make_shared<sf::CircleShape>(circle1));
}

void CreateShapesTask2(Shapes& shapes)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(sf::Vector2f(10, 10));
	rect.setSize(sf::Vector2f(300, 50));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(125, 60 ));
	rect.setSize(sf::Vector2f(50, 300));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(430, 10));
	rect.setSize(sf::Vector2f(300, 50));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(430, 310));
	rect.setSize(sf::Vector2f(300, 50));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(430, 60));
	rect.setSize(sf::Vector2f(50, 300));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(780, 10));
	rect.setSize(sf::Vector2f(50, 350));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(830, 10));
	rect.setSize(sf::Vector2f(190, 50));
	rect.setRotation(45);
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setRotation(0);
	rect.setPosition(sf::Vector2f(1030, 10));
	rect.setSize(sf::Vector2f(50, 350));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(1069, 43));
	rect.setSize(sf::Vector2f(195, 50));
	rect.setRotation(135);
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));
}

void CreateShapesTask3(Shapes& shapes)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(102, 37, 73));
	rect.setPosition(sf::Vector2f(50, 500));
	rect.setSize(sf::Vector2f(700, 400));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	sf::ConvexShape conv;
	conv.setFillColor(sf::Color(174, 68, 90));
	conv.setPointCount(4);
	conv.setPoint(0, sf::Vector2f(20, 500));
	conv.setPoint(1, sf::Vector2f(780, 500));
	conv.setPoint(2, sf::Vector2f(700, 350));
	conv.setPoint(3, sf::Vector2f(100, 350));
	shapes.push_back(std::make_unique<sf::ConvexShape>(conv));

	rect.setFillColor(sf::Color::Black);
	rect.setPosition(sf::Vector2f(120, 600));
	rect.setSize(sf::Vector2f(150, 300));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setFillColor(sf::Color(150, 150, 150));
	rect.setPosition(sf::Vector2f(600, 300));
	rect.setSize(sf::Vector2f(40, 100));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	rect.setPosition(sf::Vector2f(550, 300));
	rect.setSize(sf::Vector2f(140, 60));
	shapes.push_back(std::make_unique<sf::RectangleShape>(rect));

	sf::CircleShape circle;
	circle.setFillColor(sf::Color(200, 200, 200));
	circle.setRadius(30);
	circle.setPosition(sf::Vector2f(620, 250));
	shapes.push_back(std::make_shared<sf::CircleShape>(circle));

	circle.setRadius(40);
	circle.setPosition(sf::Vector2f(650, 200));
	shapes.push_back(std::make_shared<sf::CircleShape>(circle));

	circle.setRadius(50);
	circle.setPosition(sf::Vector2f(680, 160));
	shapes.push_back(std::make_shared<sf::CircleShape>(circle));

	circle.setRadius(60);
	circle.setPosition(sf::Vector2f(720, 110));
	shapes.push_back(std::make_shared<sf::CircleShape>(circle));
}

void DrawShapes(Shapes const& shapes, double width, double height)
{
	sf::RenderWindow window(sf::VideoMode(width, height), "My window");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (auto shape : shapes)
		{
			window.draw(*shape);
		}

		window.display();
	}
}

int main()
{
	Shapes shapes;

	CreateShapesTask1(shapes);
	DrawShapes(shapes, 240, 690);
	shapes.clear();

	CreateShapesTask2(shapes);
	DrawShapes(shapes, 1600, 1000);
	shapes.clear();

	CreateShapesTask3(shapes);
	DrawShapes(shapes, 1000, 1000);
	shapes.clear();

	return EXIT_SUCCESS;
}