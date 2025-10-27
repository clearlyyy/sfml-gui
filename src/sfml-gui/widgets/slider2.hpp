// slider2.hpp
// Slider 2 Widget

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"
#include "slider_template.hpp"

namespace SFGUI {

template<typename T>
class Slider2 : public SFWIDGET
{
    public:

        // Constructor where both sliders have same min/max values and default width.
        Slider2 (T *val, T* val2, const std::string& text, T min, T max) : SFWIDGET("Slider"), label(TEXT_FONT),
            slider(val, text, min, max, DEFAULT_BUTTON_SIZE.x),
            slider2(val2, text, min, max, DEFAULT_BUTTON_SIZE.x)
        {
            label_text = text;
            this->SetupSlider();
        }

        // Constructor where both sliders have same min/max values with a defined width.
        Slider2 (T *val, T* val2, const std::string& text, T min, T max, float slider_width) : SFWIDGET("Slider"), label(TEXT_FONT),
            slider(val, text, min, max, slider_width),
            slider2(val2, text, min, max, slider_width)
        {
            label_text = text;
            this->SetupSlider();
        }

        // Constructor where both sliders have different min/max values with a default width.
        Slider2 (T *val, T* val2, const std::string& text, T min_val1, T max_val1, T min_val2, T max_val2, float slider_width) : SFWIDGET("Slider"), label(TEXT_FONT),
            slider(val, text, min_val1, max_val1, slider_width),
            slider2(val2, text, min_val2, max_val2, slider_width)
        {
            label_text = text;
            this->SetupSlider();
        }

        // Constructor where both sliders have different min/max values with a defined width.
        Slider2 (T *val, T* val2, const std::string& text, T min_val1, T max_val1, T min_val2, T max_val2) : SFWIDGET("Slider"), label(TEXT_FONT),
            slider(val, text, min_val1, max_val1, DEFAULT_BUTTON_SIZE.x),
            slider2(val2, text, min_val2, max_val2, DEFAULT_BUTTON_SIZE.x)
        {
            label_text = text;
            this->SetupSlider();
        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            slider.setPosition(w_pos);
            slider2.setPosition(slider.getPosition() + sf::Vector2f(slider.getSize().x + WIDGET_PADDING_HOR/2, 0));
            label.setPosition(slider2.getPosition() + sf::Vector2f((slider2.getSize().x) + WIDGET_PADDING_HOR/2, slider.getSize().y /2.f - label.getLocalBounds().size.y/2.f));
        }

        void SoftUpdate()
        {
            slider.UpdateSlider();
            slider2.UpdateSlider();
        }

        void setDecimalPrecision(int decimals) {
            slider.setDecimalPrecision(decimals);
            slider2.setDecimalPrecision(decimals);
        }
        
        // This needs to be overriden to pass a pointer of the main window to the slider object.
        void setWindow(sf::RenderWindow* window) override {
            SFWIDGET::setWindow(window);
            slider.setWindow_and_GuiRef(window, guiRef);
            slider2.setWindow_and_GuiRef(window, guiRef);
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

            w_size = computeBoundingBox(t_parts);
        }

    private:

        sf::Text label;
        std::string label_text;

        Slider_Template<T> slider;
        Slider_Template<T> slider2;

};
}