//This Project is just drawing a triangle and a rectangle.

#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "iostream"
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Window dimensions
const GLuint WIDTH = 1600, HEIGHT = 900;

//Shaders
const GLchar* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";

const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

int main()
{
	//Init GLFW
	glfwInit();
	//Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create a GLFW window object that we can use for GLFW's fuctions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Time to Start", nullptr, nullptr);//Set GLFW ���ô��ڴ�С
	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;//Reset GLEW
	if (glewInit() != GLEW_OK)	//Initialize GLEW to setup the OpenGL Function pointers
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	//Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);//View Port ��Ⱦ���ڵĳߴ��С

	//Set the required callback fuctions
	glfwSetKeyCallback(window, key_callback);

	//Build and compile our shader program
	//Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	//Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	//Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//To draw a triangle
	/*
	//Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		-0.5f, -0.5f,  0.0f,//Left
		 0.5f, -0.5f,  0.0f,//Right
		 0.0f,  0.5f,  0.0f//Top
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);//Unbind VAO (it's always a good thing to unbind an buffer/array to prevent strange bugs)
	*/

	//To draw a rectangle
	//Set up vertex data (and buffer(s)) and attribute pointers
	//GLfloat vertices[] =
	//{
	//	//First triangle
	//	 0.5f,  0.5f,  //Top Right
	//	 0.5f, -0.5f,  //Bottom Right
	//	-0.5f,  0.5f,  //Top Left
	//	//Second triangle
	//	 0.5f, -0.5f,  //Bottom Right
	//	-0.5f, -0.5f,  //Bottom Left
	//	-0.5f,  0.5f   //Top Left
	//};
	GLfloat vertices[] =
	{
		 0.5f,  0.5f,  0.0f,  //Top Right
		 0.5f, -0.5f,  0.0f,  //Bottom Right
		-0.5f, -0.5f,  0.0f,  //Bottom Left
		-0.5f,  0.5f,  0.0f   //Top Left
	};
	GLuint indices[] =
	{
		0, 1, 3,  //First Triangle
		1, 2, 3   //Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);//Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), rementer: do NOT unbind the EBO, keep it bound to this VAO

	//Uncommneting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	while (!glfwWindowShouldClose(window))//Game loop
	{
		glfwPollEvents();//Check Event ����¼�

		//Rendering ��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw our first triangle
		/*
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		*/

		//Draw our first rectangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//Swap Buffers ����������
	}

	//Properly de-allocate all resources once they've outlived their purpose
	//For drawing triangle
	/*
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	*/

	//For drawing rectangle
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//Terminate GLFW, clearing any resources allocated by GLFW
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE&&action == GLFW_PRESS)//Close Window with pressing ESC
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}