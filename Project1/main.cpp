///////////////////////////////////////////
////Type your name and student ID here/////
////Name: Romario Timothy Vaz
////Student ID: 1155085563

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using glm::vec3;
using glm::mat4;

GLint programID;

float x_delta = 0.1f;
float rotate_value = 0.0f;
float whole_rotate_value = 0.0f;
int x_press_num = 0;
float scale_factor = 1;

GLuint vaoID;
GLuint vboID;
GLuint elementbuffer;
GLuint vaoID2;
GLuint vboID2;
GLuint elementbuffer2;



bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	//adapter[0] = vertexShaderCode;
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	//adapter[0] = fragmentShaderCode;
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
}

void keyboard(unsigned char key, int x, int y)
{
	//TODO:
	if (key == 'a')
	{
		x_press_num -= 1;
	}
	if (key == 'd')
	{
		x_press_num += 1;
	}
	if (key == 'w')
	{
		scale_factor += 0.1;
	}
	if (key == 's')
	{
		scale_factor -= 0.1;
	}
	if (key == 'q')
	{
		rotate_value -= 0.1;
	}
	if (key == 'e')
	{
		rotate_value += 0.1;
	}
	if (key == 'r')
	{
		whole_rotate_value -= 0.1;
	}
	if (key == 't')
	{
		whole_rotate_value += 0.1;
	}

}

void sendDataToOpenGL()
{
	//TODO:
	//create point, line, 2D object and 3D object here and bind to VAOs & VBOs
	const GLfloat triangle[] =
	{
		-0.9f, +0.0f, -0.9f, //ground coordinates 0 to 3
		+0.0f, +0.5f, +0.0f,
		+0.9f, +0.0f, -0.9f,
		+0.0f, +0.5f, +0.0f,
		-0.9f, +0.0f, +0.9f,
		+0.0f, +0.5f, +0.0f,
		+0.9f, +0.0f, +0.9f,
		+0.0f, +0.5f, +0.0f,


		// house coordinates 4 to 17

		//base of house coordinates 4 to 7
		-0.7f, +0.01f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.2f, +0.01f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.7f, +0.01f, +0.2f,
		+0.0f, +0.0f, +0.9f,
		-0.2f, +0.01f, +0.2f,
		+0.0f, +0.0f, +0.9f,

		// top of house coordinates 8 to 11
		-0.7f, +0.5f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.2f, +0.5f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.7f, +0.5f, +0.2f,
		+0.0f, +0.0f, +0.9f,
		-0.2f, +0.5f, +0.2f,
		+0.0f, +0.0f, +0.9f,

		//roof coordinates 12 to 13

		-0.45f, +0.8f, +0.7f,
		+0.9f, +0.0f, +0.0f,
		-0.45f, +0.8f, +0.2f,
		+0.9f, +0.0f, +0.0f,

		//door coordinates 14 to 17
		-0.55f, +0.01f, +0.71f,
		+0.9f, +0.4f, +0.1f,
		-0.35f, +0.01f, +0.71f,
		+0.9f, +0.4f, +0.1f,
		-0.55f, +0.3f, +0.71f,
		+0.9f, +0.4f, +0.1f,
		-0.35f, +0.3f, +0.71f,
		+0.9f, +0.4f, +0.1f,


	};

	const GLfloat ground[] =
	{
		-1.9f, +0.0f, -1.9f, //ground coordinates 0 to 3
		+0.0f, +0.5f, +0.0f,
		+1.9f, +0.0f, -1.9f,
		+0.0f, +0.5f, +0.0f,
		-1.9f, +0.0f, +1.9f,
		+0.0f, +0.5f, +0.0f,
		+1.9f, +0.0f, +1.9f,
		+0.0f, +0.5f, +0.0f,
	};

	const GLfloat house[]= 
	{
		// house coordinates 4 to 17

		//base of house coordinates 4 to 7
		-0.7f, +0.01f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.2f, +0.01f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.7f, +0.01f, +0.2f,
		+0.0f, +0.4f, +0.9f,
		-0.2f, +0.01f, +0.2f,
		+0.0f, +0.4f, +0.9f,

		// top of house coordinates 8 to 11
		-0.7f, +0.5f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.2f, +0.5f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.7f, +0.5f, +0.2f,
		+0.0f, +0.4f, +0.9f,
		-0.2f, +0.5f, +0.2f,
		+0.0f, +0.4f, +0.9f,

		//roof coordinates 12 to 13

		-0.45f, +0.8f, +0.7f,
		+0.9f, +0.0f, +0.0f,
		-0.45f, +0.8f, +0.2f,
		+0.9f, +0.0f, +0.0f,

		//door coordinates 14 to 17
		-0.55f, +0.01f, +0.71f,
		+0.9f, +0.4f, +0.1f,
		-0.35f, +0.01f, +0.71f,
		+0.9f, +0.4f, +0.1f,
		-0.55f, +0.3f, +0.71f,
		+0.9f, +0.4f, +0.1f,
		-0.35f, +0.3f, +0.71f,
		+0.9f, +0.4f, +0.1f,


	};


	const GLfloat tree[] =
	{
		// 2D tree coordinates

		//base of house coordinates 4 to 7
		-0.7f, +0.01f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.2f, +0.01f, +0.7f,
		+0.0f, +0.0f, +0.9f,
		-0.7f, +0.01f, +0.2f,
		+0.0f, +0.4f, +0.9f,
		-0.2f, +0.01f, +0.2f,
		+0.0f, +0.4f, +0.9f,


	};

	unsigned int groundIndices[] = { 0, 1, 2, 2, 3, 1 };
	unsigned int houseIndices[] = { 4, 5, 6, 6, 7, 5, 8, 9, 10, 10, 11, 9, 8, 4, 6, 6, 8, 10, 8, 9, 4, 4, 5, 9, 5, 7, 9, 9, 11, 7, 10, 11, 7, 7, 6, 10, 8, 12, 9, 10, 13, 11, 12, 13, 9, 9, 11, 13, 12, 13, 10, 10, 8, 12, 14, 15, 16, 16, 17, 15 };



	vector<unsigned int> gIndices(groundIndices, groundIndices + sizeof(groundIndices) / sizeof(groundIndices[0]));
	vector<unsigned int> hIndices(houseIndices, houseIndices + sizeof(houseIndices) / sizeof(houseIndices[0]));
	
	vector<unsigned int> indices;

	indices.reserve(gIndices.size() + hIndices.size()); // preallocate memory
	indices.insert(indices.end(), gIndices.begin(), gIndices.end());
	indices.insert(indices.end(), hIndices.begin(), hIndices.end());
	//vector<unsigned int> indices(intIndices, intIndices + sizeof(intIndices) / sizeof(intIndices[0]));


	// This for loop is used because initially I created the objects using a single array of vertices, but later split
	// the array into many arrays. Therefore, the loop is used to correct the indices to fit the new style.
	for (auto i = hIndices.begin(); i != hIndices.end(); ++i)
	{
		*i-=4;
		cout << *i << ' ';
	}

	const GLfloat triangle2[] =
	{
	-0.5f, -0.5f, +0.0f, //left
	+0.0f, +0.0f, +1.0f, //color

	+0.5f, -0.5f, +0.0f, //right
	+0.0f, +0.0f, +1.0f,

	+0.0f, +0.5f, +0.0f, //top
	+0.0f, +0.0f, +1.0f,


	};

	// Putting post-split stuff here

	//GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);  //first VAO
							   //GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STATIC_DRAW);


	//GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, gIndices.size() * sizeof(unsigned int), &gIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));



	// Experimenting with multiple objects here

	glGenVertexArrays(1, &vaoID2);
	glBindVertexArray(vaoID2);  //first VAO
								//GLuint vboID;
	glGenBuffers(1, &vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, vboID2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(house), house, GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, hIndices.size() * sizeof(unsigned int), &hIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer2);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));



	//End of post-split stuff


	/*
	//GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);  //first VAO
	//GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);


	//GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));

	

	// Experimenting with multiple objects here

	glGenVertexArrays(1, &vaoID2);
	glBindVertexArray(vaoID2);  //first VAO
							   //GLuint vboID;
	glGenBuffers(1, &vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, vboID2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);


	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));
	*/
	
	/*GLuint elementbuffer[2];
	glGenBuffers(2, elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, gIndices.size() * sizeof(unsigned int), &gIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[0]);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, hIndices.size() * sizeof(unsigned int), &hIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[1]);
	*/
	/*
	GLuint vaoID2;
	glGenVertexArrays(1, &vaoID2);
	glBindVertexArray(vaoID2);  //second VAO

	GLuint vboID2;
	glGenBuffers(1, &vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, vboID2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));
*/


	/*
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));
	*/


}





void paintGL(void)
{
	//TODO:
	//render your objects and control the transformation here
	glClearColor(0.4f, 0.7f, 0.9f, 1.0f); //specify the background color
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	GLint projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	GLint modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");






	glBindVertexArray(vaoID);

	glm::mat4 modelTransformMatrix = glm::mat4(1.0f);
	glm:mat4 scaleMatrix = glm::scale(mat4(), vec3(scale_factor, scale_factor, scale_factor));

	

	glm::mat4 translate_matrix = glm::translate(glm::mat4(),
		glm::vec3(x_delta * x_press_num, 0.0f, 0.0f));;
	glm::mat4 whole_rotateMatrix = glm::rotate(mat4(), whole_rotate_value, vec3(0, 1, 0));
	modelTransformMatrix *= whole_rotateMatrix;
	modelTransformMatrix *= scaleMatrix;
	modelTransformMatrix *= translate_matrix;
	
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	
	// New stuff adding here





	//glDrawArrays(GL_TRIANGLES, 0, 12); //render primitives from array data
	glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(vaoID2);
	modelTransformMatrix = glm::mat4(1.0f);
	translate_matrix = glm::translate(glm::mat4(),
		glm::vec3(x_delta * x_press_num, 0.0f, 0.0f));;

	glm::mat4 rotateMatrix = glm::rotate(mat4(), rotate_value, vec3(0, 1, 0));
	modelTransformMatrix *= whole_rotateMatrix;
	modelTransformMatrix *= rotateMatrix;
	
	modelTransformMatrix *= scaleMatrix;
	modelTransformMatrix *= translate_matrix;

	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);


	//glDrawArrays(GL_TRIANGLES, 0, 12); //render primitives from array data
	glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, (void*)0);


	// Projections
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)1.0, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 1, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	projectionMatrix *= View;

	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);



	glFlush();
	glutPostRedisplay();
}

void initializedGL(void) //run only once
{
	sendDataToOpenGL();
	installShaders();
}

int main(int argc, char *argv[])
{
	/*Initialization*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Assignment 1");
	glewInit();

	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	initializedGL();
	glutDisplayFunc(paintGL);
	glutKeyboardFunc(keyboard);

	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

	return 0;
}