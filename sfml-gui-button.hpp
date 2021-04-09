
#include <SFML/Graphics.hpp>

class Button
{

public:

	Button(sf::RectangleShape GUI_PID, sf::RectangleShape GUI_COLOR, float BUTTON_LENGTH, sf::Color TEXT_COLOR, std::string BUTTON_TEXT, std::string RIGHT_TEXT)
	{
		buttonFont.loadFromFile("fonts/cour.ttf");
		buttonText.setCharacterSize(13);
		buttonText.setFillColor(TEXT_COLOR);
		buttonText.setFont(buttonFont);
		buttonText.setString(BUTTON_TEXT);
		buttonText.setOrigin(buttonText.getGlobalBounds().width / 2, buttonText.getGlobalBounds().height / 2);

		rightText.setCharacterSize(13);
		rightText.setFillColor(TEXT_COLOR);
		rightText.setFont(buttonFont);
		rightText.setString(RIGHT_TEXT);

		button.setSize(sf::Vector2f(BUTTON_LENGTH, 15.0f));
		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);
		buttonSize = button.getSize();
	}

	void updateButton(sf::RectangleShape GUI_PID, int slot, sf::RenderWindow &window)
	{
		BUTTON_POSITION = sf::Vector2f(GUI_PID.getGlobalBounds().left + 10.0f, GUI_PID.getGlobalBounds().top + slot * 20.0f);
		button.setPosition(BUTTON_POSITION);

		BUTTON_TEXTPOSITION = sf::Vector2f(button.getPosition().x + button.getSize().x / 2, button.getPosition().y + 2.0f);
		buttonText.setPosition(BUTTON_TEXTPOSITION);

		rightText.setPosition(button.getPosition().x + button.getSize().x + 10.0f, button.getPosition().y);

		if (sf::Mouse::getPosition(window).x >= button.getPosition().x &&
			sf::Mouse::getPosition(window).x <= button.getPosition().x + button.getSize().x &&
			sf::Mouse::getPosition(window).y >= button.getPosition().y &&
			sf::Mouse::getPosition(window).y <= button.getPosition().y + button.getSize().y)
		{
			button.setFillColor(sf::Color(themeColor.r + 30.0f, themeColor.g + 30.0f, themeColor.b + 30.0f));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				button.setPosition(BUTTON_POSITION.x + 2.0f, BUTTON_POSITION.y + 2.0f);
				buttonText.setPosition(BUTTON_TEXTPOSITION.x + 2.0f, BUTTON_TEXTPOSITION.y + 2.0f);
			}
		}
		else {
			button.setFillColor(themeColor);
			button.setSize(buttonSize);
		}
	}

	bool isButtonClicked(sf::RenderWindow &window)
	{
		if (sf::Mouse::getPosition(window).x >= button.getPosition().x &&
			sf::Mouse::getPosition(window).x <= button.getPosition().x + button.getSize().x &&
			sf::Mouse::getPosition(window).y >= button.getPosition().y &&
			sf::Mouse::getPosition(window).y <= button.getPosition().y + button.getSize().y)
		{
			button.setFillColor(sf::Color(themeColor.r + 30.0f, themeColor.g + 30.0f, themeColor.b + 30.0f));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonClock.getElapsedTime().asSeconds() >= 0.3f)
			{
				buttonClock.restart();
				return true;				
			}
			else {
				return false;
			}
		}
	}

	void Draw(sf::RenderWindow &window, sf::RectangleShape GUI_PID, sf::RectangleShape GUI_COLOR, int slot)
	{
		window.draw(button);
		window.draw(buttonText);
		window.draw(rightText);
		updateButton(GUI_PID, slot, window);
	}


private:
	sf::RectangleShape button;


	bool isClicked = false;
	sf::Vector2f BUTTON_POSITION;
	sf::Vector2f BUTTON_TEXTPOSITION;

	sf::Color themeColor;
	sf::Vector2f buttonSize;
	sf::Clock buttonClock;
	sf::Clock buttonClockAnim;
	sf::Text buttonText;
	sf::Text rightText;
	sf::Font buttonFont;

};