#include <vector>
#include <string>

//Window
unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

GLFWwindow* window;

// time settings
float deltaTime = 0.0f;

//Map info
char** generatedMap = nullptr;
std::string mapPath = "ActiveMap/map01.mmp";

// Cubemap for skybox
std::vector<std::string> cubeFaces
{
	"Textures/skybox/right.jpg",
	"Textures/skybox/left.jpg",
	"Textures/skybox/top.jpg",
	"Textures/skybox/bottom.jpg",
	"Textures/skybox/front.jpg",
	"Textures/skybox/back.jpg",
};

float skyboxVertices[] =
{
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

std::vector<std::string> modelPaths
{
	"Models/backpack/backpack.obj",
	"Models/tower/Medieval_tower_High.obj",
	"Models/aircraft/E 45 Aircraft_obj.obj",
	"Models/nanosuit/nanosuit.obj",
	"Models/plant/indoor plant_02.obj",
};

std::vector<glm::vec3> modelScales
{
	glm::vec3(0.5f),
	glm::vec3(0.5f),
	glm::vec3(0.5f),
	glm::vec3(0.5f),
	glm::vec3(0.5f),
};