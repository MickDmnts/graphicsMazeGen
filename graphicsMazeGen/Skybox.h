#ifndef SKYBOX_H
#define SKYBOX_H

#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <stb_image.h>

#include "Object.h"

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

class Skybox : public Object
{
private:
	unsigned int skyboxTexture;
	unsigned int skyboxVBO, skyboxVAO;

	virtual void SetShaderPaths(const char* vertexPath, const char* fragmentPath)
	{
		shader = Shader(vertexPath, fragmentPath);
	}

	void InitSkybox()
	{
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);

		glBindVertexArray(skyboxVAO);

		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

public:

	Skybox(unsigned int skbTexture)
	{
		SetShaderPaths("Shaders/skyboxVertexShader.vs", "Shaders/skyboxFragmentShader.fs");
		InitSkybox();
		skyboxTexture = skbTexture;
	};

	void UpdateSkyboxShader(glm::mat4 view, glm::mat4 projection)
	{
		glDepthFunc(GL_LEQUAL);

		shader.use();

		shader.setInt("skybox", 0);
		shader.setMat4("view", glm::mat4(glm::mat3(view)));
		shader.setMat4("projection", projection);

		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
		glBindVertexArray(skyboxVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthFunc(GL_LESS);

	}
};
#endif