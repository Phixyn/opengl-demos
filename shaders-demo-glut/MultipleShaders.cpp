// Week 10 lecture

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glut.h>
#include "textfile.h"	

GLint giXRes = 400;
GLint giYRes = 400;
GLint window1ID;
GLuint sID;
GLuint vbo = 0;
GLuint vao = 0;

float points[] = {
	0.0f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f
};

//////////////////////////////////////////////////////////////////////////////////////////
// VERTEX ATTRIBUTES
// These variables will become attributes (properties) of the vertices

// This is the position for each vertex
float positionData[] = {
	-0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f,
	0.0f, 0.8f, 0.0f };

// This is the color value for each vertex
float colorData[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f };

// handle to the vertex array object:
GLuint vaoHandle;
//////////////////////////////////////////////////////////////////////////////////////////

char *vs = NULL;
char *fs = NULL;


void shaderCompilerCheck(GLuint ID) {
	GLint comp;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);

	if (comp == GL_FALSE) {
		printf("Shader Compilation FAILED");
		GLchar messages[256];
		glGetShaderInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}


void shaderLinkCheck(GLuint ID) {
	GLint linkStatus, validateStatus;
	glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE) {
		printf("Shader Linking FAILED\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}

	glValidateProgram(ID);

	glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);

	if (validateStatus == GL_FALSE) {
		printf("Shader Validation FAILED\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}


void shaders()
{
	sID = glCreateProgram();

	GLuint vID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("Wk10-1 Vertex.vert");
	fs = textFileRead("Wk10-1 Fragment.frag");


	//////////////////////////////////////////////////////////////////////////////////////////
	// Bind index 0 to the shader input variable "VertexPosition" which is an "IN" variable defined in the vertex shader file
	glBindAttribLocation(sID, 0, "VertexPosition");
	// Bind index 1 to the shader input variable "VertexColor" which is an "IN" variable defined in the vertex shader file
	glBindAttribLocation(sID, 1, "VertexColor");

	// Create the buffer objects and create two references to the buffer handles
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint posBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];

	// Populate the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, posBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData,
		GL_STATIC_DRAW);

	// Populate the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

	// Create and set-up the vertex array object
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	// Enable the vertex attribute arrays
	glEnableVertexAttribArray(0); // Vertex position
	glEnableVertexAttribArray(1); // Vertex color
								  // Map index 0 to the position buffer

	glBindBuffer(GL_ARRAY_BUFFER, posBufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

	// Map index 1 to the color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
	//////////////////////////////////////////////////////////////////////////////////////////



	glShaderSource(vID, 1, &vs, NULL);
	glShaderSource(fID, 1, &fs, NULL);

	glCompileShader(vID);
	glCompileShader(fID);

	shaderCompilerCheck(vID);
	shaderCompilerCheck(fID);

	glAttachShader(sID, vID);
	glAttachShader(sID, fID);

	glLinkProgram(sID);

	shaderLinkCheck(sID);

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

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(sID);

	//////////////////////////////////////////////////////////////////////////////////////////
	//bind to the vertex array object and call glDrawArrays to initiate rendering
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//////////////////////////////////////////////////////////////////////////////////////////

	glUseProgram(0);

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

	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else
	{
		printf("No GLSL support\n");
		exit(1);
	}

	shaders();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}