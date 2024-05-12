#include "../include/window.hpp"

Window::Window(int width, int height) : m_width(width), m_height(height),
    m_window(nullptr, &SDL_DestroyWindow),
    m_renderer(nullptr, &SDL_DestroyRenderer)
{
    CHK_SDL(SDL_Init(SDL_INIT_VIDEO) == 0);

    CHK_SDL((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG));

    CHK_SDL(TTF_Init() == 0);

    m_font = TTF_OpenFont("data/font/font.ttf", 24);
    CHK_TTF(m_font != nullptr);

    m_window.reset(SDL_CreateWindow("Bricks Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN));
    CHK_SDL(m_window != nullptr);

    m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
    CHK_SDL(m_renderer != nullptr);

    SDL_Surface *buttonSurface = IMG_Load("data/img/orangeButton.png");
    CHK_SDL(buttonSurface != nullptr);

    m_levelButtonTexture = SDL_CreateTextureFromSurface(m_renderer.get(), buttonSurface);
    SDL_FreeSurface(buttonSurface);

    SDL_Surface *backgroundSurface = IMG_Load("data/img/background3.png");
    CHK_SDL(backgroundSurface != nullptr);

    m_backgroundTexture = SDL_CreateTextureFromSurface(m_renderer.get(), backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    CHK_SDL(m_levelButtonTexture != nullptr);
}

Window::~Window()
{
    if (m_font)
        TTF_CloseFont(m_font);
    if (m_levelButtonTexture)
        SDL_DestroyTexture(m_levelButtonTexture);
    if (m_backgroundTexture)
        SDL_DestroyTexture(m_backgroundTexture);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
