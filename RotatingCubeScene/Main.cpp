// Based on https ://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html

#include <iostream>
#include "include/Game.hpp"
#include "include/Camera.hpp"

const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 800;

GLfloat zRotate = 0.0f;			// Current rotation angle
GLfloat rotateSpeed = 0.02f;	// Speed of rotation, used to increment zRotate

GLenum faceCullingMode;
GLint cullingSubMenuID;
GLint lightingSubMenuID;

GLuint myImage;

bool enableCubeRotation = true;
bool enableLighting = false;
bool enableLight0 = true;
bool enableLight1 = false;

OpenGLScene::Camera camera;

/// <summary>
/// Draws a textured cube using OpenGL's immediate mode.
/// </summary>
void drawTexturedCube()
{
	glEnable(GL_TEXTURE_2D);				// Switch on 2D texture mapping, this will overiride any glColor()
	glBindTexture(GL_TEXTURE_2D, myImage);	// Use the suplied 2D texture with any primitive shapes cfeated from this point onwards

	// Lighting colors
	// GLfloat qaGreen[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	// GLfloat qaWhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// GLfloat qaBlue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	// GLfloat qaRed[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

	// Values for emmisve surface
	GLfloat qaEmmission[] = { 0.8f, 0.8f, 0.8f, 1.0f };

	// Setting colors for individual lighting
	// glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlue);		// Reflective colour for ambient light
	// glMaterialfv(GL_FRONT, GL_DIFFUSE, qaWhite);		// Reflective colour for diffuse light
	// glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);	// Colour for specular light
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0f);			// Define how shiney the surface is
	// glMaterialfv(GL_FRONT, GL_EMISSION, qaEmmission);	// Define self illuminating surface behaviour

	// Define a cube

	glBegin(GL_POLYGON);
	// Set vertex color to Red
	// glColor3f(1.0f, 0.0f, 0.0f);
	// Normal for lighting
	glNormal3f(0.0f, 0.0f, 1.0f);
	// Define clockwise
	// Front face  (z = 1.0f)
	glTexCoord2f(0.0, 0.0);			// Assign a UV coordinate for the next vertex
	glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	// Left face (x = -1.0f)
	glBegin(GL_POLYGON);
	// glNormal3f(0.0f, 0.0f, 1.0f);
	// Define anti-clockwise
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	// Top (y = 1.0f)
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	// Back face (z = -1.0f)
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	// Right face (x = 1.0f)
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	// Swich off 2D texture mapping
	glDisable(GL_TEXTURE_2D);
}

/// <summary>
/// Callback display function for GLUT.
/// </summary>
void displayMainWindow()
{
	// Clear depth as well as color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Add perspective view
	glMatrixMode(GL_PROJECTION);	// Switch to projection mode
	glLoadIdentity();				// Reset the view
	// Far cliping plane set to 10.5 so that it just clips the rear of the
	// rotating cube, so that you can see the effect of the clipping.
	gluPerspective(45.0, 1.0, 1.0, 10.5);	// Define the perspective view

	// Switch back to Model view and reset that matrix
	// This is good practice to start the frame in a clean state
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Tell camera where to look at
	camera.look();

	// Create the viewport
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Define scissor area, nothing beyond this will be rendered
	glScissor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Enable the scissor test
	glEnable(GL_SCISSOR_TEST);

	if (enableCubeRotation == true)
	{
		zRotate = zRotate + rotateSpeed;	// Increase the rotation
	}
	glTranslatef(0.0f, 0.0f, -7.0f);	// Push evrything back 7 units from camera

	// Apply rotatation only to the cube
	glPushMatrix();							// Save the current state of the world
	glRotatef(zRotate, 0.0f, 1.0f, 0.0f);	// Apply a rotational effect to the world
	drawTexturedCube();						// Draw the cube at the new position
	glPopMatrix();		// Restore the save state, so that only the cube has been rotated

	glDisable(GL_SCISSOR_TEST);		// Switch off scissor test
	glutSwapBuffers();				// Swap the front/back buffers
	glutPostRedisplay();			// Force the graphics to be displayed
}

void keyboardInputCallback(unsigned char key, int x, int y)
{
	// TODO toggle textures
	switch (key)
	{
		case 'w':
			camera.moveForward();
			break;
		case 's':
			camera.moveBack();
			break;
		case 'a':
			camera.moveLeft();
			break;
		case 'd':
			camera.moveRight();
			break;
		case 'l':
			enableLighting = !enableLighting;
			if (enableLighting == true)
			{
				glEnable(GL_LIGHTING);
			}
			else
			{
				glDisable(GL_LIGHTING);
			}
			break;
		case 'r':
			enableCubeRotation = !enableCubeRotation;
			break;
		default:
			break;
	}

	glutPostRedisplay();
}

// Callback function for main menu of window 1
void mainWindowMenuCallback(GLint menuEntryID)
{
	switch (menuEntryID)
	{
		default:
			break;
	}
}

// Callback function for face culling menu
void faceCullingMenu(GLint menuEntryID)
{
	switch (menuEntryID)
	{
		case 1:
			faceCullingMode = GL_FRONT;
			glCullFace(faceCullingMode);
			glEnable(GL_CULL_FACE);
			break;
		case 2:
			faceCullingMode = GL_BACK;
			glCullFace(faceCullingMode);
			glEnable(GL_CULL_FACE);
			break;
		case 3:
			faceCullingMode = GL_FRONT_AND_BACK;
			glCullFace(faceCullingMode);
			glEnable(GL_CULL_FACE);
			break;
		case 4:
			glDisable(GL_CULL_FACE);
			break;
		default:
			break;
	}
}

// Callback function for lighting menu
void lightingMenu(GLint menuEntryID)
{
	switch (menuEntryID)
	{
		case 1:
			enableLighting = !enableLighting;
			if (enableLighting == true)
			{
				glEnable(GL_LIGHTING);
			}
			else
			{
				glDisable(GL_LIGHTING);
			}
			break;
		case 2:
			enableLight0 = !enableLight0;
			if (enableLight0 == true)
			{
				glEnable(GL_LIGHT0);
			}
			else
			{
				glDisable(GL_LIGHT0);
			}
			break;
		case 3:
			enableLight1 = !enableLight1;
			if (enableLight1 == true)
			{
				glEnable(GL_LIGHT1);
			}
			else
			{
				glDisable(GL_LIGHT1);
			}
			break;
		default:
			break;
	}
}

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	OpenGLScene::Game game(WINDOW_WIDTH, WINDOW_HEIGHT, "Rotating Cube");
	myImage = ilutGLLoadImage("assets/box.bmp"); // Load our texture image with ILUT and store it

	// Register GLUT callbacks
	// glutMouseFunc(mouseInputCallback);
	glutKeyboardFunc(keyboardInputCallback);
	glutDisplayFunc(displayMainWindow);

	// Face culling sub-menu
	cullingSubMenuID = glutCreateMenu(faceCullingMenu);
	glutAddMenuEntry("Display front-faces only", 1);
	glutAddMenuEntry("Display back-faces only", 2);
	glutAddMenuEntry("Display no faces (cull front and back)", 3);
	glutAddMenuEntry("Disable culling (display all faces)", 4);

	// Lighting sub-menu
	lightingSubMenuID = glutCreateMenu(lightingMenu);
	glutAddMenuEntry("Toggle lighting (can also press L)", 1);
	glutAddMenuEntry("Toggle light source 0 (GL_LIGHT0)", 2);
	glutAddMenuEntry("Toggle light source 1 (GL_LIGHT1)", 3);

	// Window 1 menu
	glutCreateMenu(mainWindowMenuCallback);
	glutAddSubMenu("Face culling", cullingSubMenuID);
	glutAddSubMenu("Lighting", lightingSubMenuID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Start the GLUT processing main loop
	glutMainLoop();
	return 0;
}
