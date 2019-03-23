#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Float4x4.h"
#include "Float3.h"

class VertexProcessor
{
public:
	Float4x4 obj2world;
	Float4x4 world2view;
	Float4x4 view2proj;

	Float4x4 obj2proj;
	Float4x4 obj2view;

public:
	VertexProcessor();
	~VertexProcessor();

	Float3 eye;

	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookAt(Float3 eye, Float3 center, Float3 up);
	//7 obiektów, poruszanie nimi niezale¿nie
	void setIdentityWorld2View();
	void setIdentityObj2World();
	Float3 tr(Float3 vector);
	Float3 lt(Float3 vec);
	void multByTranslation(Float3 v);
	void multByRotation(float a, Float3 v);
	void multByScale(Float3 v);
	void transform();

	Float4x4 GetObj2ViewMatrix();

	Float3 obj2View(Float3 vec);
};

