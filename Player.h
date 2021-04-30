#pragma once
#include "enemy.h"
#include "Shootable.h"


using namespace std;
class Player : public Entity
{
private:

	int wx, wy;
	bool isJump = false, shielded = false, alive = true;
	sf::Time JumpTimer = sf::seconds(4), ShieldTimer = sf::seconds(8);
	sf::Sound snd;
	sf::SoundBuffer shield_sound, jump_sound;
	sf::Sprite shield;
	float speedMod=1;

public:

	Player(sf::RenderWindow &window, sf::Vector2f coords);

	virtual void Update(float time, sf::Window &window, sf::Time tps) override;	

	sf::Vector2f getPos();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool chekAlive();

};
