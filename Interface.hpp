#ifndef TX_INTERFACE_HPP
#define TX_INTERFACE_HPP

#include <string>
using namespace std;

#include "SDL.h"

#include "Area.hpp"
#include "Camera.hpp"

class Interface {
	private:
		bool finished_;
		int width_;
		int height_;
		Area* area_;

		bool cam_move_;

		int fps_;
		int mpf_;
		bool limit_fps_;
		Camera camera_;

	public:
		Interface(const int width, const int height);
		~Interface();
		void SetTitle(const string title);
		void MainLoop();
		void DrawScene();
		void HandleKeys(const SDL_Event& event);
		void ResizeEvent(const SDL_Event& event);
		void RotateCamera(const GLfloat x, const GLfloat y);
		void CheckEvents();
		void setArea(Area* area);
		void PerspectiveSet();
		void PositionCamera();
};

#endif
