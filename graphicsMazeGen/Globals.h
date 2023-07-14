#include <vector>
#include <string>

//Window width
unsigned int SCR_WIDTH = 1280;
//Window height
unsigned int SCR_HEIGHT = 720;

//Window reference
GLFWwindow* window;

//Delta time for framing
float deltaTime = 0.0f;

//Generated map information
char** generatedMap = nullptr;
//The map path
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

//Skybox vertices
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

//All the model paths of the app
std::vector<std::string> modelPaths
{
	"Models/backpack/backpack.obj",
	"Models/tower/Medieval_tower_High.obj",
	"Models/aircraft/E 45 Aircraft_obj.obj",
	"Models/nanosuit/nanosuit.obj",
	"Models/plant/indoor plant_02.obj",
};

//All the model scales for each model
std::vector<glm::vec3> modelScales
{
	glm::vec3(0.5f),
	glm::vec3(0.5f),
	glm::vec3(0.5f),
	glm::vec3(0.5f),
	glm::vec3(0.5f),
};