#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>  
#include "C_FPS.h"
#pragma once
class C_Player
{
private:
	C_FPS FPS;
public:
	// Error code for engine error process
	std::string error;

	float dt2;
	enum FaceDirection { Left, Right };
	enum Direction { Walk_Left, Walk_Right, Idle_Left, Idle_Right, Jump_Left, Jump_Right, Fall_Left, Fall_Right, Death_Right, Death_Left};
	Direction dir;
	FaceDirection FaceDir;

	sf::Clock C_Player_clock;
	sf::Time C_Player_elapsed;
	sf::Clock C_Player_clock_2;
	sf::Time C_Player_elapsed_2;
	sf::Clock C_Player_clock_3;
	sf::Time C_Player_elapsed_3;
	sf::Clock clock;
	sf::Clock clock2;
	sf::Sound sound2;
	sf::SoundBuffer buffer2;

	sf::Vector2i source;
	sf::Texture P_Texture;
	sf::Sprite P_Sprite;
	int block, levelcount;
	bool groundtest;
	bool Ground, Wall_R, Wall_L, soundtest, Roof, intersects, goal = false;
	bool up, down, left, right, jump, jump2, douplejump, douplejump2, idle, Death, score = false;
	void Load(std::string Texture_Name, int x, int y);
	void update(sf::RenderWindow &window);
	void move();
	void colisionRectangle(sf::RectangleShape rectangle, int blocks);
	void colisionSprite(sf::Sprite sprite, std::string tag, int level);
	C_Player();
	~C_Player();
};

