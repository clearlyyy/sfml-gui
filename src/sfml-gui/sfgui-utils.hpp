// sfgui-utils.hpp
// Contains a bunch of useful helper functions that will get used alot.

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

inline void centerText(sf::Text& text, const sf::RectangleShape& rect) {
    sf::FloatRect bounds = text.getLocalBounds();

    // Compute origin from position + size
    text.setOrigin(bounds.position + bounds.size / 2.0f);

    // Set position to center of rectangle
    text.setPosition(rect.getPosition() + rect.getSize() / 2.0f);
}

inline bool isMouseInsideRect(sf::RenderWindow& window, const sf::RectangleShape& rect)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect bounds = rect.getGlobalBounds();
    return (bounds.contains(static_cast<sf::Vector2f>(mousePos)));
}

inline sf::Color Darken(sf::Shape &shape)
{
    sf::Color darkenedColor = sf::Color(shape.getFillColor().r - 20, shape.getFillColor().g - 20, shape.getFillColor().b - 20);
    return darkenedColor;
}

inline void scaleFromCenter(sf::RectangleShape& rect, const float scaleFactor)
{
    sf::Vector2f oldSize = rect.getSize();
    sf::Vector2f newSize(sf::Vector2f(oldSize.x * scaleFactor, oldSize.y * scaleFactor));

    sf::Vector2f offset = (newSize - oldSize) / 2.f;
    rect.setScale(sf::Vector2f(scaleFactor, scaleFactor));

    rect.setPosition(rect.getPosition() - offset);
}