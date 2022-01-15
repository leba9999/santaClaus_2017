#include "C_Button.h"

void C_Button::setSize(int Hight, int Width)
{
	button.setSize(sf::Vector2f(Hight, Width));
}

void C_Button::setPosition(int X, int Y)
{
	button.setPosition(X, Y);
}

void C_Button::setString(std::string String)
{
	text.setString(String);
}

void C_Button::setTextSize(int size)
{
	text.setCharacterSize(size);
}

void C_Button::setBaseFillColor(int R, int G, int B)
{
	Color_R = R;
	Color_G = G;
	Color_B = B;
	Outline_Color_R = R;
	Outline_Color_G = G;
	Outline_Color_B = B;
	Hover_Color_R = R;
	Hover_Color_G = G;
	Hover_Color_B = B;
	O_Hover_Color_R = R;
	O_Hover_Color_G = G;
	O_Hover_Color_B = B;
	Click_Color_R = R;
	Click_Color_G = G;
	Click_Color_B = B;
	O_Click_Color_R = R;
	O_Click_Color_G = G;
	O_Click_Color_B = B;
	if (R > 71)
	{
		Outline_Color_R = R - 70;
	}
	if (G > 71)
	{
		Outline_Color_G = G - 70;
	}
	if (B > 71)
	{
		Outline_Color_B = B - 70;
	}
	Hover_Color_R = R + 20;
	Hover_Color_G = G + 20;
	Hover_Color_B = B + 20;
	if (R > 51)
	{
		O_Hover_Color_R = R - 50;
	}
	if (G > 51)
	{
		O_Hover_Color_G = G - 50;
	}
	if (B > 51)
	{
		O_Hover_Color_B = B - 50;
	}

	if (R > 51)
	{
		Click_Color_R = R - 50;
	}
	if (G > 51)
	{
		Click_Color_G = G - 50;
	}
	if (B > 51)
	{
		Click_Color_B = B - 50;
	}

	if (R > 81)
	{
		O_Click_Color_R = R - 80;
	}
	if (G > 81)
	{
		O_Click_Color_G = G - 80;
	}
	if (B > 81)
	{
		O_Click_Color_B = B - 80;
	}
}

void C_Button::setFillColor(int R, int G, int B)
{
	Color_R = R;
	Color_G = G;
	Color_B = B;
}

void C_Button::setOutlineColor(int R, int G, int B)
{
	Outline_Color_R = R;
	Outline_Color_G = G;
	Outline_Color_B = B;
}

void C_Button::setHoverFillColor(int R, int G, int B)
{
	Hover_Color_R = R;
	Hover_Color_G = G;
	Hover_Color_B = B;
}

void C_Button::setHoverOutlineColor(int R, int G, int B)
{
	O_Hover_Color_R = R;
	O_Hover_Color_G = G;
	O_Hover_Color_B = B;
}

void C_Button::setClickFillColor(int R, int G, int B)
{
	Click_Color_R = R;
	Click_Color_G = G;
	Click_Color_B = B;
}

void C_Button::setClickOutlineColor(int R, int G, int B)
{
	O_Click_Color_R = R;
	O_Click_Color_G = G;
	O_Click_Color_B = B;
}

void C_Button::setTextStyle(std::string style)
{
}

void C_Button::setTextFillColor(int R, int G, int B)
{
	text.setFillColor(sf::Color(R, G, B));
}

void C_Button::setOutlineThickness(int Thickness)
{
	button.setOutlineThickness(Thickness);
}

void C_Button::update(sf::Vector2f MPos, sf::Event &event)
{
	click = false;
	pressed = false;
	if (draww)
	{
		boxleft = button.getPosition().x;
		boxright = button.getPosition().x + button.getSize().x;
		boxbottom = button.getPosition().y + button.getSize().y;
		boxtop = button.getPosition().y;
		// Checking for is mouse in the box  (Random button)
		if (boxleft < MPos.x && boxright > MPos.x && boxtop < MPos.y && boxbottom > MPos.y)
		{
			// Mouse hover over button and it  change color
			button.setFillColor(sf::Color(Hover_Color_R, Hover_Color_G, Hover_Color_B));
			button.setOutlineColor(sf::Color(O_Hover_Color_R, O_Hover_Color_G, O_Hover_Color_B));

			// if Mouse Button is Released while mouse is hovering over button
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				// bool is needed because we need one click
				if (!test && !pressed)
				{
					click = true;
					test = true;
				}
			}
			else
			{
				test = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				button.setFillColor(sf::Color(Click_Color_R, Click_Color_G, Click_Color_B));
				button.setOutlineColor(sf::Color(O_Click_Color_R, O_Click_Color_G, O_Click_Color_B));
				test = false;
				click = false;
				pressed = true;
			}
		}
		else
		{
			button.setFillColor(sf::Color(Color_R, Color_G, Color_B));
			button.setOutlineColor(sf::Color(Outline_Color_R, Outline_Color_G, Outline_Color_B));
		}
	}
	text.setPosition(button.getPosition().x, button.getPosition().y);
}

void C_Button::draw(sf::RenderWindow & window)
{
	window.draw(button);
	window.draw(text);
	draww = true;
}

C_Button::C_Button()
{
	if (!font.loadFromFile("Resources/arial.TTF"))
	{
		// Error
	}
	// set font for texts
	text.setFont(font);
}