#ifndef OBJECT_H
#define OBJECT_H

#include "Shader.h"

class Object
{
public:
	glm::vec3 Position;
	Shader shader;

	virtual void SetShaderPaths(const char* vertexPath, const char* fragmentPath) = 0;
};
#endif