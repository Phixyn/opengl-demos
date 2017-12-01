#include <glut.h>
#include <iostream>

GLint giXRes = 800;			// X axis resolution
GLint giYRes = 800;			// Y axis resolution
GLfloat xPan = 0.0;			// Where the pan starts
GLfloat zEye = 0.0;
GLint window1ID;			// The ID number of window 1

struct Vertex
{
	// Vertex struct for OpenGL
	float x;
	float y;
	float z;
};

// TODO use number of points read as size?
// Array of Vertex objects
Vertex vertexlist[8];

void parseObj()
{
	char ch = '1';
	FILE *fp;	// Pointer to OBJ file to read from
	int read;	// Return value from open file
	GLfloat x, y, z; // Variables used to store in values from the file
	unsigned int linesread = 0; // Counter for lines read

	// Open file for reading
	fopen_s(&fp, "cube.obj", "r");
	if (!fp)
	{
		// If fopen returned null, something most likely went wrong when
		// trying to open the file
		printf("Could not open OBJ file for reading");
		exit(1);
	}

	// Loop through lines in the file until we reach EOF (End Of File)
	while (!(feof(fp)))
	{
		// Use space characters to split values in the line
		// TODO look up fscanf and its return value
		// TODO fscan_f and remove prepocessor definition
		read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
		
		// Store values read into our local variables
		// Only look for lines starting with 'v' for now (vertices)
		if (read == 4 && ch == 'v')
		{
			vertexlist[linesread].x = x;
			vertexlist[linesread].y = y;
			vertexlist[linesread].z = z;
			std::cout << "Vertex stored: ";
			std::cout << vertexlist[linesread].x << ", " << vertexlist[linesread].y << ", " << vertexlist[linesread].z << std::endl;
			linesread++;
		}
	}
}

void initGL() {
	// glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); // Run a depth test to ensure triangles are drawn over each other in the correct order. Comment this line and look at the results.
	glDepthFunc(GL_LEQUAL);  // Decide the rules for the depth test. If the new pixel has a depth less than or equal to the curent depth value for that pixel (ie the new pixel is closer to the screen) draw the new pixel 
	glMatrixMode(GL_PROJECTION);
}

void drawObj()
{
	unsigned int pointcount = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Add perspective view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(2.0, 1.0, 1.0, 2.5);
	gluOrtho2D(1, -1, 1, -1);
	// glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	// Switch back to Model view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Look at cube from above
	gluLookAt(-1.0, 1.0, 0.0, -1.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	glViewport(0, 0, giXRes, giYRes);	// Create the viewport
	// glScissor(0, 0, giXRes, giYRes);	// Define scissor area, nothing beyond this will be rendered
	// glEnable(GL_SCISSOR_TEST);			// Enable the scissor test
	// glClearColor(1.0, 1.0, 1.0, 0.0);
	// glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 1.0f);
	while (pointcount < 8)
	{
		//if (vertexlist[pointcount].x != 0.0)
		//{
			std::cout << "Drawing point: ";
			std::cout << vertexlist[pointcount].x << ", " << vertexlist[pointcount].y << ", " << vertexlist[pointcount].z << std::endl;
			glVertex3f(vertexlist[pointcount].x, vertexlist[pointcount].y, vertexlist[pointcount].z);
			pointcount++;
		//}
	}
	glEnd();

	glutSwapBuffers();				// Swap the front/back buffers
	glutPostRedisplay();			// Force the graphics to be displayed
}

int main(int argc, char** argv)
{
	parseObj();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // This defines that we wish to use double duffering
	// Create a window of a specified size
	glutInitWindowSize(giXRes, giYRes);
	glutInitWindowPosition(50, 50);
	window1ID = glutCreateWindow("OBJ file demo");
	initGL();
	glutDisplayFunc(drawObj);
	glutMainLoop();	// Start the GLUT processing loop

	return 0;
}