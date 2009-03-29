#ifndef TX_CAMERA_HPP
#define TX_CAMERA_HPP

#include "Object.hpp"

const float PI = 3.14152f;

const float Y_MIN = 0.01f;
const float Y_MAX = 75.0f-Y_MIN;

const float ZOOM_STEP = 0.5f;
const float ZOOM_MIN = 0.5f;
const float ZOOM_MAX = 20.0f;

class Camera : public Object {
	public:
		Camera();
		~Camera();
		void Draw();
		void Update(int time);
		void setTarget(const Object* object);
		GLfloat getFov();
		void setZoom(GLfloat zoom);
		GLfloat getZoom();
		void Position();
		void setRotX(const GLfloat rx);
		void setRotY(GLfloat ry);

	private:
		const Object* target_;
		GLfloat fov_;
		GLfloat zoom_;
};

#endif
