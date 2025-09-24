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
// THINGS ARE NOT GUARANTEED TO LOOK NICE IF CHANGING THESE SETTINGS
inline constexpr uint16_t     DEFAULT_GUI_SIZE_X   = 400;
inline constexpr uint16_t     DEFAULT_GUI_SIZE_Y   = 300;
inline constexpr int          DEFAULT_BAR_HEIGHT   = 24;
inline constexpr sf::Vector2f DEFAULT_GUI_POSITION = sf::Vector2f(30, 30);
inline constexpr sf::Color    GUI_BACKGROUND_COLOR = sf::Color(14, 14, 14);
inline constexpr sf::Color    GUI_PRIMARY_COLOR    = sf::Color(6, 87, 194);
inline constexpr sf::Color    GUI_TEXT_COLOR       = sf::Color::White;
inline constexpr sf::Vector2f DEFAULT_BUTTON_SIZE  = sf::Vector2f(100, 30);
inline constexpr uint8_t      CHARACTER_SIZE       = 15;
inline constexpr uint8_t      WIDGET_PADDING_HOR   = 10;
inline constexpr uint8_t      WIDGET_PADDING_VER   = 15;
inline constexpr uint8_t      BORDER_THICKNESS     = 1;
inline constexpr sf::Color    BORDER_COLOR         = sf::Color(54, 54, 54);



extern sf::Font TEXT_FONT;

class SFMLGUI {
public:
    SFMLGUI(sf::RenderWindow& window);

    void Add(SFWIDGET& widget);
    void Draw();

    void Setup();
    void Update();

    void Hide();
    void Show();
    void Close();
    void Open();

    void setWindowTitle(const std::string& text);
    
    std::vector<SFWIDGET*> SF_WIDGETS;
private:
    sf::RenderWindow* SF_WINDOW; 

    // WINDOW ELEMENTS ///////////
    sf::RectangleShape BG;      
                                
    sf::RectangleShape BAR;     
    sf::Text WIN_TEXT;
    sf::RectangleShape CLOSE_BUTTON;
    sf::RectangleShape CLOSE_BUTTON_BG;
    sf::RectangleShape HIDE_BUTTON;
    sf::RectangleShape HIDE_BUTTON_BG;
    sf::Texture CLOSE_TEXTURE;
    sf::Texture HIDE_TEXTURE;
    //////////////////////////////

    bool dragging;
    sf::Vector2f dragOffset;
    bool hidden = false;
    bool closed = false;
    bool leftMouseWasPressed = false;
    std::string WIN_TITLE;

    sf::Vector2f pos;

};

}