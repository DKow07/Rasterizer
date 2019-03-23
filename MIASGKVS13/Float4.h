#pragma once
class Float4
{
public:

	union
	{
		struct
		{
			float x, y, z, w;
		};
		float p[4];
	};

	Float4();
	Float4(float w, float x, float y, float z);
	~Float4();

	float operator[](int index);

	Float4 operator * (const float& scallar);
	friend Float4 operator *(const float & scallar, const Float4 & v);

	Float4 operator / (const float& scallar);
	friend Float4 operator /(const float & scallar, const Float4 & v);

	Float4 operator + (const Float4& v);
	Float4 operator - (const Float4& v);
	Float4 operator ! ();

	float Dot(Float4 vector);
	float Length();
	float LengthSquared();
	Float4 Normalized();

	void Display();
};