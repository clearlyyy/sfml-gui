// slider3.hpp
// Slider 3 Widget

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"
#include "slider_template.hpp"



namespace SFGUI {

template<typename T>
class Slider3 : public SFWIDGET
{
    public:

        // Constructor where all 3 sliders have same min/max values with default width.
        Slider3 (T *val1, T *val2, T *val3, const std::string& text, T min, T max) : SFWIDGET("Slider3"), label(TEXT_FONT),
            slider(val1, text, min, max, DEFAULT_BUTTON_SIZE.x),
            slider2(val2, text, min, max, DEFAULT_BUTTON_SIZE.x),
            slider3(val3, text, min, max, DEFAULT_BUTTON_SIZE.x)
        {
            label_text = text;
            this->SetupSlider();
        }
        // Constructor where all 3 sliders have same min/max values with defined width.
        Slider3 (T *val1, T *val2, T *val3, const std::string& text, T min, T max, float slider_width) : SFWIDGET("Slider3"), label(TEXT_FONT),
            slider(val1, text, min, max, slider_width),
            slider2(val2, text, min, max, slider_width),
            slider3(val3, text, min, max, slider_width)
        {
            label_text = text;
            this->SetupSlider();
        }

        // Constructor where all 3 sliders have different min/max values with default width.
        Slider3 (T *val1, T *val2, T *val3, const std::string& text, T min_val1, T max_val1, T min_val2, T max_val2, T min_val3, T max_val3) : SFWIDGET("Slider3"), label(TEXT_FONT),
            slider(val1, text, min_val1, max_val1, DEFAULT_BUTTON_SIZE.x),
            slider2(val2, text, min_val2, max_val2, DEFAULT_BUTTON_SIZE.x),
            slider3(val3, text, min_val3, max_val3, DEFAULT_BUTTON_SIZE.x)
        {
            label_text = text;
            this->SetupSlider();
        }

        // Constructor where all 3 sliders have different min/max values with defined width.
        Slider3 (T *val1, T *val2, T *val3, const std::string& text, T min_val1, T max_val1, T min_val2, T max_val2, T min_val3, T max_val3, float slider_width) : SFWIDGET("Slider3"), label(TEXT_FONT),
            slider(val1, text, min_val1, max_val1, slider_width),
            slider2(val2, text, min_val2, max_val2, slider_width),
            slider3(val3, text, min_val3, max_val3, slider_width)
        {
            label_text = text;
            this->SetupSlider();
        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            slider.setPosition(w_pos);
            slider2.setPosition(slider.getPosition() + sf::Vector2f(slider.getSize().x + WIDGET_PADDING_HOR/2, 0));
            slider3.setPosition(slider2.getPosition() + sf::Vector2f(slider2.getSize().x + WIDGET_PADDING_HOR/2, 0));
            label.setPosition(slider3.getPosition() + sf::Vector2f((slider3.getSize().x) + WIDGET_PADDING_HOR/2, slider.getSize().y /2.f - label.getLocalBounds().size.y/2.f));
        }

        void SoftUpdate()
        {
            slider.UpdateSlider();
            slider2.UpdateSlider();
            slider3.UpdateSlider();
        }

        void setDecimalPrecision(int decimals) {
            slider.setDecimalPrecision(decimals);
            slider2.setDecimalPrecision(decimals);
            slider3.setDecimalPrecision(decimals);
        }
        
        // This needs to be overriden to pass a pointer of the main window to the slider object.
        void setWindow(sf::RenderWindow* window) override {
            SFWIDGET::setWindow(window);
            slider.setWindow(window);
            slider2.setWindow(window);
            slider3.setWindow(window);
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
            slider2.addParts(t_parts, d_parts);
            slider3.addParts(t_parts, d_parts);

            w_size = computeBoundingBox(t_parts);
        }

    private:

        sf::Text label;
        std::string label_text;

        Slider_Template<T> slider;
        Slider_Template<T> slider2;
        Slider_Template<T> slider3;

};
}