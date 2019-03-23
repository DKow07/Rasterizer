#pragma once
#include "Float3.h"
class Vertex
{
public:
	Vertex(Float3 position, Float3 normal);
	~Vertex();

	Float3 position;
	Float3 normal;
};

