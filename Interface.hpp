#ifndef TX_INTERFACE_HPP
#define TX_INTERFACE_HPP

#include <string>
using namespace std;

#include "SDL.h"

#include "Area.hpp"
#include "Camera.hpp"
#include "Creature.hpp"

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
		virtual void setCreature(Creature* creature);
		virtual void windowToWorld(const int mx, const int my, GLdouble* x, GLdouble* y, GLdouble* z);


	private:
		void HandleKeyDown_(const SDL_Event& event);
		void HandleKeyUp_(const SDL_Event& event);
		void HandleMouse1_(const SDL_Event& event);
		void HandleMouse3_(const SDL_Event& event);

		void ResizeEvent_(const SDL_Event& event);
		void CheckEvents_();
		void PerspectiveSet_();

		bool finished_;
		int width_;
		int height_;

		bool cam_move_;

		int fps_;
		int mpf_;
		bool limit_fps_;
		Camera camera_;
		Creature* creature_;
};

#endif
