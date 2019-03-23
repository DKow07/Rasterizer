#include "DirectionalLight.h"
#include <cmath>


DirectionalLight::DirectionalLight(Float3 position, Float3 ambient, Float3 diffuse, Float3 specular, float shininess)
	: Light(position, ambient, diffuse, specular, shininess)
{
}


DirectionalLight::~DirectionalLight()
{
}

Float3 DirectionalLight::calculate(Fragment & f, VertexProcessor & vp, bool f1)
{
	Float3 p = position.Normalized();
	Float3 N = vp.lt(f.normal);
	N = N.Normalized();
	Float3 V = vp.obj2View(!f.position);
	V = V.Normalized();
	V = !V;
	Float3 R = p.Reflect(N);
	R = R.Normalized();
	Float3 resultColor = (ambient) + (diffuse * clamp( p.Dot(N), 0, 1)) + (specular * ( pow(clamp(R.Dot(V), 0, 1 ), shininess)));

	if (resultColor.x < 0)
	resultColor.x = 0;
	if (resultColor.y < 0)
	resultColor.y = 0;
	if (resultColor.z < 0)
	resultColor.z = 0;
	if (resultColor.x > 255)
	resultColor.x = 255;
	if (resultColor.y > 255)
	resultColor.y = 255;
	if (resultColor.z > 255)
	resultColor.z = 255;
	return resultColor;

	/*Float3 p = position.Normalized();

	Float3 n = vp.lt(f.normal);
	n = n.Normalized();

	Float4 v4 = vp.GetObj2ViewMatrix().mulByFloat3(!f.position);

	Float3 v = Float3(v4.x, v4.y, v4.z);

	//v = vp.lt(!f.position); ///

//	v = v.Normalized();

//	Float3 r = p.Reflect(p, n);

//	r = r.Normalized();

	Float3 diffusePart = clamp(p.Dot(n), 0, 1) * diffuse;

//	Float3 specularPart = (float)std::pow(clamp(r.Dot(v), 0, 1), shininess) * specular;

	Float3 result = diffusePart;// (ambient + diffusePart) + specularPart;

	if (result.x > 255)
	{
		result.x = 255;
	}

	if (result.y > 255)
	{
		result.y = 255;
	}

	if (result.z > 255)
	{
		result.z = 255;
	}

	return result;*/


	//-----------------------------

	/*Float4 normal2ObjToView = (vp.GetObj2ViewMatrix()).mulByFloat3(f.normal);
	Float3 n = Float3(normal2ObjToView.x / normal2ObjToView.w, normal2ObjToView.y / normal2ObjToView.w, normal2ObjToView.z / normal2ObjToView.w);
	n = n.Normalized();

	Float4 position2ObjToView = (vp.GetObj2ViewMatrix()).mulByFloat3((!f.position));
	Float3 v = Float3(position2ObjToView.x / position2ObjToView.w, position2ObjToView.y / position2ObjToView.w, position2ObjToView.z / position2ObjToView.w);
	v = v.Normalized();

	Float3 r = n.Reflect(this->position, n);
	r = r.Normalized();
	
	float diffusePart = this->position.Dot(n);
	Float3 powV = Float3(pow(v.x, this->shininess), pow(v.y, this->shininess), pow(v.z, this->shininess));
	powV = powV.Normalized();
	float specularPart = r.Dot(powV);

	Float3 color = diffusePart * this->diffuse + ambient + specularPart * this->specular;

	return color;*/
}
