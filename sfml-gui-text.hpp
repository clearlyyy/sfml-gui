#include <SFML/Graphics.hpp>


class text
{
public:

	text(sf::RectangleShape GUI_BACKGROUND, std::string TEXT, sf::Color TEXT_COLOR, sf::RenderWindow& window)
	{
		font.loadFromFile("fonts/cour.ttf");
		Text.setCharacterSize(13);
		Text.setFillColor(TEXT_COLOR);
		Text.setFont(font);
		Text.setString(TEXT);
		flag = false;
			
		//updateText(window, slot, GUI_BACKGROUND);
		
	}

	void updateText(sf::RenderWindow &window, int slot, sf::RectangleShape GUI_BACKGROUND)
	{
		sf::Vector2f TEXT_POSITION;		
		
		TEXT_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);			
		
		Text.setPosition(TEXT_POSITION);
	}


	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID) {
		window.draw(Text);
		updateText(window, slot, GUI_PID);
	}
	


	sf::Text returnText()
	{
		return Text;
	}

private:
	sf::Text Text;
	sf::Font font;
	sf::Vector2f TEXT_POSITION;
	bool flag = true;
};
