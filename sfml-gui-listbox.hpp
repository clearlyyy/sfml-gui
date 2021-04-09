#include <SFML/Graphics.hpp>



class ListBox
{
public:
	ListBox(sf::RectangleShape GUI_COLOR, float LISTBOX_LENGTH)
	{

		font.loadFromFile("fonts/cour.ttf");

		dropdownTex.loadFromFile("images/dropdown.png");


		listBoxBackground.setSize(sf::Vector2f(LISTBOX_LENGTH, 15.0f));
		listBoxBackground.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 
			40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));

		
		listBoxDropdown.setSize(sf::Vector2f(15, listBoxBackground.getSize().y));
		listBoxDropdownTexture.setSize(sf::Vector2f(15, listBoxBackground.getSize().y));
		listBoxDropdownTexture.setTexture(&dropdownTex);
		listBoxDropdown.setFillColor(sf::Color( GUI_COLOR.getFillColor().r - 10.0f, GUI_COLOR.getFillColor().g - 10.0f, GUI_COLOR.getFillColor().b - 10.0f));

		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);

		

	}

	void updateListBox(sf::RectangleShape GUI_BACKGROUND, int slot, sf::RenderWindow &window, int size, std::string items[], int &selectedItem)
	{
		LISTBOX_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		listBoxBackground.setPosition(LISTBOX_POSITION);
		listBoxDropdown.setPosition(listBoxBackground.getGlobalBounds().left + listBoxBackground.getSize().x - listBoxDropdown.getSize().x, listBoxBackground.getPosition().y);
		listBoxDropdownTexture.setPosition(listBoxBackground.getGlobalBounds().left + listBoxBackground.getSize().x - listBoxDropdown.getSize().x, listBoxBackground.getPosition().y);

		if (init) {
			for (int i = 0; i <= size; i++) {
				
				dropDowns[i].setSize(listBoxBackground.getSize());
				dropDowns[i].setFillColor(sf::Color(themeColor.r - 60.0f, themeColor.g - 60.0f, themeColor.b - 60.0f));
				dropDownsText[i].setCharacterSize(12);
				dropDownsText[i].setFillColor(sf::Color(255, 255, 255));
				dropDownsText[i].setFont(font);
				dropDownsText[i].setString(items[i]);
				selectedText.setCharacterSize(13);
				selectedText.setFillColor(sf::Color(255, 255, 255));
				selectedText.setFont(font);
				selectedText.setString(actual_selectedItem);				
			}
			init = false;
		}

		selectedText.setPosition(listBoxBackground.getPosition().x + 5.0f, listBoxBackground.getPosition().y - 2.0f);
		selectedText.setString(actual_selectedItem);
		for (int i = 0; i <= size; i++) {
			if (i == 0)
			{
				dropDowns[0].setPosition(listBoxBackground.getPosition().x, listBoxBackground.getPosition().y + 15);
			}
			dropDowns[i].setPosition(listBoxBackground.getPosition().x, listBoxBackground.getPosition().y + i * 15 + 15);
			dropDownsText[i].setPosition(dropDowns[i].getPosition().x + 10.0f, dropDowns[i].getPosition().y - 1.0f);

			if (checkHover(window, dropDowns[i])) {
				dropDowns[i].setFillColor(sf::Color(themeColor.r - 30.0f, themeColor.g - 30.0f, themeColor.b - 30.0f));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					actual_selectedItem = items[i];
					selectedItem = i + 1;
					dropDownActivated = false;
				}
			}
			else {
				dropDowns[i].setFillColor(sf::Color(themeColor.r - 60.0f, themeColor.g - 60.0f, themeColor.b - 60.0f));
			}

		}


		if (checkHover(window, listBoxDropdown))
		{
			listBoxDropdown.setFillColor(sf::Color(themeColor.r + 60.0f, themeColor.g + 60.0f, themeColor.b + 60.0f));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dropDownClock.getElapsedTime().asSeconds() >= 0.2f)
			{
				dropDownClock.restart();
				dropDownClock2.restart();
				dropDownActivated = !dropDownActivated;
			}
		}
		
		else {
			listBoxDropdown.setFillColor(sf::Color(themeColor.r + 30.0f, themeColor.g + 30.0f, themeColor.b + 30.0f));
		}


	}

	void Draw(sf::RenderWindow &window, sf::RectangleShape GUI_PID, int slot, int size, std::string items[], int &selectedItem)
	{
		window.draw(listBoxBackground);
		window.draw(listBoxDropdown);
		window.draw(listBoxDropdownTexture);
		if (dropDownActivated) {
			for (int i = 0; i <= size; i++) {
				window.draw(dropDowns[i]);
				window.draw(dropDownsText[i]);
			}
		}
		window.draw(selectedText);
		updateListBox(GUI_PID, slot, window, size, items, selectedItem);
	}


	bool checkHover(sf::RenderWindow &window, sf::RectangleShape Object)
	{
		if (sf::Mouse::getPosition(window).x >= Object.getPosition().x &&
			sf::Mouse::getPosition(window).x <= Object.getPosition().x + Object.getSize().x &&
			sf::Mouse::getPosition(window).y >= Object.getPosition().y &&
			sf::Mouse::getPosition(window).y <= Object.getPosition().y + Object.getSize().y)
			return true;
		else
			return false;
	}
	bool checkHoverOppo(sf::RenderWindow& window, sf::RectangleShape Object)
	{
		if (sf::Mouse::getPosition(window).x > Object.getPosition().x + Object.getSize().x ||
			sf::Mouse::getPosition(window).x < Object.getPosition().x ||
			sf::Mouse::getPosition(window).y > Object.getPosition().y + Object.getSize().y ||
			sf::Mouse::getPosition(window).y < Object.getPosition().y
			)
			return true;
		else
			return false;
	}

private:
	sf::RectangleShape listBoxBackground;
	sf::Vector2f LISTBOX_POSITION;

	sf::RectangleShape listBoxDropdown;

	sf::RectangleShape dropDowns[99];
	sf::Text dropDownsText[99];
	sf::Font font;

	sf::Text selectedText;

	sf::Clock dropDownClock;
	sf::Clock dropDownClock2;

	std::string actual_selectedItem;

	sf::RectangleShape listBoxDropdownTexture;

	bool init = true;

	bool dropDownActivated = false;

	sf::Color themeColor;

	sf::Texture dropdownTex;

};