
# Creating a widget

### First your custom widget class must publicly inherit from SFWIDGET.
```c++ class Checkbox : public SFWIDGET ```

### Setup
In your widgets constructor, you absolutely need to do a few things

You must call the SFWIDGET constructor prior to the derived classes constructor gets ran, like so
```c++
    Button() : SFWIDGET("Button") {
        // Now do setup in the derived constructor
    }
```

Each SFWIDGET contains two lists, ```std::vector<sf::Transformable*> t_parts;``` and ```std::vector<sf::Drawable*> d_parts```
The two lists just hold pointers to your actual objects.

These two lists are used for two different things. d_parts is solely used for drawing the widget. t_parts is used for transformation of the widget.

For every SFML object that makes up your GUI, (sf::RectangleShape, sf::Text, sf::Circle, sf::Sprite, etc, etc) NEEDS TO BE ADDED TO BOTH THESE LISTS.
An example:
```c++
    sf::RectangleShape background;
    sf::Text label;
    t_parts->push_back(&background);
    t_parts->push_back(&label);
    d_parts->push_back(&background);
    d_parts->push_back(&label);
```
For complex widgets this can get quite long, unfortunately there is no base class that different things like sf::Text's and sf::Shape's both inherit from that allow for both drawing and transformations of the object in SFML.

---

### Size of the widget.
As well as this, we need to compute the actual bounding box size of your widget, so other widgets around it can also be placed without overlapping.

Each SFWIDGET has a ```sf::FloatRect w_size``` variable that holds the actual total size of the widget.

So after you've set the size and positions of all the parts that make up your widget, you need to calculate the bounding box. Fortunately, each SFWIDGET class also has a ```sf::FloatRect computeBoundingBox(const std::vector<sf::Transformable*>& parts)``` function.

So at the end of the constructor (or anytime the size of the widget may be altered.) you just need to: 
```c++ 
    w_size = computeBoundingBox(t_parts);
```

If your curious about the bounding box of your widget, the GUI class has a ```void DebugDraw()``` function that will draw the bounding boxes of all widgets.

---

### Positioning the widget in the correct place.
Every SFWIDGET has a ```sf::Vector2f w_pos```, this is the actual position
of the widget relative to the GUI window. A.K.A this is the top left point of the widget. (automatically determined via w_index)

Now that you know of your w_pos variable, you can then set the position of all the parts that make up your widget relative to w_pos.

Positioning should be done within ```void setPosition(sf::Vector2f pos)```
Every SFWIDGET should override setPosition(), and inside this you can set the positions of all the parts that make your widget.

setPosition() is automatically ran every time the gui window is moved.

Below is an example from ```button.hpp```
```c++
    // b_background = the actual button object (origin is top left)
    // centerText is a helper to just put text in the center of a rect.
    void setPosition(sf::Vector2f pos) override {
        w_pos = pos;
        b_background.setPosition(w_pos);
        centerText(b_text, b_background);
    }
```

---

### Handling Interaction
Every SFWIDGET has a ```void SoftUpdate()``` function that gets ran every single frame inside gui.Update()

Here you can handle interaction for the widget, i recommend using the helper functions provided in sfgui-utils.hpp to make your life a little easier.

Below is an example of the interaction logic in ```button.hpp```
```c++
    void SoftUpdate() override {
        hovering = false;
        clicked = false;
        if (isMouseInsideRect(*SF_WINDOW, b_background)) {
            b_background.setFillColor(HOVER_COLOR);
            hovering = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !leftMouseWasPressed) {
                clicked = true;
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                b_background.setFillColor(CLICK_COLOR);
                b_text.setScale(sf::Vector2f(0.9f, 0.9f));
            } else {
                b_text.setScale(sf::Vector2f(1.f, 1.f));
            }
        }
        else
        {
            b_background.setFillColor(GUI_PRIMARY_COLOR);
        }
    }
```

---

### Conclusion
Other than that, the rest is up to you. The SFWIDGET base class only handles positioning, size, drawing and managing the widget by assigning each widget created an ID. I highly recommend taking a look at sf_widget.h before making your own widget.

I Recommend taking a look at ```label.hpp```, this is as simple as it gets for a widget.

Side note, each SFWIDGET has a pointer to the main sf::RenderWindow under the name SF_WINDOW


