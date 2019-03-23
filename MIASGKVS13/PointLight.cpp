#include "PointLight.h"



PointLight::PointLight(Float3 position, Float3 ambient, Float3 diffuse, Float3 specular, float shininess)
	: Light(position, ambient, diffuse, specular, shininess)
{
}

PointLight::~PointLight()
{
}

Float3 PointLight::calculate(Fragment & f, VertexProcessor & vp, bool f1)
{

	Float3 N = (vp.lt(f.normal)).Normalized();

	Float3 V = vp.obj2View(f.position);
	Float4 L4 = (vp.world2view).mulByFloat3(this->position);
	Float3 L = Float3(L4.x, L4.y, L4.z) - V;
	L = L.Normalized();

	float diff = L.Dot(N);
	diff = std::max(0.0f, diff);

	float spec = 0.0f;
	if (diff > 0.000f)
	{
		Float3 R = L.Reflect(N).Normalized();

		spec = R.Dot(V.Normalized());
		spec = std::max(0.0f, spec);
		spec = std::pow(spec, this->shininess);
	}

	Float3 color = diffuse * diff;
	color += Float3(1.0f, 1.0f, 1.0f) * spec;
	color = color.Saturate();
	return color;





	//Float4 worldPosition4 = (vp.obj2world.mulByFloat3(!f.position));
	//Float3 worldPosition = Float3(worldPosition4.x, worldPosition4.y, worldPosition4.z);
	//Float3 worldNormal = vp.lt(f.normal);
	//worldNormal = worldNormal.Normalized();
	//if(f1)
	//	worldNormal = !worldNormal;
	//Float3 lightVector = (position - worldPosition);
	//lightVector = lightVector.Normalized();
	//float brightness = clamp(lightVector.Dot(worldNormal), 0.0f, 1.0f);
	//Float3 diffuseColor = brightness * diffuse;
	//float specularFloat = 0.0f;
	//if (brightness > 0.0f)
	//{
	//	Float3 reflected = ((lightVector).Reflect(worldNormal));
	//	reflected = reflected.Normalized();
	//	specularFloat = clamp(reflected.Dot(lightVector), 0.0f, 1.0f);
	//	specularFloat = std::pow(specularFloat, shininess);
	//}
	//Float3 specularColor = specular * specularFloat;
	//Float3 result = (ambient + diffuseColor) + specularColor;
	//result = result.Saturate();
	//return result;


	/*
	auto N = vp.lt(f.normal).Normalized();
	//auto V = (position - vp.obj2View(!f.position));
	auto V = vp.lt(!f.position);
	//auto L = V.Normalized();
	auto L = position - V;
	auto R = L.Reflect(L, N);

	auto diff = L.Dot(N);
	diff = diff<0.f ? 0 : diff >1.f ? 1.f : diff;

	auto spec = R.Dot((position - vp.eye).Normalized());
	spec = spec < 0.f ? 0.f : spec;

	spec = pow(spec, 10);

	auto color = ambient + (diffuse * diff) + (specular * spec);
	color.Saturate();

	return color;
	*/

	//---------------------------------------
	/*
	Float3 p = position;// .Normalized();

	Float3 n = vp.lt(f.normal);

	n = n.Normalized();
	n = !n;

	Float4 v4 = vp.GetObj2ViewMatrix().mulByFloat3(!f.position);

	Float3 v = vp.obj2View(!f.position);//Float3(v4.x, v4.y, v4.z);

	v = v.Normalized();

	Float3 l = (p - v); ////
	l = !l; ////

	l = l.Normalized();

	Float3 r = l.Reflect(l, n);

	r = r.Normalized();

	Float3 diffusePart = clamp(l.Dot(n), 0, 1) * diffuse;

	Float3 specularPart = (float)std::pow(clamp(r.Dot(v), 0, 1), shininess) * specular;

	Float3 result = (ambient + diffusePart) + specularPart;

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

	return result;

	*/
}
