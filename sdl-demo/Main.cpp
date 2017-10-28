#include <iostream>
#include "include/Display.hpp"
#include <GL/glew.h>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 400;
const unsigned int WINDOW_XPOS = 400;
const unsigned int WINDOW_YPOS = 200;
const std::string WINDOW_TITLE = "SDL Demo";

// Bool used to determine if the triangle should be drawn
bool drawTriangle = true;

float movingPoint = -1.0f;
float centerVertexX = 0.0f;
float bottomVertexX = 1.0f;
float topVertexX = 0.0f;
float movingSpeed = 0.02f;

GLenum cullMode = GL_FRONT;

// Function to display opengGL primitives, this is called from within main()
void drawTriangles()
{
	// Week 2 - Exercise 3.1:
	// By default an object defined in counter clockwise direction has its front face facing forward
	// A clockwise direction object has its back face facing forward, so it won't be visible if we cull the back
	// glCullFace(GL_BACK);
	// Week 2 - Exercise 3.2:
	// glCullFace(GL_FRONT);
	// glCullFace(GL_FRONT_AND_BACK)
	// glEnable(GL_CULL_FACE);

	// Week 3 - Exercise 1:
	if (movingPoint <= -1) movingPoint *= -1;
	movingPoint -= movingSpeed;
	centerVertexX -= movingSpeed;
	// if (bottomVertexX <= -1) bottomVertexX = 1;
	bottomVertexX -= movingSpeed;
	// if (topVertexX <= -1) topVertexX = 0;
	topVertexX -= movingSpeed;

	if (topVertexX <= -1 || centerVertexX <= -1 || bottomVertexX >= 1) {
		// TODO: Top vertex is going down in last frame for some reason
		movingSpeed *= -1;
	}

	// Clamp values before drawing (todo: do this better...)
	if (topVertexX < -1) topVertexX = -1;
	if (centerVertexX < -1) centerVertexX = -1;
	if (bottomVertexX < -1) bottomVertexX = -1;

	if (topVertexX > 1) topVertexX = 1;
	if (centerVertexX > 1) centerVertexX = 1;
	if (bottomVertexX > 1) bottomVertexX = 1;

	if (drawTriangle)		// Draw the triangle if required
	{
		glBegin(GL_TRIANGLES);				// Start to define a set of triangle data points
		glColor3f(1, 0, 0);					// Define colour of first vertex
		glVertex3f(centerVertexX, 0, 0);	// Define location of first vertex

		glColor3f(0, 1, 0);					// Define colour of second vertex
		glVertex3f(bottomVertexX, 0, 0);	// Define location of second vertex
											// glVertex3f(1, movingPoint, 0);	// Move the vertex in the Y axis

		glColor3f(0, 0, 1);				// Define colour of third vertex
		glVertex3f(topVertexX, 1, 0);	// Define location of third vertex
										// glVertex3f(0, movingPoint, 0);
		glEnd();						// Declare that data points have now finished

		// Week 2 - Exercise 3.0 - Clockwise direction
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3f(0, -1, 0);

		glColor3f(0, 1, 0);
		glVertex3f(-1, 0, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glEnd();
	}
}

/// <summary>
/// Main entry point for the game.
/// </summary>
int main(int argc, char* args[])
{
	bool exit = false;  // Variable to control when to exit application
	SDL_Event event;	// Create an event handler. This is used to react to any user events within the SDL window

	// Display() constructor here
	SDLDemo::Display display(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// Main game Loop START
	while (!exit)	// Continue until the 'exit' variable has been changed to true
	{
		while (SDL_PollEvent(&event) != 0)	// Check if there are any events to process
		{
			if (event.type == SDL_QUIT)		// If the current event is a quit (exit) action, change the 'exit' variable to true
			{
				exit = true;
			}
			else if (event.type == SDL_TEXTINPUT)	// If the current event is a text input event 
			{
				if (event.text.text[0] == 't')	// If use pressed the 't' key toggle draw state of the triangle
				{
					drawTriangle = !drawTriangle;
				}

				// Week 2 - Exercise 4
				if (event.text.text[0] == 'b')
				{
					switch (cullMode)
					{
						case GL_FRONT:
							glCullFace(cullMode);
							glEnable(GL_CULL_FACE);
							cullMode = GL_BACK;
							break;
						case GL_BACK:
							glCullFace(cullMode);
							cullMode = 0x0;
							break;
						default:
							glDisable(GL_CULL_FACE);
							cullMode = GL_FRONT;
							break;
					}
				}

				// Week 2 - Exercise 5
				if (event.text.text[0] == 'p')
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hey", "Hey I'm a message box.", NULL);
				}
			}
		}

		display.clear();
		// Execute the drawTriangles() function on each loop of the main game loop
		drawTriangles();
		display.update();
	}
	// Main game Loop END

	return 0;
}
