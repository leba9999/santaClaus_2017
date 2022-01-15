#include "C_Player.h"
#include "Collision.h"


void C_Player::Load(std::string Texture_Name, int x, int y)
{
	if (!P_Texture.loadFromFile(Texture_Name))
	{
		// error...
		error = "#1000";
	}
	P_Sprite.setTexture(P_Texture);
	P_Sprite.setPosition(x, y - 24);
	//P_Sprite.setScale(sf::Vector2f(2, 2));
	//P_Sprite.setRotation(-90);
	block = 0;
	if (!buffer2.loadFromFile("Resources/Jump.ogg")) {
		std::cout << "Error" << std::endl;
	}
	sound2.setBuffer(buffer2);
}

void C_Player::update(sf::RenderWindow &window)
{
	
	P_Sprite.setTextureRect(sf::IntRect(source.x * 25, source.y * 25, 25, 25));
	C_Player_elapsed = C_Player_clock.getElapsedTime();
	if (C_Player_elapsed.asMilliseconds() >= 50)
	{
		source.x++;
		C_Player_clock.restart();
		if (source.x * 25 >= P_Texture.getSize().x)
			source.x = 0;
	}
	if (FaceDir == Left && left && !up)
	{
		source.y = Walk_Left;
	}
	if (FaceDir == Right && Right && !up)
	{
		source.y = Walk_Right;
	}
	if (FaceDir == Left && up)
	{
		source.y = Jump_Left;
	}
	if (FaceDir == Right && up)
	{
		source.y = Jump_Right;
	}
	if (idle && FaceDir == Left)
	{
		source.y = Idle_Left;
	}
	if (idle && FaceDir == Right)
	{
		source.y = Idle_Right;
	}
	if (down && FaceDir == Left)
	{
		source.y = Fall_Left;
	}
	if (down && FaceDir == Right)
	{
		source.y = Fall_Right;
	}
	window.draw(P_Sprite);
}

void C_Player::move()
{
	C_Player_elapsed_2 = C_Player_clock_2.getElapsedTime();
	const float dt = clock.restart().asSeconds();
	dt2 = clock2.restart().asSeconds();
	//if (C_Player_elapsed_2.asMilliseconds() >= 10)
	//{
		if (down && FaceDir == Right)
		{
			
			if (Wall_R)
			{
				P_Sprite.move(0, 100 *dt);
			}
			else
			{
				P_Sprite.move(0, 100 * dt);
			}
		}
		if (down && FaceDir == Left)
		{
			if (Wall_L)
			{
				P_Sprite.move(0, 100 * dt);
			}
			else
			{
				P_Sprite.move(0, 100 * dt);
			}
		}
		if (up && FaceDir == Right)
		{
			if (Wall_R)
			{
				P_Sprite.move(0, -200 * dt);
			}
			else
			{
				P_Sprite.move(50*dt, -200 * dt);
			}
		}
		if (up && FaceDir == Left)
		{
			
			if (Wall_L)
			{
				P_Sprite.move(0, -200 * dt);
				
			}
			else
			{
				P_Sprite.move(-50*dt, -200 * dt);
			}
		}
		if (right && !Wall_R)
		{
			FaceDir = Right;
			P_Sprite.move(100 * dt, 0);
		}
		if (left && !Wall_L)
		{
			FaceDir = Left;
			P_Sprite.move(-100 * dt, 0);
		}
		//C_Player_clock_2.restart();
	//}
	if (!Ground && !up)
		down = true;
	else
		down = false;

	C_Player_elapsed_3 = C_Player_clock_3.getElapsedTime();
	if (C_Player_elapsed_3.asMilliseconds() <= 500 && jump2)
	{
		up = true;
	}
	else
	{
		up = false;
	}
	if (!jump)
	{
		up = false;
		jump2 = false;
	}
	soundtest = false;
	if (!jump2 && !douplejump && jump)
	{
		jump2 = true;
		douplejump = true;
		soundtest = true;
		sound2.play();
		C_Player_clock_3.restart();
	}
	if (jump && Ground)
	{
		douplejump = false;
		soundtest = true;
		jump2 = true;
		jump = false;
		C_Player_clock_3.restart();
	}
	if (soundtest && sound2.getStatus() == sound2.Stopped)
	{
		sound2.play();
		//std::cout << soundtest << " | " << sound2.getStatus() << std::endl;
	}
	if (Ground)
	{
		douplejump = false;
	}

	// std::cout << P_Sprite.getPosition().y + 24 << " | " << P_Sprite.getPosition().x << std::endl;
}

void C_Player::colisionRectangle(sf::RectangleShape rectangle, int blocks)
{
	
	if (block >= blocks)
	{
		block = 0;
		Ground = false;
		Wall_L = false;
		Wall_R = false;
	}
	if (P_Sprite.getPosition().y + 24 >= rectangle.getPosition().y && P_Sprite.getPosition().y + 24 <= rectangle.getPosition().y + 10 )
	{
		//std::cout << P_Sprite.getPosition().x << " | " << rectangle.getPosition().x + 10 << "  " << block << "  " << blocks << std::endl;
		if (P_Sprite.getPosition().x + 24 >= rectangle.getPosition().x + 1 && P_Sprite.getPosition().x <= rectangle.getPosition().x + rectangle.getSize().x - 1)
		{
			Ground = true;
			down = false;
		}
	}
	if (P_Sprite.getPosition().y >= rectangle.getPosition().y + rectangle.getGlobalBounds().height -10 && P_Sprite.getPosition().y <= rectangle.getPosition().y + rectangle.getGlobalBounds().height && Roof)
	{
		//std::cout << P_Sprite.getPosition().x << " | " << rectangle.getPosition().x + 10 << "  " << block << "  " << blocks << std::endl;
		if (P_Sprite.getPosition().x + 24 >= rectangle.getPosition().x + 1 && P_Sprite.getPosition().x <= rectangle.getPosition().x + rectangle.getSize().x - 1)
		{
			up = false;
		}
	}
	if (P_Sprite.getPosition().x + 25 >= rectangle.getPosition().x && P_Sprite.getPosition().x + 25 <= rectangle.getPosition().x + rectangle.getSize().x/3 && !Wall_R)
	{
		if (P_Sprite.getPosition().y + 25 >= rectangle.getPosition().y + 3 && P_Sprite.getPosition().y <= rectangle.getPosition().y + rectangle.getSize().y - 3)
		{
			Wall_R = true;
			//std::cout << Wall_L << " | " << Wall_R << " | " << Ground << "  " << Ground << std::endl;
		}
	}
	if (P_Sprite.getPosition().x <= rectangle.getPosition().x + rectangle.getSize().x  && P_Sprite.getPosition().x >= rectangle.getPosition().x + rectangle.getSize().x - rectangle.getSize().x / 3 && !Wall_L)
	{
		if (P_Sprite.getPosition().y + 25 >= rectangle.getPosition().y + 3 && P_Sprite.getPosition().y <= rectangle.getPosition().y + rectangle.getSize().y - 3)
		{
			Wall_L = true;
			//std::cout << Wall_L << " | " << Wall_R << " | " << Ground << "  " << Ground << std::endl;
		}
	}
	if (P_Sprite.getPosition().y + 25 >= rectangle.getPosition().y + 2 && P_Sprite.getPosition().y + 25 <= rectangle.getPosition().y + 20)
	{
		if (rectangle.getPosition().x < round(P_Sprite.getPosition().x + 25) && rectangle.getPosition().x + rectangle.getSize().x > round(P_Sprite.getPosition().x) && Ground)
		{
			P_Sprite.setPosition(P_Sprite.getPosition().x, rectangle.getPosition().y - 25);
		}
	}
	/*if (P_Sprite.getPosition().x + 25 >= rectangle.getPosition().x + 3 && P_Sprite.getPosition().x + 25 <= rectangle.getPosition().x + rectangle.getSize().x / 4 && Wall_R)
	{
		if (P_Sprite.getPosition().y + 25 >= rectangle.getPosition().y + 3 && P_Sprite.getPosition().y <= rectangle.getPosition().y + rectangle.getSize().y - 3)
		{
			P_Sprite.setPosition(rectangle.getPosition().x - 25, P_Sprite.getPosition().y);
		}
	}
	if (P_Sprite.getPosition().x <= rectangle.getPosition().x + rectangle.getSize().x - 3  && P_Sprite.getPosition().x >= rectangle.getPosition().x + rectangle.getSize().x - rectangle.getSize().x / 4 && Wall_L)
	{
		if (P_Sprite.getPosition().y + 25 >= rectangle.getPosition().y + 3 && P_Sprite.getPosition().y <= rectangle.getPosition().y + rectangle.getSize().y - 3)
		{
			P_Sprite.setPosition(rectangle.getPosition().x + rectangle.getSize().x, P_Sprite.getPosition().y);
		}
	}*/
	block++;
}

void C_Player::colisionSprite(sf::Sprite sprite, std::string tag, int level)
{
	if (P_Sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		if (tag == "goal")
		{
			if (Collision::PixelPerfectTest(P_Sprite, sprite))
			{
				goal = true;
				levelcount = level;
			}
		}
		if (tag == "score")
		{
			if (Collision::PixelPerfectTest(P_Sprite, sprite))
			{
				score = true;
			}
		}
		if (tag == "death")
		{
			if (Collision::PixelPerfectTest(P_Sprite, sprite))
			{
				Death = true;
			}
		}
	}
}

C_Player::C_Player()
{
}


C_Player::~C_Player()
{
}
