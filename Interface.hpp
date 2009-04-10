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
		virtual void SetTitle(const string title);
		virtual void MainLoop();
		virtual void Draw();
		virtual void setArea(Area* area);
		virtual void setCreature(Creature* creature);
		virtual void PerspectiveSet();
		void PositionCamera();
		virtual void windowToWorld(int mx, int my, GLdouble* x, GLdouble* y, GLdouble* z);


	private:
		void HandleKeyDown(const SDL_Event& event);
		void HandleKeyUp(const SDL_Event& event);
		void HandleMouse1(const SDL_Event& event);
		void HandleMouse3(const SDL_Event& event);

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
