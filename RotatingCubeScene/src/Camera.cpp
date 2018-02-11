#include "../include/Camera.hpp"

OpenGLScene::Camera::Camera()
{
	m_eyeX = 0.0;
	m_eyeY = 3.0;
	m_eyeZ = 0.0;
	m_centerX = 0.0;
	m_centerY = 0.0;
	m_centerZ = -7.0;
	m_upX = 0.0;
	m_upY = 1.0;
	m_upZ = 0.0;

	m_moveSpeed = 0.1;
}

void OpenGLScene::Camera::look()
{
	// Look at cube from above
	// gluLookAt(0.0, 6.0, 0.0, 0.0, 0.0, -7.0, 0, 1, 0);
	// Look at cube from vertical center
	// gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -7.0, 0, 1, 0);
	// Look at cube from a "decent" center
	gluLookAt(m_eyeX, m_eyeY, m_eyeZ, m_centerX, m_centerY, m_centerZ, m_upX, m_upY, m_upZ);

	// Invert pan speed if camera reaches panning bounds
	/* Not implemented
	if (m_xPan >= m_xPanMax || m_xPan <= -m_xPanMax)
		m_panSpeed = -m_panSpeed;
	*/
}

void OpenGLScene::Camera::moveForward()
{
	m_eyeZ -= m_moveSpeed;
}

void OpenGLScene::Camera::moveBack()
{
	m_eyeZ += m_moveSpeed;
}

void OpenGLScene::Camera::moveLeft()
{
	m_eyeX -= m_moveSpeed;
	m_centerX -= m_moveSpeed;
}

void OpenGLScene::Camera::moveRight()
{
	m_eyeX += m_moveSpeed;
	m_centerX += m_moveSpeed;
}

void OpenGLScene::Camera::setMoveSpeed(GLdouble moveSpeed)
{
	m_moveSpeed = moveSpeed;
}
