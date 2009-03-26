#ifndef TX_INTERFACE_HPP
#define TX_INTERFACE_HPP

#include <string>
using namespace std;

#include "SDL.h"
#include "Area.hpp"

#define PI 3.14152f

#define Y_MIN 0.01f
#define Y_MAX 75.0f-Y_MIN

#define ZOOM_STEP 0.5f
#define ZOOM_MIN 0.5f
#define ZOOM_MAX 20.0f

class Interface {
	private:
		bool finished_;
		int width_;
		int height_;
		Area* area_;

		GLfloat cam_rot_x_;
		GLfloat cam_rot_x_temp_;
		GLfloat cam_rot_y_;
		GLfloat cam_rot_y_temp_;
		GLfloat cam_x_;
		GLfloat cam_y_;
		GLfloat cam_z_;
		GLfloat cam_zoom_;
		GLfloat cam_fov_;
		bool cam_move_;

		int fps_;
		int mpf_;
		bool limit_fps_;

	public:
		Interface(int width, int height);
		~Interface();
		void SetTitle(string title);
		void MainLoop();
		void DrawScene();
		void HandleKeys(SDL_Event& event);
		void ResizeEvent(SDL_Event& event);
		void RotateCamera(GLfloat x, GLfloat y);
		void CheckEvents();
		void setArea(Area* area);
		void PerspectiveSet();
		void PositionCamera();
};

#endif
