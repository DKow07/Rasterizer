#include "VertexProcessor.h"



VertexProcessor::VertexProcessor()
	:obj2proj(), obj2view(), obj2world(), world2view(), view2proj()
{
}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= M_PI / 360;
	float f = cos(fovy) / sin(fovy);

	view2proj.a = Float4(f / aspect, 0, 0, 0);
	view2proj.b = Float4(0, f, 0, 0);
	view2proj.c = Float4(0, 0, (far + near) / ((near - far)*1.0f), -1);
	view2proj.d = Float4(0, 0, 2 * far * near / (near - far), 0);
}

void VertexProcessor::setLookAt(Float3 eye, Float3 center, Float3 up)
{
	this->eye = eye;
	Float3 f = center - eye;
	f = f.Normalized();
	up = up.Normalized();
	Float3 s = f.Cross(up);
	Float3 u = s.Cross(f);

	world2view.a = Float4(s.x, u.x, -f.x, 0);
	world2view.b = Float4(s.y, u.y, -f.y, 0);
	world2view.c = Float4(s.z, u.z, -f.z, 0);
	world2view.d = Float4(-eye.x, -eye.y, -eye.z, 1);
}

void VertexProcessor::setIdentityWorld2View()
{
	world2view = Float4x4(
		Float4(1, 0, 0, 0),
		Float4(0, 1, 0, 0),
		Float4(0, 0, 1, 0),
		Float4(0, 0, 0, 1)
	);
}

void VertexProcessor::setIdentityObj2World()
{
	obj2world = Float4x4(
		Float4(1, 0, 0, 0),
		Float4(0, 1, 0, 0),
		Float4(0, 0, 1, 0),
		Float4(0, 0, 0, 1)
	);
}

Float3 VertexProcessor::tr(Float3 vector)
{
	Float4 result = obj2proj.mulByFloat3(vector);
	return Float3(result.x / result.w, result.y / result.w, result.z / result.w);
}

void VertexProcessor::multByTranslation(Float3 v)
{
	Float4x4 m(
		Float4(1, 0, 0, 0),
		Float4(0, 1, 0, 0),
		Float4(0, 0, 1, 0),
		Float4(v.x, v.y, v.z, 1)
	);
	this->obj2world = m.mulByFloat4x4(this->obj2world);
}

void VertexProcessor::multByRotation(float a, Float3 v)
{
	float s = sin(a*M_PI / 180);
	float c = cos(a*M_PI / 180);
	v = v.Normalized();
	Float4x4 m = Float4x4(
		Float4(v.x*v.x*(1 - c) + c, v.y*v.x*(1 - c) + v.z*s, v.x*v.z*(1 - c) - v.y*s, 0),
		Float4(v.x*v.y*(1 - c) - v.z*s, v.y*v.y*(1 - c) + c, v.y*v.z*(1 - c) + v.x*s, 0),
		Float4(v.x*v.z*(1 - c) + v.y*s, v.y*v.z*(1 - c) - v.x*s, v.z*v.z*(1 - c) + c, 0),
		Float4(0, 0, 0, 1)
	);
	this->obj2world = m.mulByFloat4x4(this->obj2world);
}

void VertexProcessor::multByScale(Float3 v)
{
	Float4x4 m(
		Float4(v.x, 0, 0, 0),
		Float4(0, v.y, 0, 0),
		Float4(0, 0, v.z, 0),
		Float4(0, 0, 0, 1)
	);
	this->obj2world = m.mulByFloat4x4(this->obj2world);
}

void VertexProcessor::transform()
{
	obj2view = world2view.mulByFloat4x4(obj2world);
	obj2proj = view2proj.mulByFloat4x4(obj2view);
}

Float4x4 VertexProcessor::GetObj2ViewMatrix()
{
	return this->obj2view;
}

Float3 VertexProcessor::obj2View(Float3 vec)
{
	Float4 result = obj2view.mulByFloat3(vec);
	return Float3(result.x, result.y, result.z);
}

Float3 VertexProcessor::lt(Float3 vec)
{
	Float3 result;
	Float3 a = Float3(obj2view[0][0], obj2view[0][1], obj2view[0][2]);
	Float3 b = Float3(obj2view[1][0], obj2view[1][1], obj2view[1][2]);
	Float3 c = Float3(obj2view[2][0], obj2view[2][1], obj2view[2][2]);
	for (int i = 0; i < 3; i++)
	{
		result[i] = 0;
		result[i] += a[i] * vec[0];
		result[i] += b[i] * vec[1];
		result[i] += c[i] * vec[2];
	}

	return Float3(result.x, result.y, result.z);
}


VertexProcessor::~VertexProcessor()
{
}