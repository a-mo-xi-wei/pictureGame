#pragma once
#include"Global.h"

typedef struct Game
{
	int** map;
	int row;
	int cols;
	int imgw;
	int imgh;
	SDL_Surface* img;
}Game;

//初始化游戏数据
void init_game(Game* pthis, int row, int cols);

//游戏渲染过程
void render_game(SDL_Renderer* render, Game* pthis);

//玩游戏
void event_game(Game* pthis, SDL_Event* msg);

//获取位置信息
SDL_Point get_pos(Game* pthis);

//游戏结束
bool over_game(Game* pthis);