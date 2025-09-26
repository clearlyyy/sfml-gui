// checkbox.hpp
// Checkbox widget

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"

namespace SFGUI {
class Checkbox : public SFWIDGET {

    public:
        Checkbox(const std::string text, bool* condition) : SFWIDGET("Checkbox"), label(TEXT_FONT)
        {

            // Checkmark Setup
            c_condition = condition;
            l_text = text;
            label.setPosition(w_pos);
            label.setString(l_text);
            label.setCharacterSize(CHARACTER_SIZE);
            label.setFillColor(GUI_TEXT_COLOR);
            sf::FloatRect bounds = label.getLocalBounds();
            label.setOrigin(sf::Vector2f(bounds.position.x, bounds.position.y-1)); // Not sure why, but the bounds are 1 pixel off.

            c_background.setSize(sf::Vector2f(CHECKBOX_SIZE, CHECKBOX_SIZE));
            c_background.setFillColor(GUI_PRIMARY_COLOR);
            c_background.setOutlineThickness(BORDER_THICKNESS);
            c_background.setOutlineColor(BORDER_COLOR);

            if (!check_texture.loadFromFile("check_tex.png"))
                std::cout << "Failed to load check_texture" << std::endl;

            c_checkmark.setTexture(&check_texture);
            c_checkmark.setSize(sf::Vector2f(CHECKBOX_SIZE - 8, CHECKBOX_SIZE - 8));
            c_checkmark.setOrigin(sf::Vector2f(c_checkmark.getSize().x/2.f, c_checkmark.getSize().y/2.f));

            this->setPosition(w_pos);

            // Fill parts arrays
            this->t_parts.push_back(&label);
            this->t_parts.push_back(&c_background);
            this->t_parts.push_back(&c_checkmark);
            this->d_parts.push_back(&label);
            this->d_parts.push_back(&c_background);
            this->d_parts.push_back(&c_checkmark);

            w_size = computeBoundingBox(t_parts);
        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            c_background.setPosition(w_pos);
            c_checkmark.setPosition(c_background.getPosition() + sf::Vector2f(c_background.getSize().x/2.f, c_background.getSize().y/2.f));
            label.setPosition(c_background.getPosition() + sf::Vector2f(c_background.getSize().x + WIDGET_PADDING_HOR, c_background.getSize().y/2.f - label.getLocalBounds().size.y/2.f));
        }

        void setText(const std::string text) {
            l_text = text;
            label.setString(l_text);
        }

        void SoftUpdate() override {

            if (!*c_condition) {
                c_checkmark.setSize(sf::Vector2f(0,0));
            } else {
                c_checkmark.setSize(sf::Vector2f(CHECKBOX_SIZE - 8, CHECKBOX_SIZE - 8));
            }

            hovering = false;
            clicked = false;

            if (isMouseInsideRect(*SF_WINDOW, c_background, guiRef)) {
                c_background.setFillColor(HOVER_COLOR);
                hovering = true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !leftMouseWasPressed) {
                    clicked = true;
                    *c_condition = !*c_condition;
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    c_background.setFillColor(CLICK_COLOR);
                } 
            } else {
                c_background.setFillColor(GUI_PRIMARY_COLOR);
            }
            leftMouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        }

        bool isClicked() {
            return clicked;
        }

    private:

        // Label
        std::string l_text;
        sf::Text label;

        bool* c_condition;

        // Checkbox
        sf::RectangleShape c_background;
        sf::RectangleShape c_checkmark;
        sf::Texture check_texture;

        // Logic
        bool clicked;
        bool leftMouseWasPressed = false;


};
}