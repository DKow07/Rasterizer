#include "Float4x4.h"


Float4x4::Float4x4()
	: a(), b(), c(), d()
{
}

Float4x4::Float4x4(Float4 a, Float4 b, Float4 c, Float4 d)
{
	//TODO: konstruktor kopiuj¹cy
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

Float4x4 Float4x4::mulByFloat4x4(Float4x4 matrix)
{
	Float4x4 result;
	float tmp[4][4];
	Float4 results[4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				tmp[j][i] += this->p[k][j] * matrix[i][k];
			}
		}
	}

	results[0] = Float4(tmp[0][0], tmp[1][0], tmp[2][0], tmp[3][0]);
	results[1] = Float4(tmp[0][1], tmp[1][1], tmp[2][1], tmp[3][1]);
	results[2] = Float4(tmp[0][2], tmp[1][2], tmp[2][2], tmp[3][2]);
	results[3] = Float4(tmp[0][3], tmp[1][3], tmp[2][3], tmp[3][3]);
	result = Float4x4(results[0], results[1], results[2], results[3]);
	return result;
}

Float4 Float4x4::mulByFloat4(Float4 vector)
{
	float x = a.x * vector.x + b.x * vector.y + c.x * vector.z + d.x * vector.w; //[0]
	float y = a.y * vector.x + b.y * vector.y + c.y * vector.z + d.y * vector.w; //[1]
	float z = a.z * vector.x + b.z * vector.y + c.z * vector.z + d.z * vector.w; //[2]
	float w = a.w * vector.x + b.w * vector.y + c.w * vector.z + d.w * vector.w; //[3]
	return Float4(x, y, z, w);
}

Float4 Float4x4::mulByFloat3(Float3 vector)
{
	Float4 f4(vector.x, vector.y, vector.z, 1.0f);
	return mulByFloat4(f4);
}

Float4 Float4x4::operator[](int index)
{
	return p[index];
}

void Float4x4::Display()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << this->p[j][i] << '\t';
		}
		std::cout << std::endl;
	}
}

Float4x4 Float4x4::transpose()
{
	Float4x4 transposedMatrix;
	Float4 tmp[4];
	for (int i = 0; i < 4; i++)
	{
		tmp[i] = Float4(this->a[i], this->b[i], this->c[i], this->d[i]);
	}
	transposedMatrix = Float4x4(tmp[0], tmp[1], tmp[2], tmp[3]);
	return transposedMatrix;
}

Float4x4::~Float4x4()
{
}
