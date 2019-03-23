#pragma once
#include "Light.h"
#include <algorithm>
#include <cstdint>
#include <iomanip>

class DirectionalLight : public Light
{
public:
	DirectionalLight(Float3 position, Float3 ambient, Float3 diffuse, Float3 specular, float shininess);
	~DirectionalLight();

	Float3 calculate(Fragment& f, VertexProcessor& vp, bool f1);
	float clamp(float n, float lower, float upper) {
		return std::max(lower, std::min(n, upper));
	}
};

