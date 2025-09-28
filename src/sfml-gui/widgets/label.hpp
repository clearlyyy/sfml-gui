// label.hpp
// Label widget

#include "../sf_widget.h"
#include "../gui.hpp"
#include "../sfgui-utils.hpp"

namespace SFGUI {
class Label : public SFWIDGET {

    public:
        Label(std::string text) : SFWIDGET("Label"), label(TEXT_FONT)
        {
            // Label Init
            label.setPosition(w_pos);
            label.setString(text);
            label.setCharacterSize(CHARACTER_SIZE);
            label.setFillColor(GUI_TEXT_COLOR);
            //Label's origin is left middle.
            sf::FloatRect bounds = label.getLocalBounds();
            label.setOrigin(sf::Vector2f(bounds.position.x, bounds.position.y+1)); // Not sure why, but the bounds are 1 pixel off.

            // Fill list of parts
            this->t_parts.push_back(&label);
            this->d_parts.push_back(&label);

            // Compute bounding box.
            w_size = computeBoundingBox(t_parts);
        }

        void setPosition(sf::Vector2f pos) override {
            w_pos = pos;
            label.setPosition(pos);
        }

        void setText(std::string text) {
            sf::FloatRect old_w_size = w_size;
            label.setString(text);
            w_size = computeBoundingBox(t_parts);
            if (old_w_size != w_size)
                needsCompleteResize = true;
        }

    private:
        std::string l_text;
        sf::Text label;
};
}