// main.cpp
// this is just a driver for the gui 

#include <SFML/Graphics.hpp>

#include "sfml-gui/gui.hpp"
#include "sfml-gui/widgets/button.hpp"
#include "sfml-gui/widgets/label.hpp"
#include "sfml-gui/widgets/checkbox.hpp"
#include "sfml-gui/widgets/slider.hpp"

int main()
{

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");

    sf::Font ft;
    ft.openFromFile("Poppins-Medium.ttf");
    sf::Text fpsText(ft, "", 24);
    fpsText.setPosition(sf::Vector2f(30, 30));
    sf::Clock clock;
    float fps = 0.f; 

    int ding = 38;

    bool flag = false;

    SFGUI::SFMLGUI gui(window);
    SFGUI::Button button;
    gui.Add(button);

    SFGUI::Checkbox checkbox("Toggle Visibility", &flag);
    gui.Add(checkbox);

    
    SFGUI::Button button2;
    gui.Add(button2);
    
    SFGUI::Label label("This is a label!");
    gui.Add(label);

    SFGUI::Button button3;
    gui.Add(button3);

    SFGUI::Slider<int> slider(&ding, "ding", -100, 100, 200);
    gui.Add(slider);

    button.setText("Button 1 gdasgjhdfsijghdfsighdsf ");
    button2.setText("Button 2");
    button3.setText("Button 3");

    std::cout << "ding" << std::endl;

    gui.Setup();
    gui.SF_WIDGETS[0]->DebugOutput();
    gui.SF_WIDGETS[1]->DebugOutput();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();
        fps = 1.f / dt;

        fpsText.setString("FPS: " + std::to_string(fps));

        //if (!flag)
        //    std::cout << "FLAG: FALSE" << std::endl;
        //else
        //    std::cout << "FLAG: TRUE" << std::endl;
        //std::cout << ding << std::endl;
        window.clear(sf::Color(129, 197, 240));
        gui.Draw();
        window.draw(fpsText);
        gui.Update();

        if (button.isClicked()) {
            std::cout << "Clicked Button 1" << std::endl;
            label.setText("I JUST CHANGED THIS LABEL!!!!!!!");
        }

        window.display();
    }
}
