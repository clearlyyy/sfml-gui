#pragma once

// slider_template.hpp
// This is not a widget, but a reuseable slider object for other widgets that may need a slider.
namespace SFGUI {
    
// This is not a widget, use Slider1, Slider2, Slider3, or Slider4!
template<typename T>
class Slider_Template {

    public:

        Slider_Template(T *val, const std::string& text, T min, T max, float slider_Width, sf::RenderWindow* sfml_window) : value(val), num_display(TEXT_FONT)
        {
            SF_WINDOW = sfml_window;
            width = slider_Width;
            min_val = min;
            max_val = max;
            this->SetupSlider();
        }
        
        // Constructor without SF_WINDOW for early initialization
        Slider_Template(T *val, const std::string& text, T min, T max, float slider_Width) : value(val), num_display(TEXT_FONT)
        {
            SF_WINDOW = nullptr;
            width = slider_Width;
            min_val = min;
            max_val = max;
            this->SetupSlider();
        }

        void UpdateSlider()
        {
            // Update Number Display
            num_display.setString(to_string_prec(value, precision));
            this->updateSliderPickPosition();

            // Check for interaction.
            if (SF_WINDOW && isMouseInsideRect(*SF_WINDOW, bg)) {
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

        void setPosition(sf::Vector2f pos) {
            bg.setPosition(pos);
            centerText(num_display, bg);
            updateSliderPickPosition();
        }

        sf::Vector2f getSize() {
            return bg.getSize();
        }

        sf::Vector2f getPosition() {
            return bg.getPosition();
        }

        void addParts(std::vector<sf::Transformable*> &tr_parts, std::vector<sf::Drawable*> &dr_parts)
        {
            for (sf::Transformable* part : t_parts) {
                tr_parts.push_back(part);
            }
            for (sf::Drawable* part : d_parts) {
                dr_parts.push_back(part);
            }
        }
        
        void setWindow(sf::RenderWindow* window) {
            SF_WINDOW = window;
        }

    private:

        void SetupSlider()
        {
            bg.setFillColor(GUI_PRIMARY_COLOR);
            bg.setSize(sf::Vector2f(width, DEFAULT_BUTTON_SIZE.y));
            bg.setOutlineThickness(BORDER_THICKNESS);
            bg.setOutlineColor(BORDER_COLOR);
            slider.setFillColor(GUI_PRIMARY_COLOR + sf::Color(40, 40, 40));
            num_display.setCharacterSize(CHARACTER_SIZE);
            num_display.setString("0"); 
            slider.setSize(sf::Vector2f(SLIDER_PICK_WIDTH, DEFAULT_BUTTON_SIZE.y));
            slider.setOrigin(sf::Vector2f(slider.getSize().x/2.f, slider.getSize().y/2.f));

            this->t_parts.push_back(&bg);
            this->t_parts.push_back(&slider);
            this->t_parts.push_back(&num_display);
            this->d_parts.push_back(&bg);
            this->d_parts.push_back(&slider);
            this->d_parts.push_back(&num_display);

        }

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
                this->dragging = false;
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

    private:
        T *value;

        sf::RectangleShape bg;
        sf::RectangleShape slider;
        sf::Text num_display;
        float width;
        T min_val;
        T max_val;

        // Interaction Logic
        bool hovering = false;
        bool leftMouseWasPressed = false;
        bool dragging = false;
        int precision = 1;

        std::vector<sf::Transformable*> t_parts;
        std::vector<sf::Drawable*> d_parts;

        sf::RenderWindow* SF_WINDOW;

};
}