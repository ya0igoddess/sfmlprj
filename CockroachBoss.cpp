#include "CockroachBoss.h"

CockroachBoss::CockroachBoss(Player * pl, sf::Vector2f coords): Boss(coords,texture_list[6])
{
	sprite.setPosition(coords);
	this->pl = pl;
	pathTo(pl->sprite.getPosition());
	speed = 0.15;
	stage = 5;
}

void spawnCockroach(Player* p, sf::Vector2f coords)
{
	bosslist.push_back(new CockroachBoss(p,coords));
}

void CockroachBoss::Update(float time, sf::Window & window, sf::Time tps)
{
	timer += tps;
	damageTimer += tps;
	if (damageTimer.asSeconds()>0.65)
	for (auto el : shootable_list)
	{
		if (el->canHitTheBoss && this->myIntersect(el))
		{
			damageTimer = sf::Time::Zero;
			stage--;
			sprite.setColor(sf::Color(128, 0, 0, 255));
			if (stage < 1)
				alive = false;
		}
	}
	

	if (sprite.getGlobalBounds().contains(goesTO))
	{ 
		if (jumps > 0 && timer.asSeconds()>rand()%5*0.1+0.8)
		{
			sprite.setColor(sf::Color(255, 255, 255, 255));
			pathTo(pl->sprite.getPosition());
			timer = sf::Time::Zero;
			jumps--;
		}
		else
			if (timer.asSeconds() > 0.9)
			{
				if (throw_sword)
				{
					shootable_list.push_back(new giant_sword(sprite.getPosition(), pl, true));
					throw_sword = false;
					damageTimer = sf::Time::Zero;
				}
				else
					if (timer.asSeconds() > 1.3) {
						shootable_list.push_back(new giant_sword(sprite.getPosition(), pl, true));
						jumps = 3;
						timer = sf::Time::Zero;
						throw_sword = true;
					}
			}
	}
	else
		sprite.move(speed*time*cos,speed*time*sin);

}
