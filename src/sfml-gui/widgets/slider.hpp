// slider.hpp
// Slider 1 Widget

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"



namespace SFGUI {

template<typename T>
class Slider : public SFWIDGET
{
    public:
        Slider(T *val, const std::string& text, T min, T max) : SFWIDGET("Slider"), value(val), label(TEXT_FONT), num_display(TEXT_FONT)
        {
            label_text = text;
            width = DEFAULT_BUTTON_SIZE.x;
            min_val = min;
            max_val = max;
            this->SetupSlider();
        }

        Slider(T *val, const std::string& text, T min, T max, float slider_width) : SFWIDGET("Slider"), value(val), label(TEXT_FONT), num_display(TEXT_FONT)
        {
            label_text = text;
            width = slider_width;
            min_val = min;
            max_val = max;
            this->SetupSlider();
        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            bg.setPosition(pos);
            centerText(num_display, bg);
            label.setPosition(bg.getPosition() + sf::Vector2f(bg.getSize().x + WIDGET_PADDING_HOR, bg.getSize().y /2.f - label.getLocalBounds().size.y/2.f));
            updateSliderPickPosition();

        }

        void SoftUpdate()
        {
            // Update Number Display
            num_display.setString(to_string_prec(value, precision));
            this->updateSliderPickPosition();

            // Check for interaction.
            if (isMouseInsideRect(*SF_WINDOW, bg)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    this->setValue();
                if (isMouseInsideRect(*SF_WINDOW, slider)) {
                    slider.setFillColor(HOVER_COLOR);
                    hovering = true;
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                        dragging = true;
                        slider.setFillColor(CLICK_COLOR);
                    }
                } else {
                    slider.setFillColor(GUI_PRIMARY_COLOR + sf::Color(40, 40, 40));
                }
            } else {
                slider.setFillColor(GUI_PRIMARY_COLOR + sf::Color(40,40,40));
            }
            
            if (dragging)
            {
                this->setValue();
            }

        }

        void setDecimalPrecision(int decimals) {
            precision = decimals;
        }
    
    private:

        void setValue() {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*SF_WINDOW);
                
            //Left and right edges of bg
            float left = bg.getPosition().x;
            float right = bg.getPosition().x + bg.getSize().x;

            float halfHandle = slider.getSize().x / 2.f;

            // Clamp mouse X inside bg
            float clampedX = std::max(left + halfHandle, std::min((float)mousePos.x, right - halfHandle));

            // Normalized ratio in 0,1
            float t = (clampedX - (left + halfHandle)) / (bg.getSize().x - slider.getSize().x);
            
            //Map back to min_val, max_val
            *value = min_val + t * (max_val - min_val);

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                dragging = false;
            } 
        }

        void updateSliderPickPosition()
        {
            float t = (static_cast<float>(*value) - static_cast<float>(min_val)) / (static_cast<float>(max_val) - static_cast<float>(min_val));
            float halfHandle = slider.getSize().x /2.f;
            float sliderX = bg.getPosition().x + halfHandle + t * (bg.getSize().x - slider.getSize().x);
            slider.setPosition(sf::Vector2f(sliderX,bg.getPosition().y + (bg.getSize().y/2.f)));
            centerText(num_display, bg);
        }

        void SetupSlider()
        {
            bg.setFillColor(GUI_PRIMARY_COLOR);
            bg.setSize(sf::Vector2f(width, DEFAULT_BUTTON_SIZE.y));
            bg.setOutlineThickness(BORDER_THICKNESS);
            bg.setOutlineColor(BORDER_COLOR);
            slider.setFillColor(GUI_PRIMARY_COLOR + sf::Color(40, 40, 40));
            label.setString(label_text);
            label.setCharacterSize(CHARACTER_SIZE);
            num_display.setCharacterSize(CHARACTER_SIZE);
            num_display.setString("0"); 
            slider.setSize(sf::Vector2f(SLIDER_PICK_WIDTH, DEFAULT_BUTTON_SIZE.y));
            slider.setOrigin(sf::Vector2f(slider.getSize().x/2.f, slider.getSize().y/2.f));

            this->setPosition(w_pos);
            
            this->t_parts.push_back(&bg);
            this->t_parts.push_back(&slider);
            this->t_parts.push_back(&num_display);
            this->t_parts.push_back(&label);
            this->d_parts.push_back(&bg);
            this->d_parts.push_back(&slider);
            this->d_parts.push_back(&num_display);
            this->d_parts.push_back(&label);

        }

    private:
        T *value;

        sf::RectangleShape bg;
        sf::RectangleShape slider;
        sf::Text num_display;
        sf::Text label;
        std::string label_text;
        float width;
        T min_val;
        T max_val;

        int precision = 1;

        // Interaction Logic
        bool hovering = false;
        bool leftMouseWasPressed = false;
        bool dragging = false;

};
}

