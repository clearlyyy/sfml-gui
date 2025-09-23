#include <SFML/Graphics.hpp>

#include "sfml-gui/gui.hpp"
#include "sfml-gui/button.hpp"

int main()
{

    sf::RenderWindow window(sf::VideoMode({1280, 720}), "SFML works!");

    SFGUI::SFMLGUI gui(window);
    SFGUI::SFBUTTON button;
    gui.Add(button);
    SFGUI::SFBUTTON button2;
    gui.Add(button2);

    SFGUI::SFBUTTON button3;
    gui.Add(button3);

    button.setText("Button 1");
    button2.setText("Button 2");
    button3.setText("Button 3");

    std::cout << "ding" << std::endl;

    gui.Update();

    gui.SF_WIDGETS[0]->DebugOutput();
    gui.SF_WIDGETS[1]->DebugOutput();
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        gui.Draw();
        gui.Update();
        window.display();
    }
}
