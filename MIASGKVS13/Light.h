#pragma once
#include "Float3.h"
#include "Vertex.h"
#include "VertexProcessor.h"

typedef Vertex Fragment;

class Light
{
protected:
	Float3 position;
	Float3 ambient;
	Float3 diffuse;
	Float3 specular;
	float shininess;

public:
	Light(Float3 position, Float3 ambient, Float3 diffuse, Float3 specular, float shininess);
	~Light();

	virtual Float3 calculate(Fragment& f, VertexProcessor& vp, bool f1) = 0;
};

