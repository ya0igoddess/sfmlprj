#pragma once
#include "stdafx.h"

using namespace std;
class Shootable;

class GraphObj : public sf::Drawable, public sf::Transformable
{
public:

	sf::Sprite sprite;

	float sin, cos;

	sf::Vector2f goesTO;

	virtual void DoAnimation(sf::Time timepersec);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		target.draw(sprite);
	}
};

class Entity : public GraphObj
{
public:


	Entity(sf::Vector2f coords, sf::Texture &tx);

	float speed;

	bool myIntersect(Shootable* shot);

	bool myIntersect(Entity* ent);

	virtual void Update(float time, sf::Window &window, sf::Time tps) = 0;

	virtual void resetPath(unsigned int rad);

	void pathTo(sf::Vector2f coords);
};

extern list<Entity*> entitylist, special_entitylist;
extern vector<sf::Texture> texture_list;
extern vector<sf::SoundBuffer> sound_list;
extern unsigned short int wght, hght;

