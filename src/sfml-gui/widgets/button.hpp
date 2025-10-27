// button.hpp
// Button Widget.

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"

namespace SFGUI {
class Button : public SFWIDGET
{
    public:
        Button(std::string text) : SFWIDGET("Button"), b_text(TEXT_FONT)
        {
            b_size = DEFAULT_BUTTON_SIZE;
            
            b_background.setFillColor(GUI_PRIMARY_COLOR);
            b_background.setSize(b_size);
            b_background.setPosition(w_pos);

            b_text.setFillColor(GUI_TEXT_COLOR);
            b_text.setCharacterSize(CHARACTER_SIZE);
            sf::FloatRect bounds = b_text.getLocalBounds();
            b_text.setString(text);
            centerText(b_text, b_background);

            this->t_parts.push_back(&b_background);
            this->t_parts.push_back(&b_text);
            this->d_parts.push_back(&b_background);
            this->d_parts.push_back(&b_text);

            // Make Button size account for text length
            sf::FloatRect textBounds = b_text.getGlobalBounds();

            float newWidth = textBounds.size.x + WIDGET_PADDING_HOR;
            if (newWidth > DEFAULT_BUTTON_SIZE.x)
                b_size = sf::Vector2f(newWidth, b_size.y);
                b_background.setSize(b_size);

            w_size = computeBoundingBox(t_parts);

        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            b_background.setPosition(w_pos);
            centerText(b_text, b_background);
        }

        void setText(std::string text) {
            b_text.setString(text);
            sf::FloatRect textBounds = b_text.getGlobalBounds();
            float newWidth = textBounds.size.x + WIDGET_PADDING_HOR;
            if (newWidth > DEFAULT_BUTTON_SIZE.x) {
                b_size = sf::Vector2f(newWidth, b_size.y);
                b_background.setSize(b_size);
            }
            w_size = computeBoundingBox(t_parts);
            
        }

        void SoftUpdate() override {
            hovering = false;
            clicked = false;
            if (isMouseInsideRect(*SF_WINDOW, b_background, guiRef)) {
                b_background.setFillColor(HOVER_COLOR);
                hovering = true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !leftMouseWasPressed) {
                    clicked = true;
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    b_background.setFillColor(CLICK_COLOR);
                    b_text.setScale(sf::Vector2f(0.9f, 0.9f));
                } else {
                    b_text.setScale(sf::Vector2f(1.f, 1.f));
                }
            }
            else
            {
                b_background.setFillColor(GUI_PRIMARY_COLOR);
            }
            leftMouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        }

        bool isClicked() {
            return clicked;
        }

    private:
    sf::RectangleShape b_background;
    sf::Text b_text;
    bool clicked = false;
    bool leftMouseWasPressed = false;

    sf::Vector2f b_size;
};
}
