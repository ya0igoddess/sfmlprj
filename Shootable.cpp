#include "Shootable.h"

list<Shootable*> shootable_list;

void Shootable::Fly(float time)
{
	sprite.move(sf::Vector2f(time*speed*cos,time*speed*sin));
}

bool Entity::myIntersect(Shootable* shot)
{
	return sprite.getGlobalBounds().intersects(shot->sprite.getGlobalBounds());
}

void Shootable::setDirection(sf::Vector2f coords)
{
	int pri = coords.x - sprite.getPosition().x;
	int pro = coords.y - sprite.getPosition().y;

	double hyp = sqrt(pri*pri + pro * pro);

	sin = pro / hyp;
	cos = pri / hyp;


	sprite.setRotation(atan(sin/cos)/ 3.1415926535 * 180);
	if (coords.x < sprite.getPosition().x)
		sprite.rotate(180);
}

Shootable::Shootable(sf::Vector2f startpos, sf::Vector2f goesto, sf::Texture & tx, bool canHitTheBoss)
{
	sprite.setTexture(tx);
	sprite.setOrigin(tx.getSize().x/2,tx.getSize().y/2);
	sprite.setPosition(startpos);
	setDirection(goesto);
	this->canHitTheBoss = canHitTheBoss;
}

bool Shootable::check_mapBounds()
{
	return sprite.getPosition().x < 0 || sprite.getPosition().x > wght * 16 || sprite.getPosition().y<0 || sprite.getPosition().y>hght * 16;
}
