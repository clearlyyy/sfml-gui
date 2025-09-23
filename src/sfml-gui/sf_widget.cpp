// sf_widget.cpp
// Definitions for sf_widget.h

#include "sf_widget.h"
#include <algorithm>

// Helper
sf::FloatRect combineRects(const sf::FloatRect& a, const sf::FloatRect b) {
    float minX = std::min(a.position.x, b.position.x);
    float minY = std::min(a.position.y, b.position.y);
    float maxX = std::max(a.position.x + a.size.x, b.position.x + b.size.x);
    float maxY = std::max(a.position.y + a.size.y, b.position.y + b.size.y);

    return sf::FloatRect{ {minX, minY}, {maxX - minX, maxY - minY} };
}

SFGUI::SFWIDGET::SFWIDGET(const std::string &n) {
    w_index = counter++; 

    w_size = computeBoundingBox(t_parts);
    w_pos = sf::Vector2f(10, 10);
    std::cout << "New Widget Created: " << n << std::endl;
}

void SFGUI::SFWIDGET::Draw(sf::RenderWindow &window) 
{
    for (auto& part : d_parts) {
        window.draw(*part);
    }
}

void SFGUI::SFWIDGET::DebugOutput() 
{
    std::cout << "-------SFWIDGET: " << name << "-------DEBUG OUTPUT-----" << std::endl;
    std::cout << "INDEX: " << w_index << std::endl;
    std::cout << "TOTAL PARTS: "  << t_parts.size() << std::endl;
    std::cout << "BOUNDING BOX SIZE: " << w_size.size.x << " , " << w_size.size.y << std::endl;
    std::cout << "POSITION: " << w_pos.x << " , " << w_pos.y << std::endl;
}

void SFGUI::SFWIDGET::Update()
{
   w_size = computeBoundingBox(t_parts);
}

void SFGUI::SFWIDGET::SoftUpdate()
{
    // do nothing right now   
}

sf::FloatRect SFGUI::SFWIDGET::computeBoundingBox(const std::vector<sf::Transformable*>& parts) {
    sf::FloatRect totalBounds;
    bool first = true;

    for (sf::Transformable* d : parts) {
        sf::FloatRect bounds;
        if (auto* shape = dynamic_cast<sf::Shape*>(d)) {
            bounds = shape->getGlobalBounds();
        } else if (auto* text = dynamic_cast<sf::Text*>(d)) {
            bounds = text->getGlobalBounds();
        } else if (auto* sprite = dynamic_cast<sf::Sprite*>(d)) {
            bounds = sprite->getGlobalBounds();
        } else {
            continue; // Skip
        }

        if (first) {
            totalBounds = bounds;
            first = false;
        } else {
            totalBounds = combineRects(totalBounds, bounds);
        }
    }

    return totalBounds;
}

void SFGUI::SFWIDGET::setPosition(sf::Vector2f pos)
{
    w_pos = pos;
    std::cout << "Updated Position" << w_pos.x << "," << w_pos.y << std::endl;
}

// Definition of the static counter
uint8_t SFGUI::SFWIDGET::counter = 0;