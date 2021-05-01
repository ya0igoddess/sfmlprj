#pragma once
#include "enemy.h"

using namespace std;

list<Boss*> bosslist;

RandomMovementEnemy::RandomMovementEnemy(sf::Vector2f coords, sf::Texture &texture) : Entity(coords, texture)
{
	speed = 0.04;
	resetPath(360);
}

void spawnRME(sf::Vector2f coords)
{
	entitylist.push_back(new RandomMovementEnemy(coords,texture_list[1]));
}

void spawnRME_green(sf::Vector2f coords)
{
	special_entitylist.push_back(new RandomMovementEnemy(coords,texture_list[2]));
}

void spawnSpawner(sf::Vector2f coords, unsigned short int stage)
{
	bosslist.push_back(new SpawnerBoss(stage,coords,texture_list[4]));
}

void RandomMovementEnemy::Update(float time, sf::Window & window, sf::Time tps)
{
	if (sprite.getGlobalBounds().contains(goesTO))
		resetPath(360);
	else
		sprite.move(time*speed*cos, time*speed*sin);
}

SpawnerBoss::SpawnerBoss(unsigned short int stage, sf::Vector2f coords, sf::Texture &tx) : Boss(coords, tx)
{
	sprite.setTexture(tx);
	sprite.setOrigin((int)tx.getSize().x / 2, (int)tx.getSize().y / 2);
	sprite.setScale((float)stage / 3, (float)stage / 3);
	charges = 3 + rand() % 3;
	resetPath(360);
	speed = 0.05;
	this->stage = stage;
}

void SpawnerBoss::Update(float time, sf::Window & window, sf::Time tps)
{
	timer += tps;

	if (sprite.getGlobalBounds().contains(goesTO))
	{
		if (shots > 0)
		{
			if (timer.asSeconds() > 0.1)
			{
				spawnRME(sprite.getPosition());
				timer = sf::Time::Zero;
				shots--;
			}
		}
		else
			if (charges > 0)
			{
				if (timer.asSeconds() > 2)
				{
					shots = 5 + rand() % 9;
					timer = sf::Time::Zero;
					charges--;
				}
			}
			else
				if (alive)
				{
					spawnRME_green(sprite.getPosition());
					if (stage > 1) {
						spawnSpawner(sprite.getPosition(), stage - 1);
						spawnSpawner(sprite.getPosition(), stage - 1);
					}
					alive = false;
				}
	}
	else
		sprite.move(speed*cos*time, speed*sin*time);


}

