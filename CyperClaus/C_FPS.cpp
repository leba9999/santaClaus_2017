#include "C_FPS.h"

void C_FPS::Counter(sf::RenderWindow & window)
{
	// counting fps
	fps++;

	// get the current mouse position in the window
	pixelPos = sf::Mouse::getPosition(window);
	// convert it to world coordinates
	worldPos = window.mapPixelToCoords(pixelPos);
	T_FPS.setPosition(window.getView().getCenter().x - 400, window.getView().getCenter().y - 300);

}

void C_FPS::Logic_Counter()
{
	// Elapsed time from last clock restart
	C_FPS_elapsed = C_FPS_clock.getElapsedTime();

	// If elapsed time gets over 1 second
	if (C_FPS_elapsed.asSeconds() >= 1)
	{
		// Getting highest fps value
		if (fps > fpsMax)
		{
			fpsMax = fps;
			T_FPS.setFillColor(sf::Color::Cyan);
		}
		else
		{
			T_FPS.setFillColor(sf::Color::Magenta);
		}

		// Having fun with colors
		// Text color change when fps value is smaller or higher
		if (fps < 30)
		{
			// if fps is smaller than 30 T_FPS color is Red
			T_FPS.setFillColor(sf::Color::Red);
		}
		if (fps >= 30 && fps < 60)
		{
			// if fps is higher or equal to 30 but smaller than 60 T_FPS color is Yellow
			T_FPS.setFillColor(sf::Color::Yellow);
		}
		if (fps >= 60 && fps < 300)
		{
			// if fps is higher or equal to 30 but smaller than 300 T_FPS color is Green
			T_FPS.setFillColor(sf::Color::Green);
		}

		// Create stringstream sstr_FPS
		std::stringstream sstr_FPS;
		fpstest = fps;

		sstr_FPS << "fps: " << fpstest << " \nMax fps: " << fpsMax << " \nMouse X: " << worldPos.x << " Y : " << worldPos.y;
		// Text set string
		T_FPS.setString(sstr_FPS.str());

		//Reseting fps count
		fps = 0;

		// Reseting clock for next countdown
		C_FPS_clock.restart();
	}
}

C_FPS::C_FPS()
{
	if (!font.loadFromFile("Resources/arial.TTF"))
	{
		// error code...
		error = "#0000";
	}

	// select the font
	T_FPS.setFont(font); // font is a sf::Font

	// set the string to display
	T_FPS.setString("Hello. \nTest 1, 2, 3");

	// set the character size
	T_FPS.setCharacterSize(10); // in pixels, not points!

	T_FPS.setOutlineThickness(2);
	T_FPS.setOutlineColor(sf::Color::Black);

	// set the color
	T_FPS.setFillColor(sf::Color::Magenta);
}

