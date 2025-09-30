// inputbox.hpp
// InputBox Widget.

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"
#include <algorithm>

namespace SFGUI {
class InputBox : public SFWIDGET
{
    public:
        InputBox(std::string* input, std::string label) : SFWIDGET("Button"), b_text(TEXT_FONT, "", CHARACTER_SIZE), label(TEXT_FONT, "", CHARACTER_SIZE)
        {
            b_size = DEFAULT_BUTTON_SIZE;

            input_str = input;
            
            text = *input; 
            b_background.setFillColor(GUI_PRIMARY_COLOR);
            b_background.setSize(b_size);
            b_background.setPosition(w_pos);
            caret.setSize(sf::Vector2f(CARET_WIDTH,b_background.getSize().y - 6));

            b_text.setFillColor(GUI_TEXT_COLOR);
            b_text.setCharacterSize(CHARACTER_SIZE);
            sf::FloatRect bounds = b_text.getLocalBounds();
            b_text.setString(*input_str);
            this->label.setString(label);

            this->t_parts.push_back(&b_background);
            this->t_parts.push_back(&b_text);
            this->d_parts.push_back(&b_background);
            
            this->t_parts.push_back(&this->label);
            this->d_parts.push_back(&this->label);

            // Make Button size account for text length
            sf::FloatRect textBounds = b_text.getGlobalBounds();

            float newWidth = textBounds.size.x + WIDGET_PADDING_HOR;
            if (newWidth > DEFAULT_BUTTON_SIZE.x)
                b_size = sf::Vector2f(newWidth, b_size.y);
                b_background.setSize(b_size);

            w_size = computeBoundingBox(t_parts);

            this->setPosition(w_pos);

        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            b_background.setPosition(w_pos);
            label.setPosition(b_background.getPosition() + sf::Vector2f(b_background.getSize().x + WIDGET_PADDING_HOR, 0.f));
        }

        void setLabel(std::string text) {
            label.setString(text);
            w_size = computeBoundingBox(t_parts);
        }

        void pollEvents(const sf::Event& e) override {
           if (isFocused) {
              if (const auto* textEntered = e.getIf<sf::Event::TextEntered>()) {
                   char32_t unicode = textEntered->unicode;
                   if (unicode >= 32 && unicode < 127) {
                       text.insert(caretIndex, unicode);
                       *input_str = text;
                       caretIndex++;
                       b_text.setString(*input_str);
                   }
              }
              // Handle Special keys.
              else if (const auto* keyPressed = e.getIf<sf::Event::KeyPressed>()) {
                   switch (keyPressed->scancode) {
                       case sf::Keyboard::Scan::Left:
                           if (caretIndex > 0) caretIndex--;
                           break;
                       case sf::Keyboard::Scan::Right:
                           if (caretIndex < text.getSize()) caretIndex++;
                           break;
                       case sf::Keyboard::Scan::Backspace:
                           if (caretIndex > 0) {
                               text.erase(caretIndex - 1);
                               caretIndex--;
                               *input_str = text;
                               b_text.setString(*input_str);
                           }
                           break;
                       case sf::Keyboard::Scan::Delete:
                           if (caretIndex < text.getSize()) {
                               text.erase(caretIndex);
                               *input_str = text;
                               b_text.setString(*input_str);
                           }
                           break;
                       default:
                           break;
                   }
              }
           }
        }

        void SoftUpdate() override {
            hovering = false;
            hoveringOnText = false;
            clicked = false;
            if (isMouseInsideRect(*SF_WINDOW, b_background, guiRef)) {
                hoveringOnText = true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !leftMouseWasPressed) {
                    clicked = true;
                    isFocused = true;
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    b_background.setFillColor(CLICK_COLOR);
                } 
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { // We clicked somewhere else
                isFocused = false;
            }
            else
            {
                b_background.setFillColor(GUI_PRIMARY_COLOR);
            }
            leftMouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
            float boxLeft = b_background.getPosition().x;
            float boxWidth = b_background.getSize().x;
            float textWidth = b_text.getLocalBounds().size.x;
            if (textWidth < boxWidth - 10) {
                float centeredX = boxLeft + (boxWidth - textWidth) /2.f;
                b_text.setPosition({centeredX, b_background.getPosition().y});
                textOffsetX = 0.f;
            } else {
                b_text.setPosition({boxLeft + 5.f + textOffsetX, b_background.getPosition().y});
            }
            sf::Vector2f caret_pos = b_text.findCharacterPos(caretIndex);
            if (isFocused) {
                b_background.setFillColor(HOVER_COLOR);
                // Caret Logic
                float boxRight = boxLeft + b_background.getSize().x;
                // If caret goes past right side, we shift text left.
                if (caret_pos.x > boxRight - 5) {
                    textOffsetX -= (caret_pos.x - (boxRight -5));
                }
                // If caret goes past left side, we shift text right.
                else if (caret_pos.x < boxLeft + 5) {
                    textOffsetX += (boxLeft + 40 - caret_pos.x);
                }
                b_text.setPosition({boxLeft + 5 + textOffsetX, b_background.getPosition().y});
            }
            caret_pos = b_text.findCharacterPos(caretIndex);
            float bgCenterY   = b_background.getPosition().y + b_background.getSize().y / 2.f;
            float caretCenter = caret.getSize().y / 2.f;
            caret.setPosition(sf::Vector2f(caret_pos.x, bgCenterY - caretCenter));

            // If we click, we want the caret to be placed where the user clicked.
            if (clicked) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*SF_WINDOW);
                float relativeX = mousePos.x - b_text.getPosition().x;

                //Find closest character index.
                std::size_t closestIndex = 0;
                float textRightX = b_text.getPosition().x + b_text.getLocalBounds().size.x;
                if (mousePos.x >= textRightX) {
                    caretIndex = text.getSize();
                } else {
                    for (std::size_t i = 0; i < text.getSize(); i++) {
                        float charX = b_text.findCharacterPos(i).x - b_text.getPosition().x;
                        float nextCharX = (i + 1 < text.getSize()) ? b_text.findCharacterPos(i + 1).x - b_text.getPosition().x
                                                                     : charX + 10.f + b_text.getCharacterSize();
                        if (relativeX >= charX && relativeX < nextCharX) {
                            closestIndex = i + 1;
                            break;
                        }                                           
                    }
                    caretIndex = closestIndex;
                }   
            }
            
        }

        bool isClicked() {
            return clicked;
        }

        void Draw(sf::RenderWindow &window) override {
           for (auto& part : d_parts) {
                window.draw(*part);
           } 
           GLint prevScissor[4];
           glGetIntegerv(GL_SCISSOR_BOX, prevScissor);
           glEnable(GL_SCISSOR_TEST);
           sf::FloatRect bounds = b_background.getGlobalBounds();
           GLint newX = std::max(prevScissor[0], (GLint)bounds.position.x);
           GLint newY = std::max(prevScissor[1], (GLint)window.getSize().y - (GLint)(bounds.position.y + bounds.size.y));
           GLint newW = std::min(prevScissor[0] + prevScissor[2], (GLint)(bounds.position.x + bounds.size.x)) - newX;
           GLint newH = std::min(prevScissor[1] + prevScissor[3], (GLint)window.getSize().y - (GLint)bounds.position.y) - newY;

           glScissor(newX, newY, newW, newH);
           window.draw(b_text);
           if (isFocused) {
             window.draw(caret);
           }
           glScissor(prevScissor[0], prevScissor[1], prevScissor[2], prevScissor[3]);
        }

    private:
    sf::RectangleShape b_background;
    sf::Text b_text;
    sf::Text label;
    bool clicked = false;
    bool leftMouseWasPressed = false;
    std::string* input_str;
    sf::String text;
    std::size_t caretIndex = 0;
    float textOffsetX = 0.f;

    bool isFocused = false;

    sf::RectangleShape caret;

    sf::Vector2f b_size;
};
}