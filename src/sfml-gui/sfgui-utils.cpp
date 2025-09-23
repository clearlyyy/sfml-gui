// sfgui-utils.cpp
// Contains a bunch of useful helper functions that will get used alot.

#include <SFML/Graphics.hpp>

void centerText(sf::Text& text, const sf::RectangleShape& rect) {
    sf::FloatRect bounds = text.getLocalBounds();

    // Compute origin from position + size
    text.setOrigin(bounds.position + bounds.size / 2.0f);

    // Set position to center of rectangle
    text.setPosition(rect.getPosition() + rect.getSize() / 2.0f);
}