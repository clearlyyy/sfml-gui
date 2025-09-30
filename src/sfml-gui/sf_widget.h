// sf_widget.h
// Base class for all widgets to inherit from.1
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <SFML/Graphics.hpp>

namespace SFGUI {
class SFWIDGET {
    public:
        std::string name;

        SFWIDGET(const std::string& n);

        virtual ~SFWIDGET() {}

        virtual void Draw(sf::RenderWindow &window);

        // Full Update (Resizing Widget)
        virtual void Update();

        virtual void DebugOutput();

        // Soft Update (Only moving the widget.)
        virtual void SoftUpdate();

        // For polling an sf::Event, right now only used for the InputBox Widget
        virtual void pollEvents(const sf::Event& e);

        //Set Position (This should be overridden for each widget.)
        virtual void setPosition(sf::Vector2f pos);

        virtual void setWindow(sf::RenderWindow* window);

        void provideGUIBounds(sf::RectangleShape *gui_size);

        int w_index;
        sf::FloatRect w_size;
        sf::Vector2f w_pos;
        bool hovering = false;
        bool hoveringOnText = false;

        bool needsCompleteResize = false; 
    private:
        // A Widgets index (used for positioning)
        static uint8_t counter;
        
    protected:
        sf::FloatRect computeBoundingBox(const std::vector<sf::Transformable*>& parts);
        sf::FloatRect computeBoundingBox(const std::vector<sf::Transformable*>& parts1, const std::vector<sf::Transformable*>& parts2);
        sf::RenderWindow* SF_WINDOW;
        sf::RectangleShape *guiRef;

        // All SFML components that make up a widget.
        // Two lists are needed to account for text, shape and sprites.
        // We need Drawables for drawing, and Transformables for pos, size calculations.
        // i could dynamic_cast between them, but i'll avoid the performance overhead for slighly higher mem usage.
        // This just means that for every widget, we must fill both arrays for every shape, text or sprite we create. 
        std::vector<sf::Transformable*> t_parts;
        std::vector<sf::Drawable*> d_parts;

        // This list is for storing objects that aren't always visible
        // Like the Listbox for example, we need to recalculate the bounding box
        // Depending on if its hidden or shown, so we hold the list parts of the listbox in this vector.
        std::vector<sf::Transformable*> t_parts_sometimes;

};
}