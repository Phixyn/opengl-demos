// An example of a shader program where the shaders are stored as seperate
// text files which must be read into an array of characters before being 
// passed to the shader program

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glut.h>

GLint giXRes = 400;
GLint giYRes = 400;
GLint window1ID;
GLuint sID;
GLuint vbo = 0; // Used to store the vertex buffer object
GLuint vao = 0; // Used to store the vertex array object

float points[] = {		// three vertices used to draw a triagle
	0.0f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f
};

char *vs = NULL;	// Pointer to a Charcter array for the vertext shader
char *fs = NULL;	// Pointer to a character array for the fragment shader

					//////////////////////////////////////////////////////////////////////////////
					// shaderCompilerCheck()
					//
					// Function to check the shader has been compiled correctly
					// Outputs any compile errors in the shader to the command line window
					//////////////////////////////////////////////////////////////////////////////
void shaderCompilerCheck(GLuint ID) {
	GLint comp;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);  // Return the compile status from the shader

	if (comp == GL_FALSE) {		// If shader failed to compile, print the error message
		printf("Shader Compilation FAILED");
		GLchar messages[256];
		glGetShaderInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}

//////////////////////////////////////////////////////////////////////////////
// shaderLinkCheck()
//
// Function to check the shader has been linked to the main application correctly
// Outputs any compile errors in the shader to the command line window
//////////////////////////////////////////////////////////////////////////////
void shaderLinkCheck(GLuint ID) {
	GLint linkStatus, validateStatus;
	glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus); // Return the linker status from the shader

	if (linkStatus == GL_FALSE) {	// If shader failed to link, print the error message
		printf("Shader Linking FAILED\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}

	glValidateProgram(ID);	// Check to see if the application can be executed.

	glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus); // Return the result of the validation process.

	if (validateStatus == GL_FALSE) {	// If application failed to validate, print the error message
		printf("Shader Validation FAILED\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}

//////////////////////////////////////////////////////////////////////////////
// shaders()
//
// Function to create the vertex and fragment shaders
//////////////////////////////////////////////////////////////////////////////
void shaders()
{
	const char* vertex_shader =
		"#version 430\n"
		"in vec3 vp;"
		"void main() {"
		" gl_Position = vec4(vp, 1.0);"
		"}";
	const char* fragment_shader =
		"#version 430\n"
		"out vec4 frag_colour;;"
		"void main() {"
		" frag_colour = vec4( 0.0, 0.0, 1.0, 1.0 );"
		"}";

	sID = glCreateProgram();	// Create the main program

	GLuint vID = glCreateShader(GL_VERTEX_SHADER);	// Create an empty vertex shader program
	GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);// Create an empty fragment shader program

	glShaderSource(vID, 1, &vertex_shader, NULL); // Load vertex from local var
	glShaderSource(fID, 1, &fragment_shader, NULL); // Load fragment from local var

	glCompileShader(vID);	// Compile the vertex shader
	glCompileShader(fID);	// Compile the fragment shader

	shaderCompilerCheck(vID);	// Check for compile errors in the vertext shader
	shaderCompilerCheck(fID);	// Check for compile errors in the fragment shader

	glAttachShader(sID, vID);	// Attached the vertex shader to the main program
	glAttachShader(sID, fID);	// Attached the fragment shader to the main program

	glLinkProgram(sID);	// Send the vertex shader program to the GPU vertex processor, and the fragment shader program to the GPU fragment processor

	shaderLinkCheck(sID);	// Check for Linker errors


	glGenBuffers(1, &vbo);				// Create a buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // Make the buffer object a vertex array
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);  //Set the size of the buffer, and insert the data
	glGenVertexArrays(1, &vao);			// Generate a name for the vertex array
	glBindVertexArray(vao);				// Bind the vertex arary object (also seemed to have mem impact)
	glEnableVertexAttribArray(0);		// Now enable the vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // Apply some properties to the vertices. Lookup this command in documentation for more details

	glUseProgram(0);	//Unbind the shader program
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 6.0, 0.0, 0.0, 0.0, -7.0, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, -7.0f);

	glClearColor(0.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(sID);	// Use shader program which has already been setup in main()

	glDrawArrays(GL_TRIANGLES, 0, 3);	// Use the first 3 vertices from position 0 to draw a triangle

	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(giXRes, giYRes);
	glutCreateWindow("Shader Example");
	initGL();
	glewInit();

	// Check if OpenGL Shading Language is available
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else
	{
		printf("No GLSL support\n");
		exit(1);
	}

	shaders();	// Create the shader programs

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}
