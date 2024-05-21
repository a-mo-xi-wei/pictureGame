#include "Game.h"

void init_game(Game* pthis, int row, int cols)
{
	pthis->imgw = WIDTH / cols;
	pthis->imgh = HEIGHT / row;
	pthis->row = row;
	pthis->cols = cols;
	//二级指针申请内存成为二维数组
	pthis->map = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
	{
		pthis->map[i] = (int*)malloc(sizeof(int) * cols);
	}
	//初始化
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			pthis->map[i][j] = i * row + j;//转化为序号
		}
	}
	//打乱地图
	int pos_row = row - 1;
	int pos_cols = cols - 1;
	int max = row * cols - 1;
	for (int i = 0; i < COMPLEX; i++)
	{
		int dir = rand() % 4;//		[0,1,2,3]
		switch (dir)
		{
		case Left:
			if (pos_cols > 0)
			{
				int temp= pthis->map[pos_row][pos_cols - 1];
				pthis->map[pos_row][pos_cols - 1] = max;
				pthis->map[pos_row][pos_cols] = temp;
				pos_cols = pos_cols - 1;
			}
			break;
		case Right:
			if (pos_cols < cols - 1)
			{
				int temp = pthis->map[pos_row][pos_cols + 1];
				pthis->map[pos_row][pos_cols + 1] = max;
				pthis->map[pos_row][pos_cols] = temp;
				pos_cols = pos_cols + 1;
			}
			break;
		case Down:
			if (pos_row <row-1)
			{
				int temp = pthis->map[pos_row + 1][pos_cols];
				pthis->map[pos_row + 1][pos_cols] = max;
				pthis->map[pos_row][pos_cols] = temp;
				pos_row = pos_row + 1;
			}
			break;
		case Up:
			if (pos_row>0)
			{
				int temp = pthis->map[pos_row-1][pos_cols];
				pthis->map[pos_row-1][pos_cols ] = max;
				pthis->map[pos_row][pos_cols] = temp;
				pos_row = pos_row - 1;
			}
			break;
		}
	}

	//测试地图
	/*for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%2d ", pthis->map[i][j]);
		}
		printf("\n");
	}*/
	pthis->img = IMG_Load("./1.jpg");
}

void render_game(SDL_Renderer* render, Game* pthis)
{
	SDL_Texture* temp = SDL_CreateTextureFromSurface(render, pthis->img);
	int max = pthis->row * pthis->cols - 1;

	for (int i = 0; i < pthis->row; i++)
	{
		for (int j = 0; j < pthis->cols; j++)
		{
			SDL_Rect dst = { pthis->imgw * j,pthis->imgh * i,pthis->imgw,pthis->imgh };
				int row = pthis->map[i][j] / pthis->cols;
				int cols = pthis->map[i][j] % pthis->cols;
				SDL_Rect src = { pthis->imgw * cols,pthis->imgh * row,pthis->imgw,pthis->imgh };
			if (pthis->map[i][j] == max)
			{
				SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
				SDL_RenderFillRect(render, &dst);
			}
			else
			{
				
				SDL_RenderCopy(render, temp, &src, &dst);
			}
		}
	}
	SDL_DestroyTexture(temp);
}

void event_game(Game* pthis, SDL_Event* msg)
{
	if (msg->type == SDL_MOUSEBUTTONDOWN &&
		msg->button.button == SDL_BUTTON_LEFT)//鼠标按下左键
	{
		int x = msg->motion.x;
		int y = msg->motion.y;
		int row = y / pthis->imgh;
		int cols = x / pthis->imgw;
		int i = get_pos(pthis).x;
		int j = get_pos(pthis).y;
		if ((row == i && cols == j - 1)||
			(row == i && cols == j + 1)|| 
			(row == i - 1 && cols == j)||
			(row == i + 1 && cols == j))
		{
			pthis->map[i][j] = pthis->map[row][cols];
			pthis->map[row][cols] = pthis->row * pthis->cols - 1;
		}
	}
}

SDL_Point get_pos(Game* pthis)
{
	int max = pthis->row * pthis->cols - 1;
	for (int i = 0; i < pthis->row; i++)
	{
		for (int j = 0; j < pthis->cols; j++)
		{
			if (pthis->map[i][j] == max)
			{
				return (SDL_Point) { i, j };
			}
		}
	}
	return (SDL_Point) {-1,-1};
}

bool over_game(Game* pthis)
{
	int count = 0;
	for (int i = 0; i < pthis->row; i++)
	{
		for (int j = 0; j < pthis->cols; j++)
		{
			if (pthis->map[i][j] != count)return false;
			count++;
		}
	}
	return true;
}
