#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#pragma once
/*
Updates needed:
-----------------
1. font path load
2. text color change
3. coloring might get easier if just setBaseColor then it uses base color to hover and click colors
4. Sprite/Texture using then i can make fully custom  buttons
5. Text style?
6. try to make if statement if button is drawed then button works but when it is not then it dosen't work
7. More comments! (to .cpp)
8. More button posibilities (radio, -----|--, menu)
9. Try to make everything much easier to code where this is included
10. maybe new name?
-----------------------------------------------------------
*/
class C_Button
{
private:
	int Color_R, Color_G, Color_B, Outline_Color_R, Outline_Color_G, Outline_Color_B;
	int	Hover_Color_R, Hover_Color_G, Hover_Color_B, O_Hover_Color_R, O_Hover_Color_G, O_Hover_Color_B;
	int	Click_Color_R, Click_Color_G, Click_Color_B, O_Click_Color_R, O_Click_Color_G, O_Click_Color_B;
	// "colision detection"
	float boxleft, boxright, boxbottom, boxtop;

	sf::Font font;
public:
	// Output's:
	bool click, pressed, draww, test;
	sf::RectangleShape button;
	sf::Text text;

	// set Button size
	void setSize(int Hight, int Width);
	// set Button position
	void setPosition(int X, int Y);
	// set What read's in the Button
	void setString(std::string String);
	// set text charater size
	void setTextSize(int size);
	// set text style ("bold")
	void setTextStyle(std::string style);
	// set text color
	void setTextFillColor(int R, int G, int B);
	// set outlineThickness if want some cool depth
	void setOutlineThickness(int Thickness);

	// Base Color (use when you dosen't want select all colors)
	void setBaseFillColor(int R, int G, int B);

	// Normal Color
	void setFillColor(int R, int G, int B);
	void setOutlineColor(int R, int G, int B);
	// Hover Color
	void setHoverFillColor(int R, int G, int B);
	void setHoverOutlineColor(int R, int G, int B);
	// Click Color (when button is pressed but no released)
	void setClickFillColor(int R, int G, int B);
	void setClickOutlineColor(int R, int G, int B);

	void update(sf::Vector2f MPos, sf::Event &event);

	void draw(sf::RenderWindow &window);
	C_Button();
};