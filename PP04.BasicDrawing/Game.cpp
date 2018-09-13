#include "Game.h"

bool Game::init(const char*title, int xpos, int yops, int width, int height, bool fullscree)
{
	m_bRunning = true;
	// 각자 추가해 볼 것
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow("Wanna go home? Keep up pal.",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1600, 900, SDL_WINDOW_SHOWN);

		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
		SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
		
		SDL_FreeSurface(pTempSurface);

		SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
	}

	else {
		return 1;
	}
	return true;
}

void Game::render()
{
	//원본 사각형 : m_sourceRectangle, 대상 사각형: m_destinationRectangle
	m_destinationRectangle.x = m_sourceRectangle.x = 0;
	m_destinationRectangle.y = m_sourceRectangle.y = 0;
	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;

	//clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer); // 원본 사각형과 대상 사각형의 위치와 크기에 따라 화면에 다르게 나타남
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
	SDL_RenderPresent(m_pRenderer); // 화면 제시하기
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}