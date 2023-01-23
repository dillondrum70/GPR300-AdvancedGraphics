#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <string>
#include <fstream>

#include "Vertex.h"

//void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);

void ReadShader(std::string filename, std::string& contents);

//TODO: Vertex shader source code
/*const char* vertexShaderSource =
"#version 450							\n"
"layout(location = 0) in vec3 vPos;		\n"
"layout(location = 1) in vec4 vColor;	\n"
"out vec4 Color;						\n"
"uniform float _Time;					\n"
"void main(){							\n"
"	Color = vColor;						\n"
"	gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);		\n"
"}										\0";

//TODO: Fragment shader source code
const char* fragmentShaderSource = 
"#version 450							\n"
"out vec4 FragColor;					\n"
"in vec4 Color;							\n"
"uniform float _Time;					\n"
"void main(){							\n"
"	float t = abs(sin(_Time));			\n"
"	FragColor = Color * t;				\n"
"}										\0";*/

//TODO: Vertex data array
/*const float vertexData[] = {
	//x		y	 z	  r    g    b    a
	-0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0,	//Bottom Left
	 0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0,	//Bottom Right
	 0.5,  0.5, 0.0, 0.0, 0.0, 1.0, 1.0,		//Top Right
	 -0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0,	//Bottom Left
	 0.5,  0.5, 0.0, 0.0, 0.0, 1.0, 1.0,		//Top Right
	-0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 1.0		//Top Left
};*/

const Vertex vertexData[] = {
	//x		y	 z	  r    g    b    a
	Vertex{Vec3(-0.5, -0.5, 0.0), Color(1.0, 0.0, 0.0, 1.0)},	//Bottom Left
	Vertex{Vec3(0.5, -0.5, 0.0), Color(0.0, 1.0, 0.0, 1.0)},	//Bottom Right
	Vertex{Vec3(0.5,  0.5, 0.0), Color(0.0, 0.0, 1.0, 1.0)},	//Top Right
	Vertex{Vec3(-0.5, -0.5, 0.0), Color(1.0, 0.0, 0.0, 1.0)},	//Bottom Left
	Vertex{Vec3(0.5,  0.5, 0.0), Color(0.0, 0.0, 1.0, 1.0)},	//Top Right
	Vertex{Vec3(-0.5, 0.5, 0.0), Color(0.0, 1.0, 0.0, 1.0)}	//Top Left	
};

const std::string VERTEX_SHADER_FILEPATH = "./Shaders/default.vert";
const std::string FRAGMENT_SHADER_FILEPATH = "./Shaders/default.frag";

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGLExample", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	
	//TODO: Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Read in contents of vertex shader file
	std::string contents;
	ReadShader(VERTEX_SHADER_FILEPATH, contents);
	const char* vertexShaderSource = contents.c_str();
	printf("Vertex Shader: \n\n %s \n", vertexShaderSource);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//TODO: Get vertex shader compilation status and output info log
	GLint vertSuccess;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertSuccess);

	if (!vertSuccess)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Failed to compile vertex shader: %s", infoLog);
	}
	
	//TODO: Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Read in contents of fragment shader file
	contents = "";
	ReadShader(FRAGMENT_SHADER_FILEPATH, contents);
	const char* fragmentShaderSource = contents.c_str();
	printf("Fragment Shader: \n\n %s \n", fragmentShaderSource);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//TODO: Get fragment shader compilation status and output info log
	GLint fragSuccess;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);

	if (!fragSuccess)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("Failed to compile fragment shader: %s", infoLog);
	}

	//TODO: Create shader program
	GLuint shaderProgram = glCreateProgram();

	//TODO: Attach vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//TODO: Link shader program
	glLinkProgram(shaderProgram);

	//TODO: Check for link status and output errors
	GLint shaderProgramSuccess;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramSuccess);

	if (!shaderProgramSuccess)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Failed to link shader program: %s", infoLog);
	}

	//TODO: Delete vertex + fragment shader objects
	//glDeleteShader(...)

	//TODO: Create and bind Vertex Array Object (VAO)
	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//TODO: Create and bind Vertex Buffer Object (VBO), fill with vertexData
	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//TODO: Define vertex attribute layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
	glEnableVertexAttribArray(0); //enable this vertex attribute

	//Color (4 floats, rgba)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(Vec3)));
	glEnableVertexAttribArray(1); //enable this vertex attribute

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO:Use shader program
		glUseProgram(shaderProgram);

		//Set Uniforms
		float time = (float)glfwGetTime();
		GLint  timeLocation = glGetUniformLocation(shaderProgram, "_Time");
		glUniform1f(timeLocation, time);
		
		Vec3 offset = Vec3(std::cos(time) / 2, std::sin(time) / 2, 0.0f);
		GLint  offsetLocation = glGetUniformLocation(shaderProgram, "_Offset");
		glUniform3f(offsetLocation, offset.x, offset.y, offset.z);
		
		//TODO: Draw triangle (3 indices!)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ReadShader(std::string filename, std::string& contents)
{
	std::ifstream fin;
	fin.open(filename);

	if (fin.fail())
	{
		contents = "Shader failed to open\n\0";
		return;
	}

	std::string currentLine = "";
	while (std::getline(fin, currentLine))
	{
		contents.append(currentLine + "\n");
	}

	contents.append("\0");

	fin.close();
}

