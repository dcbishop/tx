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
	//gm_ = NULL;
	mode_ = MODE_NONE;
	tm_ = NULL;
	to_ = NULL;
	selectedObject_ = NULL;
	creature_ = NULL;
	rm_ = NULL;
	editor_ = NULL;

	VModel* model = new VModel("cube.dae");
	RigidBody* object = new RigidBody("Object_00", model);
	//Object* object = new Object("Object_00", model);
	object->setShape(new btBoxShape(btVector3(.125,.125,.125)));
	object->setMass(1.0f);
	//Object* object = new Object("Object_00", model);
	to_ = object;
	ts_ = true;

	edit_tiles_.push_back(TILE_VOID);
	edit_tiles_.push_back(TILE_FLOOR);
	edit_tiles_.push_back(TILE_WALL);
	edit_tiles_.push_back("outer corner.dae");
	edit_tiles_.push_back("2 sided wall.dae");
	edit_tiles_.push_back("3 sided wall.dae");
	edit_tiles_.push_back("Pillar.dae");
	edit_tiles_.push_back(TILE_INNERCORNER);
	edit_tiles_.push_back("combined wall + inner corner A.dae");
	edit_tiles_.push_back("combined wall + inner corner B.dae");
	edit_tiles_.push_back("two inner corners.dae");
	edit_tiles_.push_back("opposite inner corners.dae");

	setTitle("Tilxor...");

	editor_ = new Editor();
	editor_->setInterface(this);
	editor_->setEditObject(to_);
	editor_->setEditTile(tm_);
	editor_->show();
	//editor_->processQtEvents();
	//editor_->hide();
}

Interface::~Interface() {
	DEBUG_M("Entering function...");
	delete editor_;
	SDL_Quit();
}

/**
 * Sets the title of the window.
 * @param title
 */
void Interface::setTitle(const string title) {
	DEBUG_M("Entering function...");
	SDL_WM_SetCaption(title.c_str(), NULL);
}

/**
 * Starts the Qt editor interface.
 */
void Interface::startEditor() {
	editor_->show();
	editor_->updateWindow();
}

/**
 * The main rendering and input loop.
 */
void Interface::mainLoop() {
	DEBUG_M("Entering function...");

	while(!finished_) {
		int now = SDL_GetTicks();
		camera_.update(now);

		checkEvents_();
		draw();

#warning ['TODO']: Keep track of game time when paused
		if(creature_) {
			GameManager* gm = creature_->getGameManager();
			if(gm) {
				gm->update(now);
			}
		}

		if(editor_) {
			editor_->processQtEvents();
		}
	}
}

/**
 * Set the OpenGL 3D perspective mode.
 */
void Interface::perspectiveSet__() {
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
	DEBUG_V("Entering function...");
	if(!creature_) {
		return NULL;
	}
	return creature_->getArea();
}

/**
 * Sets the tile currently selected for edit mode.
 * @param filename Filename of model.
 */
void Interface::setEditTile_(const string filename) {
	DEBUG_M("Entering function...");
	tm_ = new Tile(filename);
}

Tile& Interface::getEditTile_() {
	return *tm_;
}

Object& Interface::getEditObject_() {
	return *to_;
}

void Interface::setEditObject_(Object& object) {
	delete(to_);
	to_ = &object;
}


void Interface::setEditModeObject() {
	mode_ = MODE_EDIT_OBJECTS;
}

void Interface::setEditModeTiles() {
	mode_ = MODE_EDIT_TILES;
}


/**
 * Renders the scene using OpenGL.
 */
void Interface::draw() {
	static int frame = 0;
	static int last_render_time = 0;
	static int last_fps_time = 0;
	int current_time = SDL_GetTicks();

	// Limit framerate
	if(limit_fps_ && !( (current_time - last_render_time) >= 1000/60) ) {
		return;
	}
	//gm_->update(current_time);
	// Calculate FPS
	frame++;
	if(current_time - last_fps_time > 1000) {
		fps_ = frame*1000.0f/(current_time-last_fps_time);
		last_fps_time = current_time;
		frame = 0;
		LOG("FPS: %d,\tMPF: %d", fps_, mpf_);
		//editor_->updateWindow();
	}
	last_render_time = current_time;

	perspectiveSet__();
	glLoadIdentity();
	camera_.Position();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING) ;
	glEnable(GL_LIGHT0);
	glColor3f(1.0f, 1.0f, 1.0f);
	//glEnable(GL_COLOR_MATERIAL);

	/*ResourceManager& rm = getResourceManager();
	if(!&rm) {
		ERROR("No resource manager set.");
		return;
	}*/

	if(creature_) {
		Area* area = creature_->getArea();
		if(area) {
			area->draw(this);

			if(mode_ != MODE_NONE) {
				windowToWorld(mx_, my_, tx_, ty_, tz_);
			}

			if(mode_ == MODE_EDIT_TILES) {
				int gx, gy;
				area->getGridCord(tx_, tz_, gx, gy);
				float fx, fz;
				area->getWorldCord(gx, gy, fx, fz);

				Tile& tilem = getEditTile_();
				if(&tilem) {
					glPushMatrix();
					glTranslatef(fx , 0.01, fz);
					//RCBC_Render(tilem);
					tilem.draw(this);
					glPopMatrix();
					//area->getResourceManager()->unloadModel(tilem);
				}
			}

			if(mode_ == MODE_EDIT_OBJECTS) {
				//Object& object = getEditObject_();
				Object* object = getSelectedObject();
				if(object) {
					glPushMatrix();
					glTranslatef(tx_, ty_+0.125, tz_);
					object->draw(this);
					//RCBC_Render(&object.getModel());
					glPopMatrix();
				}
			}
			
		}
	}

	glFlush();
	SDL_GL_SwapBuffers();

	mpf_ = SDL_GetTicks() - current_time;
}

void Interface::handleKeyDown_(const SDL_Event& event) {
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

void Interface::handleKeyUp_(const SDL_Event& event) {
	static vector<string>::iterator iter = edit_tiles_.begin();
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
		case SDLK_p:
			ts_ = !ts_;
			LOG("Tile solid: %d", ts_);
			break;
		case SDLK_r:
			tm_->setRotation(tm_->getRotation() + 90.0f);
			break;
		case SDLK_F1:
			LOG("Setting game mode.");
			mode_ = MODE_NONE;
			if(editor_) {
				editor_->hide();
			}
			break;
		case SDLK_F2:
			LOG("Setting tiles edit mode.");
			startEditor();
			setEditTile_(*iter);
			iter++;
			if(iter == edit_tiles_.end()) {
				iter = edit_tiles_.begin();
			}
			mode_ = MODE_EDIT_TILES;
			break;
		case SDLK_F3:
			LOG("Setting objects edit mode.");
			mode_ = MODE_EDIT_OBJECTS;
			startEditor();
			break;
		default:
			break;
	}
}

#warning ['TODO']: Fix bug when height > width
void Interface::resizeEvent(const SDL_Event& event) {
	DEBUG_M("Screen resize %dx%d...", event.resize.w, event.resize.h);
	width_ = event.resize.w;
	height_ = event.resize.h;

	if(SDL_SetVideoMode(width_, height_, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
		ERROR("SDL: Failed to set video mode: %s", SDL_GetError());
		SDL_Quit();
		throw "SDL setvideo";
	}

	glViewport(0, 0, width_, height_);
	perspectiveSet__();
}

/**
 * Converts 2D Window x, y coordinates into 3D OpenGL world coordinates
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
void Interface::handleMouse1_(const SDL_Event& event) {
	if(!creature_) {
		return;
	}

	Tile* tile;
	Area* area = creature_->getArea();
	switch(mode_) {
		case(MODE_NONE):
			return;
			break;
		case(MODE_EDIT_TILES):
			int gx, gy;
			tile =  new Tile(*tm_);
			area->getGridCord(tx_, tz_, gx, gy);
			area->setTile(gx, gy, tile);
			area->setSolid(gx, gy, ts_);
			DEBUG_A("Clicked: %f, %f, %f, gx:%d, gy:%d", tx_, ty_, tz_, gx, gy);
			break;
		case(MODE_EDIT_OBJECTS):
			getSelectedObject()->setXYZ(tx_, ty_+0.125f, tz_);
			//getGameManager()->registerObject(*getSelectedObject());
			area->addObject(*getSelectedObject());
			mode_ = MODE_NONE;
			editor_->updateWindow();
			break;
	}
}

/**
 * When the middle mouse button is clicked.
 * @param event The SDL event structure.
 */
void Interface::handleMouse3_(const SDL_Event& event) {
	if(!creature_) {
		return;
	}

	//GLdouble x, y, z;
	//windowToWorld(event.button.x, event.button.y, x, y, z);

	Area* area = creature_->getArea();

	//Model* model = area->getResourceManager()->loadModel("unmaptest.dae");

	VModel* model = new VModel("unmaptest.dae");
	RigidBody* newobj = new RigidBody;
	newobj->setVisual(*model);
	newobj->setShape(new btSphereShape(1));
	newobj->setXYZ(-tx_, ty_+1.0f, -tz_);
	
	area->addObject(*newobj);
}

/**
 * Checks for any SDL events that have occured.
 */
void Interface::checkEvents_() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				finished_ = true;
				break;
			case SDL_KEYDOWN:
				handleKeyDown_(event);
				break;
			case SDL_KEYUP:
				handleKeyUp_(event);
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

				if(event.button.button == 3) {
					cam_move_ = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				DEBUG_M("Mouse button %d up at (%d, %d)",
					event.button.button, event.button.x, event.button.y);
				switch(event.button.button) {
					case 1:
						handleMouse1_(event); break;
					case 2:
						handleMouse3_(event); break;
					case 3:
						cam_move_ = false; break;
					case 5:
						camera_.setZoom(camera_.getZoomTarget() + ZOOM_STEP); break;
					case 4:
						camera_.setZoom(camera_.getZoomTarget() - ZOOM_STEP); break;
				}
				break;
			case SDL_VIDEORESIZE:
				resizeEvent(event);
				break;
			default:
				DEBUG_M("Unknown event occured...");
				break;
		}
		editor_->updateWindow();
	}
}

/**
 * Sets the creature that the interface controls.
 * @param creature The creature to follow and control.
 */
void Interface::setCreature(Creature& creature) {
	creature_ = &creature;
	camera_.setTarget(creature);
	editor_->updateWindow();
}

/**
 * Returns the GameManager of the currently controlled creature.
 * @return Pointer to the GameManager.
 */
GameManager* Interface::getGameManager() {
	if(!creature_) {
		return NULL;
	}
	return creature_->getGameManager();
}

/**
 * Sets the ResourceManager that the interface uses.
 * @param rm The ResourceManager
 */
void Interface::setResourceManager(ResourceManager* rm) {
	rm_ = rm;
}

/**
 * Gets the resource manager.
 * @return The resource manager refrence or NULL
 */
ResourceManager* Interface::getResourceManager() {
	return rm_;
}

/**
 * Gets the currently selected Object.
 * @return The selected object or NULL
 */
Object* Interface::getSelectedObject() {
	return selectedObject_;
}

/**
 * Sets the currently selected Object.
 * @param object The Object to select.
 */
void Interface::setSelectedObject(Object* object) {
	selectedObject_ = object;
	editor_->updateWindow();
}
