#include "gui.hpp"
#include "sfgui-utils.hpp"
#include <SFML/OpenGL.hpp>

sf::Font SFGUI::TEXT_FONT; 

// Constructor
// This initializes the GUI Window, Placing things like the BG, BAR, Hide button, close button, and title in the correct place.
SFGUI::SFMLGUI::SFMLGUI(sf::RenderWindow& window, std::string window_title) : pos(DEFAULT_GUI_POSITION), dragging(false),
                                                    WIN_TEXT(TEXT_FONT, "sfml-gui", CHARACTER_SIZE)
{

    // This is a cluster fuck of ui programming but it works
    
    SF_WINDOW = &window;
    WIN_TITLE = window_title;

    // Load a font once globally
    if (!SFGUI::TEXT_FONT.openFromFile("sfml-gui-assets/Poppins-Medium.ttf")) {
        std::cout << "Default Font failed to load :(" << std::endl;
    }

    BG.setFillColor(GUI_BACKGROUND_COLOR);
    BG.setSize(sf::Vector2f(DEFAULT_GUI_SIZE_X, DEFAULT_GUI_SIZE_Y)); 
    BG.setPosition(DEFAULT_GUI_POSITION);
    BG.setOutlineThickness(BORDER_THICKNESS);
    BG.setOutlineColor(BORDER_COLOR);

    BAR.setFillColor(GUI_PRIMARY_COLOR);
    BAR.setPosition(sf::Vector2f(DEFAULT_GUI_POSITION.x, (DEFAULT_GUI_POSITION.y - DEFAULT_BAR_HEIGHT)));
    BAR.setSize(sf::Vector2f(DEFAULT_GUI_SIZE_X, DEFAULT_BAR_HEIGHT));
    BAR.setOutlineThickness(BORDER_THICKNESS);
    BAR.setOutlineColor(BORDER_COLOR);

    sf::FloatRect barBounds = BAR.getGlobalBounds();

    WIN_TEXT.setFillColor(GUI_TEXT_COLOR);
    
    if (!CLOSE_TEXTURE.loadFromFile("sfml-gui-assets/close_tex.png"))
    std::cout << "Failed to load CLOSE_TEXTURE" << std::endl;
    if (!HIDE_TEXTURE.loadFromFile("sfml-gui-assets/hide_tex.png"))
    std::cout << "Failed to load HIDE_TEXTURE" << std::endl;
    
    HIDE_BUTTON.setTexture(&HIDE_TEXTURE);
    HIDE_BUTTON.setSize(sf::Vector2f(DEFAULT_BAR_HEIGHT/2, DEFAULT_BAR_HEIGHT/2));
    HIDE_BUTTON.setOrigin(sf::Vector2f(HIDE_BUTTON.getSize().x/2.f, HIDE_BUTTON.getSize().y/2.f));
    HIDE_BUTTON_BG.setSize(sf::Vector2f(DEFAULT_BAR_HEIGHT, DEFAULT_BAR_HEIGHT));
    HIDE_BUTTON_BG.setPosition(BAR.getPosition());
    HIDE_BUTTON_BG.setFillColor(sf::Color::Transparent);
    HIDE_BUTTON.setPosition(sf::Vector2f(BAR.getPosition().x + WIDGET_PADDING_HOR, BAR.getPosition().y + BAR.getSize().y / 2.f));
    
    CLOSE_BUTTON.setSize(sf::Vector2f(DEFAULT_BAR_HEIGHT/2, DEFAULT_BAR_HEIGHT/2));
    CLOSE_BUTTON.setOrigin(sf::Vector2f(CLOSE_BUTTON.getSize().x/2.f, CLOSE_BUTTON.getSize().y/2.f));
    CLOSE_BUTTON.setTexture(&CLOSE_TEXTURE);
    CLOSE_BUTTON_BG.setSize(sf::Vector2f(DEFAULT_BAR_HEIGHT, DEFAULT_BAR_HEIGHT));
    CLOSE_BUTTON_BG.setPosition(sf::Vector2f(BAR.getPosition().x + BAR.getSize().x - CLOSE_BUTTON_BG.getSize().x, BAR.getPosition().y));
    CLOSE_BUTTON_BG.setFillColor(sf::Color::Transparent);
    CLOSE_BUTTON.setPosition(CLOSE_BUTTON_BG.getPosition() + sf::Vector2f(CLOSE_BUTTON_BG.getSize().x/2, CLOSE_BUTTON_BG.getSize().y/2));
    
    if (!hidden)
        HIDE_BUTTON.setRotation(sf::degrees(180));
    
    // Resize area
    if (!RESIZE_TEXTURE.loadFromFile("sfml-gui-assets/resize_tex.png"))
        std::cout << "Failed to load RESIZE_TEXTURE" << std::endl;
    RESIZE_RECT.setSize(sf::Vector2f(RESIZE_RECT_SIZE, RESIZE_RECT_SIZE));
    RESIZE_RECT.setTexture(&RESIZE_TEXTURE);
    RESIZE_RECT.setPosition(sf::Vector2f(BG.getPosition().x + BG.getSize().x - RESIZE_RECT_SIZE, BG.getPosition().y + BG.getSize().y - RESIZE_RECT_SIZE));
    RESIZE_AREA.setSize(sf::Vector2f(RESIZE_BOUNDS_SIZE, RESIZE_BOUNDS_SIZE));
    RESIZE_AREA.setOrigin(sf::Vector2f(RESIZE_AREA.getSize().x/2.f, RESIZE_AREA.getSize().y/2.f));
    RESIZE_AREA.setPosition(sf::Vector2f(BG.getPosition().x + BG.getSize().x, BG.getPosition().y + BG.getSize().y));

    
    this->setWindowTitle(WIN_TITLE);
    this->Update();
}

void SFGUI::SFMLGUI::setWindowTitle(const std::string& text)
{
    WIN_TITLE = text;
    WIN_TEXT.setString(WIN_TITLE);
    sf::FloatRect barBounds = BAR.getGlobalBounds();
    sf::FloatRect textBounds = WIN_TEXT.getLocalBounds();

    WIN_TEXT.setPosition(sf::Vector2f(BAR.getPosition().x + (WIDGET_PADDING_HOR*2) + HIDE_BUTTON.getSize().x,
                         barBounds.position.y + (barBounds.size.y - textBounds.size.y) / 2.f - textBounds.position.y));
}

void SFGUI::SFMLGUI::Draw()
{
    if (!closed) {
        if (!hidden) {
            SF_WINDOW->draw(BG);
            // SCISSOR TEST for masking widgets, keeping them from overflowing outside the gui. //
            sf::Vector2i pos = static_cast<sf::Vector2i>(BG.getPosition());
            sf::Vector2i size = static_cast<sf::Vector2i>(BG.getSize());
            GLint guiPrevScissor[4];
            glGetIntegerv(GL_SCISSOR_BOX, guiPrevScissor);
            glEnable(GL_SCISSOR_TEST);
            glScissor(pos.x, SF_WINDOW->getSize().y - (pos.y + size.y), size.x, size.y);
            for (SFWIDGET* widget : SF_WIDGETS) {
                widget->Draw(*SF_WINDOW);
            }
            glScissor(guiPrevScissor[0], guiPrevScissor[1], guiPrevScissor[2], guiPrevScissor[3]); 
            glDisable(GL_SCISSOR_TEST);
            //                                                                                  //
            SF_WINDOW->draw(RESIZE_RECT);
        }
        SF_WINDOW->draw(BAR);
        {
            glEnable(GL_SCISSOR_TEST);
            GLint scissorX = static_cast<GLint>(BAR.getPosition().x);
            GLint scissorY = static_cast<GLint>(SF_WINDOW->getSize().y - (BAR.getPosition().y + BAR.getSize().y));
            GLint scissorWidth = static_cast<GLint>(CLOSE_BUTTON_BG.getPosition().x - BAR.getPosition().x);
            GLint scissorHeight = static_cast<GLint>(BAR.getSize().y); 
            glScissor(scissorX, scissorY, scissorWidth, scissorHeight);
            SF_WINDOW->draw(WIN_TEXT);
            glDisable(GL_SCISSOR_TEST);
        }
        SF_WINDOW->draw(CLOSE_BUTTON_BG);
        SF_WINDOW->draw(CLOSE_BUTTON);
        SF_WINDOW->draw(HIDE_BUTTON_BG);
        SF_WINDOW->draw(HIDE_BUTTON);
    }
}

void SFGUI::SFMLGUI::Add(SFWIDGET& widget)
{
    SF_WIDGETS.push_back(&widget);
    this->Setup();
}

// TODO: THIS FUNCTION GLOBALLY HIJACKS THE MOUSE CURSOR STATE, FIX!
void SFGUI::SFMLGUI::Update()
{

    if (!closed) {
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(*SF_WINDOW);
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(mousePosWindow);
    bool leftMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    bool hovering = false;
    cursorToUse = sf::Cursor::Type::Arrow;

    // Resizing
    if (isMouseInsideRect(*SF_WINDOW, RESIZE_AREA)) {
        cursorToUse = sf::Cursor::Type::SizeBottomRight;
        if (leftMousePressed) {
            resizing = true;

            float newWidth  = mousePos.x - BG.getPosition().x;
            float newHeight = mousePos.y - BG.getPosition().y;
            if (newWidth  < MINIMUM_GUI_SIZE.x) newWidth  = MINIMUM_GUI_SIZE.x;
            if (newHeight < MINIMUM_GUI_SIZE.y) newHeight = MINIMUM_GUI_SIZE.y;

            BG.setSize(sf::Vector2f(
                newWidth,
                newHeight
            )); 
           
        } else {
            resizing = false;
        }
    } 

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

        if (!dragging && isMouseInsideRect(*SF_WINDOW, BAR)) {
            dragging = true;
            dragOffset = mousePos - pos; 
        }

        if (resizing) {
            BAR.setSize(sf::Vector2f(BG.getSize().x, DEFAULT_BAR_HEIGHT));
            HIDE_BUTTON_BG.setPosition(BAR.getPosition());
            HIDE_BUTTON.setPosition(HIDE_BUTTON_BG.getPosition() + sf::Vector2f(HIDE_BUTTON_BG.getSize().x/2, HIDE_BUTTON_BG.getSize().y/2));
            CLOSE_BUTTON_BG.setPosition(sf::Vector2f(BAR.getPosition().x + BAR.getSize().x - CLOSE_BUTTON_BG.getSize().x, BAR.getPosition().y)); CLOSE_BUTTON.setPosition(CLOSE_BUTTON_BG.getPosition() + sf::Vector2f(CLOSE_BUTTON_BG.getSize().x/2, CLOSE_BUTTON_BG.getSize().y/2));
            RESIZE_RECT.setPosition(sf::Vector2f(BG.getPosition().x + BG.getSize().x - RESIZE_RECT_SIZE, BG.getPosition().y + BG.getSize().y - RESIZE_RECT_SIZE));
            RESIZE_AREA.setPosition(sf::Vector2f(BG.getPosition().x + BG.getSize().x, BG.getPosition().y + BG.getSize().y));
        }

        if (dragging && ~resizing) {
            pos = mousePos - dragOffset;
            // Set Position of GUI Window Elements
            this->setWindowTitle(WIN_TITLE);
            BG.setPosition(pos);
            BAR.setPosition(sf::Vector2f(pos.x, pos.y - DEFAULT_BAR_HEIGHT));
            HIDE_BUTTON_BG.setPosition(BAR.getPosition());
            HIDE_BUTTON.setPosition(HIDE_BUTTON_BG.getPosition() + sf::Vector2f(HIDE_BUTTON_BG.getSize().x/2, HIDE_BUTTON_BG.getSize().y/2));
            CLOSE_BUTTON_BG.setPosition(sf::Vector2f(BAR.getPosition().x + BAR.getSize().x - CLOSE_BUTTON_BG.getSize().x, BAR.getPosition().y));
            CLOSE_BUTTON.setPosition(CLOSE_BUTTON_BG.getPosition() + sf::Vector2f(CLOSE_BUTTON_BG.getSize().x/2, CLOSE_BUTTON_BG.getSize().y/2));
            RESIZE_RECT.setPosition(sf::Vector2f(BG.getPosition().x + BG.getSize().x - RESIZE_RECT_SIZE, BG.getPosition().y + BG.getSize().y - RESIZE_RECT_SIZE));
            RESIZE_AREA.setPosition(sf::Vector2f(BG.getPosition().x + BG.getSize().x, BG.getPosition().y + BG.getSize().y));

            if (!hidden) {
                for (int i = 0; i < SF_WIDGETS.size(); i++)
                { 
                    float xPos = 0, yPos = 0;
                    //First Widget
                    if (SF_WIDGETS[i]->w_index == 0) {
                        xPos = WIDGET_PADDING_HOR + pos.x;
                        yPos = WIDGET_PADDING_VER + pos.y;
                    } else { // All other widgets
                        xPos = WIDGET_PADDING_HOR + pos.x;
                        yPos = SF_WIDGETS[i-1]->w_pos.y + SF_WIDGETS[i-1]->w_size.size.y + WIDGET_PADDING_VER; 
                    }
                    sf::Vector2f finalPosition = sf::Vector2f(xPos, yPos);
                    SF_WIDGETS[i]->setPosition(finalPosition);
                }
            }
        }
    } else {
        // Mouse Released
        dragging = false;
    }

    // Check if hide button is pressed.
    if (isMouseInsideRect(*SF_WINDOW, HIDE_BUTTON_BG)) {
        hovering = true;
        HIDE_BUTTON.setScale(sf::Vector2f(1.3f, 1.3f));
        HIDE_BUTTON_BG.setFillColor(sf::Color(0, 0, 0, 90));
        if (leftMousePressed && !leftMouseWasPressed) {
            if (!hidden)
                this->Hide();
            else
                this->Show();
        }
    } else {
        HIDE_BUTTON.setScale(sf::Vector2f(1.0f, 1.0f));
        HIDE_BUTTON_BG.setFillColor(sf::Color::Transparent);
    }

    // Check if close button is pressed.
    if (isMouseInsideRect(*SF_WINDOW, CLOSE_BUTTON_BG)) {
        hovering = true;
        CLOSE_BUTTON.setScale(sf::Vector2f(1.3f, 1.3f));
        CLOSE_BUTTON_BG.setFillColor(sf::Color(0, 0, 0, 90));
        if (leftMousePressed && !leftMouseWasPressed) {
            this->Close();
        }
    } else {
        CLOSE_BUTTON.setScale(sf::Vector2f(1.0f, 1.0f));
        CLOSE_BUTTON_BG.setFillColor(sf::Color::Transparent);
    }

    leftMouseWasPressed = leftMousePressed;

    // Make sure each widget in the gui gets SoftUpdated.

    for (SFWIDGET* widget : SF_WIDGETS) {
        if (!resizing)
            widget->SoftUpdate();

        if (widget->hovering) {
            cursorToUse = sf::Cursor::Type::Hand;
        }
        if (widget->hoveringOnText) {
            cursorToUse = sf::Cursor::Type::Text;
        }
    }
    if (hovering) {
        cursorToUse = sf::Cursor::Type::Hand;
    }



    SF_WINDOW->setMouseCursor(sf::Cursor(cursorToUse));

    //////////////////////
    } else {
        //Window is closed.
        SF_WINDOW->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
    }

    // Check if any parts of the gui need a total resize.
    for (SFWIDGET* widget : SF_WIDGETS) {
        if (widget->needsCompleteResize) {
            this->Setup();
            widget->needsCompleteResize = false;
        }
    }

}

void SFGUI::SFMLGUI::Hide() {
    HIDE_BUTTON.setRotation(sf::degrees(0));
    hidden = true;    
}

void SFGUI::SFMLGUI::Show() {
    HIDE_BUTTON.setRotation(sf::degrees(180));
    hidden = false;
}

void SFGUI::SFMLGUI::Close() {
    closed = true;
}

void SFGUI::SFMLGUI::Open() {
    closed = false;
}

void SFGUI::SFMLGUI::Setup() {
    for (int i = 0; i < SF_WIDGETS.size(); i++)
    { 
        float xPos = 0, yPos = 0;
        //First Widget
        if (SF_WIDGETS[i]->w_index == 0) {
            xPos = WIDGET_PADDING_HOR + pos.x;
            yPos = WIDGET_PADDING_VER + pos.y;
        } else { // All other widgets
            xPos = WIDGET_PADDING_HOR + pos.x;
            yPos = SF_WIDGETS[i-1]->w_pos.y + SF_WIDGETS[i-1]->w_size.size.y + WIDGET_PADDING_VER; 
        }
        sf::Vector2f finalPosition = sf::Vector2f(xPos, yPos);
        SF_WIDGETS[i]->provideGUIBounds(&BG);
        SF_WIDGETS[i]->setPosition(finalPosition);
        SF_WIDGETS[i]->setWindow(SF_WINDOW);
    }
}

void SFGUI::SFMLGUI::DebugDraw() {
    if (!hidden) {
        sf::RectangleShape shape;
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(1);
        for (SFWIDGET* widget : SF_WIDGETS) {
            shape.setSize(sf::Vector2f(widget->w_size.size.x, widget->w_size.size.y));
            shape.setPosition(widget->w_pos);
            SF_WINDOW->draw(shape);
        }
    }

}

void SFGUI::SFMLGUI::pollEvents(const sf::Event& e)
{
    for (SFWIDGET* widget : SF_WIDGETS) {
        widget->pollEvents(e);
    }
}
