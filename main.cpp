#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <sstream>
#include "menu.h"
#include <vector>
#include <list>


using namespace sf;
////////////////////////////////////����� ����� ��������//////////////////////////
class Entity {
public:
	float dx, dy, x, y, speed,moveTimer;//�������� ���������� ������ ��� ������� �����
	int w,h,health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;//����� ����� ���� ������, �� �� ����� ������ ������ ����� ��� �������������� �����.����� ���� �������� ������ �� ����� � ����� ������� ���� �������� � update � ����������� �� �����
	Entity(Image &image, float X, float Y,int W,int H,String Name){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	FloatRect GetRect()
	{
		return FloatRect(x,y,w,h);
	}
};
////////////////////////////////////////////////////����� ������////////////////////////
class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay, ladder, win, onladder, rope } state;//��������� ��� ������������ - ��������� �������
	int playerScore;//��� ���������� ����� ���� ������ � ������
 
	   Player(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){
		   playerScore = 1; state = stay;
		   if (name == "Player1"){
			   sprite.setTextureRect(IntRect(0, 0, w, h));
		   }
	   }
 
	   void control(){
		   if (Keyboard::isKeyPressed){//���� ������ �������
			   if (Keyboard::isKeyPressed(Keyboard::Left)) {//� ������ �����
				   state = left; speed = 0.1; sprite.setScale(-1,1);
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Right)) {
				   state = right; speed = 0.1; sprite.setScale(1,1);
			   }
			   
			   if ((Keyboard::isKeyPressed(Keyboard::Up))&&(state == ladder))
			   {
					state = up; dy+= -0.1;  	
			   }
			   if ((Keyboard::isKeyPressed(Keyboard::Down))&&((state == ladder)||(state == onladder)))
			   {
				   state = down; 
				   dy += 0.1;
			   }
			   if ((Keyboard::isKeyPressed(Keyboard::Left))&&(state == rope))
			   {
					dx = -0.1;
			   }
			   if ((Keyboard::isKeyPressed(Keyboard::Right))&&(state == rope))
			   {
					dx = 0.1;
			   }
			   if ((Keyboard::isKeyPressed(Keyboard::Down))&&(state == rope))
			   {
					dy = 0.15;
					state = stay;
			   }
			   if (Keyboard::isKeyPressed(Keyboard::C))
			   {
					for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
						for (int j = x / 32; j<(x + w) / 32; j++)
						{
							if (TileMap [i+1][j+1] == '0') TileMap[i+1][j+1] = '5';
						}
			   }
			   if (Keyboard::isKeyPressed(Keyboard::X))
			   {
					for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
						for (int j = x / 32; j<(x + w) / 32; j++)
						{
							if (TileMap [i+1][j-1] == '0') TileMap[i+1][j-1] = '5';
						}
			   }
		   }
	   } 
 
	   void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	   {
		   for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		   for (int j = x / 32; j < (x + w) / 32; j++)
		   {
			   if (TileMap [i][j] == 'e') state = win;
			   if (TileMap[i+1][j] == 'f') state = onladder;
			   if (TileMap[i][j] == 'f')
			   {
					state = ladder;
			   }
			   if (TileMap[i][j] == 's')
			   {
					TileMap[i][j] = ' ';
					playerScore--;
			   }

			   
			   if (TileMap[i][j] == 'd') 
				   {
					   life = false;
					   for (int k = HEIGHT_MAP-1; k > 1; k--)
						   for (int m = WIDTH_MAP-1; m > 1; m--)
							{
								TileMap[k][m] = 'd';
						   }

				   }

			   if ((TileMap[i][j] == '0') || (TileMap[i][j] == '1'))//���� ������� ��� ������ �����? ��
			   {
				   if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
				   if (Dy<0){ y = i * 32 + 32;  dy = 0; }//������������ � �������� ������ �����(����� � �� �����������)
				   if (Dx>0){ x = j * 32 - w; }//� ������ ����� �����
				   if (Dx<0){ x = j * 32 + 32; }// � ����� ����� �����
			   }
			   if (TileMap[i][j] == 'r')
				   {
					   state = rope;
					}
			   //else { onGround = false; }//���� ������ �.� �� ����� ���������� � �� ������ ����������� ��� ��������� ������� �������� ����
		   }
	   }
	    
	   void update(float time)
	   {
		   control();//������� ���������� ����������
		   switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		   {
		   case right:dx = speed; break;//��������� ���� ������
		   case left:dx = -speed; break;//��������� ���� �����
		   case up: dx = 0;  break;//����� ��������� �������� ������ (�������� �� ��������)
		   case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		   case ladder: dx = 0; break;
		   case stay: dx = 0; break;//� ����� ����		
		   case onladder: dx = 0; break;
		   case rope: dx = 0; break;
		   }
		   x += dx*time;
		   checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		   y += dy*time;
		   checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		   sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		   if (health <= 0){ life = false; }
		   if (!isMove){ speed = 0; }
		   //if (!onGround) { dy = dy + 0.0015*time; }//������� � ����� ������ ����������� � �����
		   if (life) { setPlayerCoordinateForView(x, y); }
		   if ((state != ladder)||(state != onladder)) dy = dy + 0.0015*time;
		   if ((state == ladder)||(state == onladder)) dy = 0;//��������� ������������� � �����
		   if (state == rope) dy = 0;
		}

};
 
 
class Enemy :public Entity{
public:
	Enemy(Image &image, float X, float Y,int W,int H,String Name):Entity(image,X,Y,W,H,Name){ 
		if (name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(5, 0, w, h));
			dx = 0.1;
			dy = 0.8;
			sprite.setScale(-1,1);
		}
	}
 
	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if ((TileMap[i][j] == '0')||(TileMap[i][j] == '1'))//���� ������� ��� ������ �����, ��
			{
				if (Dy>0){ y = i * 32 - h; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����, ��� ���� ������� ��� �� �� ����� ��� ����� ����� ����� �������
				if (Dy<0){ y = i * 32 + 32; }//������������ � �������� ������ �����(����� � �� �����������)
				if (Dx>0){ x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }//� ������ ����� �����
				if (Dx<0){ x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }// � ����� ����� �����
			}

			if (TileMap[i][j] == '5')
			{
				//y = (i+1)*32-h; x = (j+1)*32 - w;
			}
		}
	}
 
	void update(float time)
	{
		if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� �����
			
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ��
			x += dx*time;
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			y += dy*time;
		    checkCollisionWithMap(0, dy);//������������ ������������ �� Y
			sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
			if (health <= 0){ life = false; }
		}
	}
};
 
/*void Robot(Player pl, Enemy en)
{
	if (en.x < pl.x)
	{
		if (en.y < pl.y)
		{
			GetLadder(en.x, en.y, 1);
		}
		else if (en.y = pl.y)
		{
			en.dx = -0.075;
		}
		else
		{
			GetLadder(en.x, en.y, 2);
		}
	}
	else
	{
		if (en.y < pl.y)
		{
			GetLadder(en.x, en.y, 3);
		}
		else if (en.y = pl.y)
		{
			en.dx = -0.075;
		}
		else
		{
			GetLadder(en.x, en.y, 4);
		}
	}
};*/

void UpdateMap(int time, std::vector <Destroyed> &des)
{
	for (int l = 0; l < HEIGHT_MAP; l++)
		for (int m = 0; m < WIDTH_MAP; m++)
		{
			bool exist = false;
			if (TileMap[l][m] == '5')
				for (int k = 0; k < des.size(); k++)
				{
					if ((l == des[k].i)&&(m == des[k].j)) exist = true;
				}
			if (!exist)
			{
				Destroyed destr;
				destr.i = l; destr.j = m; destr.sec = 4;
				des.push_back(destr);
			}
		}

		for (int k = 0; k < des.size(); k++)
		{
			des[k].sec -= time;
			if (des[k].sec == 0)
			{
				TileMap[des[k].i][des[k].j] = '0';
			}
		}
};

int main()
{
	RenderWindow window(VideoMode(1376, 768), "Lode Runner 2016");
	menu(window);
	view.reset(FloatRect(0, 0, 640, 480));
 
	std::vector <Enemy> Enemies; 
	std::vector <Destroyed> destr;

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	Image heroImage;
	heroImage.loadFromFile("images/myhero.bmp");
	heroImage.createMaskFromColor(Color(0,0,0));
 
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color(0, 0, 0));//������� ����� �� �����.�� ����� ���������� ����� ���������� ��������
 
 
	Player p(heroImage, 750, 500, 27, 32,"Player1");//������ ������ ������
	Enemy easyEnemy(easyEnemyImage, 850, 500, 19 , 32,"EasyEnemy"); Enemies.push_back(easyEnemy);//������� ����, ������ ������ �����
	Enemy easyEnemy2(easyEnemyImage, 950, 500, 19 , 32,"EasyEnemy"); Enemies.push_back(easyEnemy2);
	Enemy easyEnemy3(easyEnemyImage, 1050, 500, 19 , 32,"EasyEnemy"); Enemies.push_back(easyEnemy3);

	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float MapTime = clock.getElapsedTime().asSeconds();
 
		clock.restart();
		time = time / 800;
		
		if (p.state == p.win) 
		{
			std::cout << "You win!" << '\n';
			system("pause");
			window.close();
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();	
		}

		p.update(time);// Player update function	
		for (int i = 0; i < Enemies.size(); i++) Enemies[i].update(time);
		window.setView(view);
		window.clear();
 
		
			for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '5')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if ((TileMap[i][j] == 's')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if ((TileMap[i][j] == 'r')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
				if (TileMap[i][j] == 'e') s_map.setTextureRect(IntRect(160, 0, 32, 32));
				if (TileMap[i][j] == 'd') s_map.setTextureRect(IntRect(192,0,32,32));
				s_map.setPosition(j * 32, i * 32);
				
				window.draw(s_map);
			}

			if (p.playerScore == 0) 
			{
				for (int j = 5; j < 14; j++) TileMap[j][10] = 'f';
			}
		for (int i = 0; i < Enemies.size(); i++) window.draw(Enemies[i].sprite);
		window.draw(p.sprite);
		window.display();

		

		for (int i = 0; i < Enemies.size(); i++)
		{
			if (p.GetRect().intersects(Enemies[i].GetRect()))
			p.life = false;
		}


		if (p.life == false)
		{
			std::cout << "You Died!" << '\n';
			system("pause");
			window.close();
		}

	}
	return 0;
}