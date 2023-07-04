#define STB_IMAGE_IMPLEMENTATION

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <stb_image.h>

#include "Globals.h"
#include "Camera.h"
#include "Player.h"
#include "Shader.h"
#include "MapGenerator.h"
#include "UI_Handler.h"

#pragma region VARS
//Input handling
glm::vec3 displacement = glm::vec3(0.0f, 0.0f, -2.0f);
float movementSpeed = 1.0f;

// Mouse position data
float previousX = 0.0f;
float previousY = 0.0f;
bool isFirstFrame = true;

//UI Handling
UI_Handler uiHandler;

//Player info
Camera playerCam;
Player player;
#pragma endregion

#pragma region GLFW_GLAD_INIT
/// <summary>
/// Initializes the GLFW internals
/// </summary>
void GLFW_Init()
{
	//glfw init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

//frame buffer resizing callback
void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);
}

/// <summary>
/// Initialized the GLFW window and then returns it.
/// </summary>
/// <returns>The created app window, or NULL</returns>
GLFWwindow* GLFW_WindowInit()
{
	//Window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Computer Graphics 2023", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window \n";
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	return window;
}

/// <summary>
/// Returns true if GLAD was successfully initialized, false otherwise.
/// </summary>
/// <returns>True if GLAD was succesfully initialized, false otherwise</returns>
bool GLAD_Init()
{
	// glad: load OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to load OpenGL function pointers!" << endl;
		return false;
	}

	return true;
}

/// <summary>
/// Initialized the ImGui Interface and OpenGL connections
/// </summary>
void IMGUI_Init()
{
	//GUI Initialization			
	//IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}
#pragma endregion

#pragma region PROCESS_INPUT
void processInput(GLFWwindow* window)
{
	//Exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//Movement
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		playerCam.HandleKeyboard(LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		playerCam.HandleKeyboard(BACKWARD, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		playerCam.HandleKeyboard(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		playerCam.HandleKeyboard(FORWARD, deltaTime);
	}
}

// Mouse position callback
void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (isFirstFrame)
	{
		previousX = (float)xPos;
		previousY = (float)yPos;
		isFirstFrame = false;
	}

	float xOffset = (float)xPos - previousX;
	float yOffset = (float)yPos - previousY;

	previousX = (float)xPos;
	previousY = (float)yPos;

	playerCam.HandleMouseMovement(xOffset, yOffset, deltaTime);
}

// Scrolling callback
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	playerCam.HandleMouseScroll((float)yOffset);
}
#pragma endregion

#pragma region UTILS
// Face order should follow the rule:
// 0. Right face (+X)
// 1. Left face (-X)
// 2. Top face (+Y)
// 3. Bottom face (-Y)
// 4. Front face (+Z)
// 5. Back face (-Z)
unsigned int loadCubeMap(std::vector<std::string> faces)
{
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	// Texture wrapping properties
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// ---------------------------

	// Texture filtering properties
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ----------------------------

	int width, height, numOfChannels;

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &numOfChannels, 0);

		if (data)
		{
			GLenum format;

			if (numOfChannels == 1)
			{
				format = GL_RED;
			}
			else if (numOfChannels == 3)
			{
				format = GL_RGB;
			}
			else if (numOfChannels == 4)
			{
				format = GL_RGBA;
			}
			else
			{
				std::cout << "TEXTURE FILE " << faces[i] << " FAILED TO LOAD: INCOMPATIBLE NUMBER OF CHANNELS!!" << std::endl;
				stbi_image_free(data);
				continue;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "TEXTURE FILE FAILED TO LOAD FROM PATH " << faces[i] << "!!" << std::endl;
		}

		stbi_image_free(data);
	}

	return textureID;
}
#pragma endregion

int main()
{
	GLFW_Init();

	window = GLFW_WindowInit();
	if (window == NULL)
	{
		glfwTerminate();
	}

	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// Cursor grabbing settings
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!GLAD_Init())
	{
		glfwTerminate();
		return -1;
	}

	IMGUI_Init();

	//Enabling depth testing
	glEnable(GL_DEPTH_TEST);

	Shader mainShader("Shaders/vertexShader.vs", "Shaders/fragmentShader.fs");
	Shader skyboxShader("Shaders/skyboxVertexShader.vs", "Shaders/skyboxFragmentShader.fs");

	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Vertex attribute for Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Vertex attribute for texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//VAO - VBO Unbinding to make the pipeline clearer.
	glBindBuffer(GL_ARRAY_BUFFER, 0); //VBO Unbind
	glBindVertexArray(0); //VAO Unbind

	//Skybox creation
	unsigned int skyboxTexture, skyboxVBO, skyboxVAO;

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	skyboxTexture = loadCubeMap(cubeFaces);

	//Ui handler instantiation
	uiHandler = UI_Handler();

	//Map generator start
	MapGenerator mapGen(mapPath);
	mapGen.ReadGridFromFile(generatedMap);
	mapGen.PrintGrid(generatedMap);

	//WORLD PARSING and OBJECT/MODEL CREATION HERE

	//Player init
	playerCam = Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	player = Player(100, 100);

	while (!glfwWindowShouldClose(window))
	{
		// DeltaTime calculation
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		// handle user input
		processInput(window);

		// Reinitialize frame buffer
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Transform declaration
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(playerCam.fov), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

		// Update view matrix
		view = playerCam.GetViewMatrix();

		mainShader.use();
		mainShader.setVec3("viewPosition", playerCam.position);
		mainShader.setMat4("view", view);
		mainShader.setMat4("projection", projection);
		mainShader.setMat4("model", model);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//UI
		uiHandler.Draw2DCharArrayAsMap(reinterpret_cast<char**>(generatedMap), mapGen.GetRows(), mapGen.GetColumns());
		uiHandler.DrawPlayerInfo(player.GetStats());

		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Skybox updating
		glDepthFunc(GL_LEQUAL);

		skyboxShader.use();

		skyboxShader.setInt("skybox", 0);
		skyboxShader.setMat4("view", glm::mat4(glm::mat3(view)));
		skyboxShader.setMat4("projection", projection);

		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
		glBindVertexArray(skyboxVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthFunc(GL_LESS);

		// glfw: double buffering and polling IO events (keyboard, mouse, etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Resource and GLFW cleanup
	glfwTerminate();

	return 0;
}
