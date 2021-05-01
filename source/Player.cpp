#include "Player.h"

Player::Player(sf::RenderWindow &window,  sf::Vector2f coords) :Entity(coords, texture_list[0])
{
	shield.setTexture(texture_list[3]);
	shield.setOrigin(8, 8);
	shield.setColor(sf::Color::Color(255, 255, 255, 128));
	jump_sound = sound_list[0];
	shield_sound = sound_list[1];
	snd.setVolume(30);

	wx = window.getSize().x / 2;
	wy = window.getSize().y / 2;
	speed = 0.14;

}



void Player::Update(float time, sf::Window & window, sf::Time tps)
{
	{
		JumpTimer += tps;
		ShieldTimer += tps;

		if (shielded)
		{
			if (ShieldTimer.asSeconds() > 2)
			{
				shielded = false;
				ShieldTimer = sf::Time::Zero;
				snd.setBuffer(shield_sound);
				snd.play();
			}

		}
		else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && ShieldTimer.asSeconds()>3.5)
			{
				shielded = true;
				ShieldTimer = sf::Time::Zero;
				snd.setBuffer(shield_sound);
				snd.play();
			}

		for (auto el = entitylist.begin(); el != entitylist.cend();)
		{


			if (this->myIntersect(*el) && (*el != this))
			{
				if (isJump)
					el = entitylist.erase(el);
				else
				{
					if (!shielded)
						alive = false;
					++el;
				}
			}
			else
				++el;

		}

		for (auto el = special_entitylist.begin(); el != special_entitylist.cend();)
		{


			if (this->myIntersect(*el))
			{
				if (isJump)
					el = special_entitylist.erase(el);
				else
				{
					if (!shielded)
						alive = false;
					++el;
				}
			}
			else
				++el;

		}

		for (auto el = bosslist.begin(); el != bosslist.cend();)
		{


			if (this->myIntersect(*el))
			{
					if (!shielded)
						alive = false;
					++el;
			}
			else
				++el;

		}

		for (auto el = shootable_list.begin(); el != shootable_list.cend();)
		{


			if (this->myIntersect(*el))
			{
				if (!shielded)
					alive = false;
				++el;
			}
			else
				++el;

		}
		

		if (!isJump)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				speedMod = 0.5;
			else
				speedMod = 1.0;


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getPosition().y < 16 * hght) sprite.move(0, speedMod*time*0.1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getPosition().y > 0) sprite.move(0, speedMod*time*-0.1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite.getPosition().x < 16 * wght) sprite.move(speedMod*0.1*time, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getPosition().x > 0) sprite.move(-0.1*speedMod*time, 0);
			if (sf::Mouse::getPosition(window).x > wx)
			{
				sprite.setScale(1, 1);
				sprite.setRotation(-atan(float(wy - sf::Mouse::getPosition(window).y) / (sf::Mouse::getPosition(window).x - wx)) / 3.1415926535 * 180);
			}
			else
			{
				sprite.setScale(-1, 1);
				sprite.setRotation(180 - atan2(wy - sf::Mouse::getPosition(window).y, sf::Mouse::getPosition(window).x - wx) / 3.1415926535 * 180);
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && JumpTimer.asSeconds()>0.63)
			{
				float msx = sf::Mouse::getPosition(window).x;
				float msy = sf::Mouse::getPosition(window).y;

				msx = (msx / window.getSize().x) * 200 - 100;
				msy = (msy / window.getSize().y) * 200 - 100;



				if (abs(msx) < 100 && abs(msy) < 100)
				{

					goesTO.x = sprite.getPosition().x + msx;
					goesTO.y = sprite.getPosition().y + msy;


					
						int pri = goesTO.x - sprite.getPosition().x;
						int pro = goesTO.y - sprite.getPosition().y;

						if (goesTO.x > 0 && goesTO.y > 0 && goesTO.x<20*16 && goesTO.y<20*16 )
						{
							float hyp = sqrt(pri*pri + pro * pro);

							sin = pro / hyp;
							cos = pri / hyp;

							goesTO.x += cos * 11;
							goesTO.y += sin * 11;

							sprite.setScale(sprite.getScale().x*1.25, sprite.getScale().y*1.25);
							isJump = true;
							snd.setBuffer(jump_sound);
							snd.play();
						}
				}

			}

		}
		else
			if (sprite.getGlobalBounds().contains(goesTO))
			{
				isJump = false;
				JumpTimer = sf::Time::Zero;
			}
			else
				sprite.move(speed*time*cos, speed*time*sin);

		shield.setPosition(sprite.getPosition());

	}
}

sf::Vector2f Player::getPos()
{
	return sprite.getPosition();
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
	if (shielded)
		target.draw(shield);
}

bool Player::chekAlive()
{
	return alive;
}
