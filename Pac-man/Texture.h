#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


class Texture {
private:
	// Actual texture
	SDL_Texture* texture;

	int width;
	int height;

public:
	static SDL_Renderer* Renderer;
	Texture();
	~Texture();

	bool LoadImage(const char* path);
	void Render(int x, int y);
	//Rendering specific text
	void RenderText(std::string text, const SDL_Rect destination);

	void Free();

	int GetWidth();
	int GetHeight();

};