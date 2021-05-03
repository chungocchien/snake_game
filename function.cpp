#include"header.h"

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface",1);
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP",1);
	}
	return texture;
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), trong khi
* giữ nguyên chiều rộng và cao của ảnh
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), với
* chiều rộng và cao mới
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
* @param w: chiều rộng (mới)
* @param h: độ cao (mới)
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
void FillBackground(SDL_Renderer* renderer)
{
	//tô nền
	SDL_SetRenderDrawColor(renderer, 255, 241, 204, 255);
	SDL_RenderClear(renderer);
}
void DropFood(SDL_Renderer* renderer, SDL_Rect rectangle)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rectangle);
	SDL_RenderPresent(renderer);
}

void GameMode1()
{
    int score;
    int x1;
	//Khởi tạo thư viện(Khởi động)
	SDL_Init(SDL_INIT_EVERYTHING);
	srand((unsigned int)time(NULL));
	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);	//CREATE SDL WINDOW
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// We must call SDL_CreateRenderer in order for draw calls to affect this window.
    SDL_Rect wall_;


    SDL_Texture *game_over = loadTexture("game_over.bmp", renderer);
    SDL_Texture *replay = loadTexture("replay.bmp", renderer);
    SDL_Texture *diem = loadTexture("score.bmp", renderer);
    SDL_Texture* num[10];
    num[0] = loadTexture("0.bmp", renderer);
    num[1] = loadTexture("1.bmp", renderer);
    num[2] = loadTexture("2.bmp", renderer);
    num[3] = loadTexture("3.bmp", renderer);
    num[4] = loadTexture("4.bmp", renderer);
    num[5] = loadTexture("5.bmp", renderer);
    num[6] = loadTexture("6.bmp", renderer);
    num[7] = loadTexture("7.bmp", renderer);
    num[8] = loadTexture("8.bmp", renderer);
    num[9] = loadTexture("9.bmp", renderer);
    if(game_over==nullptr||replay==nullptr||diem==nullptr)
    {
        SDL_DestroyTexture(game_over);
        quitSDL(window, renderer);
    }
    SDL_RenderClear(renderer);
    bool running;
game:
    x1=640;
    SDL_Event e;
	int game_delay=200;
	Snake snake;
	SDL_Rect food;
	food_ a;
	running = true;

	khoi_tao(a);
	food.w = 20;
	food.h = 20;
	food.x=a.x;
	food.y=a.y;
	DropFood(renderer, food);

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) {
				goto quit;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_w: case SDLK_UP:
					snake.setDirection(0, -1);
					FillBackground(renderer);//tô nền
					wall(renderer, wall_);
					SDL_Delay(game_delay);
					snake.Move();
					snake.ShowSnake(renderer);
                    if(running && (snake.xwall()||snake.eattail()))
                    {
                        running = false;

                    }

                    if (running && snake.Eat(food))
					{

						snake.GrowUp();
						khoi_tao(a);
						food.x=a.x;
						food.y=a.y;

						DropFood(renderer, food);
					}
					if(running) DropFood(renderer, food);

                    break;

				case SDLK_s: case SDLK_DOWN:
					snake.setDirection(0, 1);
					FillBackground(renderer);//tô nền
					wall(renderer, wall_);
					SDL_Delay(game_delay);
					snake.Move();
					snake.ShowSnake(renderer);
                    if(running && (snake.xwall()||snake.eattail()))
                    {
                        running = false;

                    }

                    if (running && snake.Eat(food))
					{

						snake.GrowUp();
						khoi_tao(a);
						food.x=a.x;
						food.y=a.y;

						DropFood(renderer, food);
					}
					if(running) DropFood(renderer, food);



                    break;
				case SDLK_a: case SDLK_LEFT:
					snake.setDirection(-1, 0);
					FillBackground(renderer);//tô nền
					wall(renderer, wall_);
					SDL_Delay(game_delay);
					snake.Move();
					snake.ShowSnake(renderer);
					if(running && (snake.xwall()||snake.eattail()))
                    {
                        running = false;

                    }
                    if (running&&snake.Eat(food))
					{

						snake.GrowUp();
						khoi_tao(a);
						food.x=a.x;
						food.y=a.y;

						DropFood(renderer, food);
					}
                    if(running) DropFood(renderer, food);


					break;

				case SDLK_d: case SDLK_RIGHT:
					snake.setDirection(1, 0);
					FillBackground(renderer);//tô nền
					wall(renderer, wall_);
					SDL_Delay(game_delay);
					snake.Move();
					snake.ShowSnake(renderer);
					if(running && (snake.xwall()||snake.eattail()))
                    {
                        running = false;

                    }

                    if (running&&snake.Eat(food))
					{

						snake.GrowUp();
						khoi_tao(a);
						food.x=a.x;
						food.y=a.y;

						DropFood(renderer, food);
					}
					if(running) DropFood(renderer, food);


					break;
				}
			}


		}
		if(!running) break;
        FillBackground(renderer);//tô nền
        wall(renderer, wall_);
        SDL_Delay(game_delay);
        snake.Move();
        snake.ShowSnake(renderer);

        if(running && (snake.xwall()||snake.eattail()))
            {
                running = false;

            }

        if (running&&snake.Eat(food))
            {

                snake.GrowUp();
                khoi_tao(a);
                food.x=a.x;
                food.y=a.y;

                DropFood(renderer, food);
            }
        if(running)	 DropFood(renderer, food);


	}
    renderTexture(game_over, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture(replay, renderer, 225, 400, 250, 50);
    renderTexture(diem, renderer, 50, 150, 130, 40);
    score=snake.cell.size()-1;
    if(score==0) renderTexture(num[0], renderer, 600, 150, 40, 40);
    while(score) {
		int tmp = score % 10;
		score /= 10;
		x1 -= 50;
		renderTexture(num[tmp], renderer, x1, 150, 40, 40);
	}
    SDL_RenderPresent(renderer);
    while(!running)
    {
        while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT) goto quit;
        if(e.type==SDL_MOUSEBUTTONDOWN){
            if(e.button.x>=225&&e.button.x<=475&&e.button.y>=400&&e.button.y<=450){
                if(e.button.button==SDL_BUTTON_LEFT) {
                    running=true;
                    goto game;
                }
            }
        }
        }
    }

quit:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
}
