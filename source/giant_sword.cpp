#include "giant_sword.h"

giant_sword::giant_sword(sf::Vector2f startpos, Entity* pl, bool bossable) : Shootable(startpos,(*pl).sprite.getPosition(),texture_list[5], bossable)
{
	this->pl = pl;
	speed = 0.1;
}

bool giant_sword::Update(float time, sf::Window & window, sf::Time tps)
{
	if (check_mapBounds())
		if (firstThrow)
		{
			setDirection(pl->sprite.getPosition());
			Fly(time);
			firstThrow = false;
		}
		else
			return true;
		Fly(time);
		return false;
}
