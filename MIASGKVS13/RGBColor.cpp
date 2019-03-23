#include "RGBColor.h"
#include <iostream>

RGBColor::RGBColor()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

RGBColor::RGBColor(double r, double g, double b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}


RGBColor::~RGBColor()
{
}

RGBColor RGBColor::operator +(const RGBColor& c)
{
	return RGBColor(this->r + c.r, this->g + c.g, this->b + c.b);
}
RGBColor operator + (const RGBColor& c, const double& scallar)
{
	return RGBColor(c.r + scallar, c.g + scallar, c.b + scallar);
}
RGBColor operator + (const double& scallar, const RGBColor& c)
{
	return RGBColor(c.r + scallar, c.g + scallar, c.b + scallar);
}

RGBColor RGBColor::operator -(const RGBColor& c)
{
	return RGBColor(this->r - c.r, this->g - c.g, this->b - c.b);
}
RGBColor operator - (const RGBColor& c, const double& scallar)
{
	return RGBColor(c.r - scallar, c.g - scallar, c.b - scallar);
}
RGBColor operator - (const double& scallar, const RGBColor& c)
{
	return RGBColor(c.r - scallar, c.g - scallar, c.b - scallar);
}

RGBColor RGBColor::operator *(const RGBColor& c)
{
	return RGBColor(this->r * c.r, this->g * c.g, this->b * c.b);
}
RGBColor operator * (const RGBColor& c, const double& scallar)
{
	return RGBColor(c.r * scallar, c.g * scallar, c.b * scallar);
}
RGBColor operator * (const double& scallar, const RGBColor& c)
{
	return RGBColor(c.r * scallar, c.g * scallar, c.b * scallar);
}

RGBColor RGBColor::operator /(const RGBColor& c)
{
	std::cout << "halo halo dzielenie przez dwa kolory" << std::endl;
	return RGBColor();
}
RGBColor operator / (const RGBColor& c, const double& scallar)
{
	return RGBColor(c.r / scallar, c.g / scallar, c.b / scallar);
}
RGBColor operator / (const double& scallar, const RGBColor& c)
{
	return RGBColor(c.r / scallar, c.g / scallar, c.b / scallar);
}


RGBColor RGBColor::StripColor(RGBColor color)
{
	RGBColor tmp;
	if (color.r > 255)
		tmp.r = 255;
	if (color.g > 255)
		tmp.g = 255;
	if (color.b > 255)
		tmp.b = 255;
	return tmp;

}

void RGBColor::Display()
{
	std::cout << "RGBColor = (" << this->r << ", " << this->g << ", " << this->b << ")" << std::endl;;
}


const RGBColor RGBColor::WHITE = RGBColor(1,1,1);
const RGBColor RGBColor::BLACK = RGBColor(0, 0, 0);
const RGBColor RGBColor::GREEN = RGBColor(0, 1, 0);
const RGBColor RGBColor::BLUE = RGBColor(0, 0, 1);
const RGBColor RGBColor::RED = RGBColor(1, 0, 0);

