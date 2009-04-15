#include <iostream>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Interface.hpp"
#include "console.h"
#include "Object.hpp"
#include "RigidBody.hpp"

/**
 * Creates an opengl window.
 * @param width Window width in pixles.
 * @param height Window height in pixles.
 */
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
	gm_ = NULL;
	mode_ = MODE_NONE;
	tm_ = NULL;
	creature_ = NULL;

	SetTitle("Tilxor...");
}

Interface::~Interface() {
	DEBUG_M("Entering function...");
	SDL_Quit();
}

/**
 * Sets the title of the window.
 * @param title
 */
void Interface::SetTitle(const string title) {
	DEBUG_M("Entering function...");
	SDL_WM_SetCaption(title.c_str(), NULL);
}

/**
 * The main rendering and input loop.
 */
void Interface::MainLoop() {
	DEBUG_M("Entering function...");
	
	while(!finished_) {
		int now = SDL_GetTicks();
		camera_.Update(now);
		
		/*if(creature_) {
			creature_->Update(now);
			if(creature_->getArea()) {
				creature_->getArea()->Update(now);
			}
		}*/
		//creature_->Update(now);
		gm_->Update(now);
		Draw();
		CheckEvents_();
	}
}

/**
 * Set the OpenGL 3D perspective mode.
 */
void Interface::PerspectiveSet_() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera_.getFov(), width_ / height_, 0.1f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
}

/**
 * Gets the area the controlled creature is in.
 * @return The area.
 */
Area* Interface::getArea() {
	DEBUG_M("Entering function...");
	if(!creature_) {
		return NULL;
	}
	return creature_->getArea();
}

/**
 * Gets the resource manager of the area the creature is in.
 * @return The resource manager
 */
ResourceManager* Interface::getResourceManager() {
	DEBUG_M("Entering function...");
	Area* area = getArea();
	if(!area) {
		DEBUG_V("No area...");
		return NULL;
	}

	DEBUG_V("done...");
	return area->getResourceManager();
}

/**
 * Sets the tile currently selected for edit mode.
 * @param filename Filename of model.
 */
void Interface::setEditTile_(const string filename) {
	DEBUG_M("Entering function...");
	ResourceManager* rm = getResourceManager();
	if(!rm) {
		DEBUG_V("No resource manager...");
		return;
	}

	rm->unloadModel(tm_);
	tm_ = rm->loadModel(filename);
	DEBUG_V("done...");
}

Tile* Interface::getEditTile_() {
	return tm_;
}

/**
 * Renders the scene using OpenGL.
 */
void Interface::Draw() {
	static int frame = 0;
	static int last_render_time = 0;
	static int last_fps_time = 0;
	int current_time = SDL_GetTicks();

	// Limit framerate
	if(limit_fps_ && !( (current_time - last_render_time) >= 1000/60) ) {
		return;
	}

	// Calculate FPS
	frame++;
	if(current_time - last_fps_time > 1000) {
		fps_ = frame*1000.0f/(current_time-last_fps_time);
		last_fps_time = current_time;
		frame = 0;
		LOG("FPS: %d,\tMPF: %d", fps_, mpf_);
	}
	last_render_time = current_time;

	PerspectiveSet_();
	glLoadIdentity();
	camera_.Position();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING) ;
	glEnable(GL_LIGHT0);
	glColor3f(1.0f, 1.0f, 1.0f);
	//glEnable(GL_COLOR_MATERIAL);

	if(creature_) {
		Area* area = creature_->getArea();
		if(area) {
			area->Draw();

			if(mode_ != MODE_NONE) {
				windowToWorld(mx_, my_, tx_, ty_, tz_);
			}

			if(mode_ == MODE_EDIT_TILES) {
				int gx, gy;
				area->getGridCord(tx_, tz_, gx, gy);
				float fx, fz;
				area->getWorldCord(gx, gy, fx, fz);

				Model* tilem = getEditTile_();
				if(tilem) {
					glPushMatrix();
					glTranslatef(fx , 0.0, fz);
					RCBC_Render(tilem);
					glPopMatrix();
					area->getResourceManager()->unloadModel(tilem);
				}
			}
			
		}
	}

	glFlush();
	SDL_GL_SwapBuffers();

	mpf_ = SDL_GetTicks() - current_time;
}

void Interface::HandleKeyDown_(const SDL_Event& event) {
	switch(event.key.keysym.sym) {
		case SDLK_ESCAPE:
			finished_ = true;
			break;
		case SDLK_UP:
			creature_->Forward(true);
			break;
		case SDLK_DOWN:
			creature_->Reverse(true);
			break;
		case SDLK_LEFT: case SDLK_q:
			creature_->TurnRight(true);
			break;
		case SDLK_RIGHT: case SDLK_e:
			creature_->TurnLeft(true);
			break;
		case SDLK_a:
			creature_->StrafeLeft(true);
			break;
		case SDLK_d:
			creature_->StrafeRight(true);
			break;	
		case SDLK_SPACE:
			creature_->Jump();
			break;
		case SDLK_LSHIFT: case SDLK_RSHIFT:
			creature_->Run(true);
			break;
		/*case SDLK_q:
			finished_ = true;
			break;*/
		case SDLK_1:
			camera_.setFov(15.0f);
			break;
		case SDLK_2:
			camera_.setFov(30.0f);
			break;
		case SDLK_3:
			camera_.setFov(45.0f);
			break;
		case SDLK_4:
			camera_.setFov(60.0f);
			break;
		case SDLK_5:
			camera_.setFov(90.0f);
			break;
		case SDLK_6:
			camera_.setFov(110.0f);
			break;
		case SDLK_7:
			camera_.setFov(120.0f);
			break;
		case SDLK_8:
			camera_.setFov(130.0f);
			break;
		case SDLK_9:
			camera_.setFov(140.0f);
			break;
		case SDLK_0:
			camera_.setFov(175.0f);
			break;
		default:
			DEBUG_M("Unknown key down %d...", event.key.keysym.sym);
	}
}

void Interface::HandleKeyUp_(const SDL_Event& event) {
	switch(event.key.keysym.sym) {
		case SDLK_UP:
			creature_->Forward(false);
			break;
		case SDLK_DOWN:
			creature_->Reverse(false);
			break;
		case SDLK_LEFT: case SDLK_q: 
			creature_->TurnRight(false);
		case SDLK_RIGHT: case SDLK_e:
			creature_->TurnLeft(false);
			break;
		case SDLK_LSHIFT: case SDLK_RSHIFT:
			creature_->Run(false);
			break;
		case SDLK_a:
			creature_->StrafeLeft(false);
			break;
		case SDLK_d:
			creature_->StrafeRight(false);
			break;
		case SDLK_F1:
			LOG("Setting game mode.");
			mode_ = MODE_NONE;
			break;
		case SDLK_F2:
			LOG("Setting tiles edit mode.");
			setEditTile_("data/models/monkey-test.dae");
			mode_ = MODE_EDIT_TILES;
			break;
		case SDLK_F3:
			LOG("Setting objects edit mode.");
			mode_ = MODE_EDIT_OBJECTS;
			break;
		default:
			break;
	}
}


void Interface::ResizeEvent_(const SDL_Event& event) {
	DEBUG_M("Screen resize %dx%d...", event.resize.w, event.resize.h);
	width_ = event.resize.w;
	height_ = event.resize.h;

	if(SDL_SetVideoMode(width_, height_, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
		ERROR("SDL: Failed to set video mode: %s", SDL_GetError());
		SDL_Quit();
		throw "SDL setvideo";
	}

	glViewport(0, 0, width_, height_);
	PerspectiveSet_();
}

/**
 * Converts 2D Window x, y cordinates into 3D OpenGL world cordinates
 * @param mx Window X cord.
 * @param my Window Y cord.
 * @param x X cord to set.
 * @param y Y cord to set.
 * @param z Z cord to set.
 */
void Interface::windowToWorld(const int mx, const int my, GLdouble& x, GLdouble& y, GLdouble& z) {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	
	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	GLfloat winX = mx;
	GLfloat winY = my;
	GLfloat winZ;

	winY = viewport[3] - winY;
	glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &x, &y, &z);
}

/**
 * When the left mouse button is clicked.
 * @param event The SDL event structure.
 */
void Interface::HandleMouse1_(const SDL_Event& event) {
	if(!creature_) {
		return;
	}

	Area* area = creature_->getArea();
	switch(mode_) {
		case(MODE_NONE):
			return;
			break;
		case(MODE_EDIT_TILES):
			//area->setTile(gx, gy, tile);
			break;
		case(MODE_EDIT_OBJECTS):
			Model* model = area->getResourceManager()->loadModel("data/models/monkey-robot.dae");
			RigidBody* newobj = new RigidBody;
			newobj->setModel(*model);
			newobj->setShape(new btBoxShape(btVector3(.5,.5,.5)));
			newobj->setPos(-tx_, ty_+1.0f, tz_);
			area->addObject(*newobj);
			break;
	}
}

/**
 * When the middle mouse button is clicked.
 * @param event The SDL event structure.
 */
void Interface::HandleMouse3_(const SDL_Event& event) {
	if(!creature_) {
		return;
	}
	
	//GLdouble x, y, z;
	//windowToWorld(event.button.x, event.button.y, x, y, z);
	
	Area* area = creature_->getArea();

	Model* model = area->getResourceManager()->loadModel("data/models/unmaptest.dae");

	RigidBody* newobj = new RigidBody;
	newobj->setModel(*model);
	newobj->setShape(new btSphereShape(1));
	newobj->setPos(-tx_, ty_+1.0f, tz_);
	
	area->addObject(*newobj);
}

/**
 * Checks for any SDL events that have occured.
 */
void Interface::CheckEvents_() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				finished_ = true;
				break;
			case SDL_KEYDOWN:
				HandleKeyDown_(event);
				break;
			case SDL_KEYUP:
				HandleKeyUp_(event);
				break;
			case SDL_MOUSEMOTION:
				mx_ = event.motion.x;
				my_ = event.motion.y;
				if(cam_move_) {
					camera_.setRotX(camera_.getRotX() + (GLfloat)event.motion.xrel / width_ * 100);
					camera_.setRotY(camera_.getRotY() - (GLfloat)event.motion.yrel / height_ * 100);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				DEBUG_M("Mouse button %d down at (%d, %d)",
					event.button.button, event.button.x, event.button.y);
				
				//windowToWorld(event.button.x, event.button.y, tx_, ty_, tz_);
				if(event.button.button == 3) {
					cam_move_ = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				DEBUG_M("Mouse button %d up at (%d, %d)",
					event.button.button, event.button.x, event.button.y);
				switch(event.button.button) {
					case 1:
						HandleMouse1_(event); break;
					case 2:
						HandleMouse3_(event); break;
					case 3:
						cam_move_ = false; break;
					case 5:
						camera_.setZoom(camera_.getZoomTarget() + ZOOM_STEP); break;
					case 4:
						camera_.setZoom(camera_.getZoomTarget() - ZOOM_STEP); break;
				}
				break;
			case SDL_VIDEORESIZE:
				ResizeEvent_(event);
				break;
			default:
				DEBUG_M("Unknown event occured...");
				break;
		}
	}
}

/**
 * Sets the creature that the interface controls.
 * @param creature The creature to follow and control.
 */
void Interface::setCreature(Creature& creature) {
	creature_ = &creature;
	camera_.setTarget(creature);
}

#warning ['TODO']: The game manager shouldnt be driven by the interface. Either make a seperate thread or a class containing both...
/**
 * Sets the gamemanger that the interface controls.
 * @param gm The game manager
 */
void Interface::setGameManager(GameManager& gm) {
	gm_ = &gm;
}
