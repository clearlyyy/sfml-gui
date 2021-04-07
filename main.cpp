#include <SFML/Graphics.hpp>
#include "sfml-gui.hpp"
/*
this file shouldn't be used if you want to use the library, main.cpp is only for testing purposes, and gives me a way to test
and imagine what the GUI would work like in a real games enviroment.

All that said, if you want to test the library feel free to use my main.cpp, although you could create your own.
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    gui GUI("test window 1", sf::Vector2f(400, 400), sf::Vector2f(720, 350), sf::Color(41, 39, 39, 128), sf::Color(200, 152, 237), sf::Color(46, 45, 46));
    text Text1(GUI.getGUI(), "test text 1", sf::Color(255, 255, 255), window);
    text Text2(GUI.getGUI(), "Text Number 2!", sf::Color(255, 255, 255), window);
    CheckBox checkBox1(GUI.getGUIColor(), "Checkbox Test 1", sf::Color(255, 255, 255));
   
    bool checktest = false;

    sf::RectangleShape test;
    test.setPosition(sf::Vector2f(200, 200));
    test.setSize(sf::Vector2f(200, 200));
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(123, 187, 219));    
        GUI.UPDATE_GUI(window);
        GUI.DRAW_GUI(window);     
        Text1.Draw(window, 1, GUI.getGUI());        
        checkBox1.Draw(window, 2, GUI.getGUI(), checktest);
        if (checktest) {
            window.draw(test);
            Text2.Draw(window, 3, GUI.getGUI());
        }              
        window.display();
    }

    return 0;
}
