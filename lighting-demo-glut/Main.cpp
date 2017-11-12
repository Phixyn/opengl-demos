// Based on: Michael Hall

#include <glut.h>

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	////////////////////////////////////////////////////////////////
	// Define the properties of the surfaces on the primitives
	//
	// Remember to remove any glColor commands as the commands below
	// replace the use of glColor with more advanced settings.
	////////////////////////////////////////////////////////////////
	GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 };		// values for green
	GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };		// values for white
	GLfloat qaBlue[] = { 0.0, 0.0, 1.0, 1.0 };		// values for blue
	GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 };		// values for red
	GLfloat qaEmmission[] = { 0.8, 0.8, 0.8, 1.0 }; // values for emmisve surface
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlue);	// Set the reflective colour for ambient light
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qaWhite);	// set the reflective colour for diffuse light
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);	// set the colour for specular light
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);		// define how shiney the surface is
	// glMaterialfv(GL_FRONT, GL_EMISSION, qaEmmission);		// define self illuminating surface behaviour

	// Draw lots of small squares, side by side, to creaet one big square (easier to see effects of lighting across multiple small surfaces, rather than one big surface.
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	const GLfloat kqDelta = .01;
	for (int i = -90; i < 90; ++i) {
		for (int j = -90; j < 90; ++j) {
			glVertex3f(j*kqDelta, i*kqDelta, -.2);
			glVertex3f((j + 1)*kqDelta, i*kqDelta, -.2);
			glVertex3f((j + 1)*kqDelta, (i + 1)*kqDelta, -.2);
			glVertex3f(j*kqDelta, (i + 1)*kqDelta, -.2);
		}
	}
	glEnd();

	glFlush();
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);  // Use the normals from each surface to calculate lighting (FALSE = faster but not as accurate)
	glEnable(GL_LIGHTING);		// Enable Lighting
	glEnable(GL_LIGHT0);		// Create a light called LIGHT0
	glEnable(GL_LIGHT1);

	GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 }; // ambient settings
	GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 }; // diffuse settings
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 }; // specular settings
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);   // Define ambient light behaviour
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);   // Define diffuse ambient light behaviour
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight); // Define specular light behaviour

	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

	////////////////////////////////////////////////////////////////
	// Include to make the light a directional spotlight
	////////////////////////////////////////////////////////////////
	//GLfloat dirVector[] = { 0.8,0.8,-1.0 };	// Create vector to hold spot light direction 
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dirVector);	// Set direction on spotlight on light0
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);			// define angle of spotlight
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.5);			// Intensity of the the distribution of light within the cone
	//GLfloat qaLightPosition[] = { 0.0, 0.0, 0.0, 1.0 };	// vector to store location of light0
	//glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);	// Set position of light0

	////////////////////////////////////////////////////////////////
	// Include to make lightbulb
	////////////////////////////////////////////////////////////////
	GLfloat qaLight0Position[] = { 0.5, 0.5, 0.0, 1.0 };		// vector to store location of light0
																// top-right
	// GLfloat qaLight0Position[] = { 0.0, 0.5, 0.5, 1.0 };		// center
	GLfloat qaLight1Position[]{ -1.0, -1.0, 0.0, 1.0 };			// bottom-left
	glLightfv(GL_LIGHT0, GL_POSITION, qaLight0Position);		// Set position of light0
	glLightfv(GL_LIGHT1, GL_POSITION, qaLight1Position);		// Set position of light1
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 50);
	glutCreateWindow("OpengGL Lights");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	return 0;
}