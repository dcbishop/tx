#ifndef TX_INTERFACE_HPP
#define TX_INTERFACE_HPP

#include <string>
#include <vector>
using namespace std;



#include "SDL.h"
#include "Tile.hpp"
#include "Area.hpp"
#include "Camera.hpp"
#include "Creature.hpp"
#include "GameManager.hpp"
#include "Editor.hpp"

const int MODE_NONE = 0;
const int MODE_SELECT = 1;
const int MODE_EDIT_TILES = 2;
const int MODE_EDIT_OBJECTS = 3;

/**
 * A interface used for playing the game (SDL OpenGL Window and Input).
 */
class Interface {
	public:
		Interface(const int width, const int height);
		~Interface();
		virtual void setTitle(const string title);
		virtual void mainLoop();
		virtual void draw();
		virtual void setCreature(Creature& creature);
		//virtual void setGameManager(GameManager& gm);
		virtual GameManager* getGameManager();
		virtual void windowToWorld(const int mx, const int my, GLdouble& x, GLdouble& y, GLdouble& z);
		Area* getArea();
		ResourceManager* getResourceManager();
		void setResourceManager(ResourceManager* rm);
		void startEditor();

		Object* getSelectedObject();
		void setSelectedObject(Object* object);
		void setEditTileSolid(bool solid);
		void setEditMode(int editMode);
		int getEditMode();
		void setEditTile(const string filename);
		int getComputerTime();


	private:
		void handleKeyDown_(const SDL_Event& event);
		void handleKeyUp_(const SDL_Event& event);
		void handleMouse1_(const SDL_Event& event);
		void handleMouse3_(const SDL_Event& event);
		Tile& getEditTile_();
		Object& getEditObject_();
		void setEditObject_(Object& object);

		void resizeEvent_(const SDL_Event& event);
		void checkEvenisEditTileSolid_();
		void perspectiveSet__();

		bool finished_;
		int width_;
		int height_;
		bool cam_move_;
		int mode_;

		int fps_;
		int mpf_;
		bool limit_fps_;

		Camera camera_;
		Creature *creature_;
		//GameManager *gm_;
		ResourceManager *rm_;
		Editor *editor_;

		// For the coordinates the mouse is targeting
		GLdouble tx_, ty_, tz_;

		// Mouse window coordinates
		int mx_, my_;
		Tile* tm_;
		Object* to_;
		Object* selectedObject_;
		bool isEditTileSolid_;
		//vector<string> edit_tiles_;
};

#endif /* TX_INTERFACE_HPP */
