#include <iostream>

#include "SDL.h"		// SDL header file
#include <GL/glew.h>	// GLEW header file which provide all the opengGL functionality

using namespace std;

// Define window size and position
int width = 800;
int height = 400;
int xpos = 400;
int ypos = 200;

SDL_Window* window = NULL;	// Create a pointer for the window
SDL_GLContext context;	// Create a context for opengGL

bool drawTriangle = true;	// Bool used to determine if the triangle should be drawn
GLenum cullMode = GL_FRONT;

// float movingPoints[3] = {0, 0, 0};
float movingPoint = -1;
float centerVertexX = 0;
float bottomVertexX = 1;
float topVertexX = 0;
float movingSpeed = 0.02;


////////////////////////////////////////////////////////////////////////////
//
// Function to display opengGL primitives, this is called from within main()
//
////////////////////////////////////////////////////////////////////////////
void display()
{
	// Week 2 - Exercise 1:
	// glClearColor(173.0, 0.0, 186.0, 0.0); // set clear color to purple / pink-ish
	glClear(GL_COLOR_BUFFER_BIT);	// Clear colour buffer

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
		// std::cout << movingPoint << endl;
		// glBeginTransformFeedback
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

////////////////////////////////////////////////////////////////////////////
//
// The main entry point into the application 
//
////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[])
{
	bool exit = false;  // Variable to control when to exit application
	SDL_Event event;	// Create an event handler. This is used to react to any user events within the SDL window

						////////////////////////////////////////////////////////////////////////////
						// SDL Initialisation START         (could be placed in a seperate function)
						////////////////////////////////////////////////////////////////////////////

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);	// Restrict maximum version of opengGL to v4
															// --- Changed this ----
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);	// Restrict minimum version of opengGL to v6

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)	// Initialize ALL features of SDL and get return value to check if this worked
	{
		cout << "Error Intialising SDL: " << SDL_GetError() << "\n";	// Output message if there was an error
	}
	else	// If there was no error, procedd to initialising SDL and OpneGL
	{
		// ---- Do this before initializing SDL ----
		// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);	// Restrict maximum version of opengGL to v4
		// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);	// Restrict minimum version of opengGL to v6

		window = SDL_CreateWindow("Hello Triangle", xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);	// Create an SDL window

		if (window == NULL)	// Output a message if the window was not created properly
		{
			cout << "Error Creating Window: " << SDL_GetError() << "\n";
		}
		else
		{
			context = SDL_GL_CreateContext(window);		// Create the context, this tells SDL which graphics library it is working with

			if (context == NULL)	// Output a message if there was an error with the context
			{
				cout << "Error Creating Context: " << SDL_GetError() << "\n";
			}
			////////////////////////////////////////////////////////////////////////////
			// SDL Initialisation END 
			////////////////////////////////////////////////////////////////////////////
			else
			{
				////////////////////////////////////////////////////////////////////////////
				// opengGL Initialise START          (could be placed in a seperate function)
				////////////////////////////////////////////////////////////////////////////
				GLenum error = GL_NO_ERROR;		// Create an error handler

				glMatrixMode(GL_PROJECTION);	// Make the Projection matrix active. The projection matrix defines the properties of the camera that views the objects in 3D space (zoom, aspect ratio etc)
				glLoadIdentity();				// Load the identity matrix. Because the projection matrix is currently loaded, this resets the projection matrix settings to defaults (ie clears it)

				error = glGetError();			// Check if any errors were generated by previous steps
				if (error != GL_NO_ERROR)
				{
					cout << "Error initializing opengGL";
				}

				glMatrixMode(GL_MODELVIEW);		// Make the Model View matrix active. The modelview matrix defines how your objects are transformed 
				glLoadIdentity();				// Load the identity matrix.  Because the model view matrix is currently loaded, this resets the model view matrix settings to defaults (ie clears it)

				error = glGetError();			// Check if any errors were generated by previous steps
				if (error != GL_NO_ERROR)
				{
					cout << "Error initializing opengGL";
				}
				////////////////////////////////////////////////////////////////////////////
				// opengGL Initialise END 
				////////////////////////////////////////////////////////////////////////////
			}
		}
	}

	SDL_StartTextInput();	// Enable text input through SDL

							////////////////////////////////////////////////////////////////////////////
							// Main game Loop START 
							// Now that all initialisation has taken place, the main game loop can start
							////////////////////////////////////////////////////////////////////////////
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

		display();	// Execute the display() function on each loop of the main game loop

		SDL_GL_SwapWindow(window);	// Refresh the window to show any changes made in the previous display() function
	}
	////////////////////////////////////////////////////////////////////////////
	// Main game Loop END 
	////////////////////////////////////////////////////////////////////////////	

	// The main game loop has now been exited, so we need to clean up

	SDL_StopTextInput();	// Stop text input

	SDL_DestroyWindow(window);  // Destroy the window
	window = NULL;				// Free up the memory used by the window

	SDL_Quit();				// Shutdown SDL

	return 0;
}
