#pragma once

class ColorBuffer
{
public:
    ColorBuffer(int width, int height);
    ~ColorBuffer();
    int getPixel(int column, int row);
	void setPixel(int column, int row, int color);
	float getDepth(int column, int row);
	void setDepth(int column, int row, float depth);
    int getWidth();
    int getHeight();
    void setUniformColor(int color);
	void setUniformDepth(float depth = -1);
private:
    int* pixelColors;
	float* depths;
    int width;
    int height;
};
