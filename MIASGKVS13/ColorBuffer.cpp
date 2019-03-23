#include "ColorBuffer.h"

ColorBuffer::ColorBuffer(int width, int height)
{
    this->width = width;
    this->height = height;
    long imageSize = width * height;
    this->pixelColors = new int[imageSize];
	this->depths = new float[imageSize];
	this->setUniformDepth(-1);
}

void ColorBuffer::setUniformColor(int color)
{
    long imageSize = this->width * this->height;
    for(long i = 0; i < imageSize; i++)
    {
        this->pixelColors[i] = color;
    }
}

void ColorBuffer::setUniformDepth(float depth)
{
	long imageSize = this->width * this->height;
	for (long i = 0; i < imageSize; i++)
	{
		this->depths[i] = depth;
	}
}

int ColorBuffer::getPixel(int column, int row)
{
    long index = this->width * row + column;
	return this->pixelColors[index];
}

void ColorBuffer::setPixel(int column, int row, int color)
{
	long index = this->width * row + column;
	this->pixelColors[index] = color;
}

float ColorBuffer::getDepth(int column, int row)
{
	long index = this->width * row + column;
	return this->depths[index];
}

void ColorBuffer::setDepth(int column, int row, float depth)
{
	long index = this->width * row + column;
	this->depths[index] = depth;
}

int ColorBuffer::getWidth()
{
    return this->width;
}

int ColorBuffer::getHeight()
{
    return this->height;
}

ColorBuffer::~ColorBuffer()
{
	delete this->pixelColors;
}