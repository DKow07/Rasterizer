#pragma once
#include <vector>
#include "Int3.h"
#include "Vertex.h"
#include "OBJLoader.h"
#include "VertexProcessor.h"
#include "Rasterizer.h"
#include "Light.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool loadMesh(std::string fileName);
	void drawMesh(Rasterizer& rasterizer, VertexProcessor& vp, Light& light, bool f1);
	void drawMesh(Rasterizer& rasterizer, VertexProcessor& vp, std::vector<Light*> lights, bool isSmoothed, bool f1);
	void drawMeshPixel(Rasterizer& rasterizer, VertexProcessor& vp, std::vector<Light*> lights, bool f1);
	void smooth();

	int vSize;
	int tSize;

	OBJLoader objLoader;

	std::vector<Vertex> vertices;
	std::vector<Int3> indices;
};