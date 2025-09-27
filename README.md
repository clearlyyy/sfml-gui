
<h1 align="center">SFML-GUI</h1>
<h2 align="center"> A Fast Retained-Mode Graphical User Interface Library for SFML 3 written in C++ </h2>

![DEMO IMAGE](/github-assets/sfml-gui-demo.gif/)

*SFML-GUI 2* I've rewritten the entire library from scratch for SFML 3.0, this new version is much faster and way easier to use. If you'd like to use the original version, I've archived it on a separate branch.

## About the project
SFML-GUI is a *Retained Mode* GUI, Its fast, extremely simple to use and it just works.
It enables fast iterations and quick GUI design, so you can spend more time on your game logic, and less on temporary debugging UI.

## Performance
*SFML-GUI 2* is exponentially faster than the previous version. Using the example below, rendering just the GUI takes *~0.2ms* on my system. This comes with changes how we handle the state of the GUI, since it is a *Retained Mode* GUI, we dont need to reconstruct the UI every single frame.

<h1></h1>

Currently sfml-gui Supports the following widgets.

Labels | Check Boxes | List Boxes | Sliders | Buttons | 
-------|-------------|------------|---------|---------|

<h1> Creating a GUI has never been easier! </h1>

The Following code showcases how some widgets can be created, and used.
```c++
int main() {
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
        // Main SFML Draw Loop
        gui.Update();
        gui.Draw();
        if (button.isClicked())
            std::cout << "Just Clicked this Button!" << std::endl;
    }
}
```
<h2> Output </h2>

![DEMO GIF](/github-assets/sfml-gui-example.gif/)

This project is inspired by dear imgui, i recommend checking it out:
https://github.com/ocornut/imgui




