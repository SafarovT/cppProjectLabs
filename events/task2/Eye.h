#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Eye
{
public:
    Eye(float x, float y)
    {
        m_center = { x, y };
        int pointCount = 1000;

        sf::ConvexShape ellipse;
        ellipse.setPosition({ x, y });
        ellipse.rotate(90);
        ellipse.setFillColor(sf::Color::White);

        ellipse.setPointCount(pointCount);
        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            sf::Vector2f point = {
                100 * std::sin(angle),
                30 * std::cos(angle),
            };
            ellipse.setPoint(pointNo, point);
        }

        m_eye = ellipse;

        sf::ConvexShape ellipse2;
        ellipse2.setPosition({ x, y });
        ellipse2.rotate(90);
        ellipse2.setFillColor(sf::Color::Black);

        ellipse2.setPointCount(pointCount);
        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            sf::Vector2f point = {
                15 * std::sin(angle),
                10 * std::cos(angle),
            };
            ellipse2.setPoint(pointNo, point);
        }

        m_pupil = ellipse2;

        sf::Vector2f startMousePos = { m_pupil.getPosition().x + 100, m_pupil.getPosition().y};
        Update(startMousePos);
    }

    void Update(sf::Vector2f& mousePosition)
    {
        if (
            (mousePosition.x >= m_center.x - MAX_DIST_FROM_CENTER.x && mousePosition.x <= m_center.x + MAX_DIST_FROM_CENTER.x)
            && (mousePosition.y >= m_center.y - MAX_DIST_FROM_CENTER.y && mousePosition.y <= m_center.y + MAX_DIST_FROM_CENTER.y))
        {
            m_pupil.setPosition(mousePosition);
            return;
        }
        const sf::Vector2f delta = mousePosition - m_center;
        const float angle = std::atan2(delta.y, delta.x);
        
        m_pupil.setPosition({
            m_center.x + 15 * cos(angle),
            m_center.y + 50 * sin(angle),
        });

        UpdateArrowElements();
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_eye);
        window.draw(m_pupil);
    }

private:
    sf::ConvexShape m_eye, m_pupil;
    sf::Vector2f m_center;
    sf::Vector2f MAX_DIST_FROM_CENTER = { 15, 50 };

    void UpdateArrowElements()
    {
        
    }
};