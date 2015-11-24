#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>

template <typename T>
inline constexpr int RoundReal(T real) noexcept
{
    return (int)(real + 0.5);
}

static constexpr auto WIDTH = 1280;
static constexpr auto HEIGHT = 800;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);

	constexpr auto MAX = 100.0f;
	constexpr SDL_Rect progressBarBase = { WIDTH - 250, 100, 200, 25 };
	SDL_Rect progressBarProgress = { WIDTH - 250, 100, 1, 25 };

    for (auto k = 1.0f; k < MAX; k += 0.005f)
    {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

        for (auto i = 0; i < 200; ++i)
        {
            auto x1 = cos(2.0f * M_PI * i / 200.0f);
            auto y1 = sin(2.0f * M_PI * i / 200.0f);
            auto x2 = cos(2.0f * M_PI * (i * k) / 200.0f);
            auto y2 = sin(2.0f * M_PI * (i * k) / 200.0f);

            SDL_RenderDrawLine(renderer,
                               RoundReal(((x1 + 1.0f) * HEIGHT / 2) * 0.95) + 120,
                               RoundReal(((y1 + 1.0f) * HEIGHT / 2) * 0.95),
                               RoundReal(((x2 + 1.0f) * HEIGHT / 2) * 0.95) + 120,
                               RoundReal(((y2 + 1.0f) * HEIGHT / 2) * 0.95));
        }

        SDL_RenderDrawRect(renderer, &progressBarBase);

		progressBarProgress.w = RoundReal((k / 100 * 100) * 2);

		if (progressBarProgress.w >= MAX * 2)
		{
			SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);

			progressBarProgress.w = 200;
		}
        SDL_RenderFillRect(renderer, &progressBarProgress);

        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                return 0;
        }

        SDL_Delay(1000 / 60);
    }

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
