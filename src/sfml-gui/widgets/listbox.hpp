// listbox.hpp
// Listbox Widget.

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"
#include <SFML/OpenGL.hpp>

namespace SFGUI {
class Listbox : public SFWIDGET {
    public:
        Listbox(std::string label, int* current_item, std::string items[], size_t count) :  SFWIDGET("Listbox"), label_text(TEXT_FONT, label, CHARACTER_SIZE),
            currently_chosen_text(TEXT_FONT, "testing", CHARACTER_SIZE)         
        {
            selected_item = current_item;

            for (int i = 0; i < count; i++) {
                list_items.push_back(items[i]);
                sf::Text text(TEXT_FONT, items[i], CHARACTER_SIZE);
                sf::RectangleShape bg_text;
                text_list.push_back(text);
                text_list_bg.push_back(bg_text);
            }

            currently_chosen_text.setString(list_items[*selected_item]);

            background.setSize(DEFAULT_LIST_SIZE);
            background.setFillColor(GUI_PRIMARY_COLOR);
            background.setOutlineColor(BORDER_COLOR);
            background.setOutlineThickness(BORDER_THICKNESS);
            
            show_bg.setSize(sf::Vector2f(background.getSize().y, background.getSize().y));
            show_bg.setFillColor(GUI_PRIMARY_COLOR); 
            show_bg.setOutlineColor(BORDER_COLOR);
            show_bg.setOutlineThickness(BORDER_THICKNESS);

            for (sf::RectangleShape& rect : text_list_bg) {
                rect.setSize(sf::Vector2f(DEFAULT_LIST_SIZE.x + BORDER_THICKNESS + show_bg.getSize().x, (CHARACTER_SIZE+5)));
                rect.setFillColor(GUI_BACKGROUND_COLOR);
            }

            if (!show_texture.loadFromFile("sfml-gui-assets/hide_tex.png")) 
                std::cout << "Failed to load SHOW_TEXTURE" << std::endl;
            show_button.setTexture(&show_texture);
            show_button.setSize(sf::Vector2f(DEFAULT_LIST_SIZE.y/2.f, DEFAULT_LIST_SIZE.y/2.f));
            show_button.setOrigin(sf::Vector2f(show_button.getSize().x/2.f, show_button.getSize().y/2.f));

            this->setPosition(w_pos);
            
            this->t_parts.push_back(&background);
            this->t_parts.push_back(&label_text);
            this->t_parts.push_back(&show_bg);
            this->t_parts.push_back(&show_button);
            this->t_parts.push_back(&currently_chosen_text);
            
            this->d_parts.push_back(&background);
            this->d_parts.push_back(&label_text);
            this->d_parts.push_back(&currently_chosen_text);
            this->d_parts.push_back(&show_bg);
            this->d_parts.push_back(&show_button);

            w_size = computeBoundingBox(t_parts);
            
            
            // We are purposfully not putting List components into the d_parts, we override Draw() later.
            for (sf::RectangleShape& rect : text_list_bg) {
                this->t_parts_sometimes.push_back(&rect);
            }
            for (sf::Text& text : text_list) {
                this->t_parts_sometimes.push_back(&text);
            }

        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            background.setPosition(w_pos);
            show_bg.setPosition(background.getPosition() + sf::Vector2f(background.getSize().x, 0));
            show_button.setPosition(show_bg.getPosition() + sf::Vector2f(show_bg.getSize().x/2, show_bg.getSize().y/2)); 
            currently_chosen_text.setPosition(background.getPosition() + sf::Vector2f(WIDGET_PADDING_HOR, 0));
            label_text.setPosition(background.getPosition() + sf::Vector2f(background.getSize().x + show_bg.getSize().x + WIDGET_PADDING_HOR, 0));

            for (int i = 0; i < text_list.size(); i++) {
                text_list_bg[i].setPosition(w_pos + sf::Vector2f(0, DEFAULT_LIST_SIZE.y + i * (CHARACTER_SIZE+5)));
                text_list[i].setPosition(w_pos + sf::Vector2f(0, DEFAULT_LIST_SIZE.y + i * (CHARACTER_SIZE+5)));
            }

        }

        void SoftUpdate() {

            show_button.setRotation(sf::degrees(0.0f));
            // Hide/Show Button
            if (isMouseInsideRect(*SF_WINDOW, show_bg, guiRef)) {
                show_bg.setFillColor(HOVER_COLOR);
                show_button.setScale(sf::Vector2f(1.3f, 1.3f));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !leftMouseWasPressed) {
                    is_shown = !is_shown;
                    needsCompleteResize = !needsCompleteResize;
                    if (!is_shown) {
                        w_size = computeBoundingBox(t_parts);
                    } else if (is_shown) {
                        w_size = computeBoundingBox(t_parts, t_parts_sometimes);
                    }
                }
            } else {
                show_bg.setFillColor(GUI_PRIMARY_COLOR);
                show_button.setScale(sf::Vector2f(1.f, 1.f));
            }

            // Elements within the list
            if (is_shown) {
                show_button.setRotation(sf::degrees(180.f));
                for (int i = 0; i < text_list.size(); i++) {
                    if (isMouseInsideRect(*SF_WINDOW, text_list_bg[i], guiRef)) {
                        text_list_bg[i].setFillColor(HOVER_COLOR);
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !leftMouseWasPressed) {
                            *selected_item = i;
                            currently_chosen_text.setString(list_items[i]);
                            text_list_bg[i].setFillColor(CLICK_COLOR);
                            is_shown = false;
                            w_size = computeBoundingBox(t_parts);
                        }
                    }
                    else {
                        text_list_bg[i].setFillColor(GUI_BACKGROUND_COLOR);
                    }
                }
            }

            leftMouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        }

        void Draw(sf::RenderWindow &window) override {
                for (auto& part : d_parts) {
                    window.draw(*part);
                }
                if (is_shown) {
                    for (int i = 0; i < text_list.size(); i++) {
                        window.draw(text_list_bg[i]);
                        window.draw(text_list[i]);
                    }
            }
        }

    private:

        int*                     selected_item = 0;
        std::vector<std::string> list_items;        


        std::vector<sf::Text>    text_list;
        std::vector<sf::RectangleShape> text_list_bg;
        sf::Text                 label_text;
        sf::Text                 currently_chosen_text;
        sf::RectangleShape       background;
        sf::RectangleShape       show_bg;
        sf::RectangleShape       show_button;
        sf::Texture              show_texture;

        bool                     is_shown = false;

        bool                     leftMouseWasPressed = false;

};
}