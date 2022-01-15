#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#pragma once
class C_FPS
{
public:
	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;
	int fps, fpsMax, fpstest;

	// Error code for engine error process
	std::string error;

	// Starts C_FPS_Clock
	sf::Clock C_FPS_clock;

	// Create Time called C_FPS_elapsed
	sf::Time C_FPS_elapsed;

	// Create Font called font
	sf::Font font;

	// Create Text called T_FPS
	sf::Text T_FPS;

	// Function called Counter
	void Counter(sf::RenderWindow &window);

	// Function called Logic_Counter for Thread
	void Logic_Counter();

	C_FPS();
};