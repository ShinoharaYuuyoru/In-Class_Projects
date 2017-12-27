#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "iostream"
#include "cmath"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Window dimensions
const GLuint WIDTH = 1600, HEIGHT = 900;

//Shaders
const GLchar* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 color;\n"

	"out vec3 ourColor;\n"

	"void main()\n"
	"{\n"
	"gl_Position = vec4(position, 1.0);\n"
	"ourColor = color;\n"
	"}\0";

const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"in vec3 ourColor;\n"
	"out vec4 color;\n"
	//"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	//"color = ourColor;\n"
	"color = vec4(ourColor, 1.0f);\n"
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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "カラフルにしよう！", nullptr, nullptr);//Set GLFW 设置窗口大小
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
	glViewport(0, 0, width, height);//View Port 渲染窗口的尺寸大小

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
	//Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		//Position                // Color
		 0.5f, -0.5f,  0.0f,		  1.0f,  0.0f,  0.0f,	//右下
		-0.5f, -0.5f,  0.0f,		  0.0f,  1.0f,  0.0f,	//左下
		 0.0f,  0.5f,  0.0f,	  0.0f,  0.0f,  1.0f	//顶部
	};
	
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);//Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), rementer: do NOT unbind the EBO, keep it bound to this VAO

	//Uncommneting this call will result in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Return number of vertex attributes supported
	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	cout << "Maximum number of vertex attributes supported: " << nrAttributes << endl;

	while (!glfwWindowShouldClose(window))//Game loop
	{
		glfwPollEvents();//Check Event 检查事件

		//Rendering 渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		////Be sure to activate the shader
		//glUseProgram(shaderProgram);

		////Update the uniform color
		//GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		////Draw the triangle
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		//Draw the triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//Swap Buffers 交换缓冲区
	}

	//Properly de-allocate all resources once they've outlived their purpose
	//For drawing triangle
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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