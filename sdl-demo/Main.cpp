#include <iostream>
#include "include/Display.hpp"
#include <GL/glew.h>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 400;
const unsigned int WINDOW_XPOS = 400;
const unsigned int WINDOW_YPOS = 200;
const std::string WINDOW_TITLE = "SDL Demo";

// Bool used to determine if the triangles should be drawn
bool drawPrimitives = true;

float centerVertexX = 0.0f;
float bottomVertexX = 1.0f;
float topVertexX = 0.0f;
float movingPoint = -1.0f;
float movingSpeed = 0.02f;

// OpenGL culling mode - can be changed in-game by pressing B
GLenum cullMode = GL_FRONT;

/// <summary>
/// Week 2 exercises.
/// Draws a triangle in CLOCKWISE direction.
/// </summary>
void drawClockwiseTriangle()
{
	// Week 2 - Exercise 3.1:
	//
	// By default an object defined in counter-clockwise direction has its
	// front face facing forward.
	//
	// A clockwise direction object has its back face facing forward, so it
	// won't be visible if we cull the back. Culling must be enabled before
	// drawing.
	//
	// See drawMovingTriangle for a counter-clockwise triangle.
	//
	// glCullFace(GL_BACK);
	// glEnable(GL_CULL_FACE);

	// Week 2 - Exercise 3.2:
	//
	// glCullFace(GL_FRONT);
	// glCullFace(GL_FRONT_AND_BACK)
	// glEnable(GL_CULL_FACE);

	// Week 2 - Exercise 3.0 - Draw in clockwise direction
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(0, -1, 0);

	glColor3f(0, 1, 0);
	glVertex3f(-1, 0, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glEnd();
}

/// <summary>
/// Week 3 exercises.
/// Draws a triangle in COUNTER-CLOCKWISE direction (default).
/// </summary>
void drawMovingTriangle()
{
	// Update values of vertex locations for movement

	// Week 3 exercise 1
	// If location of right vertex is at a boundary, invert it
	if (movingPoint <= -1) movingPoint *= -1;
	movingPoint -= movingSpeed;

	// Week 3 - exercises 2 and 3
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
	// If vertex location is out of boundaries, set it to the nearest boundary
	// (Can happen if movingSpeed is not a multiple of the min/max pos)
	if (topVertexX < -1) topVertexX = -1;
	if (centerVertexX < -1) centerVertexX = -1;
	if (bottomVertexX < -1) bottomVertexX = -1;

	if (topVertexX > 1) topVertexX = 1;
	if (centerVertexX > 1) centerVertexX = 1;
	if (bottomVertexX > 1) bottomVertexX = 1;

	// Draw triangle
	// Begin defining triangle data points
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);					// Define colour of first vertex
	glVertex3f(centerVertexX, 0, 0);	// Define location of first vertex
	glColor3f(0, 1, 0);					// Define colour of second vertex
	glVertex3f(bottomVertexX, 0, 0);	// Define location of second vertex
	// Move the right vertex in the Y axis
	// (week 3 exercise 1 - vertex up and down exercise)
	// glVertex3f(1, movingPoint, 0);
	glColor3f(0, 0, 1);					// Define colour of third vertex
	glVertex3f(topVertexX, 1, 0);		// Define location of third vertex
	// Declare that data points have now finished
	glEnd();
}

/// <summary>
/// Calls our drawing functions.
/// </summary>
void drawTriangles()
{
	// Draw triangles if required
	if (drawPrimitives)
	{
		drawMovingTriangle();
		drawClockwiseTriangle();
	}
}

/// <summary>
/// Main entry point for the game.
/// </summary>
int main(int argc, char* args[])
{
	// Bool used to control when to exit application
	bool exit = false;
	// SDL_event object used to handle user events within the SDL window.
	SDL_Event event;

	SDLDemo::Display display(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	// Start game main loop
	// Continue until the 'exit' variable has been changed to true
	while (!exit)
	{
		// Check for events and handle them if necessary
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				// Exit main loop
				exit = true;
			}
			// Handle keyboard input events
			else if (event.type == SDL_TEXTINPUT)
			{
				// If user pressed the 'T' key, toggle drawing of the triangles
				if (event.text.text[0] == 't')
				{
					drawPrimitives = !drawPrimitives;
				}

				// Week 2 - Exercise 4
				// Toggle face culling modes
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
				// Display a simple message box in SDL
				if (event.text.text[0] == 'p')
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hey", "Hey I'm a message box.", NULL);
				}
			}
		}

		display.clear();
		drawTriangles();
		display.update();
	}
	// End game main loop

	return 0;
}
