#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
#pragma once
class C_LoadMaps
{
public:
	sf::RectangleShape Blocks[1000];
	sf::Sprite object[1000];
	sf::Texture texture[1000];
	sf::Sprite item[1000];
	sf::Texture Itemtexture[1000];
	sf::Sprite entity[1000];
	sf::Texture entitytexture[1000];
	sf::Music music;
	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Sound sound2;
	sf::SoundBuffer buffer2;
	sf::Clock clock;

	enum Direction { Walk_Left, Walk_Right, Jump_Left, Jump_Right, Idle_Left, Idle_Right};
	Direction dir;

	sf::Clock C_Player_clock[1000];
	sf::Time C_Player_elapsed[1000];
	sf::Vector2i source[1000];
	bool objectDraw[1000], itemDraw[1000], BlocksDraw[1000], entityDraw[1000];
	int groundBlocks, objects, items, entities, Maxscore;
	int PointA_X[1000], PointA_Y[1000], PointB_X[1000], PointB_Y[1000], time[1000];
	int EPointA_X[1000], EPointA_Y[1000], EPointB_X[1000], EPointB_Y[1000], Etime[1000];
	bool DirectionX[1000], DirectionY[1000];
	bool EDirectionX[1000], EDirectionY[1000];
	int R, G, B, B_R, B_G, B_B, alpha, widht, hight, x, y, Px, Py;
	int levelNumber, levels, TRY, goal[1000], score[1000], death[1000], Edeath[1000], textureRect[1000];
	int levelcount[1000], animationtime[1000];
	std::string File[1000];
	std::string MapsPath[1000];
	std::string MapsTitle[1000];
	std::string functio[1000];
	std::string command, filepath, title, texturefilepath, itemtexturefilepath, musicfile;
	std::string playerTexture, soundfilepath;
	void Load(int level, sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	void update();
	C_LoadMaps();
};

