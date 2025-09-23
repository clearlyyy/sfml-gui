// button.hpp
// Button Widget.

#include "sf_widget.h"
#include "gui.hpp"
#include "sfgui-utils.cpp"

namespace SFGUI {
class SFBUTTON : public SFWIDGET
{
    public:
        SFBUTTON() : SFWIDGET("Button"), b_text(TEXT_FONT)
        {
            b_size = DEFAULT_BUTTON_SIZE;
            
            b_background.setFillColor(GUI_PRIMARY_COLOR);
            b_background.setSize(b_size);
            b_background.setPosition(w_pos);

            b_text.setFillColor(GUI_TEXT_COLOR);
            b_text.setCharacterSize(CHARACTER_SIZE);
            sf::FloatRect bounds = b_text.getLocalBounds();
            b_text.setString("Hello World");
            centerText(b_text, b_background);

            this->t_parts.push_back(&b_background);
            this->t_parts.push_back(&b_text);
            this->d_parts.push_back(&b_background);
            this->d_parts.push_back(&b_text);

            w_size = computeBoundingBox(t_parts);
        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            b_background.setPosition(pos);
            centerText(b_text, b_background);
        }

        void setText(std::string text) {
            b_text.setString(text);
        }

    private:
    sf::RectangleShape b_background;
    sf::Text b_text;

    sf::Vector2f b_size;
};
}
