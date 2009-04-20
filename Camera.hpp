#ifndef TX_CAMERA_HPP
#define TX_CAMERA_HPP

#include "Object.hpp"
#include "DynamicFloat.hpp"

const float PI = 3.14152f;

const float Y_MIN = 0.01f;
const float Y_MAX = 75.0f-Y_MIN;

const float ZOOM_STEP = 0.5f;
const float ZOOM_MIN = 0.5f;
const float ZOOM_MAX = 20.0f;
const float ZOOM_SPEED = 3.0f;
const float ZOOM_THRESHOLD = 0.001f;

/**
 * A camera.
 */
class Camera : public Object {
	public:
		Camera(string tag = DEFAULT_TAG);
		~Camera();
		void update(const int time);
		void setTarget(Object& object);
		GLfloat getFov();
		void setZoom(const GLfloat zoom);
		GLfloat getZoom();
		GLfloat getZoomTarget();
		void Position();
		void setRotX(const GLfloat rx);
		void setRotY(const GLfloat ry);
		void setFov(const float fov);

	private:
		Object* target_;
		DynamicFloat fov_;
		DynamicFloat zoom_;
};

#endif
