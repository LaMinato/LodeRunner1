#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>;
const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 71;
 
 
sf::String TileMap[HEIGHT_MAP] = {
	"000000000000000000000000000000000000000000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1 e                                    000000000000000000000000000000000",
	"1000000000 0000000000000000000000000000000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1                                      000000000000000000000000000000000",
	"1          s                           000000000000000000000000000000000",
	"1      f0000                           000000000000000000000000000000000",
	"1      f                               00000000000000000000            0",
	"1 f00000                               00000000000000000000           e0",
	"1 f                                    00000000000000000000          ee0",
	"1 f          f0000000000rrrrr          00000000000000000000         eee0",
	"10000f       f                         00000000000000000000        eeee0",
	"1    f   0000000f           0000000000000000000000000000000      eeeeee0",
	"1    f          f                      00000000000000000000     eeeeeee0",
	"100000000000000000000000000000000000000000000000000      d     eeeeeeee0",
	"111111111111111111111111111111111111111111111111111111111111111111111111",
	"0000000000000000000000000000000000000000000000000000000000000000000000000",
};

struct LadderCoord
{
	int x, y;
};

struct Destroyed
{
	int i,j, sec;
};



/*int GetLadder(int x, int y, int state)
{
	LadderCoord L;
	std::vector <LadderCoord> Lup;
	std::vector <LadderCoord> Ldw;
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == 'f')
				if (TileMap[i-1][j] != 'f')
				{
					L.x = j*32; L.y = i*32;
					Ldw.push_back(L);
				}
				else if (TileMap[i+1][j] != 'f')
				{
					L.x = j*32; L.y = i*32;
					Lup.push_back(L);
				}
		}

		switch (state)
		{
		case 1: 
			int Min = 10000000;
			for (int i = 1; i < Ldw.size; i++)
			{
				if ((Ldw[i].x < Min)&&(Ldw[i].x > x));
			}
			break;
		case 2: 
			for (int i = 0; i < Lup.size; i++)
			{
			
			}
			break;
			int Min = -1000000;
		case 3: 
			for (int i = 0; i < Lup.size; i++)
			{
			
			}
			break;
		case 4: 
			for (int i = 0; i < Lup.size; i++)
			{
			
			}
			break;
		}
};*/