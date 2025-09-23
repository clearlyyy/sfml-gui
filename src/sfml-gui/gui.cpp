#include "gui.hpp"

sf::Font SFGUI::TEXT_FONT; 
SFGUI::SFMLGUI::SFMLGUI(sf::RenderWindow& window) : pos(DEFAULT_GUI_POSITION)
{
    SF_WINDOW = &window;

    // Load a font once globally
    if (!SFGUI::TEXT_FONT.openFromFile("Roboto-Medium.ttf")) {
        std::cout << "Default Font failed to load :(" << std::endl;
    }

    BG.setFillColor(GUI_BACKGROUND_COLOR);
    BG.setSize(sf::Vector2f(DEFAULT_GUI_SIZE_X, DEFAULT_GUI_SIZE_Y)); 
    BG.setPosition(DEFAULT_GUI_POSITION); 

    BAR.setPosition(sf::Vector2f(DEFAULT_GUI_POSITION.x, (DEFAULT_GUI_POSITION.y - DEFAULT_BAR_HEIGHT)));
    BAR.setFillColor(GUI_PRIMARY_COLOR);
    BAR.setSize(sf::Vector2f(DEFAULT_GUI_SIZE_X, DEFAULT_BAR_HEIGHT));

}

void SFGUI::SFMLGUI::Draw()
{
   SF_WINDOW->draw(BG);
   SF_WINDOW->draw(BAR);
   for (SFWIDGET* widget : SF_WIDGETS) {
        widget->Draw(*SF_WINDOW);
   } 
}

void SFGUI::SFMLGUI::Add(SFWIDGET& widget)
{
    SF_WIDGETS.push_back(&widget);
}

void SFGUI::SFMLGUI::Update()
{
    for (int i = 0; i < SF_WIDGETS.size(); i++)
    { 
        float xPos = 0, yPos = 0;
        //First Widget
        if (SF_WIDGETS[i]->w_index == 0) {
            xPos = WIDGET_PADDING_HOR + pos.x;
            yPos = WIDGET_PADDING_VER + pos.y;
        } else {
            xPos = WIDGET_PADDING_HOR + pos.x;
            yPos = SF_WIDGETS[i-1]->w_pos.y + SF_WIDGETS[i-1]->w_size.size.y + WIDGET_PADDING_VER; 
        }
        sf::Vector2f finalPosition = sf::Vector2f(xPos, yPos);
        SF_WIDGETS[i]->setPosition(finalPosition);
    }
}

