#pragma once
#include "entity.h"
using namespace std;


class RandomMovementEnemy : public Entity
{
public:
	RandomMovementEnemy(sf::Vector2f coords, sf::Texture &texture);
	virtual void Update(float time, sf::Window &window, sf::Time tps) override;
};

void spawnRME(const sf::Vector2f coords);

class Boss : public Entity
{
public:

	bool alive = true;

	unsigned short int stage;
	Boss(sf::Vector2f coords, sf::Texture &tx) : Entity(coords, tx)
	{}

};

extern list<Boss*> bosslist;




class SpawnerBoss : public Boss
{
public:
	unsigned short int charges, shots=0;
	sf::Time timer = sf::Time::Zero;


	SpawnerBoss(unsigned short int stage, sf::Vector2f coords, sf::Texture &tx);

	virtual void Update(float time, sf::Window &window, sf::Time tps) override;
};

void spawnSpawner(sf::Vector2f coords, unsigned short int stage=3);

