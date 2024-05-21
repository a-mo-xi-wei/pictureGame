#include"Game.h"

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;

void sdl_init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
}

void create_window()
{
	window = SDL_CreateWindow(u8"拼图游戏", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}

void event_loop()
{
	Game game;
	init_game(&game, ORDER,ORDER);
	bool isRunning = true;
	SDL_Event msg;
	while (isRunning)
	{
		
		if (SDL_WaitEvent(&msg) != 0)
		{
			switch (msg.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			default :
				event_game(&game, &msg);
				break;
			}
		}
		//绘图
		SDL_RenderClear(render);
		render_game(render, &game);
		SDL_RenderPresent(render);
		if (over_game(&game))isRunning = false;
	}
	
}


int main(int argc,char* argv[])
{
	srand((unsigned int)time(NULL));
	sdl_init();
	create_window();
	event_loop();

	return 0;
}
