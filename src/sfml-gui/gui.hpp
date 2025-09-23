// SFML-GUI 2.0
// - Clearly
// Fast, Easy to use GUI for SFML Projects

#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include "sf_widget.h"


namespace SFGUI {

// Configuration Settings
inline constexpr uint16_t     DEFAULT_GUI_SIZE_X   = 400;
inline constexpr uint16_t     DEFAULT_GUI_SIZE_Y   = 300;
inline constexpr int          DEFAULT_BAR_HEIGHT   = 20;
inline constexpr sf::Vector2f DEFAULT_GUI_POSITION = sf::Vector2f(30, 30);
inline constexpr sf::Color    GUI_BACKGROUND_COLOR = sf::Color(14, 14, 14);
inline constexpr sf::Color    GUI_PRIMARY_COLOR    = sf::Color(6, 87, 194);
inline constexpr sf::Color    GUI_TEXT_COLOR       = sf::Color::White;
inline constexpr sf::Vector2f DEFAULT_BUTTON_SIZE  = sf::Vector2f(100, 30);
inline constexpr uint8_t      CHARACTER_SIZE       = 12;
inline constexpr uint8_t      WIDGET_PADDING_HOR   = 10;
inline constexpr uint8_t      WIDGET_PADDING_VER   = 15;


extern sf::Font TEXT_FONT;

class SFMLGUI {
public:
    SFMLGUI(sf::RenderWindow& window);

    void Add(SFWIDGET& widget);
    void Draw();

    void Update();
    
    std::vector<SFWIDGET*> SF_WIDGETS;
private:
    sf::RectangleShape BG;
    sf::RectangleShape BAR;
    sf::RenderWindow* SF_WINDOW;

    sf::Vector2f pos;

};

}