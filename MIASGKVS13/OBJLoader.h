#pragma once
#include <fstream>
#include "Float3.h"
#include "StringUtils.h"
#include "Int3.h"
#include "Vertex.h"

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	bool loadRawModel(std::string fileName);

	std::vector<Vertex> vertices;
	std::vector<Int3> indices;
	std::vector<Float3> normals;
	std::vector<Float3> textures;
	std::vector<Float3> verticesFloat;
};

