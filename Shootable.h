#pragma once
#include"entity.h"

class Shootable : public GraphObj
{
protected:
	float speed;

	virtual void Fly(float time);

	void setDirection(sf::Vector2f coords);


public:
	bool canHitTheBoss = false;

	friend bool Entity::myIntersect(Shootable* shot);

	Shootable(sf::Vector2f startpos, sf::Vector2f goesto, sf::Texture &tx, bool canHitTheBoss = false);

	virtual bool Update(float time, sf::Window &window, sf::Time tps) = 0;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}

	bool check_mapBounds();
};

extern list<Shootable*> shootable_list;