#pragma once
#include "SDL.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <ctime>
#undef main

#define MAX_SIZE_OF_SNAKE 100
using namespace std;
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 660;
const string WINDOW_TITLE = "Snake";

void GameMode1();
void FillBackground(SDL_Renderer* renderer);
void DropFood(SDL_Renderer* renderer, SDL_Rect rectangle);

class Snake
{
public:

	SDL_Rect snaketemp;
	vector<SDL_Rect> cell;
	int debug = 1;
	int LorR, UorD;
public:
	Snake()
	{

		snaketemp.h = snaketemp.w = 20;
		snaketemp.x = 0;
		snaketemp.y = 0; //tạo đốt đầu tiên cho con rắn ở tọa độ (0,0)
		cell.push_back(snaketemp);

		//hướng di chuyển
		UorD = 0;
		LorR = 1;
	}

	bool Eat(SDL_Rect food)
	{
		if (food.x == snaketemp.x && food.y == snaketemp.y)
		{
			return 1;//Ate
		}
		return 0;//not eat
	}

    bool xwall()
	{
	    if((snaketemp.x>=60&&snaketemp.x<=240&&snaketemp.y==60)||
        (snaketemp.x>=60&&snaketemp.x<=240&&snaketemp.y==560)||
        (snaketemp.x>=420&&snaketemp.x<=600&&snaketemp.y==60)||
        (snaketemp.x>=420&&snaketemp.x<=600&&snaketemp.y==560)||
        (snaketemp.y>=60&&snaketemp.y<=240&&snaketemp.x==60)||
        (snaketemp.y>=60&&snaketemp.y<=240&&snaketemp.x==600)||
        (snaketemp.y>=380&&snaketemp.y<=560&&snaketemp.x==60)||
        (snaketemp.y>=380&&snaketemp.y<=560&&snaketemp.x==600))
            {return 1;}

    else return 0;
	}
    bool eattail()
    {
        int count=0;
        for(size_t i=0;i<cell.size()-1;i++)
        {
            if(snaketemp.x==cell[i].x&&snaketemp.y==cell[i].y)
            {return 1;
            count=1;
            break;}
        }
        if(count==0) return 0;
    }
	void setDirection(int a, int b)
	{
		if ((LorR * a) != -1)
			LorR = a;
		if ((UorD * b) != -1)
			UorD = b;
	}

	//xóa đốt rắn cuối cùng
	void EraseTail()
	{
		cell.erase(cell.begin());
	}

	//trả về giá trị của hướng trái hay phải
	int getLorR()
	{
		return LorR;
	}

	//trả về giá trị của hướng trên hay dưới
	int getUorD()
	{
		return UorD;
	}

	void GrowUp()
	{
		cell.push_back(snaketemp);
	}

	void Move()
	{
		switch (LorR)
		{
		case 0:
			snaketemp.y += 20 * UorD;
			break;
		case -1: case 1:
			snaketemp.x += 20 * LorR;
			break;
		}

		if (snaketemp.x == -20)
			snaketemp.x = SCREEN_WIDTH - 20;
		else if (snaketemp.x == (SCREEN_WIDTH))
			snaketemp.x = 0;
		if (snaketemp.y == -20)
			snaketemp.y = SCREEN_HEIGHT - 20;
		else if (snaketemp.y == (SCREEN_HEIGHT))
			snaketemp.y = 0;

		cell.push_back(snaketemp);
		EraseTail();
		cout << cell.size() << endl;

	}

	void ShowSnake(SDL_Renderer* renderer)
	{
		for (size_t i = 0; i < cell.size(); i++)
		{
		    if(i==cell.size()-1)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &cell[i]);
            }else{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &cell[i]);
            }
		}
		SDL_RenderPresent(renderer);
	}
};
struct food_
{
    int x;
    int y;
};
void khoi_tao(food_ &a);
void wall(SDL_Renderer* renderer, SDL_Rect wall);

