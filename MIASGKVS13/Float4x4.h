#pragma once
#include <iostream>
#include "Float3.h"
#include "Float4.h"

class Float4x4
{
public:

	union
	{
		struct
		{
			Float4 a, b, c, d; //kolumny
		};
		struct
		{
			Float4 p[4];
		};
	};

	Float4x4();
	Float4x4(Float4 a, Float4 b, Float4 c, Float4 d);
	~Float4x4();

	Float4 operator[](int columnIndex);

	Float4x4 mulByFloat4x4(Float4x4 matrix);
	Float4 mulByFloat4(Float4 vector);
	Float4 mulByFloat3(Float3 vector);
	Float4x4 transpose();
	void Display();
};