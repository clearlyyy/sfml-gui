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

// Check if mouse is inside rect.
inline bool isMouseInsideRect(sf::RenderWindow& window, const sf::RectangleShape& rect)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect bounds = rect.getGlobalBounds();
    return (bounds.contains(static_cast<sf::Vector2f>(mousePos)));
}
// Check if mouse is inside rect accounting for the GUI size (Making sure we cant interact with widgets that are being masked by the GUI)
inline bool isMouseInsideRect(sf::RenderWindow& window, const sf::RectangleShape& rect, const sf::RectangleShape *gui_window)
{
    if (isMouseInsideRect(window, *gui_window)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect bounds = rect.getGlobalBounds();
        return (bounds.contains(static_cast<sf::Vector2f>(mousePos)));
    }
    return false;
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

// for converting from any number to a string with decimal precision.
template <typename T>
std::string to_string_prec(T* value, int decimals = 2)
{
    int size = 32;
    std::vector<char> buffer(size);
    while (true) {
        int n;
        if constexpr (std::is_integral_v<T>) {
            n = snprintf(buffer.data(), buffer.size(), "%lld", static_cast<long long>(*value));
        } else {
            n = snprintf(buffer.data(), buffer.size(), "%.*f", decimals, *value);
        }

        if (n < 0) {
            throw std::runtime_error("snprintf error!, called from to_string_prec in sfgui-utils.hpp");
        }
        if (n < static_cast<int>(buffer.size())) {
            return std::string(buffer.data(), n);
        }

        // Buffer too small, increase size.
        buffer.resize(n + 1);
    }
}