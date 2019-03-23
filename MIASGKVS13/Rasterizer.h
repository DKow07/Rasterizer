#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Float3.h"
#include "ColorBuffer.h"
#include "Light.h"
#include "VertexProcessor.h"

class Rasterizer
{
public:
	Rasterizer(std::shared_ptr<ColorBuffer> colorBuffer);
	~Rasterizer();
	void triangle(Float3 a, Float3 b, Float3 c, Float3 colorA = Float3(255.0f, 0.0f, 0.0f), Float3 colorB = Float3(0.0f, 255.0f, 0.0f), Float3 colorC = Float3(0.0f, 0.0f, 255.0f));
	void trianglePixel(Float3 a, Float3 b, Float3 c, Float3 n1, Float3 n2, Float3 n3, std::vector<Light*> lights, VertexProcessor& vp, bool f1);

private:
	std::shared_ptr<ColorBuffer> colorBuffer;
};