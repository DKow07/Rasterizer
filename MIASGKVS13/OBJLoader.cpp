#include "OBJLoader.h"


OBJLoader::OBJLoader()
{
}

bool OBJLoader::loadRawModel(std::string fileName)
{
	if (fileName.substr(fileName.size() - 4, 4) != ".obj")
	{
		return false;
	}

	std::ifstream file(fileName.c_str());

	if (!file.is_open())
	{
		return false;
	}

	std::string currentLine;
	verticesFloat.clear();
	vertices.clear();
	textures.clear();
	indices.clear();
	normals.clear();

	std::string vertexStartDelimiter = "v ";
	std::string normalsStartDelimiter = "vn ";
	std::string texturesStartDelimiter = "vt ";
	std::string facesStartDelimiter = "f ";

	while (std::getline(file, currentLine))
	{
		if (StartsWith(currentLine, vertexStartDelimiter))
		{
			std::vector<std::string> split = Split(currentLine, ' ');
			Float3 vertex(strtof(split[1].c_str(), 0), strtof(split[2].c_str(), 0), strtof(split[3].c_str(), 0));
			verticesFloat.push_back(vertex);
		}
		else if (StartsWith(currentLine, normalsStartDelimiter))
		{
			std::vector<std::string> split = Split(currentLine, ' ');
			Float3 normal(strtof(split[1].c_str(), 0), strtof(split[2].c_str(), 0), strtof(split[3].c_str(), 0));
			normals.push_back(normal);
		}
		else if (StartsWith(currentLine, texturesStartDelimiter))
		{
			std::vector<std::string> split = Split(currentLine, ' ');
			Float3 texture(strtof(split[1].c_str(), 0), strtof(split[2].c_str(), 0), 0.0f);
			textures.push_back(texture);
		}
		else if (StartsWith(currentLine, facesStartDelimiter))
		{
			std::vector<std::string> split = Split(currentLine, ' ');
			std::vector<std::string> vertex1Split = Split(split[1], '/');
			std::vector<std::string> vertex2Split = Split(split[2], '/');
			std::vector<std::string> vertex3Split = Split(split[3], '/');
			Int3 vertex1(std::stoi(vertex1Split[0].c_str()), std::stoi(vertex1Split[1].c_str()), std::stoi(vertex1Split[2].c_str()));
			Int3 vertex2(std::stoi(vertex2Split[0].c_str()), std::stoi(vertex2Split[1].c_str()), std::stoi(vertex2Split[2].c_str()));
			Int3 vertex3(std::stoi(vertex3Split[0].c_str()), std::stoi(vertex3Split[1].c_str()), std::stoi(vertex3Split[2].c_str()));
			indices.push_back(vertex1);
			indices.push_back(vertex2);
			indices.push_back(vertex3);
		}
	}

	vertices.clear(); //TODO
	/*for (int i = 0; i < verticesFloat.size(); i++)
	{
		Vertex v(verticesFloat[i], Float3(1,0,0));
		vertices.push_back(v);
	}*/

	for (auto indice : indices)
	{
		Float3 vertex = verticesFloat[indice.a - 1];
		Float3 normal = normals[indice.c - 1];
		vertices.push_back(Vertex(vertex, normal));
	}

	////dla trójk¹tów jedna normalka
	//for (int i = 0; i < vertices.size() - 1; ++i)
	//{
	//	for (int j = i + 1; j < vertices.size() - 1; ++j)
	//	{
	//		if (vertices[i].position.x == vertices[j].position.x
	//			&& vertices[i].position.y == vertices[j].position.y
	//			&& vertices[i].position.z == vertices[j].position.z)
	//		{
	//			Float3 tmp = (vertices[i].normal + vertices[j].normal) / 2; //wy¿ej
	//			vertices[i].normal = tmp;
	//			vertices[j].normal = tmp;
	//		}
	//	}
	//}



	return true;
}

OBJLoader::~OBJLoader()
{
}
