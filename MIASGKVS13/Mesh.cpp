#include "Mesh.h"

Mesh::Mesh()
	:objLoader()
{
}

bool Mesh::loadMesh(std::string fileName)
{
	bool isSuccess = this->objLoader.loadRawModel(fileName);
	if (isSuccess)
	{
		this->vSize = this->objLoader.vertices.size();
		this->tSize = this->objLoader.indices.size() / 3;
		this->vertices = this->objLoader.vertices;
		this->indices = this->objLoader.indices;
		return true;
	}
	
	return false;
}

void Mesh::drawMesh(Rasterizer& rasterizer, VertexProcessor& vp, Light& light, bool f1)
{

	for (int i = 0; i < this->tSize; i++) //TODO
	{
		Float3 colorA = light.calculate(vertices[i * 3], vp, f1);
		Float3 colorB = light.calculate(vertices[i * 3 + 1], vp, f1);
		Float3 colorC = light.calculate(vertices[i * 3 + 2], vp, f1);
		//std::cout << i << std::endl;
		rasterizer.triangle(
	/*		vp.tr(vertices[(this->indices[i].a - 1)].position),
			vp.tr(vertices[this->indices[i+1].a - 1].position),
			vp.tr(vertices[this->indices[i+2].a - 1].position)*/
			vp.tr(vertices[i*3].position),
			vp.tr(vertices[i*3+1].position),
			vp.tr(vertices[i*3+2].position),
			colorA,
			colorB, 
			colorC
		);
	}
}

void Mesh::drawMesh(Rasterizer& rasterizer, VertexProcessor& vp, std::vector<Light*> lights, bool isSmoothed, bool f1)
{
	if (isSmoothed)
		smooth();

	for (int i = 0; i < this->tSize; i++) //TODO
	{
		Float3 colorA = Float3();
		Float3 colorB = Float3();
		Float3 colorC = Float3();
		for (auto light : lights)
		{
			colorA = colorA + light->calculate(vertices[i * 3], vp, f1);
			colorB = colorB + light->calculate(vertices[i * 3 + 1], vp, f1);
			colorC = colorC + light->calculate(vertices[i * 3 + 2], vp, f1);
		}
		colorA = colorA.Saturate();
		colorB = colorB.Saturate();
		colorC = colorC.Saturate();
		rasterizer.triangle(
			vp.tr(vertices[i * 3].position),
			vp.tr(vertices[i * 3 + 1].position),
			vp.tr(vertices[i * 3 + 2].position),
			colorA,
			colorB,
			colorC
		);
	}
}


void Mesh::drawMeshPixel(Rasterizer& rasterizer, VertexProcessor& vp, std::vector<Light*> lights, bool f1)
{
	for (int i = 0; i < this->tSize; i++) //TODO
	{
		rasterizer.trianglePixel(
			vertices[i * 3].position,
			vertices[i * 3 + 1].position,
			vertices[i * 3 + 2].position,
			vertices[i * 3].normal,
			vertices[i * 3 + 1].normal,
			vertices[i * 3 + 2].normal,
			lights,
			vp,
			f1
		);


	/*	rasterizer.trianglePixel(
			vp.tr(vertices[i * 3].position),
			vp.tr(vertices[i * 3 + 1].position),
			vp.tr(vertices[i * 3 + 2].position),
			vertices[i * 3].normal,
			vertices[i * 3 + 1].normal,
			vertices[i * 3 + 2].normal,
			lights,
			vp,
			f1
		);*/
		
	}
}

void Mesh::smooth()
{
	for (int i = 0; i < this->vSize; ++i)
	{
		vertices[i].normal = Float3();
	}
	for (int i = 0; i < this->tSize; ++i)
	{
		Float3 n = ((vertices[indices[i].c].position - vertices[indices[i].a].position)
					.Cross(vertices[indices[i].b].position - vertices[indices[i].a].position))
					.Normalized();
		vertices[indices[i].a].position = vertices[indices[i].a].position + n;
		vertices[indices[i].b].position = vertices[indices[i].b].position + n;
		vertices[indices[i].c].position = vertices[indices[i].c].position + n;
	}
	for (int i = 0; i < this->vSize; ++i)
	{
		vertices[i].normal = vertices[i].normal.Normalized();
	}
}

Mesh::~Mesh()
{
}
