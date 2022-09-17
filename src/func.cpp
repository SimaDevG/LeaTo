#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/entity.h"
#include "../include/func.h"

SDL_Texture* loadIMG(const char* filepath, SDL_Renderer* renderer){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filepath);
	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void bgCFill(const char* filepath, SDL_Renderer* renderer){
	//Idea. Add a while loop that will create new pointers and push them back in a vector and then the vector will render them out according to the pointers values.
	std::vector <Entity*> tiles;
	Entity bgTile(filepath, renderer);
	int ctr = 0;
	int Wctr = 0;
	int Hctr = 0;
	int pxWCtr = 0;
	int pxHCtr = 0;
	while (ctr < 3){
		tiles.push_back(new Entity(filepath, renderer));
	}
	ctr = 0;
	while(ctr < 3){
		for(Entity* e: tiles){
			pxWCtr = Wctr * 64;
			pxHCtr = Hctr * 64;
			e->ChangeDstX(pxWCtr);
			e->ChangeDstY(pxHCtr);
			e->Render();
			Wctr++;
			Hctr++;

		}
	}
		

}


void bgFill(const char* filepath, SDL_Renderer* renderer){
	std::vector <Entity*> tiles;
	int ctr = 0;
	int Hcounter = 0;
	int Wcounter = 0;
	int pxW = 0;
	int pxH = 0;
	while (ctr < 3){
		tiles.push_back(new Entity(filepath, renderer));
	}

	for(Entity* e : tiles){
		pxW = Wcounter * 64;
		pxH = Hcounter * 64;
		if(ctr < 30){
			e->ChangeDstX(pxW);
			e->ChangeDstY(pxH);
			Wcounter = Wcounter + 1;
		}
		else if(ctr == 30){
			e->ChangeDstX(pxW);
			e->ChangeDstY(pxH);
			Wcounter = 0;
			Hcounter = Hcounter + 1;
		}
        e->Render();
		ctr = ctr + 1;
    }
}