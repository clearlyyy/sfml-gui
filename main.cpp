#include <SFML/Graphics.hpp>
#include "sfml-gui.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    gui GUI("test window 1", sf::Vector2f(400, 400), sf::Vector2f(720, 350), sf::Color(41, 39, 39, 128), sf::Color(200, 152, 237), sf::Color(46, 45, 46));
    //gui GUI2("test window 2", sf::Vector2f(300, 400), sf::Vector2f(400, 350), sf::Color(41, 39, 39, 128), sf::Color(200, 152, 237), sf::Color(46, 45, 46));
    


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
        GUI.Text("test #1", sf::Color(255, 255, 255), window, 1);
        GUI.Text("text #2", sf::Color(255, 255, 255), window, 2);
        GUI.Text("text #3", sf::Color(255, 255, 255), window, 3);
        GUI.Text("text #4", sf::Color(255, 255, 255), window, 4);
  
      



        window.display();
    }

    return 0;
}
