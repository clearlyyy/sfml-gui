// main.cpp
// this is just a driver for the gui 

#include <SFML/Graphics.hpp>

#include "sfml-gui/gui.hpp"
#include "sfml-gui/widgets/button.hpp"
#include "sfml-gui/widgets/label.hpp"
#include "sfml-gui/widgets/checkbox.hpp"
#include "sfml-gui/widgets/slider.hpp"
#include "sfml-gui/widgets/slider2.hpp"
#include "sfml-gui/widgets/slider3.hpp"
#include "sfml-gui/widgets/listbox.hpp"

int main()
{

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");

    SFGUI::SFMLGUI gui(window, "SFML-GUI Example");
    SFGUI::Button button("This is a button");
    SFGUI::Label label ("Here is a label");

    bool flag = true;
    SFGUI::Checkbox checkbox("Toggle Visbility", &flag);
    float rotation = 0;
    SFGUI::Slider<float> slider(&rotation, "Rotation", 0, 360);

    sf::Vector2f pos = sf::Vector2f(650, 340);
    SFGUI::Slider2<float> slider2(&pos.x, &pos.y, "Position", 0, 1000);
    
    int currentItem = 1;
    std::string items[] = {"Rectangle", "Circle", "Triangle", "Hexagon", "Octogon"};
    SFGUI::Listbox listbox("Items List", &currentItem, items, 5);

    gui.Add(button); gui.Add(label); gui.Add(slider); gui.Add(slider2); gui.Add(listbox);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(33, 33, 33));
        gui.Update();
        gui.Draw();

        if (button.isClicked())
            label.setText("Just clicked that button!"); 

        window.display();
    }
}
