#include <iostream>

#include "SDL.h"

#include "Interface.hpp"
#include "console.h"


Interface::Interface(int width = 640, int height = 480) {
	width_ = width;
	height_ = height;
	finished_ = false;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		ERROR("SDL: Failed to init video: %s", SDL_GetError());
		throw "SDL init";
	}

	if(SDL_SetVideoMode(width_, height_, 0, SDL_OPENGL) == NULL) {
		ERROR("SDL: Failed to set video mode: %s", SDL_GetError());
		SDL_Quit();
		throw "SDL setvideo";
	}

	SetTitle("Tilxor...");
}

Interface::~Interface() {
	SDL_Quit();
}

void Interface::SetTitle(string title) {
	SDL_WM_SetCaption(title.c_str(), NULL);
}

void Interface::MainLoop() {
	while(!finished_) {
		// DrawScene();
		CheckEvents();
	}
}

void Interface::CheckEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			finished_ = true;
		} else if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym = SDLK_ESCAPE) {
				finished_ = true;
			}
		}
	}
}
