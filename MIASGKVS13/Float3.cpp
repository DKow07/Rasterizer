#include "Float3.h"
#include <math.h>
#include <iostream>

Float3::Float3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Float3::~Float3()
{
}

Float3::Float3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float& Float3::operator[](int index)
{
	return p[index];
}

Float3 Float3::operator*(const float& scallar)
{
	return Float3(this->x * scallar, this->y * scallar, this->z * scallar);
}

Float3 operator *(const float & scallar, const Float3 & v)
{
	return Float3(v.x * scallar, v.y * scallar, v.z * scallar);
}

Float3 Float3::operator/(const float& scallar)
{
	return Float3(this->x / scallar, this->y / scallar, this->z / scallar);
}

Float3 operator /(const float & scallar, const Float3 & v)
{
	return Float3(v.x / scallar, v.y / scallar, v.z / scallar);
}

Float3 Float3::operator + (const Float3& v)
{
	return Float3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Float3 Float3::operator - (const Float3& v)
{
	return Float3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Float3 Float3::operator ! ()
{
	return Float3(-this->x, -this->y, -this->z);
}

Float3 Float3::operator += (const Float3& v)
{
	return Float3(this->x + v.x, this->y + v.y, this->z + v.z);
}

float Float3::Dot(Float3 vector)
{
	return this->x * vector.x + this->y * vector.y + this->z * vector.z;
}

Float3 Float3::Cross(Float3 vector)
{
	float xCross = y * vector.z - z * vector.y;
	float yCross = z * vector.x - x * vector.z;
	float zCross = x * vector.y - y * vector.x;

	return Float3(xCross, yCross, zCross);
}

Float3 Float3::Reflect(Float3 normal)
{
	float dot = normal.Dot(*this);
	return normal * (float)dot * 2 - *this;
}

float Float3::Length()
{
	return sqrt(this->LengthSquared());
}

float Float3::LengthSquared()
{
	return (pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Float3 Float3::Normalized()
{
	float epsilon = 0.0001f;
	Float3 v;
	float length = Length();
	if (length > epsilon)
	{
		v.x = x / length;
		v.y = y / length;
		v.z = z / length;
		return v;
	}
	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 0.0f;
	return v;
}

Float3 Float3::Saturate()
{
	Float3 saturated = Float3(this->x, this->y, this->z);

	if (saturated.x < 0)
	{
		saturated.x = 0;
	}

	if (saturated.y < 0)
	{
		saturated.y = 0;
	}

	if (saturated.z < 0)
	{
		saturated.z = 0;
	}

	if (saturated.x > 255)
	{
		saturated.x = 255;
	}

	if (saturated.y > 255)
	{
		saturated.y = 255;
	}

	if (saturated.z > 255)
	{
		saturated.z = 255;
	}

	return saturated;
}

void Float3::Display()
{
	std::cout << "Float3 = (" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;;
}
