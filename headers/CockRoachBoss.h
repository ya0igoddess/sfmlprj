#pragma once
#include "giant_sword.h"
#include "Player.h"
class CockroachBoss : public Boss
{
private:
	unsigned short int jumps = 5;
	sf::Time timer = sf::Time::Zero, damageTimer = sf::Time::Zero;
	Player* pl;
	bool throw_sword = true;
public:
	CockroachBoss(Player* pl, sf::Vector2f coords);

	virtual void Update(float time, sf::Window &window, sf::Time tps);




};

void spawnCockroach(Player* p, sf::Vector2f coords);