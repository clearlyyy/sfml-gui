#include <SFML/Graphics.hpp>

#include <string>
#include <algorithm>

#include <stdarg.h>

// T is type of value used by slider
// LEN is how many sliders you want
template <typename T, int LEN>
class Slider
{
public:
    Slider(const sf::Color& guicolor, const sf::Color& textcolor, float slidersize, const sf::Font& font, const std::string& text, ...)
        : guiColor(sf::Color(guicolor.r - 40.0f, guicolor.g - 40.0f, guicolor.b - 40.0f)),
          sliderTitle(text, font, 13)
    {
        // Visual / Graphical initialization
        for(int i = 0; i < LEN; i++)
        {
            sliderBackground[i].setSize(sf::Vector2f(slidersize, 15.0f));
            sliderBackground[i].setFillColor(guiColor);

            sliderBar[i].setSize(sf::Vector2f(0.0f, 10.0f));
            sliderBar[i].setFillColor(sf::Color(guiColor.r + 55, guiColor.g + 55, guiColor.b + 55));

            slider[i].setSize(sf::Vector2f(10.0f, 15.0f));
            slider[i].setFillColor(guicolor);

            // Other slider stuff initialization
            sliderValue[i] = 0.0f;
        }

        // Minimum and maximum value initialization
        va_list values;

        va_start(values, text);

        // Unfortunately this only supports int min / max
        // so you can't have a minimum like 2.5
        for(int i = 0; i < LEN; i++)
        {
            minimumValues[i] = va_arg(values, int);
        }
        for(int i = 0; i < LEN; i++)
        {
            maximumValues[i] = va_arg(values, int);
        }

        va_end(values);

        // Text / Font initialization
        sliderTitle.setFillColor(textcolor);
        for(int i = 0; i < LEN; i++)
        {
            sliderTextValue[i].setString(std::to_string(minimumValues[i]));
            sliderTextValue[i].setFont(font);
            sliderTextValue[i].setCharacterSize(13);
            sliderTextValue[i].setFillColor(textcolor);
        }
    }

    ~Slider()
    {

    }

    void update(const sf::RectangleShape& GUI_PID, int slot, const sf::RenderWindow& window, T* value)
    {
        for(int i = 0; i < LEN; i++)
        {
            // Positioning / Resizing the slider
            sliderBackground[i].setPosition((GUI_PID.getGlobalBounds().left + 10.0f) + ((sliderBackground[i].getSize().x + 10.0f) * i), GUI_PID.getGlobalBounds().top + slot * 20.0f);
            if(oldSliderBackgroundPosition[i] != sliderBackground[i].getPosition()) // Checks if the position of sliderBackground has changed, so it doesn't need to update positions every frame
            {
                slider[i].setPosition(((sliderBackground[i].getSize().x - slider[i].getSize().x) * sliderValue[i]) + sliderBackground[i].getPosition().x, sliderBackground[i].getPosition().y);

                sliderBar[i].setPosition(sliderBackground[i].getPosition().x + 3.0f, sliderBackground[i].getPosition().y + 2.0f);
                sliderBar[i].setSize(sf::Vector2f(slider[i].getPosition().x - sliderBackground[i].getPosition().x, 10.0f));

                sliderTextValue[i].setPosition(sliderBackground[i].getPosition().x + sliderBackground[i].getSize().x / 2, sliderBackground[i].getPosition().y);
                oldSliderBackgroundPosition[i] = sliderBackground[i].getPosition();
            }
        }
        sliderTitle.setPosition(sliderBackground[LEN - 1].getPosition().x + sliderBackground[LEN - 1].getSize().x + 10.0f, sliderBackground->getPosition().y);

        if(sliderInitFlag)
        {
            for(int i = 0; i < LEN; i++)
            {
                updateValue(value);
            }
            sliderInitFlag = false;
        }

        // Input stuff
        sf::FloatRect mousePos = {static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), sf::Vector2f(1, 1)};

        if(window.hasFocus()) // Checks if window has focus so you don't move a slider while not focused
        {
            switch(currentSelected)
            {
                case SELECTED_THIS:
                    slider[currentSelectedSlider].setFillColor(sf::Color(guiColor.r + 100, guiColor.g + 50, guiColor.b + 50));
                    sliderValue[currentSelectedSlider] = (float) ((sf::Mouse::getPosition(window).x)
                                                                   - sliderBackground[currentSelectedSlider].getPosition().x)
                                                                   / (float) sliderBackground[currentSelectedSlider].getSize().x;

                    // Swap out this clamp code if you want support for c++ versions older than C++17
                    sliderValue[currentSelectedSlider] = std::clamp(sliderValue[currentSelectedSlider], 0.0f, 1.0f); // Clamps sliderValue to 0 - 1
                    updateValue(value);

                    sliderBar[currentSelectedSlider].setSize(sf::Vector2f(slider[currentSelectedSlider].getPosition().x
                                                                          - sliderBackground[currentSelectedSlider].getPosition().x, // X
                                                                          10.0f)); // Y
                    slider[currentSelectedSlider].setPosition(((sliderBackground[currentSelectedSlider].getSize().x
                                                                - slider[currentSelectedSlider].getSize().x)
                                                                * sliderValue[currentSelectedSlider])
                                                                + sliderBackground[currentSelectedSlider].getPosition().x, // X
                                                                sliderBackground[currentSelectedSlider].getPosition().y); // Y

                    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        currentSelected = SELECTED_NOTHING;
                    }
                    break;
                case SELECTED_SOMETHING_ELSE:
                    // While selecting something else (e.g., moving a gui)
                    // it will wait for you to let go of lmb,
                    // so you dont move a slider while grabbing something else.
                    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        currentSelected = SELECTED_NOTHING;
                    }
                    break;
                case SELECTED_NOTHING:
                    for(int i = 0; i < LEN; i++)
                    {
                        slider[i].setFillColor(sf::Color(guiColor.r + 40, guiColor.g + 40, guiColor.b + 40));
                        // If you haven't selected anything it checks for lmb
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            if(mousePos.intersects(sliderBackground[i].getGlobalBounds()))
                            {
                                currentSelected = SELECTED_THIS;
                                currentSelectedSlider = i;
                                break;
                            } else
                            {
                                currentSelected = SELECTED_SOMETHING_ELSE;
                            }
                        }
                    }
                    break;
            }
        }
    }
    
    void draw(sf::RenderWindow& window, int slot, const sf::RectangleShape& GUI_PID, T* value)
    {
        update(GUI_PID, slot, window, value);

        for(int i = 0; i < LEN; i++)
        {
            window.draw(sliderBackground[i]);
            window.draw(sliderBar[i]);
            window.draw(slider[i]);

            window.draw(sliderTextValue[i]);
        }
        window.draw(sliderTitle);
    }
private:
    void updateValue(T* value)
    {
        for(int i = 0; i < LEN; i++)
        {
            int maximum = maximumValues[i] - minimumValues[i];
            value[i] = maximum* sliderValue[i] + minimumValues[i];

            std::stringstream ss;
            ss << value[i];
            sliderTextValue[i].setString(ss.str());
        }
    }

    sf::RectangleShape sliderBackground[LEN]; // Background for slider
    sf::RectangleShape sliderBar[LEN]; // Slider status bar
    sf::RectangleShape slider[LEN]; // The slider you grab

    sf::Color guiColor; // Color of the gui in use

    sf::Text sliderTitle; // Text to right of the sliders
    sf::Text sliderTextValue[LEN]; // Value of slider on the screen

    sf::Vector2f oldSliderBackgroundPosition[LEN]; // Previous position of sliderBackground

    float sliderValue[LEN]; // Current value of slider within a range of 0 - 1

    int minimumValues[LEN];
    int maximumValues[LEN];

    bool sliderInitFlag = true;

    enum Selected : unsigned char
    {
        SELECTED_THIS,
        SELECTED_SOMETHING_ELSE,
        SELECTED_NOTHING
    };
    Selected currentSelected = SELECTED_NOTHING;
    unsigned char currentSelectedSlider = 0; // Which slider is currently being slid
};