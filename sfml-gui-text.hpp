#include <SFML/Graphics.hpp>


class text
{
public:

	text(sf::RectangleShape GUI_BACKGROUND, int slot, std::string TEXT, sf::Color TEXT_COLOR, sf::RenderWindow& window)
	{
		sf::Vector2f TEXT_POSITION;
		font.loadFromFile("fonts/cour.ttf");
		Text.setCharacterSize(13);
		Text.setFillColor(TEXT_COLOR);
		Text.setFont(font);
		Text.setString(TEXT);

		if (slot == 1) {
			TEXT_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + 20.0f);		
		}
		if (slot == 2) {
			TEXT_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + 40.0f);			
		}
		if (slot == 3) {
			TEXT_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + 60.0f);			
		}
		if (slot == 4) {
			TEXT_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + 80.0f);
		}
		Text.setPosition(TEXT_POSITION);
		Draw(window);
	
	}

	void Draw(sf::RenderWindow &window)
	{
		window.draw(Text);
	}

private:
	sf::Text Text;
	sf::Font font;
};
