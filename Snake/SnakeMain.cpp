#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "setting.h"
#include "drawSth.h"
using namespace std;

//ʳ����
class Food
{
private:
	//ʳ������
	POS m_coordinate;
public:
	//���귶Χ��
	//x: 1 to CSetting::window_width - 30 ������
	//y: 1 to CSetting::window_height - 2 ������
	void RandomXY(vector<POS>& coord)
	{
		m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
		m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
		unsigned int i;
		//ԭ���ϲ�����ʳ��������ߵ�λ���ϣ�����У���������
		for (i = 0; i < coord.size(); i++)
		{
			//ʳ������������λ���ϡ���������
			if (coord[i].x == m_coordinate.x && coord[i].y == m_coordinate.y)
			{
				m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
				m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
				i = 0;
			}
		}
	}
	//Ĭ�Ϲ��캯��
	Food() {}
	//���캯�����������Ϊ��������
	Food(vector<POS>& coord)
	{
		RandomXY(coord);
	}
	//����ʳ���λ��
	void DrawFood()
	{
		setColor(12, 0);
		gotoxy(m_coordinate.x, m_coordinate.y);
		cout << "@";
		setColor(7, 0);
	}
	//�ӿڣ���ȡʳ��λ��
	POS GetFoodCoordinate()
	{
		return m_coordinate;
	}

};
//̰�����࣬����̰���ߵ��ƶ�����ӡ����ʳ��ȵ�
//��ͼ��Χwidth:2 to width-2  height: 2 to height-2
class Snake
{
private:
	bool m_model; //true�˻�  false AI
	int m_direction;
	bool m_is_alive;
private: //AI�������
	bool m_chess[CSetting::window_width - 29 + 1][CSetting::window_height]; //AI������
	//FindPathBFS m_AISnake;
	POS map_size;
public://��������
	vector<POS> m_coordinate;

public://Ĭ�Ϲ��캯��
	Snake(bool model = false) : m_model(model) //Ĭ���˻�ģʽ
	{
		map_size.x = CSetting::window_width - 29 + 1;
		map_size.y = CSetting::window_height;
		//�ƶ���������
		m_direction = 1;
		m_is_alive = true;
		POS snake_head;
		snake_head.x = CSetting::window_width / 2 - 15;
		snake_head.y = CSetting::window_height / 2;

		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head); //��ʼ����������

		//Χǽ���ϰ�
		for (int i = 0; i < CSetting::window_width - 29 + 1; i++)
		{
			m_chess[i][0] = true;
			m_chess[i][CSetting::window_height - 1] = true;
		}

		for (int j = 0; j < CSetting::window_height - 1; j++)
		{
			m_chess[0][j] = true;
			m_chess[CSetting::window_width - 29][j] = true;
		}

	}
	//������Ϸģʽ
	void set_model(bool m) { m_model = m; }
	//��������
	void listen_key_borad()
	{
		char ch;

		if (_kbhit())					//kbhit ���������� 
		{
			ch = _getch();	//ʹ�� getch ������ȡ�������� 
			switch (ch)
			{
			case 'w':
			case 'W':
				if (this->m_direction == DOWN)
					break;
				this->m_direction = UP;
				break;
			case 's':
			case 'S':
				if (this->m_direction == UP)
					break;
				this->m_direction = DOWN;
				break;
			case 'a':
			case 'A':
				if (this->m_direction == RIGHT)
					break;
				this->m_direction = LEFT;
				break;
			case 'd':
			case 'D':
				if (this->m_direction == LEFT)
					break;
				this->m_direction = RIGHT;
				break;
			case '+':
				if (g_speed >= 25)
				{
					g_speed -= 25;
				}
				break;
			case '-':
				if (g_speed < 250)
				{
					g_speed += 25;
				}
				break;
			}
		}
	}

	//����Ƿ������Լ�
	bool self_collision(POS head)
	{
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (head.x == m_coordinate[i].x && head.y == m_coordinate[i].y)
			{
				return true;
			}
		}
		return false;
	}

	//�ƶ�̰����
	void move_snake()
	{
		//��������
		listen_key_borad();
		//��ͷ
		POS head = m_coordinate[0];
		//direction����:1 ��  2 ��  3 ��  4 ��
		switch (this->m_direction)
		{
		case UP:
			head.y--;
			break;
		case DOWN:
			head.y++;
			break;
		case LEFT:
			head.x--;
			break;
		case RIGHT:
			head.x++;
			break;
		}
		//�����ƶ����µ���ͷ
		m_coordinate.insert(m_coordinate.begin(), head);
	}
	//�ж��Ƿ�Ե�ʳ��
	bool is_eat_food(Food& f)
	{
		//��ȡʳ������
		POS food_coordinate = f.GetFoodCoordinate();
		//�Ե�ʳ�ʳ���������ɣ���ɾ����β
		if (m_coordinate[HEAD].x == food_coordinate.x && m_coordinate[HEAD].y == food_coordinate.y)
		{
			f.RandomXY(m_coordinate);
			return true;
		}
		else
		{
			//û�гԵ�ʳ�ɾ����β
			m_coordinate.erase(m_coordinate.end() - 1);
			return false;
		}
	}
	//�ж�̰��������û
	bool snake_is_alive()
	{
		if (m_coordinate[HEAD].x <= 0 ||
			m_coordinate[HEAD].x >= CSetting::window_width - 29 ||
			m_coordinate[HEAD].y <= 0 ||
			m_coordinate[HEAD].y >= CSetting::window_height - 1)
		{
			//�����߽�
			m_is_alive = false;
			return m_is_alive;
		}
		//���Լ�����һ��
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (m_coordinate[i].x == m_coordinate[HEAD].x && m_coordinate[i].y == m_coordinate[HEAD].y)
			{
				m_is_alive = false;
				return m_is_alive;
			}
		}
		m_is_alive = true;

		return m_is_alive;
	}
	//����̰����
	void draw_snake()
	{
		//������ɫΪǳ��ɫ
		setColor(10, 0);
		for (unsigned int i = 0; i < this->m_coordinate.size(); i++)
		{
			gotoxy(m_coordinate[i].x, m_coordinate[i].y);
			cout << "*";
		}
		//�ָ�ԭ������ɫ
		setColor(7, 0);
	}
	//�����Ļ�ϵ�̰����
	void ClearSnake()
	{
		for (unsigned int i = 0; i < m_coordinate.size(); i++)
		{
			m_chess[m_coordinate[i].x][m_coordinate[i].y] = false;
		}
		gotoxy(m_coordinate[this->m_coordinate.size() - 1].x, m_coordinate[this->m_coordinate.size() - 1].y);
		cout << " ";

	}
	//��ȡ̰���ߵĳ���
	int GetSnakeSize()
	{
		return m_coordinate.size();
	}
	//��ȡ��ǰ��Ϸģʽ
	bool GetModel()
	{
		return m_model;
	}
};

//����������ϸ��������Դ��������Ϸ��
int main()
{
	CSetting setting;
	//PrintInfo print_info;
	Snake  snake;
	//��ʼ����Ϸ
	setting.GameInit();
	//��Ϸģʽѡ��
	DrawWelcome();


	gotoxy(CSetting::window_width / 2 - 10, CSetting::window_height / 2 + 3);
	system("pause");
	//����ͼ
	DrawMap();
	DrawGameInfo();
	//����ʳ��
	Food food(snake.m_coordinate);
	//��Ϸ��ѭ��
	while (true)
	{
		//��ӡ�ɼ�
		DrawScore(snake.GetSnakeSize());
		//����ʳ��
		food.DrawFood();
		//������β��ÿ�λ���ǰ����
		snake.ClearSnake();
		//�ж��Ƿ�Ե�ʳ��
		snake.is_eat_food(food);
		//�����û�ģʽѡ��ͬ�ĵ��ȷ�ʽ
		snake.move_snake();
		
		//����
		snake.draw_snake();
		//�ж����Ƿ񻹻���
		if (!snake.snake_is_alive())
		{
			GameOver(snake.GetSnakeSize());
			break;
		}
		//������Ϸ�ٶ�
		Sleep(g_speed);
	}

	cin.get();
	cin.get();

	return 0;
}