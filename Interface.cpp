#include <iostream>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Interface.hpp"
#include "console.h"

Interface::Interface(const int width = 640, const int height = 480) {
	DEBUG_M("Entering function...");
	width_ = width;
	height_ = height;
	finished_ = false;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		ERROR("SDL: Failed to init video: %s", SDL_GetError());
		throw "SDL init";
	}

	if(SDL_SetVideoMode(width_, height_, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
		ERROR("SDL: Failed to set video mode: %s", SDL_GetError());
		SDL_Quit();
		throw "SDL setvideo";
	}

	fps_ = 0;
	mpf_ = 0;
	limit_fps_ = true;
	cam_move_ = false;
	
	SetTitle("Tilxor...");
}

Interface::~Interface() {
	DEBUG_M("Entering function...");
	SDL_Quit();
}

void Interface::SetTitle(const string title) {
	DEBUG_M("Entering function...");
	SDL_WM_SetCaption(title.c_str(), NULL);
}

void Interface::MainLoop() {
	DEBUG_M("Entering function...");
	while(!finished_) {
		camera_.Update(0);
		DrawScene();
		CheckEvents();
	}
}

/* Set 3D perspective mode */
void Interface::PerspectiveSet() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera_.getFov(), width_ / height_, 0.1f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Interface::DrawScene() {
	static int frame = 0;
	static int last_render_time = 0;
	static int last_fps_time = 0;
	int current_time = SDL_GetTicks();

	/* Limit framerate */
	if(limit_fps_ && !( (current_time - last_render_time) >= 1000/60) ) {
		return;
	}

	/* Calculate FPS */
	frame++;
	if(current_time - last_fps_time > 1000) {
		fps_ = frame*1000.0f/(current_time-last_fps_time);
		last_fps_time = current_time;
		frame = 0;
		LOG("FPS: %d,\tMPF: %d", fps_, mpf_);
	}
	
	last_render_time = current_time;
	
	PerspectiveSet();
	glLoadIdentity();
	camera_.Position();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING) ;
	glEnable(GL_LIGHT0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_COLOR_MATERIAL);
	
	if(area_) {
		area_->Draw();
	}
	
	glFlush();
	SDL_GL_SwapBuffers();

	mpf_ = SDL_GetTicks() - current_time;
}

void Interface::setArea(Area* area) {
	area_ = area;
}

void Interface::HandleKeys(const SDL_Event& event) {
	switch(event.key.keysym.sym) {
		case SDLK_ESCAPE:
			finished_ = true;
		default:
			DEBUG_A("Unknown key down %d...", event.key.keysym.sym);
	}
}

void Interface::ResizeEvent(const SDL_Event& event) {
	DEBUG_M("Screen resize %dx%d...", event.resize.w, event.resize.h);
	width_ = event.resize.w;
	height_ = event.resize.h;

	if(SDL_SetVideoMode(width_, height_, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
		ERROR("SDL: Failed to set video mode: %s", SDL_GetError());
		SDL_Quit();
		throw "SDL setvideo";
	}

	glViewport(0, 0, width_, height_);
	PerspectiveSet();
}

void Interface::CheckEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT: case SDLK_q:
				finished_ = true;
				break;
			case SDL_KEYDOWN:
				HandleKeys(event);
				break;
			case SDL_MOUSEMOTION:
				if(cam_move_) {
					camera_.setRotX(camera_.getRotX() + (GLfloat)event.motion.xrel / width_ * 100);
					camera_.setRotY(camera_.getRotY() - (GLfloat)event.motion.yrel / height_ * 100);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				DEBUG_A("Mouse button %d down at (%d, %d)",
					event.button.button, event.button.x, event.button.y);
				if(event.button.button == 3) {
					cam_move_ = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				DEBUG_A("Mouse button %d up at (%d, %d)",
					event.button.button, event.button.x, event.button.y);
				switch(event.button.button) {
					case 3:
						cam_move_ = false; break;
					case 5:
						camera_.setZoom(camera_.getZoom() + ZOOM_STEP); break;
					case 4:
						camera_.setZoom(camera_.getZoom() - ZOOM_STEP); break;
				}
				break;
			case SDL_VIDEORESIZE:
				ResizeEvent(event);
				break;
			default:
				DEBUG_A("Unknown event occured...");
				break;
		}
	}
}
