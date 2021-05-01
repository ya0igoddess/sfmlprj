#include "map.h"
using namespace std;

Map::Map(string &directoryPath, game_type choice)
{
	path = directoryPath;
	number_map = choice;
}

sf::Texture Map::taketexture(const string name, const  sf::Color maskfromcolor)
{
	sf::Image image;
	image.loadFromFile(path + name);
	image.createMaskFromColor(maskfromcolor);
	sf::Texture tx;
	tx.loadFromImage(image);
	return tx;

}

sf::SoundBuffer  Map::takesound(const string & name)
{
	sf::SoundBuffer snd;
	snd.loadFromFile(path + name);
	return snd;
}

void Map::load(string tileset_name, unsigned int w, unsigned int h, unsigned short int ar[])
{
	{
		window.create(sf::VideoMode(800, 600), "Project M", sf::Style::Close);
		window.setView(view);
		window.setFramerateLimit(74);
		view.setSize(200, 200);



		texture.loadFromFile(path + tileset_name);
		map = ar;
		wght = w;
	    hght = h;
		varray.setPrimitiveType(sf::Quads);
		varray.resize(wght*hght * 4);

		for (unsigned short int i = 0; i < hght; i++)
		{
			for (unsigned short int j = 0; j < wght; j++)
			{
				varray[(i*wght + j) * 4].position = sf::Vector2f(16 * j, 16 * i);
				varray[(i*wght + j) * 4 + 1].position = sf::Vector2f(16 * (j + 1), 16 * i);
				varray[(i*wght + j) * 4 + 2].position = sf::Vector2f(16 * (j + 1), 16 * (i + 1));
				varray[(i*wght + j) * 4 + 3].position = sf::Vector2f(16 * j, 16 * (i + 1));

				varray[(i*w + j) * 4].texCoords = sf::Vector2f(0, 0);
				varray[(i*w + j) * 4 + 1].texCoords = sf::Vector2f(16, 0);
				varray[(i*w + j) * 4 + 2].texCoords = sf::Vector2f(16, 16);
				varray[(i*w + j) * 4 + 3].texCoords = sf::Vector2f(0, 16);
			}
		}
	}
}

void Map::end()
{
	entitylist.clear();
	special_entitylist.clear();
	bosslist.clear();
	shootable_list.clear();
	delete player;
	music.stop();
}

void Map::update(float time, sf::Time timepersec)
{
	window.clear(sf::Color::Color(165,42,42));

	for (auto el = shootable_list.cbegin(); el != shootable_list.cend(); )
	{
		if ((*el)->Update(time, window, timepersec))
			el = shootable_list.erase(el);
		else
			++el;
    }

	for (auto el = entitylist.cbegin(); el != entitylist.cend(); ++el)
	{
		(*el)->Update(time, window, timepersec);
	}

	for (auto el = special_entitylist.cbegin(); el != special_entitylist.cend(); ++el)
	{
		(*el)->Update(time, window, timepersec);
	}

	for (auto el = bosslist.cbegin(); el != bosslist.cend();)
	{
		(*el)->Update(time, window, timepersec);

		if ((*el)->alive)
			++el;
		else
			el = bosslist.erase(el);
	}

	window.draw(varray, &texture);
	window.draw(*player);

	player->Update(time,window,timepersec);

	view.setCenter(player->sprite.getPosition());
	window.setView(view);

	for (auto el : entitylist)
	{
		window.draw(*el);
	}

	for (auto el : bosslist)
	{
		window.draw(*el);
	}

	for (auto el : special_entitylist)
	{
		window.draw(*el);
	}

	for (auto el : shootable_list)
	{
		window.draw(*el);
	}


	window.display();
}

void Map::fillMap()
{
	switch (number_map)
	{
	default:
		break;

	case standart:{
		 unsigned short int kol = rand() % 100 + 1;
		 for (short int i = 0; i < kol; i++) {
			 spawnRME(sf::Vector2f(rand()%(wght*16),rand()%(hght*16)));
		 }
		 break;
	}

	case game_type::spawn: {
		spawnSpawner(sf::Vector2f(wght*8,hght*8));
		break;
	}
	case guard: {
		player->sprite.setPosition(wght * 8, hght * 8);
		spawnCockroach(player, sf::Vector2f(wght*16, hght*16));
	}
	}

}

void Map::checkEvents()
{
	switch (number_map)
	{
	case spawn:
	if (event_timer.asSeconds()>5)
	{
		spawnRME(sf::Vector2f(0,0));
		spawnRME(sf::Vector2f(0, hght*16));
		spawnRME(sf::Vector2f(wght*16, 0));
		spawnRME(sf::Vector2f(wght*16, hght*16));
		event_timer = sf::Time::Zero;
		break;
	}

	case guard:
		if (event_timer.asSeconds()>5)
	    {
		shootable_list.push_back(new giant_sword(sf::Vector2f(0,0),player));
		shootable_list.push_back(new giant_sword(sf::Vector2f(0, 16*hght), player));
		shootable_list.push_back(new giant_sword(sf::Vector2f(16*wght, 0*hght), player));
		shootable_list.push_back(new giant_sword(sf::Vector2f(16*wght, 0), player));
		event_timer = sf::Time::Zero;
		break;
	    }
	}
}

bool Map::check_victory()
{
	switch (number_map)
	{
	case standart: return entitylist.size() == 0;

	case spawn: return bosslist.size() == 0 && special_entitylist.size() == 0;

	case guard: return bosslist.size() == 0;
	}
}

void Map::printVictoryMsg()
{
	switch (number_map)
	{
	default:
	{
		cout << "Победа после обеда\n";
		break;
	}

	case spawn:
	{
		cout << "Победа после обеда\n";
		break;
	}

	case guard:
	{
		cout << "Победа после обеда\n";
		break;
	}
	}

}



void Map::loadContent()
{

	texture_list.push_back(taketexture("moch.png"));
	texture_list.push_back(taketexture("enemy.png"));
	texture_list.push_back(taketexture("greenp.png"));
	texture_list.push_back(taketexture("shield_.png")); 
	texture_list.push_back(taketexture("mama.png"));
	texture_list.push_back(taketexture("giant_sword.png"));
	texture_list.push_back(taketexture("tarakan_knight.png"));

	sound_list.push_back(takesound("sound_jumping.wav"));
	sound_list.push_back(takesound("sound_shield.wav"));
	sound_list.push_back(takesound("death.wav"));
	sound_list.push_back(takesound("say2.wav"));
}

void Map::resetplayer()
{
		player = new Player(window, sf::Vector2f(0, 0));
		if (!window.isOpen())
		{
			window.setActive();
		}
}

void Map::start()
{
	bool restart;

	do
	{
		restart = false;
		sf::Clock clock;
		float time;
		sf::Time time_per_sec;
		event_timer = sf::Time::Zero;
		resetplayer();
		fillMap();


		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			
			event_timer+= time_per_sec = clock.getElapsedTime();
			checkEvents();
			time = clock.restart().asMicroseconds() / 600;

			update(time, time_per_sec);



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				end();
				restart = true;
				break;
			}

			if (!player->chekAlive())
			{
				cout << "!ВЫ УМЕРЛИ, НАЖМИТЕ R ДЛЯ РЕСТАРТА!\r";
					while (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
					{
						
					}
					end();
					restart = true;
					break;
			}

			if (check_victory())
			{
				restart = false;
				window.close();
				system("cls");
				printVictoryMsg();
				break;
			}

		}
	} while (restart);

}

void Map::stop()
{
}


