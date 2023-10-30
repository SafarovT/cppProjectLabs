#pragma once
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <stdexcept>

class Pointer
{
public:
	Pointer()
	{
		if (!m_texture.loadFromFile("red_pointer.png"))
		{
			throw new std::exception("Can`t find cat.png file");
		}
		m_pointer.setTexture(m_texture);
		m_pointer.setOrigin(16, 16);
	}

    void Update(sf::Vector2f& mousePosition)
    {
		m_pointer.setPosition(mousePosition);
    }

    void Draw(sf::RenderWindow& window) const
    {
        window.draw(m_pointer);
    }

private:
	sf::Texture m_texture;
	sf::Sprite m_pointer;
};