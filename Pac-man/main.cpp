#include <stdio.h>
#include <string>
#include <vector>

#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include <exception>
//#include "Pacman.h"

#include "TileGraph.h"
#include "Map.h"
#include "TextureManager.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

TextureManager assetManager;

std::vector<GameObject*> Object_list;

TileGraph gTileGraph(30, 30);

Map Map_generate(&gTileGraph, &assetManager);


void removeFromVector(std::vector<GameObject*>& list, GameObject& objectToRemove)
{
	list.erase(std::remove(list.begin(), list.end(), &objectToRemove), list.end());
}

bool init()
{
	SDL_Init(SDL_INIT_VIDEO);

	//Create window
	window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Texture::Renderer = renderer;
	TTF_Init();

	try {
		Texture* wallTexture = new Texture();
		wallTexture->LoadImage("./Assets/brickwall.png");

		Texture* pacmanTexture = new Texture();
		pacmanTexture->LoadImage("./Assets/pacman.png");


		Texture* pointTexture = new Texture();
		pointTexture->LoadImage("./Assets/point.png");


		Texture* ghostTexture = new Texture();
		ghostTexture->LoadImage("./Assets/ghost.png");
			
		assetManager.Add("wall", wallTexture);
		assetManager.Add("point", pointTexture);
		assetManager.Add("pacman", pacmanTexture);
		assetManager.Add("ghost", ghostTexture);

		

		// Loading map
		if (!Map_generate.Load("./Assets/map1.txt")) {
			std::cout << "couldnt find the file";
			return false;
		}

		Map_generate.SettingTo(Object_list);
		//throw 1;
	}
	catch (...) {
		std::cout << "Failed to load from the file" << std::endl;
		return false;
	}

	return true;
}


void close()
{
	for (unsigned int i = 0; i < Object_list.size(); i++)
		delete Object_list[i];

	assetManager.Free();

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
	TTF_Quit();
}


int main(int argc, char* args[]) {
	
	
	if (!init()) {
		printf("Failed to initialize!\n");
		return -1;
	}

	bool quit = false;

	SDL_Event e;

	while (!quit) {
		for (int i = 0; i < Object_list.size(); i++) {
			if (Object_list[i]->ToDelete()) {
				delete Object_list[i];
				Object_list.erase(std::remove(Object_list.begin(), Object_list.end(), Object_list[i]), Object_list.end());
			}

		}

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			for (unsigned int i = 0; i < Object_list.size(); i++)
				Object_list[i]->HandleEvents(&e);

		}
		// Update the all the objects
		for (unsigned int i = 0; i < Object_list.size(); i++)
			Object_list[i]->Update();
		
		//std::cout << "Score: " << Pacman::Score;

		//filling screen with color-black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		// Rendering object
		for (unsigned int i = 0; i < Object_list.size(); i++)
			Object_list[i]->Render();

		//Update the surface
		SDL_RenderPresent(renderer);
	}

	close();

	return 0;
}