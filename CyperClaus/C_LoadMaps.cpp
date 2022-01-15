#include "C_LoadMaps.h"



void C_LoadMaps::Load(int level, sf::RenderWindow &window)
{
	
	std::string text;
	std::ifstream MapReader(MapsPath[level]);
	if (MapReader.is_open()){
		window.setTitle("Santa Claus: alpha | " + MapsTitle[level]);
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "player:"){
			MapReader >> playerTexture;
			MapReader >> command;
			if (command == "position:"){
				MapReader >> Px;
				MapReader >> Py;
			}
		}
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "music:")
		{
			MapReader >> musicfile;
			if (musicfile == "default"){
			}
			else
			{
				if (!music.openFromFile(musicfile))
					std::cout << "Error" << std::endl;

				std::cout << musicfile << std::endl;
				music.setLoop(true);
				music.play();
			}
		}
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "scoresound:")
		{
			MapReader >> soundfilepath;

			if (!buffer.loadFromFile(soundfilepath)) {
				std::cout << "Error" << std::endl;
			}

			sound.setBuffer(buffer);

		}
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "scoresound2:")
		{
			MapReader >> soundfilepath;

			if (!buffer2.loadFromFile(soundfilepath)) {
				std::cout << "Error" << std::endl;
			}

			sound2.setBuffer(buffer2);

		}
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "background:")
		{
			MapReader >> command;
			if (command == "color:")
			{
				MapReader >> B_R;
				MapReader >> B_G;
				MapReader >> B_B;
			}
		}
		
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "grounds:"){
			groundBlocks = 0;
			MapReader >> groundBlocks;
			for (size_t i = 0; i < groundBlocks; i++){
				PointA_X[i] = 0;
				PointA_Y[i] = 0;
				PointB_X[i] = 0;
				PointB_Y[i] = 0;
				bool all = true;
				TRY = 10;
				while(all){
					TRY--;
					if (TRY < 1)
					{
						std::cout << "[LoadMaps.cpp]: error in grounds!" << std::endl;
						system("pause");
						break;
					}
					MapReader >> command;
					std::stringstream ss;
					ss << "ground_" << i << ":";
					text = ss.str();
					if (command == text){
						MapReader >> command;
						if (command == "color:")
						{
							MapReader >> R;
							MapReader >> G;
							MapReader >> B;
							MapReader >> alpha;
							Blocks[i].setFillColor(sf::Color(R, G, B, alpha));
						}
						MapReader >> command;
						if (command == "size:"){
							MapReader >> widht;
							MapReader >> hight;
							Blocks[i].setSize(sf::Vector2f(widht, hight));
						}
						MapReader >> command;
						if (command == "position:") {
							MapReader >> x;
							MapReader >> y;
							Blocks[i].setPosition(x, y);
							all = false;
						}
						MapReader >> command;
						if (command == "move:") {
							MapReader >> PointB_X[i];
							MapReader >> PointB_Y[i];
							MapReader >> time[i];
							PointA_X[i] = Blocks[i].getPosition().x;
							PointA_Y[i] = Blocks[i].getPosition().y;
						}
					}
				}
			}
		}
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "objects:") {
			objects = 0;
			MapReader >> objects;
			for (size_t i = 0; i < objects; i++) {
				bool all = true;
				TRY = 10;
				while (all) {
					TRY--;
					if (TRY < 1)
					{
						std::cout << "[LoadMaps.cpp]: error in objects!" << std::endl;
						system("pause");
						break;
					}
					MapReader >> command;
					std::stringstream ss;
					ss << "object_" << i << ":";
					text = ss.str();
					if (command == text) {
						MapReader >> command;
						if (command == "color:") {
							MapReader >> R;
							MapReader >> G;
							MapReader >> B;
							object[i].setColor(sf::Color(R, G, B));
						}
						MapReader >> command;
						if (command == "path:") {
							MapReader >> texturefilepath;
							if (!texture[i].loadFromFile(texturefilepath)) {

							}

							object[i].setTexture(texture[i], true);
						}
						MapReader >> command;
						if (command == "position:") {
							MapReader >> x;
							MapReader >> y;
							object[i].setPosition(x, y - object[i].getGlobalBounds().height);
							all = false;
						}
					}
				}
			}
		}
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "items:") {
			items = 0;
			Maxscore = 0;
			MapReader >> items;
			for (size_t i = 0; i < items; i++) {
				bool all = true;
				TRY = 10;
				while (all) {
					TRY--;
					if (TRY < 1)
					{
						std::cout << "[LoadMaps.cpp]: error in items!" << std::endl;
						system("pause");
						break;
					}
					score[i] = 0;
					death[i] = 0;
					goal[i] = 0;
					MapReader >> command;
					std::cout << command << std::endl;
					std::stringstream ss;
					ss << "item_" << i << ":";
					text = ss.str();
					if (command == text) {
						MapReader >> command;
						if (command == "color:") {
							MapReader >> R;
							MapReader >> G;
							MapReader >> B;
							item[i].setColor(sf::Color(R, G, B));
						}
						MapReader >> command;
						if (command == "path:") {
							MapReader >> itemtexturefilepath;
							if (!Itemtexture[i].loadFromFile(itemtexturefilepath)) {

							}

							item[i].setTexture(Itemtexture[i], true);
						}
						MapReader >> command;
						if (command == "position:") {
							MapReader >> x;
							MapReader >> y;
							item[i].setPosition(x, y - item[i].getGlobalBounds().height);
							all = false;
						}
						MapReader >> command;
						if (command == "#") {
							MapReader >> command;
							if (command == "goal") {
								goal[i] = i;
								MapReader >> command;
								std::cout << command << std::endl;
								if (command == "level:") {
									MapReader >> levelcount[i];
									std::cout << levelcount[i] << std::endl;
								}
								std::cout << " X: " << item[i].getPosition().x << " Y: " << item[i].getPosition().y << "Function: goal " << levelcount[i] << std::endl;
							}
							if (command == "score") {
								score[i] = i;
								Maxscore++;
								std::cout << " X: " << item[i].getPosition().x << " Y: " << item[i].getPosition().y << "Function: score " << std::endl;
							}
							if (command == "death") {
								death[i] = i;
								std::cout << " X: " << item[i].getPosition().x << " Y: " << item[i].getPosition().y << "Function: death " << std::endl;
							}
						}

					}
				}
			}
		}
		MapReader >> command;
		std::cout << command << std::endl;
		if (command == "entities:") {
			entities = 0;
			MapReader >> entities;
			for (size_t i = 0; i < entities; i++) {
				bool all = true;
				TRY = 10;
				while (all) {
					TRY--;
					if (TRY < 1)
					{
						std::cout << "[LoadMaps.cpp]: error in entities!" << std::endl;
						system("pause");
						break;
					}
					Edeath[i] = -1;
					MapReader >> command;
					std::cout << command << std::endl;
					std::stringstream ss;
					ss << "entity_" << i << ":";
					text = ss.str();
					if (command == text) {
						MapReader >> command;
						if (command == "color:") {
							MapReader >> R;
							MapReader >> G;
							MapReader >> B;
							entity[i].setColor(sf::Color(R, G, B));
						}
						
						MapReader >> command;
						if (command == "path:") {
							MapReader >> itemtexturefilepath;
							if (!entitytexture[i].loadFromFile(itemtexturefilepath)) {

							}

							entity[i].setTexture(entitytexture[i], true);
						}
						MapReader >> command;
						if (command == "animated:") {
							MapReader >> textureRect[i];
							MapReader >> animationtime[i];
							entity[i].setTextureRect(sf::IntRect(source[i].x * textureRect[i], source[i].y * textureRect[i], textureRect[i], textureRect[i]));
						}
						MapReader >> command;
						if (command == "position:") {
							MapReader >> x;
							MapReader >> y;
							entity[i].setPosition(x, y - textureRect[i]);
							all = false;
						}
						MapReader >> command;
						if (command == "move:") {
							MapReader >> EPointB_X[i];
							MapReader >> EPointB_Y[i];
							MapReader >> Etime[i];
							EPointA_X[i] = x;
							EPointA_Y[i] = y;
						}
						MapReader >> command;
						if (command == "#") {
							MapReader >> command;
							if (command == "death") {
								Edeath[i] = i;
								std::cout << " X: " << entity[i].getPosition().x << " Y: " << entity[i].getPosition().y << "Function: death " << std::endl;
							}
						}

					}
				}
			}
		}
	}
}

void C_LoadMaps::draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < groundBlocks; i++)
	{
		if (window.getView().getCenter().x - window.getView().getSize().x / 2 <= Blocks[i].getPosition().x || 
			window.getView().getCenter().x + window.getView().getSize().x / 2 >= Blocks[i].getPosition().x + Blocks[i].getGlobalBounds().width ||
			window.getView().getCenter().y - window.getView().getSize().y / 2 <= Blocks[i].getPosition().y ||
			window.getView().getCenter().y + window.getView().getSize().y / 2 >= Blocks[i].getPosition().y + Blocks[i].getGlobalBounds().height){
			window.draw(Blocks[i]);
			BlocksDraw[i] = true;
		}
		else
		{
			BlocksDraw[i] = false;
		}
	}
	for (size_t i = 0; i < objects; i++)
	{
		if (window.getView().getCenter().x - window.getView().getSize().x / 2 <= object[i].getPosition().x ||
			window.getView().getCenter().x + window.getView().getSize().x / 2 >= object[i].getPosition().x + object[i].getGlobalBounds().width ||
			window.getView().getCenter().y - window.getView().getSize().y / 2 <= object[i].getPosition().y ||
			window.getView().getCenter().y + window.getView().getSize().y / 2 >= object[i].getPosition().y + object[i].getGlobalBounds().height	){
			window.draw(object[i]);
			objectDraw[i] = true;
		}
		else
		{
			objectDraw[i] = false;
		}
	}
	for (size_t i = 0; i < items; i++)
	{
		if (window.getView().getCenter().x - window.getView().getSize().x / 2 <= item[i].getPosition().x ||
			window.getView().getCenter().x + window.getView().getSize().x / 2 >= item[i].getPosition().x + item[i].getGlobalBounds().width ||
			window.getView().getCenter().y - window.getView().getSize().y / 2 <= item[i].getPosition().y ||
			window.getView().getCenter().y + window.getView().getSize().y / 2 >= item[i].getPosition().y + item[i].getGlobalBounds().height) {
			window.draw(item[i]);
			itemDraw[i] = true;
		}
		else
		{
			itemDraw[i] = false;
		}

	}	
	for (size_t i = 0; i < entities; i++)
	{
		if (window.getView().getCenter().x - window.getView().getSize().x / 2 <= entity[i].getPosition().x ||
			window.getView().getCenter().x + window.getView().getSize().x / 2 >= entity[i].getPosition().x + entity[i].getGlobalBounds().width ||
			window.getView().getCenter().y - window.getView().getSize().y / 2 <= entity[i].getPosition().y ||
			window.getView().getCenter().y + window.getView().getSize().y / 2 >= entity[i].getPosition().y + entity[i].getGlobalBounds().height) {
			window.draw(entity[i]);
			entityDraw[i] = true;
		}
		else
		{
			entityDraw[i] = false;
		}
	}
}

void C_LoadMaps::update()
{

	const float dt = clock.restart().asSeconds();
	for (size_t i = 0; i < groundBlocks; i++)
	{
		if (BlocksDraw[i])
		{
			if (Blocks[i].getPosition().x <= PointA_X[i])
			{
				DirectionX[i] = false;
			}
			if (Blocks[i].getPosition().x >= PointB_X[i])
			{
				DirectionX[i] = true;
			}
			if (DirectionX[i] && PointA_X[i] != PointB_X[i])
			{
				Blocks[i].move(-time[i] * dt, 0);
			}
			else if (PointA_X[i] != PointB_X[i])
			{
				Blocks[i].move(time[i] * dt, 0);
			}
			if (Blocks[i].getPosition().y <= PointA_Y[i])
			{
				DirectionY[i] = false;
			}
			if (Blocks[i].getPosition().y >= PointB_Y[i])
			{
				DirectionY[i] = true;
			}
			if (DirectionY[i] && PointA_Y[i] != PointB_Y[i])
			{
				Blocks[i].move(0, -time[i] * dt);
			}
			else if (PointA_Y[i] != PointB_Y[i])
			{
				Blocks[i].move(0, time[i] * dt);
			}
		}
	}
	for (size_t i = 0; i < entities; i++)
	{
		if (entityDraw[i])
		{
			entity[i].setTextureRect(sf::IntRect(source[i].x * textureRect[i], source[i].y * textureRect[i], textureRect[i], textureRect[i]));
			C_Player_elapsed[i] = C_Player_clock[i].getElapsedTime();
			if (C_Player_elapsed[i].asMilliseconds() >= animationtime[i])
			{
				source[i].x++;
				C_Player_clock[i].restart();
				if (source[i].x * textureRect[i] >= entitytexture[i].getSize().x)
					source[i].x = 0;
			}
			if (entity[i].getPosition().x <= EPointA_X[i])
			{
				EDirectionX[i] = false;
			}
			if (entity[i].getPosition().x + entity[i].getLocalBounds().width >= EPointB_X[i])
			{
				EDirectionX[i] = true;
			}
			if (EDirectionX[i] && EPointA_X[i] != EPointB_X[i])
			{
				entity[i].move(-Etime[i] * dt, 0);
				source[i].y = Walk_Left;
			}
			else if (EPointA_X[i] != EPointB_X[i])
			{
				entity[i].move(Etime[i] * dt, 0);
				source[i].y = Walk_Right;
			}
			if (entity[i].getPosition().y + entity[i].getLocalBounds().height <= EPointB_Y[i])
			{
				EDirectionY[i] = false;
			}
			if (entity[i].getPosition().y + entity[i].getLocalBounds().height >= EPointA_Y[i])
			{
				EDirectionY[i] = true;
			}
			if (EDirectionY[i] && EPointA_Y[i] != EPointB_Y[i])
			{
				entity[i].move(0, -Etime[i] * dt);
			}
			else if (EPointA_Y[i] != EPointB_Y[i])
			{
				entity[i].move(0, Etime[i] * dt);
			}
		}
	}
}
C_LoadMaps::C_LoadMaps()
{
	// Folder Where  to look for files
	std::string path = "levels";

	// Search all files from folder Files
	int i = 0;
	for (auto & p : fs::directory_iterator(path))
	{
		std::stringstream ss;
		// std::cout << "P: " << p << std::endl;
		ss << p;
		File[i] = ss.str();
		std::cout << "File: " << File[i] << std::endl;
		i++;
	}
	for (size_t j = 0; j < 1000; j++)
	{
		std::ifstream Reader(File[j]);
		if (Reader.is_open())
		{
			while (!Reader.eof())
			{
				Reader >> command;
				if (command == "path:")
				{
					Reader >> filepath;
					MapsPath[j] = filepath;
					std::cout << "" << MapsPath[j] << std::endl;
				}
				if (command == "title:")
				{
					Reader >> title;
					MapsTitle[j] = title;
					std::cout << "" << MapsTitle[j] << std::endl;
					//window.setTitle("Cyper Claus | " + title);
				}
			}
			levels++;
		}
		else
		{
			std::cout << "break &  levels: " << levels << std::endl;
			break;
		}
	}
}