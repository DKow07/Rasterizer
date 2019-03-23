#pragma once
class RGBColor
{
public:

	double r, g, b;

	RGBColor();
	RGBColor(double r, double g, double b);
	~RGBColor();

	RGBColor operator +(const RGBColor& c);
	friend RGBColor operator + (const RGBColor& c, const double& scallar);
	friend RGBColor operator + (const double& scallar, const RGBColor& c);
	RGBColor operator -(const RGBColor& c);
	friend RGBColor operator - (const RGBColor& c, const double& scallar);
	friend RGBColor operator - (const double& scallar, const RGBColor& c);
	RGBColor operator *(const RGBColor& c);
	friend RGBColor operator * (const RGBColor& c, const double& scallar);
	friend RGBColor operator * (const double& scallar, const RGBColor& c);
	RGBColor operator /(const RGBColor& c);
	friend RGBColor operator / (const RGBColor& c, const double& scallar);
	friend RGBColor operator / (const double& scallar, const RGBColor& c);

	void Display();
	static RGBColor StripColor(RGBColor color);

	static const RGBColor WHITE;
	static const RGBColor BLACK;
	static const RGBColor GREEN;
	static const RGBColor BLUE;
	static const RGBColor RED;
};

