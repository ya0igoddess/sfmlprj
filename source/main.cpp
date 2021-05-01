#include "map.h"
using namespace std;

string GetDirPath()
{
	char current_work_dir[FILENAME_MAX];
	string s = _getcwd(current_work_dir, sizeof(current_work_dir));
	int i=0;
	while (s[i]!='\0')
	{
		if (s[i] == '\\')
			s[i] = '/';
		i++;
	}
	
	s.erase(s.size() - 8, s.size());
	return s+"/sfmltest/content/";
}

game_type startChoice()
{
	unsigned short int choice = 0;
	char ch = '2';
	std::vector<std::string> types = { "Обычная игра", "Спавнер", "Таракан" };

	while (ch != 'e')
	{
		int i = 0;
		for (i; i < choice; i++)
		{
			std::cout << ' ' << types[i] << " \n";
		}

		std::cout << '>' << types[i++] << "<\n";

		for (i; i < types.size(); i++)
		{
			std::cout << ' ' << types[i] << " \n";
		}

		std::cout << "\nW,S - перемещение.\nE - выбор.\n";

		ch = _getch();

		if (ch == 'w')
			if (choice == 0)
				choice = types.size() - 1;
			else
				choice--;
		if (ch == 's')
			if (choice == types.size() - 1)
				choice = 0;
			else
				choice++;
		system("cls");
	}
	return (game_type)choice;
}


int main()
{
	int f = 3;
	int *p = &f;
	cout << *p;

	setlocale(LC_ALL, "ru");

	string dirPath = "./content/";

	srand(time(0)); // DEBUG
	unsigned short int ar[] = { 3,3 };

	Map mp(dirPath,startChoice());
	mp.loadContent();
	mp.load("tile_set.png", 16, 16, ar);
	mp.start();

system("pause");

	return 0;
}

