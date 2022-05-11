#include "Texture.h"
#include <SDL_image.h>
#include "Pacman.h"
#include <iostream>
#include "GameObject.h"
#include <sstream>
#include <string>
using namespace std;

SDL_Renderer* Texture::Renderer = NULL;


Texture::Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	Free();
}

bool Texture::LoadImage(const char* path)
{
	Free();

	if (Renderer == NULL)
		return false;

	// Loading image
	SDL_Surface* image = IMG_Load(path);
	if (image == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		return false;
	}

	texture = SDL_CreateTextureFromSurface(Texture::Renderer, image);
	if (texture == NULL) {
		printf("Unable to create texture from surface %s! SDL Error: %s\n", path, SDL_GetError());
		return false;
	}

	width = image->w;
	height = image->h;

	SDL_FreeSurface(image);

	return true;
}

void Texture::Free()
{
	if (texture != NULL) {
		// Freeing the texture 
		SDL_DestroyTexture(texture);
		texture = NULL;

		width = 0;
		height = 0;
	}
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}

void Texture::Render(int x, int y)
{
	if (Renderer == NULL)
		return;

	SDL_Rect destrect1 = { x + 100, y + 200, GetWidth(), GetHeight() };
	SDL_Rect destrect2 = { 250, 30, 200,200 };
	SDL_Rect destrect3 = { 250,500, 200, 200 };
	SDL_RenderCopyEx(Renderer, texture, NULL, &destrect1, 0, NULL, SDL_FLIP_NONE);

	Pacman* pacman = GameObject::tileGraph->GetPacman();
	Point* point = GameObject::tileGraph->GetPoint();

	stringstream ss;
	if (pacman != NULL) {
	
		ss << "Your score: " << pacman->score;
		//RenderText(ss.str(), destrect3);
	}

	if (!pacman) {
		RenderText("Game Over", destrect2);
		//RenderText(ss.str(), destrect3);
	}
	if (pacman!=NULL && pacman->isWon) {

		RenderText("You Won!", destrect2);
		RenderText(ss.str(), destrect3);
	}


	
}

void Texture::RenderText(string text, const SDL_Rect dest) {
	TTF_Font* font = TTF_OpenFont("Assets/arial.ttf", 48);
	SDL_Color color = { 255, 165, 0 };

	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(Renderer, surf);
	SDL_FreeSurface(surf);
	SDL_RenderCopy(Renderer, labelTexture, NULL, &dest);
	SDL_DestroyTexture(labelTexture);
	TTF_CloseFont(font);
}