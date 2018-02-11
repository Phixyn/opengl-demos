// Based on https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html

#include <glut.h>
#include <iostream>

GLfloat zRotate = 0;		//Current Rotation angle
GLfloat rotateSpeed = 0.20f;// Speed of rotation, used to increment zRotate
							// GLfloat panSpeed = 0.005f;	// Controls how much the object pans
GLfloat panSpeed = 0.1f;
GLfloat moveSpeed = 0.1f; // Move speed for camera Z axis
GLint giXRes = 800;			// X axis resolution
GLint giYRes = 800;			// Y axis resolution
GLint window1ID;			// The ID number of window 1
GLint window2ID;			// The ID number of window 2
GLint window3ID;			// The ID number of window 3
GLint cullingSubMenuID;
GLfloat xPan = 0.0;			// Where the pan starts
GLfloat zEye = 0.0;
GLfloat xPanMax = 3.0;		// When to reverse the pan

bool displayTriangle1 = true;
bool displayTriangle2 = false;
bool displaySquare = true;
GLenum triangleCullMode;

void drawCube() {
	// Define a cube, each face has a different colour
	glBegin(GL_QUADS);

	// Define vertices in counter-clockwise (CCW) order so that normal points outwards
	glColor3f(0.0f, 1.0f, 0.0f);		// Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);		// Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);		// Red

	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);		// Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);		// Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

}


void displayWin1() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Add perspective view
	glMatrixMode(GL_PROJECTION);	// Switch to projection mode
	glLoadIdentity();				// Reset the view
	// Define the perspective view
	// Note that the far cliping plane is set to 10.5 so that it just clips the rear of the
	// rotating cube, so that you can see the effect of the clipping.
	gluPerspective(45.0, 1.0, 1.0, 10.5);

	// Switch back to Model view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move x and zeye
	gluLookAt(xPan, 3.0, zEye, xPan, 0.0, -7.0, 0, 1, 0);


	// Pan the camera back and forth - works with LookAt command above when it is un-commented
	// xPan = xPan + panSpeed;
	if (xPan >= xPanMax || xPan <= -xPanMax)
		panSpeed = -panSpeed;

	glViewport(0, 0, giXRes, giYRes);	// Create the viewport
	glScissor(0, 0, giXRes, giYRes);	// Define scissor area, nothing beyond this will be rendered
	glEnable(GL_SCISSOR_TEST);			// Enable the scissor test

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	zRotate = zRotate + rotateSpeed;	// Increase the rotation
	glTranslatef(0.0f, 0.0f, -7.0f);	// Push evrything back 7 units from camera

	// Apply rotatation only to the cube
	glPushMatrix();		// Save the current state of the world
	glRotatef(zRotate, 0.0, 1.0, 0.0);	// Apply a rotational effect to the world
	drawCube();							// Draw the cube at the new position
	glPopMatrix();		// Restore the save state, so that only the cube has been rotated

	// Draw a static square in front of the cube, using trinagles
	// as this is outside the push/pop, the previosu rotate command does not apply to this polygon
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(0.0f, 0.8f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	glDisable(GL_SCISSOR_TEST);		// Switch off scissor test
	glutSwapBuffers();				// Swap the front/back buffers
	glutPostRedisplay();			// Force the graphics to be displayed
}

void displayWin2() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);	// Switch to projection mode
	glLoadIdentity();
	// glViewport(0, 0, giXRes, giYRes);
	glViewport(0, 0, giXRes / 2, giYRes / 2);
	// glScissor(0, 0, giXRes, giYRes);
	// glEnable(GL_SCISSOR_TEST);

	// glViewport(xMin, yMin, width, height)
	//	– xMin, yMin = lower left corner of viewport.

	/* Triangle 1 */
	if (displayTriangle1)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
	}

	glViewport(giXRes / 2, giYRes / 2, giXRes / 2, giYRes / 2);

	/* Triangle 2 */
	if (displayTriangle2)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glEnd();
	}

	/* Square */
	if (displaySquare)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glColor3f(0.0f, 0.8f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glEnd();
	}

	// glDisable(GL_SCISSOR_TEST);	// Switch off scissor test
	glutSwapBuffers();				// Swap the front/back buffers
	glutPostRedisplay();			// Force the graphics to be displayed
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	// Run a depth test to ensure triangles are drawn over each other in the
	// correct order
	glEnable(GL_DEPTH_TEST);
	// Decide the rules for the depth test
	// If the new pixel has a depth less than or equal to the curent depth
	// value for that pixel (ie the new pixel is closer to the screen) draw
	// the new pixel
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
}

void inputCallback(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			// zEye--;
			zEye -= moveSpeed;
			break;
		case 's':
			// zEye++;
			zEye += moveSpeed;
			break;
		case 'a':
			xPan -= panSpeed;
			break;
		case 'd':
			xPan += panSpeed;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

// Callback function for main menu
void myMenu(GLint menuEntryID)
{
	switch (menuEntryID)
	{
		case 1:
			displayTriangle1 = !displayTriangle1;
			break;
		case 2:
			displayTriangle2 = !displayTriangle2;
			break;
		case 3:
			displaySquare = !displaySquare;
			break;
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
			triangleCullMode = GL_FRONT;
			glCullFace(triangleCullMode);
			// TODO check if it's already enabled before calling this again
			glEnable(GL_CULL_FACE);
			break;
		case 2:
			triangleCullMode = GL_BACK;
			glCullFace(triangleCullMode);
			glEnable(GL_CULL_FACE);
			break;
		case 3:
			triangleCullMode = GL_FRONT_AND_BACK;
			glCullFace(triangleCullMode);
			glEnable(GL_CULL_FACE);
			break;
		case 4:
			glDisable(GL_CULL_FACE);
			break;
		default:
			break;
	}
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);

	/* Window 1 */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);		// This defines that we wish to use double duffering
	glutInitWindowSize(giXRes, giYRes);		// Create a window of a specified size
	glutInitWindowPosition(50, 50);			// locate the window at the require position
	window1ID = glutCreateWindow("Window 1 - Rotating Clipped Cube");
	// glutIconifyWindow();
	glutSetIconTitle("Window 1 - Minimized");
	initGL();	// A function to initialise opengl and glut (will only have effect for first window)
	glutKeyboardFunc(inputCallback);
	glutDisplayFunc(displayWin1);	// GLUT requires that you define one function which is used to display the graphics

	/* Window 2 */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(giXRes, giYRes);
	glutInitWindowPosition(250, 250);
	window2ID = glutCreateWindow("Window 2 - Triangles And Some Menus");
	// glutIconifyWindow();
	glutSetIconTitle("Window 2 - Minimized");
	glutSetWindow(window2ID);
	glutDisplayFunc(displayWin2);

	/* Window 2 sub-menu (face culling) */
	cullingSubMenuID = glutCreateMenu(faceCullingMenu);
	glutAddMenuEntry("Display front-faces only", 1);
	glutAddMenuEntry("Display back-faces only", 2);
	glutAddMenuEntry("Display no faces (cull front and back)", 3);
	glutAddMenuEntry("Disable culling (display all faces)", 4);

	/* Window 2 menu */
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Toggle bottom-left triangle", 1);
	glutAddMenuEntry("Toggle top-right triangle", 2);
	glutAddMenuEntry("Toggle square", 3);
	glutAddSubMenu("Face culling", cullingSubMenuID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// initGL();			
	glutMainLoop();	// Start the GLUT processing loop. Only call this once.
	return 0;
}