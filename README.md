
<h1 align="center">SFML-GUI</h1>
<h2 align="center"> A Work-in-Progress Graphical User Interface Library for SFML written in C++ </h2>

![DEMO IMAGE](/demoimages/sfml-demoimage.png/)

This Project is heavily inspired by Dear imgui, if you like this project i highly recommend checking out imgui.
https://github.com/ocornut/imgui

<h1></h1>

This project is currently a W.I.P, but it is fully functional, and will work in your own projects,
All that needs to be added is more widgets.

Currently sfml-gui Supports the following widgets.


Labels | Check Boxes | List Boxes | Many Different Sliders | Buttons | 
-------|-------------|------------|------------------------|---------|

<h1> Creating a GUI has never been easier! </h1>

The Following code showcases how some widgets can be created, and used.
```c++
#include <SFML/Graphics.hpp>
#include "sfml-gui.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    gui NewGui("Hello SFML-GUI!", sf::Vector2f(600, 400), sf::Vector2f(300, 300), sf::Color(41, 39, 39, 128), sf::Color(217, 126, 95), sf::Color(46, 45, 46));
    CheckBox checkBox(NewGui.getGUIColor(), "This is A CheckBox!", sf::Color(255, 255, 255));
    text Text(NewGui.getGUI(), "This is Some Text!", sf::Color(255, 255, 255), window);
    SliderInt newSlider(NewGui.getGUIColor(), sf::Color(255, 255, 255), 200, "This is a Slider!");
    bool testBoolean;
    int testSliderValue;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();        
        window.clear(sf::Color(33, 32, 32));
        NewGui.UPDATE_GUI(window);
        NewGui.DRAW_GUI(window);
        Text.Draw(window, 1, NewGui.getGUI());
        checkBox.Draw(window, 2, NewGui.getGUI(), testBoolean);
        newSlider.Draw(window, 3, NewGui.getGUI(), testSliderValue, 10, 900);
        window.display();
    }
    return 0;
}
```


