#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "C_FPS.h"
#include "C_Player.h"
#include "C_LoadMaps.h"
#include "C_Button.h"
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
C_Player player;
C_FPS FPS;
C_LoadMaps LoadMaps;
C_Button Play;
C_Button HighScore;
C_Button Options;
C_Button Exit;
C_Button Credits;
C_Button VSyncB;
C_Button MusicVolumeUp;
C_Button MusicVolumeDown;
C_Button SoundVolumeUp;
C_Button SoundVolumeDown;
C_Button fullscreenB;
sf::RectangleShape MusicBlocks[10];
sf::RectangleShape SoundBlocks[10];
sf::Vector2i pixelPos;
sf::Vector2f worldPos;
int levelcount = 0, score, totalscore = 0, lifepoint, musicvolume=100, soundvolume=100;
bool keys, keys2, keys3, key4, key5, focus = true, fullscreen = false, VSync = false, mainmenu = false, test = true, move, life, fps;
bool highscore, options, edithighscore, scorescreen, credits;
std::string nameEvent;
void Load(sf::RenderWindow &window)
{
	LoadMaps.Load(levelcount, window);
	player.Load(LoadMaps.playerTexture, LoadMaps.Px, LoadMaps.Py);
}
void loadmainmenu()
{
	Play.setSize(70, 35);
	Play.setPosition(1280, 300);
	Play.setOutlineThickness(2);
	Play.setBaseFillColor(150, 0, 0);
	Play.setString(" Play");
	Play.setTextSize(26);

	HighScore.setSize(145, 35);
	HighScore.setPosition(1242, 350);
	HighScore.setOutlineThickness(2);
	HighScore.setBaseFillColor(150, 0, 0);
	HighScore.setString("High Scores");
	HighScore.setTextSize(26);

	Options.setSize(100, 35);
	Options.setPosition(1265, 400);
	Options.setOutlineThickness(2);
	Options.setBaseFillColor(150, 0, 0);
	Options.setString("Options");
	Options.setTextSize(26);

	Exit.setSize(70, 35);
	Exit.setPosition(1280, 450);
	Exit.setOutlineThickness(2);
	Exit.setBaseFillColor(150, 0, 0);
	Exit.setString(" Exit");
	Exit.setTextSize(26);

	Credits.setSize(55, 25);
	Credits.setPosition(1287, 500);
	Credits.setOutlineThickness(2);
	Credits.setBaseFillColor(150, 0, 0);
	Credits.setString("Credits");
	Credits.setTextSize(16);

	VSyncB.setSize(35, 20);
	VSyncB.setPosition(1480, 450);
	VSyncB.setOutlineThickness(2);
	VSyncB.setBaseFillColor(150, 0, 0);
	VSyncB.setString("OFF");
	VSyncB.setTextSize(16);

	fullscreenB.setSize(35, 20);
	fullscreenB.setPosition(1680, 450);
	fullscreenB.setOutlineThickness(2);
	fullscreenB.setBaseFillColor(150, 0, 0);
	fullscreenB.setString("OFF");
	fullscreenB.setTextSize(16);

	MusicVolumeUp.setSize(10, 20);
	MusicVolumeUp.setPosition(1560, 370);
	MusicVolumeUp.setOutlineThickness(2);
	MusicVolumeUp.setBaseFillColor(150, 0, 0);
	MusicVolumeUp.setString(">");
	MusicVolumeUp.setTextSize(16);

	MusicVolumeDown.setSize(10, 20);
	MusicVolumeDown.setPosition(1445, 370);
	MusicVolumeDown.setOutlineThickness(2);
	MusicVolumeDown.setBaseFillColor(150, 0, 0);
	MusicVolumeDown.setString("<");
	MusicVolumeDown.setTextSize(16);

	SoundVolumeUp.setSize(10, 20);
	SoundVolumeUp.setPosition(1710, 370);
	SoundVolumeUp.setOutlineThickness(2);
	SoundVolumeUp.setBaseFillColor(150, 0, 0);
	SoundVolumeUp.setString(">");
	SoundVolumeUp.setTextSize(16);

	SoundVolumeDown.setSize(10, 20);
	SoundVolumeDown.setPosition(1595, 370);
	SoundVolumeDown.setOutlineThickness(2);
	SoundVolumeDown.setBaseFillColor(150, 0, 0);
	SoundVolumeDown.setString("<");
	SoundVolumeDown.setTextSize(16);

	for (size_t i = 0; i < 10; i++)
	{
		MusicBlocks[i].setSize(sf::Vector2f(5, 20));
		MusicBlocks[i].setOutlineThickness(2);
		MusicBlocks[i].setFillColor(sf::Color(254, 210, 21));
		MusicBlocks[i].setOutlineColor(sf::Color(224, 185, 19));

		SoundBlocks[i].setSize(sf::Vector2f(5, 20));
		SoundBlocks[i].setOutlineThickness(2);
		SoundBlocks[i].setFillColor(sf::Color(254, 210, 21));
		SoundBlocks[i].setOutlineColor(sf::Color(224, 185, 19));
	}
}
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Santa Claus: alpha | ", sf::Style::Default, settings);
	sf::View view2(sf::Vector2f(350, 300), sf::Vector2f(800, 600));
	std::ifstream Reader("Options.txt");
	if (Reader.is_open())
	{
		Reader >> musicvolume;
		Reader >> soundvolume;
		Reader >> VSync;
		Reader >> fullscreen;
	}
	Reader.close();

	sf::Clock clock;
	sf::Time elapsedtime;
	sf::Font font;
	sf::Font font2;
	sf::Text T_Score;
	sf::Text text;
	sf::Text textscore;
	sf::Text textname;
	sf::Text Total_Score;
	sf::Text LifePoint;
	sf::Text THighScore;
	sf::Text OptionsText;
	sf::Text SOptionsText[4];
	sf::Text THighScores[6];
	sf::Text NameHighScores[6];
	sf::Text ScoreHighScores[6];
	sf::Text CreditsText[10];

	sf::Sound sound;
	sf::Sound soundcontinued;
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer2;
	sf::RectangleShape orange;
	if (!buffer.loadFromFile("Resources/ToBeContinued.ogg")) {
		if (!buffer.loadFromFile("Resources/Death.ogg")) {
		}
	}

	sound.setBuffer(buffer);
	if (!buffer2.loadFromFile("Resources/ToBeContinued.ogg")) {
		std::cout << "Error" << std::endl;
	}
	//soundcontinued.setBuffer(buffer2);

	if (!font.loadFromFile("Resources/ITCBLKAD.TTF"))
	{
	}
	if (!font2.loadFromFile("Resources/arial.TTF"))
	{
	}

	sf::Sprite bar;
	sf::Sprite banner;
	sf::Sprite banner1;
	sf::Sprite continued;
	sf::Texture continued_texture;
	sf::Sprite Highscore;
	sf::Sprite SOptions;
	sf::Texture Options_texture;
	sf::Texture Highscore_texture;
	sf::Texture bar_texture;
	sf::Texture banner_texture;
	sf::Texture banner1_texture;
	if (!bar_texture.loadFromFile("Resources/banner.png"))
	{
	}
	if (!banner_texture.loadFromFile("Resources/banner.png"))
	{
	}
	if (!banner1_texture.loadFromFile("Resources/banner1.png"))
	{
	}
	if (!continued_texture.loadFromFile("Resources/tobecontinued.png"))
	{
	}
	if (!Highscore_texture.loadFromFile("Resources/highscore.png"))
	{
	}
	if (!Options_texture.loadFromFile("Resources/options.png"))
	{
	}
	bar.setTexture(bar_texture);
	bar.setScale(1.5, 1.5);

	banner.setTexture(banner_texture);
	banner.setScale(1.5, 1.5);
	banner1.setTexture(banner1_texture);
	banner1.setScale(1.5, 1.5);

	continued.setTexture(continued_texture);
	Highscore.setTexture(Highscore_texture);
	Highscore.setScale(1.5, 1.5);
	SOptions.setTexture(Options_texture);
	SOptions.setScale(1.5, 1.5);

	T_Score.setFont(font);
	T_Score.setCharacterSize(30);
	T_Score.setOutlineThickness(1);
	T_Score.setOutlineColor(sf::Color::Black);
	Total_Score.setFont(font);
	Total_Score.setCharacterSize(30);
	Total_Score.setOutlineThickness(1);
	Total_Score.setOutlineColor(sf::Color::Black);
	LifePoint.setFont(font);
	LifePoint.setCharacterSize(30);
	LifePoint.setOutlineThickness(1);
	LifePoint.setOutlineColor(sf::Color::Black);

	THighScore.setFont(font);
	THighScore.setCharacterSize(28);
	THighScore.setOutlineThickness(1);
	THighScore.setOutlineColor(sf::Color::Black);
	THighScore.setString("High Scores");

	text.setFont(font);
	text.setCharacterSize(28);
	text.setOutlineThickness(1);
	textscore.setOutlineColor(sf::Color::Black);
	textscore.setFont(font);
	textscore.setCharacterSize(26);
	textscore.setOutlineThickness(1);
	textscore.setOutlineColor(sf::Color::Black);
	textscore.setString("Score:");
	textname.setFont(font);
	textname.setCharacterSize(26);
	textname.setOutlineThickness(1);
	textname.setOutlineColor(sf::Color::Black);
	textname.setString("Name:");

	OptionsText.setFont(font);
	OptionsText.setCharacterSize(26);
	OptionsText.setOutlineThickness(1);
	OptionsText.setOutlineColor(sf::Color::Black);
	OptionsText.setString("Options");

	for (size_t i = 0; i < 4; i++)
	{
		SOptionsText[i].setFont(font);
		SOptionsText[i].setCharacterSize(24);
		SOptionsText[i].setOutlineThickness(1);
		SOptionsText[i].setOutlineColor(sf::Color::Black);
	}
	SOptionsText[0].setString("Music Volume");
	SOptionsText[1].setString("Sound Volume");
	SOptionsText[2].setString("VSync");
	SOptionsText[3].setString("Fullscreen");
	for (size_t i = 1; i < 6; i++)
	{
		std::stringstream s;
		s << i << ".";
		THighScores[i].setFont(font);
		THighScores[i].setCharacterSize(30);
		THighScores[i].setOutlineThickness(1);
		THighScores[i].setOutlineColor(sf::Color::Black);
		THighScores[i].setString(s.str());
	}
	for (size_t i = 0; i < 10; i++)
	{
		CreditsText[i].setFont(font2);
		CreditsText[i].setCharacterSize(16);
		CreditsText[i].setOutlineThickness(1);
		CreditsText[i].setOutlineColor(sf::Color::Black);
	}
	CreditsText[0].setString("Credits");
	CreditsText[1].setString("Programmer: \nLeevi Koskinen");
	CreditsText[2].setString("Level Designer: \nMikael Ronkainen\nLeevi Koskinen");
	CreditsText[3].setString("Graphics Designer: \nLeevi Koskinen\nMikael Ronkainen");
	CreditsText[4].setString("Music: \nKevin MacLeod (incompetech.com)\nLicensed under Creative Commons: \nBy Attribution 3.0 License http://creativecommons.org/licenses/by/3.0/");
	CreditsText[5].setString("Songs: \nDeck the Halls B, Jingle Bells, Jingle Bells Calm, We Wish You Merry Christmas");
	CreditsText[6].setString("Santa Claus");
	CreditsText[6].setFont(font);
	CreditsText[6].setCharacterSize(55);
	CreditsText[6].setPosition(1200, 200);
	CreditsText[4].setOutlineThickness(2);
	CreditsText[5].setOutlineThickness(2);
	CreditsText[6].setOutlineThickness(2);
	loadmainmenu();
	// T_Score.setCharacterSize(10);

	lifepoint = 2;
	LoadMaps.Load(0, window);
	player.Load(LoadMaps.playerTexture, LoadMaps.Px, LoadMaps.Py);

	LoadMaps.music.setVolume(musicvolume);
	sound.setVolume(soundvolume);
	LoadMaps.sound.setVolume(soundvolume);
	LoadMaps.sound2.setVolume(soundvolume);
	player.sound2.setVolume(soundvolume);
	if (fullscreen)
	{
		window.create(sf::VideoMode::getDesktopMode(), "Santa Claus: alpha | " + LoadMaps.MapsTitle[levelcount], sf::Style::Fullscreen, settings);
	}
	// run the program as long as the window is open
	while (window.isOpen())
	{
		if (levelcount == 4)
		{
			player.Roof = true;
		}
		else
		{
			player.Roof = false;
		}
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::LostFocus)
				focus = false;
			if (event.type == sf::Event::GainedFocus)
				focus = true;
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F11 && !fps)
				{
					fps = true;
				}
				else if (event.key.code == sf::Keyboard::F11 && fps)
				{
					fps = false;
				}
				if (event.key.code == sf::Keyboard::Escape && !options)
				{
					options = true;
				}
				else if (event.key.code == sf::Keyboard::Escape && options)
				{
					options = false;
				}
			}
			// catch the resize events
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			if (event.type == sf::Event::TextEntered && scorescreen && nameEvent.size() < 5)
			{
				if (event.text.unicode >= 33)
				{
					nameEvent += (char)event.text.unicode;
				}
			}
			if (event.key.code == sf::Keyboard::BackSpace && scorescreen)
			{
				if (!key4) {
					nameEvent = nameEvent.substr(0, nameEvent.size() - 1);
					key4 = true;

				}
				else {
					key4 = false;
				}
			}
			if (event.key.code == sf::Keyboard::Return && scorescreen)
			{
				edithighscore = true;
				scorescreen = false;
			}
			
			
		}
		if (VSync)
		{
			window.setVerticalSyncEnabled(true);
			VSyncB.setString(" ON");
			VSyncB.setPosition(1495, 455);
			VSyncB.setPosition(window.getView().getCenter().x + 115, window.getView().getCenter().y);
			VSyncB.setOutlineThickness(2);
			VSyncB.setBaseFillColor(0, 150, 0);
		}
		else
		{
			VSyncB.setPosition(1495, 455);
			VSyncB.setPosition(window.getView().getCenter().x + 115, window.getView().getCenter().y);
			VSyncB.setOutlineThickness(2);
			VSyncB.setBaseFillColor(150, 0, 0);
			window.setVerticalSyncEnabled(false);
			VSyncB.setString("OFF");
		}
		if (fullscreen)
		{
			fullscreen = true;
			fullscreenB.setString(" ON");
			fullscreenB.setPosition(1635, 455);
			fullscreenB.setPosition(window.getView().getCenter().x + 255, window.getView().getCenter().y);
			fullscreenB.setOutlineThickness(2);
			fullscreenB.setBaseFillColor(0, 150, 0);
		}
		else
		{
			fullscreen = false;
			fullscreenB.setPosition(1635, 455);
			fullscreenB.setPosition(window.getView().getCenter().x + 255, window.getView().getCenter().y);
			fullscreenB.setOutlineThickness(2);
			fullscreenB.setBaseFillColor(150, 0, 0);
			fullscreenB.setString("OFF");
		}
		if (LoadMaps.levels <= levelcount)
		{
			scorescreen = true;
			lifepoint = 2;
			LoadMaps.Load(0, window);
			LoadMaps.clock.restart();
			player.Load(LoadMaps.playerTexture, LoadMaps.Px, LoadMaps.Py);
			loadmainmenu();
			levelcount = 0;
		}
		if (levelcount > 0 && !scorescreen)
		{
			mainmenu = false;
		}
		else
		{
			mainmenu = true;
			player.FaceDir = player.Left;
			Play.update(worldPos, event);
			HighScore.update(worldPos, event);
			Options.update(worldPos, event);
			Exit.update(worldPos, event);
			Credits.update(worldPos, event);
			if (Play.click)
			{
				options = false;
				highscore = false;
				score = 0;
				levelcount++;
				Load(window);
			}
			if (HighScore.click)
			{
				credits = false;
				options = false;
				if (!highscore)
				{
					Highscore.setPosition(window.getView().getCenter().x + 100, window.getView().getCenter().y - 190);
					highscore = true;
					std::ifstream scoreReader("highscore.txt");
					if (scoreReader.is_open()) {
						std::string line;
						for (size_t i = 1; i < 6; i++)
						{
							scoreReader >> line;
							std::stringstream ss;
							ss << line;
							ScoreHighScores[i].setFont(font);
							ScoreHighScores[i].setCharacterSize(30);
							ScoreHighScores[i].setOutlineThickness(1);
							ScoreHighScores[i].setOutlineColor(sf::Color::Black);
							ScoreHighScores[i].setString(ss.str());

							scoreReader >> line;
							std::stringstream s;
							s << line;
							NameHighScores[i].setFont(font);
							NameHighScores[i].setCharacterSize(24);
							NameHighScores[i].setOutlineThickness(1);
							NameHighScores[i].setOutlineColor(sf::Color::Black);
							NameHighScores[i].setString(s.str());
						}
						scoreReader.close();
					}
				}
				else
				{
					highscore = false;
				}
			}
			if (edithighscore)
			{
				int value[6];
				std::string line[6];
				std::string line2[6];
				std::string line3[6];
				Highscore.setPosition(window.getView().getCenter().x + 100, window.getView().getCenter().y - 190);
				std::ifstream scoreReader("highscore.txt");
				if (scoreReader.is_open()) {
					for (size_t i = 1; i < 6; i++)
					{
						scoreReader >> line[i];
						value[i] = atoi(line[i].c_str());
						std::cout << value[i] << " ? " << std::endl;
						std::stringstream ss;
						ss << line;
						ScoreHighScores[i].setFont(font);
						ScoreHighScores[i].setCharacterSize(30);
						ScoreHighScores[i].setOutlineThickness(1);
						ScoreHighScores[i].setOutlineColor(sf::Color::Black);
						ScoreHighScores[i].setString(ss.str());

						scoreReader >> line2[i];
						line3[i] = line2[i];
						std::stringstream s;
						s << " " << line2[i];
						NameHighScores[i].setFont(font);
						NameHighScores[i].setCharacterSize(24);
						NameHighScores[i].setOutlineThickness(1);
						NameHighScores[i].setOutlineColor(sf::Color::Black);
						NameHighScores[i].setString(s.str());

					}
					std::ofstream scoreWriter("highscore.txt");
					if (scoreWriter.is_open()) {
						for (size_t i = 1; i < 6; i++)
						{
							std::cout << value[i] << " " << i << "  " << value[i - 1] << std::endl;
							if (value[i - 1] > totalscore && value[i] <= totalscore)
							{
								std::cout << value[i] << " " << i << " " << value[i] << std::endl;
								std::stringstream s;
								s << totalscore;
								line[i] = s.str();
								std::stringstream ss;
								ss << nameEvent;
								line2[i] = ss.str();
								if (i == 2)
								{
									value[5] = value[4];
									value[4] = value[3];
									value[3] = value[2];
									std::stringstream sss;
									sss << value[3];
									line[3] = sss.str();
									std::stringstream ssss;
									ssss << value[4];
									line[4] = ssss.str();
									std::stringstream sssss;
									sssss << value[5];
									line[5] = sssss.str();

									line3[5] = line3[4];
									line3[4] = line3[3];
									line3[3] = line3[2];
									std::stringstream ass;
									ass << line3[3];
									line2[3] = ass.str();
									std::stringstream asss;
									asss << line3[4];
									line2[4] = asss.str();
									std::stringstream assss;
									assss << line3[5];
									line2[5] = assss.str();
								}
								if (i == 3)
								{
									value[5] = value[4];
									value[4] = value[3];
									std::stringstream ssss;
									ssss << value[4];
									line[4] = ssss.str();
									std::stringstream sssss;
									sssss << value[5];
									line[5] = sssss.str();

									line3[5] = line3[4];
									line3[4] = line3[3];

									std::stringstream asss;
									asss << line3[4];
									line2[4] = asss.str();
									std::stringstream assss;
									assss << line3[5];
									line2[5] = assss.str();
								}
								if (i == 4)
								{
									value[5] = value[4];
									std::stringstream sssss;
									sssss << value[5];
									line[5] = sssss.str();

									line3[5] = line3[4];
									std::stringstream assss;
									assss << line3[5];
									line2[5] = assss.str();
								}
							}
							if (value[1] < totalscore)
							{
								//std::cout << value[i] << " 33 " << value[i] << std::endl;
								value[5] = value[4];
								value[4] = value[3];
								value[3] = value[2];
								value[2] = value[1];
								value[1] = totalscore;
								std::stringstream s;
								s << value[1];
								line[1] = s.str();
								std::stringstream ss;
								ss << value[2];
								line[2] = ss.str();
								std::stringstream sss;
								sss << value[3];
								line[3] = sss.str();
								std::stringstream ssss;
								ssss << value[4];
								line[4] = ssss.str();
								std::stringstream sssss;
								sssss << value[5];
								line[5] = sssss.str();

								line3[5] = line3[4];
								line3[4] = line3[3];
								line3[3] = line3[2];
								line3[2] = line3[1];
								line3[1] = nameEvent;
								std::stringstream a;
								a << line3[1];
								line2[1] = a.str();
								std::stringstream as;
								as << line3[2];
								line2[2] = as.str();
								std::stringstream ass;
								ass << line3[3];
								line2[3] = ass.str();
								std::stringstream asss;
								asss << line3[4];
								line2[4] = asss.str();
								std::stringstream assss;
								assss << line3[5];
								line2[5] = assss.str();
							}
							scoreWriter << line[i];
							scoreWriter << " ";
							scoreWriter << line2[i];
							scoreWriter << "\n";
						}
					}
					scoreReader.close();
					scoreWriter.close();
					totalscore = 0;
					edithighscore = false;
				}
			}
			if (Exit.click)
			{
				window.close();
			}
			if (Credits.click)
			{
				highscore = false;
				options = false;
				if (!credits)
				{
					credits = true;
				}
				else
				{
					credits = false;
				}
			}
		}
		if (Options.click)
		{
			highscore = false;
			credits = false;
			if (!options)
			{
				options = true;
			}
			else
			{
				options = false;
			}
		}
		if (focus)
		{
			if (!mainmenu && !edithighscore && !scorescreen && !options)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					player.right = true;
				else
					player.right = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					player.left = true;
				else
					player.left = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					player.jump = true;
				}
				else
					player.jump = false;
				
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					player.idle = true;
				else
					player.idle = false;
			}
			else
			{
				player.idle = true;
				player.jump = false;
				player.left = false;
				player.right = false;
			}
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
				if (!keys)
				{
					loadmainmenu();
					score = 0;
					levelcount++;
					Load(window);
					keys = true;
					options = false;
					std::cout << "  " << levelcount << std::endl;
				}

			}
			else {
				keys = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
				if (!keys2)
				{
					loadmainmenu();
					score = 0;
					levelcount--;
					Load(window);
					keys2 = true;
					options = false;
					std::cout << "" << levelcount << std::endl;
				}

			}
			else {
				keys2 = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home)) {
				if (!keys3)
				{
					Load(window);
					keys3 = true;
					score = 0;
					std::cout << "level:  " << levelcount << std::endl;
				}

			}
			else {
				keys3 = false;
			}*/
		}
		if (player.Death){
			player.P_Sprite.setTextureRect(sf::IntRect(player.source.x * 25, player.source.y * 25, 25, 25));
			player.C_Player_elapsed = player.C_Player_clock.getElapsedTime();
			if (player.C_Player_elapsed.asMilliseconds() >= 150)
			{
				player.source.y = player.Death_Right;
				if (player.source.x * 25 <= player.P_Texture.getSize().x)
					player.source.x++;

				player.C_Player_clock.restart();
			}
			if (test)
			{
				sound.play();
				soundcontinued.play();

				orange.setSize(sf::Vector2f(window.getView().getSize().x, window.getView().getSize().y));
				orange.setPosition(window.getView().getCenter().x - window.getView().getSize().x/2, window.getView().getCenter().y - window.getView().getSize().y / 2);
				orange.setFillColor(sf::Color(255, 176, 0, 150));
				continued.setPosition(window.getView().getCenter().x , window.getView().getCenter().y + window.getView().getSize().y / 3);
				if (player.source.x > 0)
				{
					player.source.x = 0;
				}
				test = false;
				move = false;
			}
			if (sound.getStatus() == sound.Stopped)
			{
				Load(window);
				player.goal = false;
				player.Death = false;
				test = true;
				score = 0;
				move = true;
				player.clock.restart();
				LoadMaps.clock.restart();
				lifepoint--;
			}
			if (lifepoint < 0)
			{
				lifepoint = 2;
				LoadMaps.Load(0, window);
				LoadMaps.clock.restart();
				player.Load(LoadMaps.playerTexture, LoadMaps.Px, LoadMaps.Py);
				levelcount = 0;
				scorescreen = true;
				nameEvent = "";
			}
		}
		
		if (player.goal)
		{
			elapsedtime = clock.getElapsedTime();
			if (elapsedtime.asMilliseconds() >= 150) {
				LoadMaps.sound2.play();
				if (score == LoadMaps.Maxscore)
				{
					life = true;
				}
				score--;
				totalscore += 10;
				clock.restart();
				move = false;
			}
			if (score <= 0)
			{
				if (life)
				{
					lifepoint++;
				}
				score = 0;
				levelcount = player.levelcount;
				player.goal = false;
				life = false;
				player.clock.restart();
				Load(window);
			}
		}
		else if (!player.Death)
		{
			move = true;
		}
		for (size_t i = 0; i < LoadMaps.items; i++)
		{
			if (LoadMaps.itemDraw[i])
			{
				if (LoadMaps.goal[i] == i)
				{
					player.colisionSprite(LoadMaps.item[LoadMaps.goal[i]], "goal", LoadMaps.levelcount[i]);
				}
				else if (LoadMaps.score[i] == i)
				{
					player.colisionSprite(LoadMaps.item[LoadMaps.score[i]], "score", levelcount);
					if (player.score)
					{
						score++;

						LoadMaps.sound.play();
						LoadMaps.item[i].setPosition(-10000, -10000);
						player.score = false;
					}
				}
				else if (LoadMaps.death[i] == i)
				{
					player.colisionSprite(LoadMaps.item[LoadMaps.death[i]], "death", levelcount);
				}
			}
		}
		for (size_t i = 0; i < LoadMaps.entities; i++)
		{
			if (LoadMaps.entityDraw[i])
			{
				if (LoadMaps.Edeath[i] == i)
				{
					player.colisionSprite(LoadMaps.entity[LoadMaps.Edeath[i]], "death", levelcount);
				}
			}
		}
		for (size_t i = 0; i < LoadMaps.groundBlocks; i++)
		{
			player.colisionRectangle(LoadMaps.Blocks[i], LoadMaps.groundBlocks);
		}
		if (move && !options)
		{
			player.update(window);
			player.move();
			LoadMaps.update();
			LoadMaps.clock.restart();
		}
		std::stringstream ss;
		ss << " " << score << "/" << LoadMaps.Maxscore;
		std::stringstream sss;
		sss << totalscore;
		std::stringstream ssss;
		ssss << "x " << lifepoint;

		T_Score.setString(ss.str());
		Total_Score.setString(sss.str());
		LifePoint.setString(ssss.str());
		// get the current mouse position in the window
		pixelPos = sf::Mouse::getPosition(window);
		// convert it to world coordinates
		worldPos = window.mapPixelToCoords(pixelPos);
		if (player.P_Sprite.getPosition().y + 24 > 580)
		{
			view2.setCenter(player.P_Sprite.getPosition().x, 480 - 24);
		}
		else if (player.P_Sprite.getPosition().y + 24 > 480)
		{
			view2.setCenter(player.P_Sprite.getPosition().x, 480 - 24);
		}
		else
		{
			view2.setCenter(player.P_Sprite.getPosition().x, player.P_Sprite.getPosition().y);
		}
		if (player.P_Sprite.getPosition().x < view2.getCenter().x - view2.getSize().x / 2)
		{
			player.Death = true;
		}
		if (player.P_Sprite.getPosition().x > view2.getCenter().x + view2.getSize().x / 2)
		{
			player.Death = true;
		}
		if (player.P_Sprite.getPosition().y > view2.getCenter().y + view2.getSize().y / 2)
		{
			player.Death = true;
		}
		if (player.P_Sprite.getPosition().y < view2.getCenter().y - view2.getSize().y / 2)
		{
			player.Death = true;
		}

		window.setView(view2);

		FPS.Logic_Counter();
		FPS.Counter(window); 
		Total_Score.setPosition(window.getView().getCenter().x - (250 + Total_Score.getGlobalBounds().width), window.getView().getCenter().y - 250);
		T_Score.setPosition(window.getView().getCenter().x - (315 + T_Score.getGlobalBounds().width), window.getView().getCenter().y - 280);
		LifePoint.setPosition(window.getView().getCenter().x - (240 + LifePoint.getGlobalBounds().width), window.getView().getCenter().y - 280);
		bar.setPosition(window.getView().getCenter().x - 400, window.getView().getCenter().y - 300);

		window.clear(sf::Color(LoadMaps.B_R, LoadMaps.B_G, LoadMaps.B_B));
		LoadMaps.draw(window);
		if (!scorescreen)
		{
			if (credits)
			{
				window.draw(SOptions);
				SOptions.setPosition(window.getView().getCenter().x + 50, window.getView().getCenter().y - 190);
				CreditsText[0].setPosition(window.getView().getCenter().x + 180, window.getView().getCenter().y - 162);
				CreditsText[1].setPosition(window.getView().getCenter().x + 60, window.getView().getCenter().y - 120);
				CreditsText[2].setPosition(window.getView().getCenter().x + 195, window.getView().getCenter().y - 120);
				CreditsText[3].setPosition(window.getView().getCenter().x + 60, window.getView().getCenter().y - 60);
				CreditsText[4].setPosition(window.getView().getCenter().x - 390, window.getView().getCenter().y + 130);
				CreditsText[5].setPosition(window.getView().getCenter().x - 390, window.getView().getCenter().y + 220);
				for (size_t i = 0; i < 10; i++)
				{
					window.draw(CreditsText[i]);
				}
			}
			window.draw(player.P_Sprite);
			if (!mainmenu)
			{
				window.draw(bar);
				window.draw(Total_Score);
				window.draw(T_Score);
				window.draw(LifePoint);
			}
			else
			{
				window.draw(CreditsText[6]);
				player.update(window);
				Play.draw(window);
				HighScore.draw(window);
				Options.draw(window);
				Exit.draw(window);
				Credits.draw(window);
			}
			if (options)
			{
				player.clock.restart();
				LoadMaps.clock.restart();
				window.draw(SOptions);
				window.draw(OptionsText);
				SOptions.setPosition(window.getView().getCenter().x + 50, window.getView().getCenter().y - 190);
				OptionsText.setPosition(window.getView().getCenter().x + 168, window.getView().getCenter().y - 171);
				
				for (size_t i = 0; i < 4; i++)
				{
					window.draw(SOptionsText[i]);
					SOptionsText[0].setPosition(window.getView().getCenter().x + 60, window.getView().getCenter().y - 120);
					SOptionsText[1].setPosition(window.getView().getCenter().x + 210, window.getView().getCenter().y - 120);
					SOptionsText[2].setPosition(window.getView().getCenter().x + 100, window.getView().getCenter().y - 40);
					SOptionsText[3].setPosition(window.getView().getCenter().x + 230, window.getView().getCenter().y - 40);
				}
				for (size_t i = 0; i < 10; i++)
				{
					window.draw(MusicBlocks[i]);
					MusicBlocks[i].setPosition(window.getView().getCenter().x + 80 + i * 10, window.getView().getCenter().y - 86);
					if (i < (musicvolume / 10))
					{
						MusicBlocks[i].setFillColor(sf::Color(230, 198, 33));
						MusicBlocks[i].setOutlineColor(sf::Color(204, 176, 29));
					}
					else
					{
						MusicBlocks[i].setFillColor(sf::Color(198, 134, 0));
						MusicBlocks[i].setOutlineColor(sf::Color(142, 99, 0));
					}
					window.draw(SoundBlocks[i]);
					SoundBlocks[i].setPosition(window.getView().getCenter().x + 230 + i * 10, window.getView().getCenter().y - 86);
					if (i < (soundvolume / 10))
					{
						SoundBlocks[i].setFillColor(sf::Color(230, 198, 33));
						SoundBlocks[i].setOutlineColor(sf::Color(204, 176, 29));
					}
					else
					{
						SoundBlocks[i].setFillColor(sf::Color(198, 134, 0));
						SoundBlocks[i].setOutlineColor(sf::Color(142, 99, 0));
					}
				}
				MusicVolumeDown.setPosition(window.getView().getCenter().x + 65, window.getView().getCenter().y - 86);
				MusicVolumeUp.setPosition(window.getView().getCenter().x + 180, window.getView().getCenter().y - 86);
				SoundVolumeDown.setPosition(window.getView().getCenter().x + 215, window.getView().getCenter().y - 86);
				SoundVolumeUp.setPosition(window.getView().getCenter().x + 330, window.getView().getCenter().y - 86);

				VSyncB.update(worldPos, event);
				fullscreenB.update(worldPos, event);
				MusicVolumeUp.update(worldPos, event);
				MusicVolumeDown.update(worldPos, event);
				SoundVolumeUp.update(worldPos, event);
				SoundVolumeDown.update(worldPos, event);

				VSyncB.draw(window);
				MusicVolumeUp.draw(window);
				MusicVolumeDown.draw(window);
				SoundVolumeUp.draw(window);
				SoundVolumeDown.draw(window);
				fullscreenB.draw(window);
			
			}
			if (MusicVolumeUp.click)
			{
				if (musicvolume < 100)
				{
					musicvolume = musicvolume + 10;
					LoadMaps.music.setVolume(musicvolume);
				}
			}
			if (MusicVolumeDown.click)
			{
				if (!musicvolume <= 0)
				{
					musicvolume = musicvolume - 10;
					LoadMaps.music.setVolume(musicvolume);
				}
			}
			if (SoundVolumeUp.click)
			{
				if (soundvolume < 100)
				{
					soundvolume = soundvolume + 10;
					LoadMaps.sound.setVolume(soundvolume);
					LoadMaps.sound2.setVolume(soundvolume);
					sound.setVolume(soundvolume);
					soundcontinued.setVolume(soundvolume);
					player.sound2.setVolume(soundvolume);
				}
				player.sound2.play();
			}
			if (SoundVolumeDown.click)
			{
				if (!soundvolume <= 0)
				{
					soundvolume = soundvolume - 10;
					sound.setVolume(soundvolume);
					LoadMaps.sound.setVolume(soundvolume);
					LoadMaps.sound2.setVolume(soundvolume);
					player.sound2.setVolume(soundvolume);
				}
				player.sound2.play();
			}
			if (fullscreenB.click && !fullscreen)
			{
				fullscreen = true;
				window.create(sf::VideoMode::getDesktopMode(), "Santa Claus: alpha | " + LoadMaps.MapsTitle[levelcount], sf::Style::Fullscreen, settings);
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			else if (fullscreenB.click && fullscreen)
			{
				fullscreen = false;
				window.create(sf::VideoMode(800, 600), "Santa Claus: alpha | " + LoadMaps.MapsTitle[levelcount], sf::Style::Default, settings);
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
			if (VSyncB.click && !VSync)
			{
				VSync = true;
			}
			else if (VSyncB.click && VSync)
			{
				VSync = false;
			}
			
			if (highscore)
			{
				window.draw(Highscore);
				THighScore.setPosition(window.getView().getCenter().x + 165, window.getView().getCenter().y - 168);
				window.draw(THighScore);
				for (size_t i = 1; i < 6; i++)
				{
					window.draw(THighScores[i]);
					THighScores[i].setPosition(window.getView().getCenter().x + 120, window.getView().getCenter().y - 165 + i * 40);
					window.draw(NameHighScores[i]);
					NameHighScores[i].setPosition(window.getView().getCenter().x + 150, window.getView().getCenter().y - 155 + i * 40);
					window.draw(ScoreHighScores[i]);
					ScoreHighScores[i].setPosition(window.getView().getCenter().x + 250, window.getView().getCenter().y - 165 + i * 40);
				}
			}
			if (player.Death) {
				window.draw(orange);
				window.draw(continued);
				//orange.setPosition(window.getView().getCenter().x - window.getView().getSize().x / 2, window.getView().getCenter().y - window.getView().getSize().y / 2);
				//continued.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + window.getView().getSize().y / 3);
			}
		}
		else
		{
			std::stringstream tex;
			tex << nameEvent;
			text.setString(tex.str());
			text.setPosition(window.getView().getCenter().x - 50, window.getView().getCenter().y+3);
			banner1.setPosition(window.getView().getCenter().x - 145, window.getView().getCenter().y - 140);
			textname.setPosition(window.getView().getCenter().x - 55, window.getView().getCenter().y - 23);
			textscore.setPosition(window.getView().getCenter().x - 55, window.getView().getCenter().y - 125);
			window.draw(banner1);
			window.draw(text);
			window.draw(textname);
			window.draw(textscore);
			move = false;
			Total_Score.setPosition(window.getView().getCenter().x-50, window.getView().getCenter().y - 105);
			window.draw(Total_Score);
		}
		if (fps)
		{
			window.draw(FPS.T_FPS);
		}
		window.display();
	}

	std::ofstream writer("Options.txt");
	if (writer.is_open())
	{
		writer << musicvolume;
		writer << " ";
		writer << soundvolume;
		writer << " ";
		writer << VSync;
		writer << " ";
		writer << fullscreen;
	}
	return 0;
}