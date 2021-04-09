#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>


class SliderInt
{
public:
	
	SliderInt(sf::RectangleShape GUI_COLOR, sf::Color TEXT_COLOR, float SliderLength, std::string TEXT)
	{

		//text init

		sliderFont.loadFromFile("fonts/cour.ttf");
		sliderText.setCharacterSize(13);
		sliderText.setFillColor(TEXT_COLOR);
		sliderText.setFont(sliderFont);
		sliderText.setString(TEXT);



		shownValueText.setCharacterSize(13);
		shownValueText.setFillColor(sf::Color::White);
		shownValueText.setFont(sliderFont);
		shownValueText.setString("123");



		shownValueRect = shownValueText.getLocalBounds();

		shownValueText.setOrigin(shownValueRect.left + shownValueRect.width / 2.0f, SliderBackground.getPosition().y + 1.0f);

		SliderBackground.setSize(sf::Vector2f(SliderLength, 15.0f));
		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);
		SliderBackground.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));
		//slider.setOrigin(sf::Vector2f(slider.getSize().x / 2, slider.getSize().y / 2));
		slider.setSize(sf::Vector2f(10, 15.0f));
		slider.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));



		sliderOverHang.setSize(sf::Vector2f(SliderBackground.getSize().x + slider.getPosition().x, 13.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);

		shownValueText.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);

		sliderOverHang.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));

		
	}

	void updateSlider(sf::RectangleShape GUI_BACKGROUND, int slot, sf::RenderWindow &window)
	{
		sf::Vector2f SLIDER_POSITION;
		sf::Vector2f SLIDER_POSITION2;
		
		SLIDER_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground.setPosition(SLIDER_POSITION);

		sliderOverHang.setSize(sf::Vector2f(slider.getPosition().x - SliderBackground.getPosition().x, 11.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x + 3.0f, SliderBackground.getPosition().y + 2);
		
		shownValueRect = shownValueText.getLocalBounds();
		shownValueText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x / 2, SliderBackground.getPosition().y);

		sliderText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x + 10.0f, SliderBackground.getPosition().y);

		if (SliderInitflag) {
			SLIDER_POSITION2 = sf::Vector2f(SliderBackground.getGlobalBounds().left + SliderBackground.getSize().x / 2 - 5.0f, SliderBackground.getGlobalBounds().top);
			slider.setPosition(SLIDER_POSITION2);
			SliderInitflag = false;
		}
		

		if (sf::Mouse::getPosition(window).x >= slider.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider.getPosition().x + slider.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider.getPosition().y + slider.getSize().y)
		{
			slider.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, SliderBackground.getPosition().y);
				newSliderPos.x = slider.getPosition().x - SliderBackground.getPosition().x;

			}
		}
		else {
			slider.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider.setPosition(newSliderPos.x + SliderBackground.getGlobalBounds().left, SliderBackground.getPosition().y);
		}

		if (sf::Mouse::getPosition(window).x >= SliderBackground.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground.getPosition().x + SliderBackground.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground.getPosition().y + SliderBackground.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, slider.getPosition().y);
			}
		}

		if (slider.getPosition().x >= SliderBackground.getPosition().x + SliderBackground.getSize().x)
		{
			slider.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x, slider.getPosition().y);
		}
		if (slider.getPosition().x <= SliderBackground.getPosition().x)
		{
			slider.setPosition(SliderBackground.getPosition().x, slider.getPosition().y);
		}


	}


	void changeValue(int &value, int min, int max)
	{
		max = max - min;
		x = SliderBackground.getSize().x / max;
		value = sliderOverHang.getSize().x / x + min;
		std::stringstream ss;
		ss << value;
		std::string shownValue = ss.str();
		shownValueText.setString(shownValue);
	}
	



	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID, int& value, int min, int max)
	{
		window.draw(SliderBackground);
		window.draw(sliderOverHang);
		window.draw(slider);
		window.draw(sliderText);
		window.draw(shownValueText);
		updateSlider(GUI_PID, slot, window);
		changeValue(value, min, max);
	}


private:
	sf::RectangleShape SliderBackground;

	sf::RectangleShape slider;

	sf::Vector2f newSliderPos;
	sf::Vector2f sliderPos;


	
	sf::FloatRect shownValueRect;
	int shownValue;
	sf::Text shownValueText;


	sf::RectangleShape sliderOverHang;

	sf::Text sliderText;
	sf::Font sliderFont;

	float x;
	int y;

	bool flag = true;
	bool negative = false;
	bool positive = false;

	bool SliderInitflag = true;

	sf::Color themeColor;
};

//for the sake of simpilicty for the user, im just bascially duplicating the class, except it will use floats, rather than an int.
class SliderFloat
{
public:

	SliderFloat(sf::RectangleShape GUI_COLOR, sf::Color TEXT_COLOR, float SliderLength, std::string TEXT)
	{

		//text init

		sliderFont.loadFromFile("fonts/cour.ttf");
		sliderText.setCharacterSize(13);
		sliderText.setFillColor(TEXT_COLOR);
		sliderText.setFont(sliderFont);
		sliderText.setString(TEXT);


		shownValueText.setCharacterSize(13);
		shownValueText.setFillColor(sf::Color::White);
		shownValueText.setFont(sliderFont);
		shownValueText.setString("123");

		shownValueRect = shownValueText.getLocalBounds();

		shownValueText.setOrigin(shownValueRect.left + shownValueRect.width / 2.0f, SliderBackground.getPosition().y + 1.0f);


		SliderBackground.setSize(sf::Vector2f(SliderLength, 15.0f));
		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);
		SliderBackground.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));
		//slider.setOrigin(sf::Vector2f(slider.getSize().x / 2, slider.getSize().y / 2));
		slider.setSize(sf::Vector2f(10, 15.0f));
		slider.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));


		sliderOverHang.setSize(sf::Vector2f(SliderBackground.getSize().x + slider.getPosition().x, 13.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		sliderOverHang.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));


	}

	void updateSlider(sf::RectangleShape GUI_BACKGROUND, int slot, sf::RenderWindow& window)
	{
		sf::Vector2f SLIDER_POSITION;
		sf::Vector2f SLIDER_POSITION2;

		SLIDER_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground.setPosition(SLIDER_POSITION);

		sliderOverHang.setSize(sf::Vector2f(slider.getPosition().x - SliderBackground.getPosition().x, 11.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x + 3.0f, SliderBackground.getPosition().y + 2);
		
		shownValueRect = shownValueText.getLocalBounds();
		//shownValueText.setOrigin(shownValueRect.left + shownValueRect.width / 2.0f, SliderBackground.getPosition().y + 1.0f);
		shownValueText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x / 2, SliderBackground.getPosition().y);

		sliderText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x + 10.0f, SliderBackground.getPosition().y);

		if (SliderInitflag) {
			SLIDER_POSITION2 = sf::Vector2f(SliderBackground.getGlobalBounds().left + SliderBackground.getSize().x / 2 - 5.0f, SliderBackground.getGlobalBounds().top - 3.0f);
			slider.setPosition(SLIDER_POSITION2);
			SliderInitflag = false;
		}


		if (sf::Mouse::getPosition(window).x >= slider.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider.getPosition().x + slider.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider.getPosition().y + slider.getSize().y)
		{
			slider.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, SliderBackground.getPosition().y);
				newSliderPos.x = slider.getPosition().x - SliderBackground.getPosition().x;

			}
		}
		else {
			slider.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider.setPosition(newSliderPos.x + SliderBackground.getSize().x + SliderBackground.getGlobalBounds().left - SliderBackground.getSize().x, SliderBackground.getPosition().y);
		}

		if (sf::Mouse::getPosition(window).x >= SliderBackground.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground.getPosition().x + SliderBackground.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground.getPosition().y + SliderBackground.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, slider.getPosition().y);
			}
		}

		if (slider.getPosition().x >= SliderBackground.getPosition().x + SliderBackground.getSize().x)
		{
			slider.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x, slider.getPosition().y);
		}
		if (slider.getPosition().x <= SliderBackground.getPosition().x)
		{
			slider.setPosition(SliderBackground.getPosition().x, slider.getPosition().y);
		}


	}


	void changeValue(float& value, float min, float max)
	{
		max = max - min;
		x = SliderBackground.getSize().x / max;
		value = sliderOverHang.getSize().x / x + min;

		//remove this is you would like more than 2 decimal places!

		value = ceilf(value * 100) / 100;

		//

		std::stringstream ss;
		ss << value;
		std::string shownValue = ss.str();
		shownValueText.setString(shownValue);

	}
	



	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID, float& value, float min, float max)
	{
		window.draw(SliderBackground);
		window.draw(sliderOverHang);
		window.draw(slider);
		window.draw(sliderText);
		window.draw(shownValueText);
		updateSlider(GUI_PID, slot, window);	
		changeValue(value, min, max);
	}


private:
	sf::RectangleShape SliderBackground;

	sf::RectangleShape slider;

	sf::Vector2f newSliderPos;
	sf::Vector2f sliderPos;

	sf::RectangleShape sliderOverHang;

	sf::Text sliderText;
	sf::Font sliderFont;


	sf::FloatRect shownValueRect;
	int shownValue;
	sf::Text shownValueText;


	float x;
	int y;

	bool flag = true;
	bool negative = false;
	bool positive = false;

	bool SliderInitflag = true;

	sf::Color themeColor;
};

class SliderInt3
{
public:

	SliderInt3(sf::RectangleShape GUI_COLOR, sf::Color TEXT_COLOR, float SliderLength, std::string TEXT)
	{

		//text init

		sliderFont.loadFromFile("fonts/cour.ttf");
		sliderText.setCharacterSize(13);
		sliderText.setFillColor(TEXT_COLOR);
		sliderText.setFont(sliderFont);
		sliderText.setString(TEXT);



		shownValueText.setCharacterSize(13);
		shownValueText.setFillColor(sf::Color::White);
		shownValueText.setFont(sliderFont);
		shownValueText.setString("123");

		shownValueText2.setCharacterSize(13);
		shownValueText2.setFillColor(sf::Color::White);
		shownValueText2.setFont(sliderFont);
		shownValueText2.setString("123");

		shownValueText3.setCharacterSize(13);
		shownValueText3.setFillColor(sf::Color::White);
		shownValueText3.setFont(sliderFont);
		shownValueText3.setString("123");

		shownValueRect = shownValueText.getLocalBounds();
		shownValueRect2 = shownValueText2.getLocalBounds();
		shownValueRect3 = shownValueText3.getLocalBounds();

		shownValueText.setOrigin(shownValueRect.left + shownValueRect.width / 2.0f, SliderBackground.getPosition().y + 1.0f);
		shownValueText2.setOrigin(shownValueRect2.left + shownValueRect2.width / 2.0f, SliderBackground2.getPosition().y + 1.0f);
		shownValueText3.setOrigin(shownValueRect3.left + shownValueRect3.width / 2.0f, SliderBackground3.getPosition().y + 1.0f);

		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);
		SliderBackground.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));

		SliderBackground2.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground2.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));

		SliderBackground3.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground3.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));



		//slider.setOrigin(sf::Vector2f(slider.getSize().x / 2, slider.getSize().y / 2));
		slider.setSize(sf::Vector2f(10, 15.0f));
		slider.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));

		slider2.setSize(sf::Vector2f(10, 15.0f));
		slider2.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));

		slider3.setSize(sf::Vector2f(10, 15.0f));
		slider3.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));



		sliderOverHang.setSize(sf::Vector2f(SliderBackground.getSize().x + slider.getPosition().x, 13.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		sliderOverHang.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));

		sliderOverHang2.setSize(sf::Vector2f(SliderBackground2.getSize().x + slider2.getPosition().x, 13.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);
		sliderOverHang2.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));

		sliderOverHang3.setSize(sf::Vector2f(SliderBackground3.getSize().x + slider3.getPosition().x, 13.0f));
		sliderOverHang3.setPosition(SliderBackground3.getPosition().x, SliderBackground3.getPosition().y);
		sliderOverHang3.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));


		shownValueText.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		shownValueText2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);
		shownValueText3.setPosition(SliderBackground3.getPosition().x, SliderBackground3.getPosition().y);



	}

	void updateSlider(sf::RectangleShape GUI_BACKGROUND, int slot, sf::RenderWindow& window)
	{
		sf::Vector2f SLIDER_POSITION;
		sf::Vector2f SLIDER_POSITION2;
		sf::Vector2f SLIDER_POSITION3;

		SLIDER_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground.setPosition(SLIDER_POSITION);

		SLIDER_POSITION2 = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + SliderBackground.getSize().x + 20.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground2.setPosition(SLIDER_POSITION2);

		SLIDER_POSITION3 = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + SliderBackground.getSize().x + SliderBackground2.getSize().x + 30.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground3.setPosition(SLIDER_POSITION3);

		sliderOverHang.setSize(sf::Vector2f(slider.getPosition().x - SliderBackground.getPosition().x, 11.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x + 3.0f, SliderBackground.getPosition().y + 2);

		sliderOverHang2.setSize(sf::Vector2f(slider2.getPosition().x - SliderBackground2.getPosition().x, 11.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x + 3.0f, SliderBackground2.getPosition().y + 2);

		sliderOverHang3.setSize(sf::Vector2f(slider3.getPosition().x - SliderBackground3.getPosition().x, 11.0f));
		sliderOverHang3.setPosition(SliderBackground3.getPosition().x + 3.0f, SliderBackground3.getPosition().y + 2);

		shownValueRect = shownValueText.getLocalBounds();
		shownValueText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x / 2, SliderBackground.getPosition().y);

		shownValueRect2 = shownValueText2.getLocalBounds();
		shownValueText2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x / 2, SliderBackground2.getPosition().y);

		shownValueRect3 = shownValueText3.getLocalBounds();
		shownValueText3.setPosition(SliderBackground3.getPosition().x + SliderBackground3.getSize().x / 2, SliderBackground3.getPosition().y);

		sliderText.setPosition(SliderBackground3.getPosition().x + SliderBackground3.getSize().x + 10.0f, SliderBackground.getPosition().y);

		if (SliderInitflag) {
			//SLIDER_POSITION2 = sf::Vector2f(SliderBackground.getGlobalBounds().left + SliderBackground.getSize().x / 2 - 5.0f, SliderBackground.getGlobalBounds().top);
			slider.setPosition(SLIDER_POSITION);
			slider.setPosition(SLIDER_POSITION2);
			slider.setPosition(SLIDER_POSITION3);

			SliderInitflag = false;
		}


		if (sf::Mouse::getPosition(window).x >= slider.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider.getPosition().x + slider.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider.getPosition().y + slider.getSize().y)
		{
			slider.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, SliderBackground.getPosition().y);
				newSliderPos.x = slider.getPosition().x - SliderBackground.getPosition().x;

			}
		}
		if (sf::Mouse::getPosition(window).x >= slider2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider2.getPosition().x + slider2.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider2.getPosition().y + slider2.getSize().y)
		{
			slider2.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, SliderBackground2.getPosition().y);
				newSliderPos2.x = slider2.getPosition().x - SliderBackground2.getPosition().x;

			}
		}
		if (sf::Mouse::getPosition(window).x >= slider3.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider3.getPosition().x + slider3.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider3.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider3.getPosition().y + slider3.getSize().y)
		{
			slider3.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider3.setPosition(sf::Mouse::getPosition(window).x - slider3.getSize().x / 2, SliderBackground3.getPosition().y);
				newSliderPos3.x = slider3.getPosition().x - SliderBackground3.getPosition().x;

			}
		}
		else {
			slider.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider2.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider3.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider.setPosition(newSliderPos.x + SliderBackground.getSize().x + SliderBackground.getGlobalBounds().left - SliderBackground.getSize().x, SliderBackground.getPosition().y);
			slider2.setPosition(newSliderPos2.x + SliderBackground2.getSize().x + SliderBackground2.getGlobalBounds().left - SliderBackground2.getSize().x, SliderBackground2.getPosition().y);
			slider3.setPosition(newSliderPos3.x + SliderBackground3.getSize().x + SliderBackground3.getGlobalBounds().left - SliderBackground3.getSize().x, SliderBackground3.getPosition().y);
		}

		if (sf::Mouse::getPosition(window).x >= SliderBackground.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground.getPosition().x + SliderBackground.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground.getPosition().y + SliderBackground.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, slider.getPosition().y);
			}
		}
		if (sf::Mouse::getPosition(window).x >= SliderBackground2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground2.getPosition().x + SliderBackground2.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground2.getPosition().y + SliderBackground2.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, slider2.getPosition().y);
			}
		}
		if (sf::Mouse::getPosition(window).x >= SliderBackground3.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground3.getPosition().x + SliderBackground3.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground3.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground3.getPosition().y + SliderBackground3.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider3.setPosition(sf::Mouse::getPosition(window).x - slider3.getSize().x / 2, slider3.getPosition().y);
			}
		}

		if (slider.getPosition().x >= SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f)
		{
			slider.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f, slider.getPosition().y);
		}
		if (slider.getPosition().x <= SliderBackground.getPosition().x)
		{
			slider.setPosition(SliderBackground.getPosition().x, slider.getPosition().y);
		}

		if (slider2.getPosition().x >= SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f)
		{
			slider2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f, slider2.getPosition().y);
		}
		if (slider2.getPosition().x <= SliderBackground2.getPosition().x)
		{
			slider2.setPosition(SliderBackground2.getPosition().x, slider2.getPosition().y);
		}

		if (slider3.getPosition().x >= SliderBackground3.getPosition().x + SliderBackground3.getSize().x - 12.0f)
		{
			slider3.setPosition(SliderBackground3.getPosition().x + SliderBackground3.getSize().x - 12.0f, slider3.getPosition().y);
		}
		if (slider3.getPosition().x <= SliderBackground3.getPosition().x)
		{
			slider3.setPosition(SliderBackground3.getPosition().x, slider3.getPosition().y);
		}


	}


	void changeValue(int& value, int min, int max, int& value2, int v2_min, int v2_max, int& value3, int v3_min, int v3_max)
	{
		max = max + 14;
		max = max - min;
		x = SliderBackground.getSize().x / max;
		value = sliderOverHang.getSize().x / x + min;
		std::stringstream ss;
		ss << value;
		std::string shownValue = ss.str();
		shownValueText.setString(shownValue);

		v2_max = v2_max + 14;
		v2_max = v2_max - v2_min;
		x1 = SliderBackground2.getSize().x / v2_max;
		value2 = sliderOverHang2.getSize().x / x1 + v2_min;
		std::stringstream ss2;
		ss2 << value2;
		std::string shownValue2 = ss2.str();
		shownValueText2.setString(shownValue2);

		v3_max = v3_max + 14;
		v3_max = v3_max - v3_min;
		x2 = SliderBackground3.getSize().x / v3_max;
		value3 = sliderOverHang3.getSize().x / x2 + v3_min;
		std::stringstream ss3;
		ss3 << value3;
		std::string shownValue3 = ss3.str();
		shownValueText3.setString(shownValue3);

	}




	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID, int& v1, int v1_min, int v1_max,
		int& v2, int v2_min, int v2_max, int& v3, int v3_min, int v3_max)
	{
		window.draw(SliderBackground);
		window.draw(SliderBackground2);
		window.draw(SliderBackground3);
		window.draw(sliderOverHang);
		window.draw(sliderOverHang2);
		window.draw(sliderOverHang3);
		window.draw(slider);
		window.draw(slider2);
		window.draw(slider3);
		window.draw(sliderText);
		window.draw(shownValueText);
		window.draw(shownValueText2);
		window.draw(shownValueText3);
		updateSlider(GUI_PID, slot, window);
		changeValue(v1, v1_min, v1_max, v2, v2_min, v2_max, v3, v3_min, v3_max);
	}


private:
	sf::RectangleShape SliderBackground;
	sf::RectangleShape SliderBackground2;
	sf::RectangleShape SliderBackground3;

	sf::RectangleShape slider;
	sf::RectangleShape slider2;
	sf::RectangleShape slider3;

	sf::Vector2f newSliderPos;
	sf::Vector2f newSliderPos2;
	sf::Vector2f newSliderPos3;
	sf::Vector2f sliderPos;



	sf::FloatRect shownValueRect;
	sf::Text shownValueText;

	sf::FloatRect shownValueRect2;
	sf::Text shownValueText2;

	sf::FloatRect shownValueRect3;
	sf::Text shownValueText3;


	sf::RectangleShape sliderOverHang;
	sf::RectangleShape sliderOverHang2;
	sf::RectangleShape sliderOverHang3;

	sf::Text sliderText;
	sf::Font sliderFont;

	float x;
	float x1;
	float x2;
	int y;

	bool flag = true;
	bool negative = false;
	bool positive = false;

	bool SliderInitflag = true;

	sf::Color themeColor;
};


class SliderFloat3
{
public:

	SliderFloat3(sf::RectangleShape GUI_COLOR, sf::Color TEXT_COLOR, float SliderLength, std::string TEXT)
	{

		//text init

		sliderFont.loadFromFile("fonts/cour.ttf");
		sliderText.setCharacterSize(13);
		sliderText.setFillColor(TEXT_COLOR);
		sliderText.setFont(sliderFont);
		sliderText.setString(TEXT);



		shownValueText.setCharacterSize(13);
		shownValueText.setFillColor(sf::Color::White);
		shownValueText.setFont(sliderFont);
		shownValueText.setString("123");

		shownValueText2.setCharacterSize(13);
		shownValueText2.setFillColor(sf::Color::White);
		shownValueText2.setFont(sliderFont);
		shownValueText2.setString("123");

		shownValueText3.setCharacterSize(13);
		shownValueText3.setFillColor(sf::Color::White);
		shownValueText3.setFont(sliderFont);
		shownValueText3.setString("123");

		shownValueRect = shownValueText.getLocalBounds();
		shownValueRect2 = shownValueText2.getLocalBounds();
		shownValueRect3 = shownValueText3.getLocalBounds();

		shownValueText.setOrigin(shownValueRect.left + shownValueRect.width / 2.0f, SliderBackground.getPosition().y + 1.0f);
		shownValueText2.setOrigin(shownValueRect2.left + shownValueRect2.width / 2.0f, SliderBackground2.getPosition().y + 1.0f);
		shownValueText3.setOrigin(shownValueRect3.left + shownValueRect3.width / 2.0f, SliderBackground3.getPosition().y + 1.0f);

		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);
		SliderBackground.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));

		SliderBackground2.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground2.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));

		SliderBackground3.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground3.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));



		//slider.setOrigin(sf::Vector2f(slider.getSize().x / 2, slider.getSize().y / 2));
		slider.setSize(sf::Vector2f(10, 15.0f));
		slider.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));

		slider2.setSize(sf::Vector2f(10, 15.0f));
		slider2.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));

		slider3.setSize(sf::Vector2f(10, 15.0f));
		slider3.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));



		sliderOverHang.setSize(sf::Vector2f(SliderBackground.getSize().x + slider.getPosition().x, 13.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		sliderOverHang.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));

		sliderOverHang2.setSize(sf::Vector2f(SliderBackground2.getSize().x + slider2.getPosition().x, 13.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);
		sliderOverHang2.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));

		sliderOverHang3.setSize(sf::Vector2f(SliderBackground3.getSize().x + slider3.getPosition().x, 13.0f));
		sliderOverHang3.setPosition(SliderBackground3.getPosition().x, SliderBackground3.getPosition().y);
		sliderOverHang3.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));


		shownValueText.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		shownValueText2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);
		shownValueText3.setPosition(SliderBackground3.getPosition().x, SliderBackground3.getPosition().y);



	}

	void updateSlider(sf::RectangleShape GUI_BACKGROUND, int slot, sf::RenderWindow& window)
	{
		sf::Vector2f SLIDER_POSITION;
		sf::Vector2f SLIDER_POSITION2;
		sf::Vector2f SLIDER_POSITION3;

		SLIDER_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground.setPosition(SLIDER_POSITION);

		SLIDER_POSITION2 = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + SliderBackground.getSize().x + 20.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground2.setPosition(SLIDER_POSITION2);

		SLIDER_POSITION3 = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + SliderBackground.getSize().x + SliderBackground2.getSize().x + 30.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground3.setPosition(SLIDER_POSITION3);

		sliderOverHang.setSize(sf::Vector2f(slider.getPosition().x - SliderBackground.getPosition().x, 11.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x + 3.0f, SliderBackground.getPosition().y + 2);

		sliderOverHang2.setSize(sf::Vector2f(slider2.getPosition().x - SliderBackground2.getPosition().x, 11.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x + 3.0f, SliderBackground2.getPosition().y + 2);

		sliderOverHang3.setSize(sf::Vector2f(slider3.getPosition().x - SliderBackground3.getPosition().x, 11.0f));
		sliderOverHang3.setPosition(SliderBackground3.getPosition().x + 3.0f, SliderBackground3.getPosition().y + 2);

		shownValueRect = shownValueText.getLocalBounds();
		shownValueText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x / 2, SliderBackground.getPosition().y);

		shownValueRect2 = shownValueText2.getLocalBounds();
		shownValueText2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x / 2, SliderBackground2.getPosition().y);

		shownValueRect3 = shownValueText3.getLocalBounds();
		shownValueText3.setPosition(SliderBackground3.getPosition().x + SliderBackground3.getSize().x / 2, SliderBackground3.getPosition().y);

		sliderText.setPosition(SliderBackground3.getPosition().x + SliderBackground3.getSize().x + 10.0f, SliderBackground.getPosition().y);

		if (SliderInitflag) {
			//SLIDER_POSITION2 = sf::Vector2f(SliderBackground.getGlobalBounds().left + SliderBackground.getSize().x / 2 - 5.0f, SliderBackground.getGlobalBounds().top);
			slider.setPosition(SLIDER_POSITION);
			slider.setPosition(SLIDER_POSITION2);
			slider.setPosition(SLIDER_POSITION3);

			SliderInitflag = false;
		}


		if (sf::Mouse::getPosition(window).x >= slider.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider.getPosition().x + slider.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider.getPosition().y + slider.getSize().y)
		{
			slider.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, SliderBackground.getPosition().y);
				newSliderPos.x = slider.getPosition().x - SliderBackground.getPosition().x;

			}
		}
		if (sf::Mouse::getPosition(window).x >= slider2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider2.getPosition().x + slider2.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider2.getPosition().y + slider2.getSize().y)
		{
			slider2.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, SliderBackground2.getPosition().y);
				newSliderPos2.x = slider2.getPosition().x - SliderBackground2.getPosition().x;

			}
		}
		if (sf::Mouse::getPosition(window).x >= slider3.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider3.getPosition().x + slider3.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider3.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider3.getPosition().y + slider3.getSize().y)
		{
			slider3.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider3.setPosition(sf::Mouse::getPosition(window).x - slider3.getSize().x / 2, SliderBackground3.getPosition().y);
				newSliderPos3.x = slider3.getPosition().x - SliderBackground3.getPosition().x;

			}
		}
		else {
			slider.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider2.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider3.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider.setPosition(newSliderPos.x + SliderBackground.getSize().x + SliderBackground.getGlobalBounds().left - SliderBackground.getSize().x, SliderBackground.getPosition().y);
			slider2.setPosition(newSliderPos2.x + SliderBackground2.getSize().x + SliderBackground2.getGlobalBounds().left - SliderBackground2.getSize().x, SliderBackground2.getPosition().y);
			slider3.setPosition(newSliderPos3.x + SliderBackground3.getSize().x + SliderBackground3.getGlobalBounds().left - SliderBackground3.getSize().x, SliderBackground3.getPosition().y);
		}

		if (sf::Mouse::getPosition(window).x >= SliderBackground.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground.getPosition().x + SliderBackground.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground.getPosition().y + SliderBackground.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, slider.getPosition().y);
			}
		}
		if (sf::Mouse::getPosition(window).x >= SliderBackground2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground2.getPosition().x + SliderBackground2.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground2.getPosition().y + SliderBackground2.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, slider2.getPosition().y);
			}
		}
		if (sf::Mouse::getPosition(window).x >= SliderBackground3.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground3.getPosition().x + SliderBackground3.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground3.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground3.getPosition().y + SliderBackground3.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider3.setPosition(sf::Mouse::getPosition(window).x - slider3.getSize().x / 2, slider3.getPosition().y);
			}
		}

		if (slider.getPosition().x >= SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f)
		{
			slider.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f, slider.getPosition().y);
		}
		if (slider.getPosition().x <= SliderBackground.getPosition().x)
		{
			slider.setPosition(SliderBackground.getPosition().x, slider.getPosition().y);
		}

		if (slider2.getPosition().x >= SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f)
		{
			slider2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f, slider2.getPosition().y);
		}
		if (slider2.getPosition().x <= SliderBackground2.getPosition().x)
		{
			slider2.setPosition(SliderBackground2.getPosition().x, slider2.getPosition().y);
		}

		if (slider3.getPosition().x >= SliderBackground3.getPosition().x + SliderBackground3.getSize().x - 12.0f)
		{
			slider3.setPosition(SliderBackground3.getPosition().x + SliderBackground3.getSize().x - 12.0f, slider3.getPosition().y);
		}
		if (slider3.getPosition().x <= SliderBackground3.getPosition().x)
		{
			slider3.setPosition(SliderBackground3.getPosition().x, slider3.getPosition().y);
		}


	}


	void changeValue(float& value, float min, float max, float& value2, float v2_min, float v2_max, float& value3, float v3_min, float v3_max)
	{
		max = max + 14;
		max = max - min;
		x = SliderBackground.getSize().x / max;

		//remove this line if you dont want to round to 2 decimal places.
		value = ceilf(value * 100) / 100;
		/////////
		value = sliderOverHang.getSize().x / x + min;
		std::stringstream ss;
		ss << value;
		std::string shownValue = ss.str();
		shownValueText.setString(shownValue);

		v2_max = v2_max + 14;
		v2_max = v2_max - v2_min;
		x1 = SliderBackground2.getSize().x / v2_max;

		//remove this line if you dont want to round to 2 decimal places.
		value2 = ceilf(value * 100) / 100;
		/////////
		value2 = sliderOverHang2.getSize().x / x1 + v2_min;
		std::stringstream ss2;
		ss2 << value2;
		std::string shownValue2 = ss2.str();
		shownValueText2.setString(shownValue2);

		v3_max = v3_max + 14;
		v3_max = v3_max - v3_min;
		x2 = SliderBackground3.getSize().x / v3_max;

		//remove this line if you dont want to round to 2 decimal places.
		value3 = ceilf(value * 100) / 100;
		/////////
		value3 = sliderOverHang3.getSize().x / x2 + v3_min;
		std::stringstream ss3;
		ss3 << value3;
		std::string shownValue3 = ss3.str();
		shownValueText3.setString(shownValue3);

	}




	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID, float& v1, float v1_min, float v1_max,
		float& v2, float v2_min, float v2_max, float& v3, float v3_min, float v3_max)
	{
		window.draw(SliderBackground);
		window.draw(SliderBackground2);
		window.draw(SliderBackground3);
		window.draw(sliderOverHang);
		window.draw(sliderOverHang2);
		window.draw(sliderOverHang3);
		window.draw(slider);
		window.draw(slider2);
		window.draw(slider3);
		window.draw(sliderText);
		window.draw(shownValueText);
		window.draw(shownValueText2);
		window.draw(shownValueText3);
		updateSlider(GUI_PID, slot, window);
		changeValue(v1, v1_min, v1_max, v2, v2_min, v2_max, v3, v3_min, v3_max);
	}


private:
	sf::RectangleShape SliderBackground;
	sf::RectangleShape SliderBackground2;
	sf::RectangleShape SliderBackground3;

	sf::RectangleShape slider;
	sf::RectangleShape slider2;
	sf::RectangleShape slider3;

	sf::Vector2f newSliderPos;
	sf::Vector2f newSliderPos2;
	sf::Vector2f newSliderPos3;
	sf::Vector2f sliderPos;



	sf::FloatRect shownValueRect;
	sf::Text shownValueText;

	sf::FloatRect shownValueRect2;
	sf::Text shownValueText2;

	sf::FloatRect shownValueRect3;
	sf::Text shownValueText3;


	sf::RectangleShape sliderOverHang;
	sf::RectangleShape sliderOverHang2;
	sf::RectangleShape sliderOverHang3;

	sf::Text sliderText;
	sf::Font sliderFont;

	float x;
	float x1;
	float x2;
	int y;

	bool flag = true;
	bool negative = false;
	bool positive = false;

	bool SliderInitflag = true;

	sf::Color themeColor;
};


//////////////////////////////////////////
//SLIDER FLOAT 2 CLASSES
//////////////////////////////////////////


class SliderInt2
{
public:

	SliderInt2(sf::RectangleShape GUI_COLOR, sf::Color TEXT_COLOR, float SliderLength, std::string TEXT)
	{

		//text init

		sliderFont.loadFromFile("fonts/cour.ttf");
		sliderText.setCharacterSize(13);
		sliderText.setFillColor(TEXT_COLOR);
		sliderText.setFont(sliderFont);
		sliderText.setString(TEXT);


		shownValueText.setCharacterSize(13);
		shownValueText.setFillColor(sf::Color::White);
		shownValueText.setFont(sliderFont);
		shownValueText.setString("123");

		shownValueText2.setCharacterSize(13);
		shownValueText2.setFillColor(sf::Color::White);
		shownValueText2.setFont(sliderFont);
		shownValueText2.setString("123");

		shownValueRect = shownValueText.getLocalBounds();
		shownValueRect2 = shownValueText2.getLocalBounds();
		
		shownValueText.setOrigin(shownValueRect.left + shownValueRect.width / 2.0f, SliderBackground.getPosition().y + 1.0f);
		shownValueText2.setOrigin(shownValueRect2.left + shownValueRect2.width / 2.0f, SliderBackground2.getPosition().y + 1.0f);
		
		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);
		SliderBackground.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));

		SliderBackground2.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground2.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));


		//slider.setOrigin(sf::Vector2f(slider.getSize().x / 2, slider.getSize().y / 2));
		slider.setSize(sf::Vector2f(10, 15.0f));
		slider.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));

		slider2.setSize(sf::Vector2f(10, 15.0f));
		slider2.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));



		sliderOverHang.setSize(sf::Vector2f(SliderBackground.getSize().x + slider.getPosition().x, 13.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		sliderOverHang.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));

		sliderOverHang2.setSize(sf::Vector2f(SliderBackground2.getSize().x + slider2.getPosition().x, 13.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);
		sliderOverHang2.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));


		shownValueText.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		shownValueText2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);
		


	}

	void updateSlider(sf::RectangleShape GUI_BACKGROUND, int slot, sf::RenderWindow& window)
	{
		sf::Vector2f SLIDER_POSITION;
		sf::Vector2f SLIDER_POSITION2;
		sf::Vector2f SLIDER_POSITION3;

		SLIDER_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground.setPosition(SLIDER_POSITION);

		SLIDER_POSITION2 = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + SliderBackground.getSize().x + 20.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground2.setPosition(SLIDER_POSITION2);

		
		sliderOverHang.setSize(sf::Vector2f(slider.getPosition().x - SliderBackground.getPosition().x, 11.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x + 3.0f, SliderBackground.getPosition().y + 2);

		sliderOverHang2.setSize(sf::Vector2f(slider2.getPosition().x - SliderBackground2.getPosition().x, 11.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x + 3.0f, SliderBackground2.getPosition().y + 2);

		
		shownValueRect = shownValueText.getLocalBounds();
		shownValueText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x / 2, SliderBackground.getPosition().y);

		shownValueRect2 = shownValueText2.getLocalBounds();
		shownValueText2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x / 2, SliderBackground2.getPosition().y);

		
		sliderText.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x + 10.0f, SliderBackground.getPosition().y);

		if (SliderInitflag) {
			//SLIDER_POSITION2 = sf::Vector2f(SliderBackground.getGlobalBounds().left + SliderBackground.getSize().x / 2 - 5.0f, SliderBackground.getGlobalBounds().top);
			slider.setPosition(SLIDER_POSITION);
			slider.setPosition(SLIDER_POSITION2);
			slider.setPosition(SLIDER_POSITION3);

			SliderInitflag = false;
		}


		if (sf::Mouse::getPosition(window).x >= slider.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider.getPosition().x + slider.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider.getPosition().y + slider.getSize().y)
		{
			slider.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, SliderBackground.getPosition().y);
				newSliderPos.x = slider.getPosition().x - SliderBackground.getPosition().x;

			}
		}
		if (sf::Mouse::getPosition(window).x >= slider2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider2.getPosition().x + slider2.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider2.getPosition().y + slider2.getSize().y)
		{
			slider2.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, SliderBackground2.getPosition().y);
				newSliderPos2.x = slider2.getPosition().x - SliderBackground2.getPosition().x;

			}
		}
		else {
			slider.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider2.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider.setPosition(newSliderPos.x + SliderBackground.getSize().x + SliderBackground.getGlobalBounds().left - SliderBackground.getSize().x, SliderBackground.getPosition().y);
			slider2.setPosition(newSliderPos2.x + SliderBackground2.getSize().x + SliderBackground2.getGlobalBounds().left - SliderBackground2.getSize().x, SliderBackground2.getPosition().y);
			
		}

		if (sf::Mouse::getPosition(window).x >= SliderBackground.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground.getPosition().x + SliderBackground.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground.getPosition().y + SliderBackground.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, slider.getPosition().y);
			}
		}
		if (sf::Mouse::getPosition(window).x >= SliderBackground2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground2.getPosition().x + SliderBackground2.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground2.getPosition().y + SliderBackground2.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, slider2.getPosition().y);
			}
		}

		if (slider.getPosition().x >= SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f)
		{
			slider.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f, slider.getPosition().y);
		}
		if (slider.getPosition().x <= SliderBackground.getPosition().x)
		{
			slider.setPosition(SliderBackground.getPosition().x, slider.getPosition().y);
		}

		if (slider2.getPosition().x >= SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f)
		{
			slider2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f, slider2.getPosition().y);
		}
		if (slider2.getPosition().x <= SliderBackground2.getPosition().x)
		{
			slider2.setPosition(SliderBackground2.getPosition().x, slider2.getPosition().y);
		}


	}


	void changeValue(int& value, int min, int max, int& value2, int v2_min, int v2_max)
	{
		max = max + 14;
		max = max - min;
		x = SliderBackground.getSize().x / max;
		value = sliderOverHang.getSize().x / x + min;
		std::stringstream ss;
		ss << value;
		std::string shownValue = ss.str();
		shownValueText.setString(shownValue);

		v2_max = v2_max + 14;
		v2_max = v2_max - v2_min;
		x1 = SliderBackground2.getSize().x / v2_max;
		value2 = sliderOverHang2.getSize().x / x1 + v2_min;
		std::stringstream ss2;
		ss2 << value2;
		std::string shownValue2 = ss2.str();
		shownValueText2.setString(shownValue2);


	}




	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID, int& v1, int v1_min, int v1_max,
		int& v2, int v2_min, int v2_max)
	{
		window.draw(SliderBackground);
		window.draw(SliderBackground2);
		
		window.draw(sliderOverHang);
		window.draw(sliderOverHang2);
		
		window.draw(slider);
		window.draw(slider2);
		
		window.draw(sliderText);
		window.draw(shownValueText);
		window.draw(shownValueText2);
		
		updateSlider(GUI_PID, slot, window);
		changeValue(v1, v1_min, v1_max, v2, v2_min, v2_max);
	}


private:
	sf::RectangleShape SliderBackground;
	sf::RectangleShape SliderBackground2;

	sf::RectangleShape slider;
	sf::RectangleShape slider2;

	sf::Vector2f newSliderPos;
	sf::Vector2f newSliderPos2;
	sf::Vector2f sliderPos;



	sf::FloatRect shownValueRect;
	sf::Text shownValueText;

	sf::FloatRect shownValueRect2;
	sf::Text shownValueText2;

	sf::RectangleShape sliderOverHang;
	sf::RectangleShape sliderOverHang2;

	sf::Text sliderText;
	sf::Font sliderFont;

	float x;
	float x1;
	float x2;
	int y;

	bool flag = true;
	bool negative = false;
	bool positive = false;

	bool SliderInitflag = true;

	sf::Color themeColor;
};


class SliderFloat2
{
public:

	SliderFloat2(sf::RectangleShape GUI_COLOR, sf::Color TEXT_COLOR, float SliderLength, std::string TEXT)
	{

		//text init

		sliderFont.loadFromFile("fonts/cour.ttf");
		sliderText.setCharacterSize(13);
		sliderText.setFillColor(TEXT_COLOR);
		sliderText.setFont(sliderFont);
		sliderText.setString(TEXT);


		shownValueText.setCharacterSize(13);
		shownValueText.setFillColor(sf::Color::White);
		shownValueText.setFont(sliderFont);
		shownValueText.setString("123");

		shownValueText2.setCharacterSize(13);
		shownValueText2.setFillColor(sf::Color::White);
		shownValueText2.setFont(sliderFont);
		shownValueText2.setString("123");

		shownValueRect = shownValueText.getLocalBounds();
		shownValueRect2 = shownValueText2.getLocalBounds();

		shownValueText.setOrigin(shownValueRect.left + shownValueRect.width / 2.0f, SliderBackground.getPosition().y + 1.0f);
		shownValueText2.setOrigin(shownValueRect2.left + shownValueRect2.width / 2.0f, SliderBackground2.getPosition().y + 1.0f);

		themeColor = sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f);
		SliderBackground.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));

		SliderBackground2.setSize(sf::Vector2f(SliderLength, 15.0f));
		SliderBackground2.setFillColor(sf::Color(GUI_COLOR.getFillColor().r - 40.0f, GUI_COLOR.getFillColor().g - 40.0f, GUI_COLOR.getFillColor().b - 40.0f));


		//slider.setOrigin(sf::Vector2f(slider.getSize().x / 2, slider.getSize().y / 2));
		slider.setSize(sf::Vector2f(10, 15.0f));
		slider.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));

		slider2.setSize(sf::Vector2f(10, 15.0f));
		slider2.setFillColor(sf::Color(themeColor.r + 40, themeColor.g + 40, themeColor.b + 40));



		sliderOverHang.setSize(sf::Vector2f(SliderBackground.getSize().x + slider.getPosition().x, 13.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		sliderOverHang.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));

		sliderOverHang2.setSize(sf::Vector2f(SliderBackground2.getSize().x + slider2.getPosition().x, 13.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);
		sliderOverHang2.setFillColor(sf::Color(themeColor.r + 55, themeColor.g + 55, themeColor.b + 55));


		shownValueText.setPosition(SliderBackground.getPosition().x, SliderBackground.getPosition().y);
		shownValueText2.setPosition(SliderBackground2.getPosition().x, SliderBackground2.getPosition().y);



	}

	void updateSlider(sf::RectangleShape GUI_BACKGROUND, int slot, sf::RenderWindow& window)
	{
		sf::Vector2f SLIDER_POSITION;
		sf::Vector2f SLIDER_POSITION2;
		sf::Vector2f SLIDER_POSITION3;

		SLIDER_POSITION = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 10.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground.setPosition(SLIDER_POSITION);

		SLIDER_POSITION2 = sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + SliderBackground.getSize().x + 20.0f, GUI_BACKGROUND.getGlobalBounds().top + slot * 20.0f);
		SliderBackground2.setPosition(SLIDER_POSITION2);


		sliderOverHang.setSize(sf::Vector2f(slider.getPosition().x - SliderBackground.getPosition().x, 11.0f));
		sliderOverHang.setPosition(SliderBackground.getPosition().x + 3.0f, SliderBackground.getPosition().y + 2);

		sliderOverHang2.setSize(sf::Vector2f(slider2.getPosition().x - SliderBackground2.getPosition().x, 11.0f));
		sliderOverHang2.setPosition(SliderBackground2.getPosition().x + 3.0f, SliderBackground2.getPosition().y + 2);


		shownValueRect = shownValueText.getLocalBounds();
		shownValueText.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x / 2, SliderBackground.getPosition().y);

		shownValueRect2 = shownValueText2.getLocalBounds();
		shownValueText2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x / 2, SliderBackground2.getPosition().y);


		sliderText.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x + 10.0f, SliderBackground.getPosition().y);

		if (SliderInitflag) {
			//SLIDER_POSITION2 = sf::Vector2f(SliderBackground.getGlobalBounds().left + SliderBackground.getSize().x / 2 - 5.0f, SliderBackground.getGlobalBounds().top);
			slider.setPosition(SLIDER_POSITION);
			slider.setPosition(SLIDER_POSITION2);
			slider.setPosition(SLIDER_POSITION3);

			SliderInitflag = false;
		}


		if (sf::Mouse::getPosition(window).x >= slider.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider.getPosition().x + slider.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider.getPosition().y + slider.getSize().y)
		{
			slider.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, SliderBackground.getPosition().y);
				newSliderPos.x = slider.getPosition().x - SliderBackground.getPosition().x;

			}
		}
		if (sf::Mouse::getPosition(window).x >= slider2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= slider2.getPosition().x + slider2.getSize().x &&
			sf::Mouse::getPosition(window).y >= slider2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= slider2.getPosition().y + slider2.getSize().y)
		{
			slider2.setFillColor(sf::Color(themeColor.r + 50, themeColor.g + 50, themeColor.b + 50));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, SliderBackground2.getPosition().y);
				newSliderPos2.x = slider2.getPosition().x - SliderBackground2.getPosition().x;

			}
		}
		else {
			slider.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider2.setFillColor(sf::Color(themeColor.r + 30, themeColor.g + 30, themeColor.b + 30));
			slider.setPosition(newSliderPos.x + SliderBackground.getSize().x + SliderBackground.getGlobalBounds().left - SliderBackground.getSize().x, SliderBackground.getPosition().y);
			slider2.setPosition(newSliderPos2.x + SliderBackground2.getSize().x + SliderBackground2.getGlobalBounds().left - SliderBackground2.getSize().x, SliderBackground2.getPosition().y);

		}

		if (sf::Mouse::getPosition(window).x >= SliderBackground.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground.getPosition().x + SliderBackground.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground.getPosition().y + SliderBackground.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider.setPosition(sf::Mouse::getPosition(window).x - slider.getSize().x / 2, slider.getPosition().y);
			}
		}
		if (sf::Mouse::getPosition(window).x >= SliderBackground2.getPosition().x &&
			sf::Mouse::getPosition(window).x <= SliderBackground2.getPosition().x + SliderBackground2.getSize().x &&
			sf::Mouse::getPosition(window).y >= SliderBackground2.getPosition().y &&
			sf::Mouse::getPosition(window).y <= SliderBackground2.getPosition().y + SliderBackground2.getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				slider2.setPosition(sf::Mouse::getPosition(window).x - slider2.getSize().x / 2, slider2.getPosition().y);
			}
		}

		if (slider.getPosition().x >= SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f)
		{
			slider.setPosition(SliderBackground.getPosition().x + SliderBackground.getSize().x - 12.0f, slider.getPosition().y);
		}
		if (slider.getPosition().x <= SliderBackground.getPosition().x)
		{
			slider.setPosition(SliderBackground.getPosition().x, slider.getPosition().y);
		}

		if (slider2.getPosition().x >= SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f)
		{
			slider2.setPosition(SliderBackground2.getPosition().x + SliderBackground2.getSize().x - 12.0f, slider2.getPosition().y);
		}
		if (slider2.getPosition().x <= SliderBackground2.getPosition().x)
		{
			slider2.setPosition(SliderBackground2.getPosition().x, slider2.getPosition().y);
		}


	}


	void changeValue(float& value, float min, float max, float& value2, float v2_min, float v2_max)
	{
		max = max + 14;
		max = max - min;
		x = SliderBackground.getSize().x / max;
		value = sliderOverHang.getSize().x / x + min;
		std::stringstream ss;
		ss << value;
		std::string shownValue = ss.str();
		shownValueText.setString(shownValue);

		v2_max = v2_max + 14;
		v2_max = v2_max - v2_min;
		x1 = SliderBackground2.getSize().x / v2_max;
		value2 = sliderOverHang2.getSize().x / x1 + v2_min;
		std::stringstream ss2;
		ss2 << value2;
		std::string shownValue2 = ss2.str();
		shownValueText2.setString(shownValue2);


	}




	void Draw(sf::RenderWindow& window, int slot, sf::RectangleShape GUI_PID, float& v1, float v1_min, float v1_max,
		float& v2, float v2_min, float v2_max)
	{
		window.draw(SliderBackground);
		window.draw(SliderBackground2);

		window.draw(sliderOverHang);
		window.draw(sliderOverHang2);

		window.draw(slider);
		window.draw(slider2);

		window.draw(sliderText);
		window.draw(shownValueText);
		window.draw(shownValueText2);

		updateSlider(GUI_PID, slot, window);
		changeValue(v1, v1_min, v1_max, v2, v2_min, v2_max);
	}


private:
	sf::RectangleShape SliderBackground;
	sf::RectangleShape SliderBackground2;

	sf::RectangleShape slider;
	sf::RectangleShape slider2;

	sf::Vector2f newSliderPos;
	sf::Vector2f newSliderPos2;
	sf::Vector2f sliderPos;



	sf::FloatRect shownValueRect;
	sf::Text shownValueText;

	sf::FloatRect shownValueRect2;
	sf::Text shownValueText2;

	sf::RectangleShape sliderOverHang;
	sf::RectangleShape sliderOverHang2;

	sf::Text sliderText;
	sf::Font sliderFont;

	float x;
	float x1;
	float x2;
	int y;

	bool flag = true;
	bool negative = false;
	bool positive = false;

	bool SliderInitflag = true;

	sf::Color themeColor;
};






