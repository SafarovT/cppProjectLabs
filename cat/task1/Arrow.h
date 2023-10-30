#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include <Windows.h>

class Arrow
{
public:
    Arrow(sf::Vector2f position)
    {
        m_arrow.setPointCount(7);
        m_arrow.setPosition(position);
        m_arrow.setPoint(0, { 0, -50 });
        m_arrow.setPoint(1, { -40, -10 });
        m_arrow.setPoint(2, { -20, -10 });
        m_arrow.setPoint(3, { -20, 50 });
        m_arrow.setPoint(4, { 20, 50 });
        m_arrow.setPoint(5, { 20, -10 });
        m_arrow.setPoint(6, { 40, -10 });
        m_arrow.setFillColor(sf::Color::Yellow);
        m_arrow.setOutlineColor(sf::Color::Black);
        m_arrow.setOutlineThickness(2);
        m_arrow.setRotation(0);
    }

    void Update(sf::Vector2f& mousePosition, float deltaTime)
    {
        const sf::Vector2f delta = mousePosition - m_arrow.getPosition();
        const float angle = std::atan2(delta.y, delta.x);
        double degrees = ToDegrees(angle);
        if (degrees < 0)
        {
            degrees = 360 - abs(degrees);
        }

        double deltaAngle = degrees - m_arrow.getRotation() + 90;
        if (abs(deltaAngle) > 180)
        {
            deltaAngle = (360 - abs(deltaAngle)) * (deltaAngle > 0 ? -1 : 1);
        }
        deltaAngle = deltaAngle / deltaTime;
        if (std::abs(deltaAngle) > MAX_ROTATION_SPEED * deltaTime)
        {
            deltaAngle = deltaAngle > 0 ? MAX_ROTATION_SPEED * deltaTime : -MAX_ROTATION_SPEED * deltaTime;
        }
        m_arrow.rotate(float(deltaAngle));

        if (abs(deltaAngle) > 10)
        {
            return;
        }

        sf::Vector2f topPointPosition = m_arrow.getTransform().transformPoint(m_arrow.getPoint(0));
        sf::Vector2f deltaMove = mousePosition - topPointPosition;
        sf::Vector2f moveSpeed;
        moveSpeed.x = std::min(std::abs(deltaMove.x), MAX_MOVE_SPEED) * GetSign(deltaMove.x);
        moveSpeed.y = std::min(std::abs(deltaMove.y), MAX_MOVE_SPEED) * GetSign(deltaMove.y);
        moveSpeed *= deltaTime;
        m_arrow.move(moveSpeed);
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_arrow);
    }

private:
    sf::ConvexShape m_arrow;
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