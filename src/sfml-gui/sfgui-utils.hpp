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