#pragma once
#include "Player.h"
#include "CockRoachBoss.h"

using namespace std;

enum game_type { standart, spawn, guard };

	class Map : public sf::Drawable
	{
	private:

		unsigned short int *map;
		game_type number_map;
		sf::Texture texture;
		sf::VertexArray varray;

		Player* player;

		sf::RenderWindow window;

		sf::View view;

		sf::Music music;

		sf::Time event_timer=sf::Time::Zero;

		string path;

		unsigned short int height, width;

		sf::Texture taketexture(const  string name, const sf::Color maskfromcolor = sf::Color::White);

		sf::SoundBuffer takesound(const string& name);

	public:

		void load(string tileset_name, unsigned int w, unsigned int h, unsigned short int ar[]);

		Map(string &directoryPath, game_type choice);

		void end();
		
		virtual	void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			states.texture = &texture;
			target.draw(varray, states);
		}

		void update(float timedelit, sf::Time timer);

		void fillMap();
		void checkEvents();
		bool check_victory();
		void printVictoryMsg();
		void loadContent();
		void resetplayer();
		void start();
		void stop();
	};