
#include <SFML/Graphics.hpp>

class CheckBox
{
public:

	CheckBox(sf::RectangleShape GUI_COLOR, std::string CHECKBOX_TEXT, sf::Color TEXT_COLOR)
	{

		//init text for the checkbox
		checkBoxFont.loadFromFile("fonts/cour.ttf");
		checkBoxText.setCharacterSize(13);
		checkBoxText.setFillColor(TEXT_COLOR);
		checkBoxText.setFont(checkBoxFont);
		checkBoxText.setString(CHECKBOX_TEXT);




		checkBox_Background.setSize(sf::Vector2f(15.0f, 15.0f));
		checkBox_Background.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));
		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40, GUI_COLOR.getFillColor().g - 40, GUI_COLOR.getFillColor().b - 40);
		check_Texture.loadFromFile("images/checkmark.png");
		checkBox_Check.setSize(checkBox_Background.getSize());
		checkBox_Check.setTexture(&check_Texture);

		checkBoxTimer.restart();

	}

	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID, bool &BOOLEAN)
	{				
		window.draw(checkBox_Background);
		window.draw(checkBoxText);

		if (activateFlag) {
			BOOLEAN = !BOOLEAN;
			activateFlag = false;
		}

		if (activated) {
			window.draw(checkBox_Check);
		}
		
		updateCheckBox(slot, GUI_PID, window);
	}

	void updateCheckBox(int slot, sf::RectangleShape GUI_BACKGROUND, sf::RenderWindow &window)
	{
		sf::Vector2f CHECKBOX_POSITION;		
		CHECKBOX_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		checkBox_Background.setPosition(CHECKBOX_POSITION);
		checkBox_Check.setPosition(CHECKBOX_POSITION);


		if (sf::Mouse::getPosition(window).x >= checkBox_Background.getPosition().x &&
			sf::Mouse::getPosition(window).x <= checkBox_Background.getPosition().x + checkBox_Background.getSize().x &&
			sf::Mouse::getPosition(window).y >= checkBox_Background.getPosition().y &&
			sf::Mouse::getPosition(window).y <= checkBox_Background.getPosition().y + checkBox_Background.getSize().y)
		{
			checkBox_Background.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (checkBoxTimer.getElapsedTime().asSeconds() >= 0.2f) {
					activateFlag = true;
					activated = !activated;
					checkBoxTimer.restart();
				}
			}			
		}
		else
			checkBox_Background.setFillColor(themeColor);
		

		//update position for text

		checkBoxText.setPosition(sf::Vector2f(CHECKBOX_POSITION.x + 20.0f, CHECKBOX_POSITION.y - 2));

	}

private:
	sf::RectangleShape checkBox_Background;
	sf::Vector2f CHECKBOX_POSITION;


	sf::RectangleShape checkBox_Check;
	sf::Texture check_Texture;
	sf::Clock checkBoxTimer;

	bool activateFlag = false;

	bool boolean2;

	sf::Text checkBoxText;
	sf::Font checkBoxFont;

	sf::Color themeColor;

	bool activated = false;

};