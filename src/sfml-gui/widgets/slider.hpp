// slider.hpp
// Slider 1 Widget

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"
#include "slider_template.hpp"



namespace SFGUI {

template<typename T>
class Slider : public SFWIDGET
{
    public:
        Slider(T *val, const std::string& text, T min, T max) : SFWIDGET("Slider"), value(val), label(TEXT_FONT),
            slider(val, text, min, max, DEFAULT_BUTTON_SIZE.x)
        {
            label_text = text;
            min_val = min;
            max_val = max;
            this->SetupSlider();
        }

        Slider(T *val, const std::string& text, T min, T max, float slider_width) : SFWIDGET("Slider"), value(val), label(TEXT_FONT),
            slider(val, text, min, max, slider_width)
        {
            label_text = text;
            min_val = min;
            max_val = max;
            this->SetupSlider();
        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            slider.setPosition(w_pos);
            label.setPosition(slider.getPosition() + sf::Vector2f(slider.getSize().x + WIDGET_PADDING_HOR, slider.getSize().y /2.f - label.getLocalBounds().size.y/2.f));
        }

        void SoftUpdate()
        {
            slider.UpdateSlider();
        }

        void setDecimalPrecision(int decimals) {
            slider.setDecimalPrecision(decimals);
        }
        
        // This needs to be overriden to pass a pointer to the main window to the slider object.
        void setWindow(sf::RenderWindow* window) override {
            SFWIDGET::setWindow(window);
            slider.setWindow(window);
        }
    
    private:

        void SetupSlider()
        {
            label.setString(label_text);
            label.setCharacterSize(CHARACTER_SIZE);

            this->setPosition(w_pos); 
            this->t_parts.push_back(&label);
            this->d_parts.push_back(&label);
            slider.addParts(t_parts, d_parts);

            w_size = computeBoundingBox(t_parts);

        }

    private:
        T *value;

        sf::Text label;
        std::string label_text;
        T min_val;
        T max_val;

        Slider_Template<T> slider;
};
}

