#include "Float4.h"

#include <math.h>
#include <iostream>

Float4::Float4()
{
	this->w = 1.0f;
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Float4::~Float4()
{
}

Float4::Float4(float x, float y, float z, float w)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

float Float4::operator[](int index)
{
	return p[index];
}

Float4 Float4::operator*(const float& scallar)
{
	return Float4(this->x * scallar, this->y * scallar, this->z * scallar, this->w * scallar);
}

Float4 operator *(const float & scallar, const Float4 & v)
{
	return Float4 (v.x * scallar, v.y * scallar, v.z * scallar, v.w * scallar);
}

Float4 Float4::operator/(const float& scallar)
{
	return Float4(this->x / scallar, this->y / scallar, this->z / scallar, this->w / scallar);
}

Float4 operator /(const float & scallar, const Float4 & v)
{
	return Float4(v.x / scallar, v.y / scallar, v.z / scallar, v.w / scallar);
}

Float4 Float4::operator + (const Float4& v)
{
	return Float4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}

Float4 Float4::operator - (const Float4& v)
{
	return Float4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}

Float4 Float4::operator ! ()
{
	return Float4(-this->x, -this->y, -this->z, -this->w);
}

float Float4::Dot(Float4 vector)
{
	return this->x * vector.x + this->y * vector.y + this->z * vector.z + this->w * vector.w;
}

float Float4::Length()
{
	return sqrt(this->LengthSquared());
}

float Float4::LengthSquared()
{
	return (pow(w,2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Float4 Float4::Normalized()
{
	float epsilon = 0.0001f;
	Float4 v;
	float length = Length();
	if (length > epsilon)
	{
		v.w = w / length;
		v.x = x / length;
		v.y = y / length;
		v.z = z / length;
		return v;
	}
	v.w = 0.0f;
	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 0.0f;
	return v;
}

void Float4::Display()
{
	std::cout << "Float4 = (" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")" << std::endl;
}
