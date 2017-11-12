#include <GL/glut.h>  
#include <IL/ilut.h>	// Adds funstionality to load textures

/*
 * For assignment: (move this somewhere else)
 *  - WASD for movement / mouse to look at
 *  - Keybinds to toggle stuff on/off (face culling, "fancy" lighting (maybe texture lighting?))
 *  - Text showing frame counter + other debug stats (that can be togled by menu and/or key)
 *  - Mipmaps
 */

GLint giXRes = 800;
GLint giYRes = 800;
GLfloat zRotate = 0;
GLfloat rotateSpeed = 0.3f;

GLfloat panSpeed = 0.3f;
GLfloat moveSpeed = 0.3f; // Move speed for camera Z axis

// TODO move camera with mouse and/or keyboard
GLfloat xPan = 0.0;			// Where the pan starts
GLfloat zEye = 1.5;

GLuint myImage;


void InitTextures(void)
{
	// Define wrapping behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Define texture Filtering behaviour for material
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	myImage = ilutGLLoadImage("box.bmp");	// Load an image and apply it to the variable myImage

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Define how material is sent further down the rendering pipeline
																// this will become redundant when we start to use shaders
}

void drawSquare() {

	glEnable(GL_TEXTURE_2D);			// Switch on 2D texture mapping, this will overiride any glColor()
	glBindTexture(GL_TEXTURE_2D, myImage); // Use the suplied 2D texture with any primitive shapes cfeated from this point onwards

	glBegin(GL_POLYGON);
	// Define clockwise
	glTexCoord2f(0.0, 0.0);			// Assign a UV c-ordinate for the next vertex
	glVertex3f(-1.0, -1.0, 1.0);

	glTexCoord2f(0.0, 1.0);			// Assign a UV c-ordinate for the next vertex
	glVertex3f(-1.0, 1.0, 1.0);

	glTexCoord2f(1.0, 1.0);			// Assign a UV c-ordinate for the next vertex
	glVertex3f(1.0, 1.0, 1.0);

	glTexCoord2f(1.0, 0.0);			// Assign a UV c-ordinate for the next vertex
	glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);
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

	// TOP?
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

	glBegin(GL_POLYGON);
	// Back?
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	// Right face (x = 1.0f)
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);			// Swich off 2D texture mapping
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xPan, 3.0, zEye, xPan, -1.5, -7.0, 0, 1, 0);

	// glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glTranslatef(0.0f, 0.0f, -5.0f);
	zRotate = zRotate + rotateSpeed;
	glPushMatrix();
	glRotatef(zRotate, 0.0, 0.1, 0.0);
	drawSquare();
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(giXRes, giYRes);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Load a texture");

	/////////////////////////////////////////////
	// Functions to setup the OpenILUT  renderer
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
	/////////////////////////////////////////////

	glFrontFace(GL_CW);		// When defining primitives, the FRONT side is assumed to be created from vertices which are listed in a clockwise direction
	glCullFace(GL_BACK);	// Specify if front or back faces should be culled. only takes effect if glEnable(GL_CULL_FACE) is executed
	// glEnable(GL_CULL_FACE); // Uncomment this line to stop the back face of the QUAD being displayed
	glEnable(GL_DEPTH_TEST);
	InitTextures();			// Custom function to configure the textures

	initGL();
	glutKeyboardFunc(inputCallback);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}