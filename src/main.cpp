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

    bool flag = true;

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

    float rotation = 0;
    SFGUI::Slider<float> slider(&rotation, "Rotation", 0, 360, 200);
    gui.Add(slider);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(100, 100));
    sf::Vector2f rectPos(sf::Vector2f(500, 800));

    SFGUI::Slider2<float> slider2(&rectPos.x, &rectPos.y, "Slider 2 (x,y)", 0, (float)window.getSize().x, 0, (float)window.getSize().y);
    gui.Add(slider2);

    sf::Color bgColor = sf::Color::Green;

    SFGUI::Slider3<uint8_t> slider3(&bgColor.r, &bgColor.g, &bgColor.b, "Slider 3", 0, 255);
    gui.Add(slider3);

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
        window.clear(bgColor);
        rect.setPosition(rectPos);
        rect.setRotation(sf::degrees(rotation));
        if (flag)
            window.draw(rect);
        gui.Draw();
//        gui.DebugDraw();
        window.draw(fpsText);
        gui.Update();

        if (button.isClicked()) {
            std::cout << "Clicked Button 1" << std::endl;
            label.setText("I JUST CHANGED THIS LABEL!!!!!!!");
        }

        window.display();
    }
}
