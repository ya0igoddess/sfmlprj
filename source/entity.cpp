#include "entity.h"

list<Entity*> entitylist, special_entitylist;
vector<sf::Texture> texture_list;
vector<sf::SoundBuffer> sound_list;
unsigned short int wght, hght;


Entity::Entity(sf::Vector2f coords, sf::Texture &tx)
{
	sprite.setTexture(tx);
	sprite.setOrigin(tx.getSize().x/2, tx.getSize().y / 2);
	sprite.setPosition(coords);
}

bool Entity::myIntersect(Entity * ent)
{
	return sprite.getGlobalBounds().intersects(ent->sprite.getGlobalBounds());
}

void Entity::resetPath(unsigned int rad)
{
	do
	{
		sf::Sprite sp = this->sprite;
		goesTO = sf::Vector2f(sprite.getPosition().x + rad / 2 - rand() % rad, sprite.getPosition().y + rad / 2 - rand() % rad);
	} while (goesTO.x<0 || goesTO.y<0 || goesTO.x>wght*16 || goesTO.y>hght*16);

	int pri = goesTO.x - sprite.getPosition().x;
	int pro = goesTO.y - sprite.getPosition().y;

	double hyp = sqrt(pri*pri + pro * pro);

	sin = pro / hyp;
	cos = pri / hyp;

	goesTO.x += sprite.getTexture()->getSize().x / 2 * cos;
	goesTO.y += sprite.getTexture()->getSize().y / 2 * sin;
}

void Entity::pathTo(sf::Vector2f coords)
{
	goesTO = coords;

	int pri = goesTO.x - sprite.getPosition().x;
	int pro = goesTO.y - sprite.getPosition().y;

	double hyp = sqrt(pri*pri + pro * pro);

	sin = pro / hyp;
	cos = pri / hyp;

	goesTO.x += sprite.getTexture()->getSize().x / 2 * cos;
	goesTO.y += sprite.getTexture()->getSize().y / 2 * sin;
}

void GraphObj::DoAnimation(sf::Time timepersec)
{
}
