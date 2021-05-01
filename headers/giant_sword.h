#pragma once
#include "Shootable.h"

class giant_sword : public Shootable
{
private:
	sf::Time timer;
	Entity* pl;
	bool firstThrow=true;
public:
	giant_sword(sf::Vector2f startpos,Entity* pl, bool bossable=false);

	virtual bool Update(float time, sf::Window &window, sf::Time tps);
};