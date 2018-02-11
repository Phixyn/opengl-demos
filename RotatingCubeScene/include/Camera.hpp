#ifndef CAMERA_H
#define CAMERA_H

#include <glut.h>

namespace OpenGLScene
{
	/// <summary>
	/// TODO
	/// </summary>
	class Camera
	{
		public:
			Camera();
			~Camera() { }

			void look();
			void moveForward();
			void moveBack();
			void moveLeft();
			void moveRight();
			void setMoveSpeed(GLdouble moveSpeed);

		private:
			// Camera position
			GLdouble m_eyeX;
			GLdouble m_eyeY;
			GLdouble m_eyeZ;
			GLdouble m_centerX;
			GLdouble m_centerY;
			GLdouble m_centerZ;
			GLdouble m_upX;
			GLdouble m_upY;
			GLdouble m_upZ;

			// Move speed for camera Z axis
			GLdouble m_moveSpeed;
		
			// Controls camera pan speed (unused atm)
			GLdouble m_panSpeed = 0.1;
			// When to reverse the pan (unused atm)
			GLdouble m_xPanMax = 3.0;
	};
}

#endif
