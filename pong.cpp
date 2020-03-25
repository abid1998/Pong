#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

// enumeration to handle directions
enum eDir { STOP = 0, LEFT, UPLEFT , DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT = 6};

class ball
{
private:
	int x, y;
	int default_x, default_y;
	eDir direction;
public:
	ball(int x, int y)
	{
		default_x = x;
		default_y = y;
		this->x = x;
		this->y = y;
		direction = STOP;
	}
	void reset()
	{
		x = default_x;
		y = default_y;
		direction = STOP;
	}
	void change_direction(eDir direction)
	{
		this->direction = direction;
	}
	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
	}
	inline int get_x()
	{
		return x;
	}
	inline int get_y()
	{
		 return y;
	}
	inline eDir get_direction()
	{
		 return direction;
	}
	void move()
	{
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		default:
			break;
		}
	}
	friend ostream & operator<<(ostream & o, ball c)
	{
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
};
class paddle
{
private:
	int x, y;
	int default_x, default_y;
public:
	paddle()
	{
		x = y = 0;
	}
	paddle(int x, int y) : paddle()
	{
		default_x = x;
		default_y = y;
		this->x = x;
		this->y = y;
	}
	inline void reset()
	{
		x = default_x;
	  y = default_y;
	}
	inline int get_x()
	{
		return x;
	}
	inline int get_y()
	{
		return y;
	}
	inline void move_up()
	{
		y--;
	}
	inline void move_down()
	{
		y++;
	}
	friend ostream & operator<<(ostream & o, paddle c)
	{
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
};
class game_manager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	ball * ball1;
	paddle *player1;
	paddle *player2;
public:
	game_manager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball1 = new ball(w / 2, h / 2);
		player1 = new paddle(1, h / 2 - 3);
		player2 = new paddle(w - 2, h / 2 - 3);
	}
	~game_manager()
	{
		delete ball1;
	  delete player1;
		delete player2;
	}
	void score_up(paddle * player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		ball1->reset();
		player1->reset();
		player2->reset();
	}
	void draw()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD Position;

		Position.X = 0;
		Position.Y = 0;

		SetConsoleCursorPosition(hOut, Position) ;
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballx = ball1->get_x();
				int bally = ball1->get_y();
				int player1x = player1->get_x();
				int player2x = player2->get_x();
				int player1y = player1->get_y();
				int player2y = player2->get_y();

				if (j == 0)
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "O"; //ball
				else if (player1x == j && player1y == i)
					cout << "\xDB"; //player1
				else if (player2x == j && player2y == i)
					cout << "\xDB"; //player2

				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB"; //player1
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB"; //player1
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB"; //player1

				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB"; //player1
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB"; //player1
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB"; //player1
				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
	}
	void input()
	{
		ball1->move();

		int player1y = player1->get_y();
		int player2y = player2->get_y();

		if (_kbhit())
		{
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->move_up();
			if (current == up2)
				if (player2y > 0)
					player2->move_up();
			if (current == down1)
				if (player1y + 4 < height)
					player1->move_down();
			if (current == down2)
				if (player2y + 4 < height)
					player2->move_down();

			if (ball1->get_direction() == STOP)
				ball1->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}
	void logic()
	{
		int ballx = ball1->get_x();
		int bally = ball1->get_y();
		int player1x = player1->get_x();
		int player2x = player2->get_x();
		int player1y = player1->get_y();
		int player2y = player2->get_y();

		//left paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball1->change_direction((eDir)((rand() % 3) + 4));

		//right paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball1->change_direction((eDir)((rand() % 3) + 1));

		//bottom
		if (bally == height - 1)
			ball1->change_direction(ball1->get_direction() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top
		if (bally == 0)
			ball1->change_direction(ball1->get_direction() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right
		if (ballx == width - 1)
			score_up(player1);
		//left
		if (ballx == 0)
			score_up(player2);
	}
	void run()
	{
		while (!quit)
		{
			draw();
			input();
			logic();
		}
	}
};
int main()
{
	system("cls");
	game_manager c(40, 20);
	c.run();
	return 0;
}
