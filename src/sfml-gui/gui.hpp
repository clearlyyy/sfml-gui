// SFML-GUI 2.0
// Fast, Easy to use GUI for SFML Projects
// - Clearly

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
inline constexpr sf::Vector2f MINIMUM_GUI_SIZE     = sf::Vector2f(50, 50);
inline constexpr int          DEFAULT_BAR_HEIGHT   = 24;
inline constexpr sf::Vector2f DEFAULT_GUI_POSITION = sf::Vector2f(100, 300);
inline constexpr sf::Color    GUI_BACKGROUND_COLOR = sf::Color(46, 52, 64, 150);
inline constexpr sf::Color    GUI_PRIMARY_COLOR    = sf::Color(76, 86, 106);
inline constexpr sf::Color    GUI_TEXT_COLOR       = sf::Color::White;
inline constexpr sf::Vector2f DEFAULT_BUTTON_SIZE  = sf::Vector2f(100, 20);
inline constexpr sf::Vector2f DEFAULT_LIST_SIZE    = sf::Vector2f(200, DEFAULT_BUTTON_SIZE.y);
inline constexpr uint8_t      CHARACTER_SIZE       = 15;
inline constexpr uint8_t      WIDGET_PADDING_HOR   = 10;
inline constexpr uint8_t      WIDGET_PADDING_VER   = 5;
inline constexpr uint8_t      BORDER_THICKNESS     = 1;
inline constexpr sf::Color    BORDER_COLOR         = sf::Color(54, 54, 54, 150);
inline constexpr sf::Color    HOVER_COLOR          = sf::Color(GUI_PRIMARY_COLOR.r-20, GUI_PRIMARY_COLOR.g-20, GUI_PRIMARY_COLOR.b-20);
inline constexpr sf::Color    CLICK_COLOR          = sf::Color(GUI_PRIMARY_COLOR.r+20, GUI_PRIMARY_COLOR.g+20, GUI_PRIMARY_COLOR.b+20);
inline constexpr float        CHECKBOX_SIZE        = 20;
inline constexpr float        SLIDER_PICK_WIDTH    = 15;
inline constexpr float        RESIZE_RECT_SIZE     = 24;
inline constexpr float        RESIZE_BOUNDS_SIZE   = 36;
inline constexpr float        CARET_WIDTH          = 1;

extern sf::Font TEXT_FONT;

class SFMLGUI {
public:

    // Constructor, Peforms setup
    // Creates and places window decorations;
    SFMLGUI(sf::RenderWindow& window, std::string window_title);
    
    // Adds a SFWIDGET to the SF_WIDGETS list. 
    void Add(SFWIDGET& widget);

    // Draws all window decorations along with all SFWIDGETS.
    void Draw();

    // Draws Widget Bounding Boxes, for debugging widget sizes only.
    void DebugDraw();

    // Setup, After all widgets are added to the GUI, we need to do an initial setup
    // This should be called after all widgets are added with SFMLGUI::Add();
    void Setup();

    // Update, Runs every frame, handles interactions with window decorations, and calls each 
    // widgets SoftUpdate() function
    void Update();

    // For polling sf::Events.
    void pollEvents(const sf::Event& e);

    // Hides the GUI, while keeping the window title bar visiable.
    void Hide();
    // Shows the GUI after its been hidden.
    void Show();

    // Closes the GUI (including the window title bar) nothing is visible.
    void Close();
    // Opens the GUI after being closed.
    void Open();

    // Set the title of the GUI Window 
    void setWindowTitle(const std::string& text);
    
    // List of all the widgets contained in the GUI.
    std::vector<SFWIDGET*> SF_WIDGETS;
private:
    // Pointer to the main sf::RenderWindow
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

    sf::RectangleShape RESIZE_AREA;
    sf::RectangleShape RESIZE_RECT;
    sf::Texture RESIZE_TEXTURE;

    sf::IntRect guiRect;

    //////////////////////////////

    bool dragging;
    bool resizing;
    sf::Vector2f dragOffset;
    bool hidden = false;
    bool closed = false;
    bool leftMouseWasPressed = false;
    std::string WIN_TITLE;

    sf::Cursor::Type cursorToUse = sf::Cursor::Type::Arrow;

    sf::Vector2f pos;

};

}