#pragma once
#include <GL/glew.h>

class Mesh
{
public:
	Mesh();

	void CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void DeleteMesh();

	~Mesh();
private:
	unsigned int VAO, VBO, IBO;
	GLsizei indexCount;
};

