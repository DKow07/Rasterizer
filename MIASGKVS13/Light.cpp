#include "Light.h"



Light::Light(Float3 position, Float3 ambient, Float3 diffuse, Float3 specular, float shininess)
{
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}


Light::~Light()
{
}
