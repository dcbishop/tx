#ifndef TX_INTERFACE_HPP
#define TX_INTERFACE_HPP

#include <string>
using namespace std;

#include "SDL.h"

#include "Area.hpp"
#include "Camera.hpp"
#include "Creature.hpp"

class Interface {
	public:
		Interface(const int width, const int height);
		~Interface();
		void SetTitle(const string title);
		void MainLoop();
		void DrawScene();
		void setArea(Area* area);
		void setCreature(Creature* creature);
		void PerspectiveSet();
		void PositionCamera();

	private:
		void HandleKeyDown(const SDL_Event& event);
		void HandleKeyUp(const SDL_Event& event);
		void ResizeEvent(const SDL_Event& event);
		void RotateCamera(const GLfloat x, const GLfloat y);
		void CheckEvents();

		bool finished_;
		int width_;
		int height_;
		Area* area_;

		bool cam_move_;

		int fps_;
		int mpf_;
		bool limit_fps_;
		Camera camera_;
		Creature* creature_;
};

#endif
