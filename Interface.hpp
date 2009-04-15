#ifndef TX_INTERFACE_HPP
#define TX_INTERFACE_HPP

#include <string>
using namespace std;

#include "SDL.h"

#include "Area.hpp"
#include "Camera.hpp"
#include "Creature.hpp"
#include "GameManager.hpp"

const int MODE_NONE = 0;
const int MODE_EDIT_TILES = 1;
const int MODE_EDIT_OBJECTS = 2;

/**
 * A interface used for playing the game (SDL OpenGL Window and Input).
 */
class Interface {
	public:
		Interface(const int width, const int height);
		~Interface();
		virtual void SetTitle(const string title);
		virtual void MainLoop();
		virtual void Draw();
		virtual void setCreature(Creature& creature);
		virtual void setGameManager(GameManager& gm);
		virtual void windowToWorld(const int mx, const int my, GLdouble& x, GLdouble& y, GLdouble& z);
		Area* getArea();
		ResourceManager* getResourceManager();
		void setEditTile_(const string filename);

	private:
		void HandleKeyDown_(const SDL_Event& event);
		void HandleKeyUp_(const SDL_Event& event);
		void HandleMouse1_(const SDL_Event& event);
		void HandleMouse3_(const SDL_Event& event);
		Tile* getEditTile_();

		void ResizeEvent_(const SDL_Event& event);
		void CheckEvents_();
		void PerspectiveSet_();

		bool finished_;
		int width_;
		int height_;
		bool cam_move_;
		int mode_;
		
		int fps_;
		int mpf_;
		bool limit_fps_;
		
		Camera camera_;
		Creature* creature_;
		GameManager* gm_;
		
		// For the cordinates the mouse is targeting
		GLdouble tx_, ty_, tz_;
		
		// Mouse window cordinates
		int mx_, my_;
		Model* tm_;
};

#endif
