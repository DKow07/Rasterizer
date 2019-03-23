#pragma once
class Float3
{
public:

	union 
	{
		struct
		{
			float x, y, z;
		};
		float p[3];
	};

	Float3();
	Float3(float x, float y, float z);
	~Float3();

	float& operator[](int index);

	Float3 operator * (const float& scallar);
	friend Float3 operator * (const float & scallar, const Float3 & v);

	Float3 operator / (const float& scallar);
	friend Float3 operator / (const float & scallar, const Float3 & v);

	Float3 operator + (const Float3& v);
	Float3 operator - (const Float3& v);
	Float3 operator ! ();

	Float3 operator += (const Float3& v);

	float Dot(Float3 vector);
	Float3 Cross(Float3 vector);
	Float3 Reflect(Float3 normal);
	float Length();
	float LengthSquared();
	Float3 Normalized();

	Float3 Saturate();

	void Display();
};

