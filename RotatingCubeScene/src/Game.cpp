#include "../include/Game.hpp"

OpenGLScene::Game::Game(const unsigned int WIDTH, const unsigned int HEIGHT, const std::string TITLE, const bool SHOW_DEBUG_PANE) :
	m_width(WIDTH), m_height(HEIGHT), m_title(TITLE), m_showDebugPane(SHOW_DEBUG_PANE)
{
	// Use double buffering in our window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Create window
	glutInitWindowSize(m_width, m_height);
	// Set location of window on the monitor
	glutInitWindowPosition(50, 50);
	m_windowID = glutCreateWindow(m_title.c_str());
	glutSetIconTitle(" - Minimized");

	// Setup the DevIL renderer
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);

	// Define wrapping behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Define texture filtering behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Define how material is sent further down the rendering pipeline
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	// Run a depth test to ensure triangles are drawn over each other in the
	// correct order
	glEnable(GL_DEPTH_TEST);
	// Define the rules for the depth test
	// If the new pixel has a depth less than or equal to the curent depth
	// value for that pixel (i.e. the new pixel is closer to the screen) draw
	// the new pixel
	glDepthFunc(GL_LEQUAL);
	// Alternatively, we could draw the new pixel if it closer to the camera than the former one
	// glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	// Lighting setup
	// glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	// Last param: Use the normals from each surface to calculate lighting
	// (FALSE = faster but not as accurate)
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// Enable Lighting (done through keybind in the game (press L))
	// glEnable(GL_LIGHTING);
	// Enable light sources
	glEnable(GL_LIGHT0);
	// Now done through right click menu in the game
	// glEnable(GL_LIGHT1);

	// Light settings
	GLfloat qaAmbientLight[4] = { 0.2f, 0.2f, 0.2f, 1.0f };		// Ambient settings
	GLfloat qaDiffuseLight[4] = { 0.8f, 0.8f, 0.8f, 1.0f };		// Diffuse settings
	GLfloat qaSpecularLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	// Specular settings

	// Light sources' behaviour
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);			// Define ambient light behaviour
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);			// Define diffuse ambient light behaviour
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);			// Define specular light behaviour

	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

	// Include to make the light a directional spotlight
	// GLfloat dirVector[] = { 0.8f, 0.8f, -1.0f };				// Create vector to hold spot light direction 
	// glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirVector);		// Set direction on spotlight on light0
	// glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);				// Define angle of spotlight
	// glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.5f);				// Intensity of the the distribution of light within the cone
	// GLfloat qaLightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// vector to store location of light0
	// glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);		// Set position of light0

	// Light sources' position
	GLfloat qaLight0Position[4] = { 0.5f, 0.5f, 1.0f, 1.0f };		// Array to store location of light0
																	// Top-right
	// GLfloat qaLight0Position[4] = { 0.0f, 0.5f, 0.5f, 1.0f };	// Center
	GLfloat qaLight1Position[4] = { -1.0f, -1.0f, 0.0f, 1.0f };		// Bottom-left
	glLightfv(GL_LIGHT0, GL_POSITION, qaLight0Position);			// Set position of light0
	glLightfv(GL_LIGHT1, GL_POSITION, qaLight1Position);			// Set position of light1
}
