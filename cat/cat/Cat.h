#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <stdexcept>

class Cat
{
public:
    Cat(sf::Vector2f position)
    {
        if (!m_texture.loadFromFile("cat.png"))
        {
            throw new std::exception("Can`t find cat.png file");
        }
        m_cat.setTexture(m_texture);
        m_cat.setPosition(position);
        m_cat.setOrigin(19, 17);
    }

    void Update(sf::Vector2f& mousePosition, float deltaTime)
    {
        const sf::Vector2f delta = mousePosition - m_cat.getPosition();
        const float angle = std::atan2(delta.y, delta.x);
        double degrees = ToDegrees(angle);
        if (degrees < 0)
        {
            degrees = 360 - abs(degrees);
        }
        m_cat.setScale((degrees > 90 && degrees < 270) ? -1 : 1, 1);

        sf::Vector2f moveSpeed;
        moveSpeed.x = std::min(std::abs(delta.x), MAX_MOVE_SPEED) * GetSign(delta.x);
        moveSpeed.y = std::min(std::abs(delta.y), MAX_MOVE_SPEED) * GetSign(delta.y);
        moveSpeed *= deltaTime;
        m_cat.move(moveSpeed);
    }

    void Draw(sf::RenderWindow& window) const
    {
        window.draw(m_cat);
    }

private:
    sf::Texture m_texture;
    sf::Sprite m_cat;
    const float MAX_ROTATION_SPEED = 90;
    const float MAX_MOVE_SPEED = 20;

    float ToDegrees(float radians) const
    {
        return float(double(radians) * 180.0 / M_PI);
    }

    float ToRadians(float degree) const
    {
        return float(double(degree) * M_PI / 180.0);
    }

    float GetSign(float number) const
    {
        return number < 0 ? -1 : 1;
    }
};