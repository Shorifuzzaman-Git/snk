#include <SDL2/SDL.h>
#include <bits/stdc++.h>
using namespace std;

const int width = 680;
const int height = 480;
const int size = 20;

struct Snake
{
    int x, y;
};

bool Collision(const vector<Snake> &snake)
{
    const Snake head = snake.front();
    if (head.x < 0 || head.x >= width - 1 || head.y < 0 || head.y >= height - 1)
    {
        return true;
    }
    for (auto it = snake.begin() + 1; it != snake.end(); ++it)
    {
        if (it->x == head.x && it->y == head.y)
        {
            return true;
        }
    }
    return false;
}

bool Overlapping(const int x, const int y, const vector<Snake> &snake)
{
    for (const auto &segment : snake)
    {
        if (x == segment.x && y == segment.y)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    int score = 0;
    int countFood = 0;
    bool bonusFood = false;
    bool paused = false;
    auto window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    enum direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    bool run = true;
    vector<Snake> snake;
    SDL_Rect food = {rand() % (width / size) * size, rand() % (height / size) * size, size, size};
    Snake bonus;

    snake.push_back({0, 0});
    SDL_Event e;
    int dir = RIGHT;
    while (run)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
                break;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_DOWN && dir != UP)
                {
                    dir = DOWN;
                }
                else if (e.key.keysym.sym == SDLK_UP && dir != DOWN)
                {
                    dir = UP;
                }
                else if (e.key.keysym.sym == SDLK_LEFT && dir != RIGHT)
                {
                    dir = LEFT;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT && dir != LEFT)
                {
                    dir = RIGHT;
                }
                else if (e.key.keysym.sym == SDLK_SPACE)
                {
                    paused = !paused;
                }
            }
        }

        if (paused)
        {
            SDL_Delay(1);
            continue;
        }

        Snake head = snake.front();
        switch (dir)
        {
        case LEFT:
            head.x -= 20;
            break;
        case DOWN:
            head.y += 20;
            break;
        case UP:
            head.y -= 20;
            break;
        case RIGHT:
            head.x += 20;
            break;
        }

        if (Collision(snake))
        {
            cout << "Game Over! Score : " << score << endl;
            SDL_Quit();
            exit(0);
        }

        while (Overlapping(food.x, food.y, snake))
        {
            food.x = rand() % (width / size) * size;
            food.y = rand() % (height / size) * size;
        }

        if (head.x == food.x && head.y == food.y)
        {
            countFood++;
            score = score + 10;
            if (countFood == 5)
            {
                bonusFood = true;

                bonus.x = rand() % (width / size) * size;
                bonus.y = rand() % (height / size) * size;
                countFood = 0;
            }
            else
            {
                food.x = rand() % (width / size) * size;
                food.y = rand() % (height / size) * size;
            }
        }
        else if (bonusFood && head.x == bonus.x && head.y == bonus.y)
        {
            score = score + 50;
            bonusFood = false;
        }
        else
        {
            snake.pop_back();
        }

        snake.insert(snake.begin(), head);

        SDL_SetRenderDrawColor(renderer, 0, 255, 130, 1);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &food);

        if (bonusFood)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_Rect bonusFoodRect = {bonus.x, bonus.y, size, size};
            SDL_RenderFillRect(renderer, &bonusFoodRect);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1);
        bool isHead = true;
        for (const auto &segment : snake)
        {
            SDL_SetRenderDrawColor(renderer, isHead ? 255 : 255, isHead ? 0 : 255, isHead ? 120 : 0, 1);
            SDL_Rect rect = {segment.x, segment.y, size, size};
            SDL_RenderFillRect(renderer, &rect);

            isHead = false;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
