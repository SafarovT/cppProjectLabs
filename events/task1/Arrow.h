#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include <Windows.h>

class Arrow
{
public:
    Arrow()
    {
        m_position = { 400, 300 };
        m_head.setPointCount(3);
        m_head.setPoint(0, { 30, 0 });
        m_head.setPoint(1, { 0, -20 });
        m_head.setPoint(2, { 0, 20 });
        m_head.setFillColor(sf::Color::Red);

        m_stem.setSize({ 80, 20 });
        m_stem.setOrigin({ 40, 10 });
        m_stem.setFillColor(sf::Color(0xF0, 0xA0, 0x00));

        sf::Vector2f startMousePos = { m_position.x + 100, m_position.y };
        Update(startMousePos);
    }

    void Update(sf::Vector2f& mousePosition)
    {
        const sf::Vector2f delta = mousePosition - m_position;
        float rotation360 = m_rotation + M_PI;
        float angle360 = atan2(delta.y, delta.x) + M_PI;
        // mouse : 180
        // rotation : 140
        // positive : 180 - 140 = 40
        // negative : 140 + 360 - 180
        float positiveWayDelta = angle360 - rotation360;
        float negativeWayDelta = rotation360 - angle360 + M_PI * 2;
        std::cout << positiveWayDelta << std::endl << negativeWayDelta << std::endl << std::endl;
        //Sleep(2000);
        float rotationSpeed = 0;
        if (positiveWayDelta <= negativeWayDelta)
        {
            rotationSpeed = positiveWayDelta;
        }
        else
        {
            rotationSpeed = negativeWayDelta;
        }
        rotationSpeed = std::min(rotationSpeed, MAX_RAD_SPEED);
        m_rotation += rotationSpeed;
        UpdateArrowElements();
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_head);
        window.draw(m_stem);
    }

private:
    sf::ConvexShape m_head;
    sf::RectangleShape m_stem;
    sf::Vector2f m_position;
    float m_rotation = 0;
    float MAX_RAD_SPEED = ToRadians(5);

    void UpdateArrowElements()
    {
        const sf::Vector2f headOffset = ToEuclidean(40, m_rotation);
        m_head.setPosition(m_position + headOffset);
        m_head.setRotation(ToDegrees(m_rotation));

        const sf::Vector2f stemOffset = ToEuclidean(-10, m_rotation);
        m_stem.setPosition(m_position);
        m_stem.setRotation(ToDegrees(m_rotation));
    }

    sf::Vector2f ToEuclidean(float radius, float angle) const
    {
        return
        {
            radius * cos(angle),
            radius * sin(angle)
        };
    }

    float ToDegrees(float radians) const
    {
        return float(double(radians) * 180.0 / M_PI);
    }

    float ToRadians(float degree) const
    {
        return float(double(degree) * M_PI / 180.0);
    }

    float GetAbs(float number)
    {
        return number < 0 ? -number : number;
    }
}; 