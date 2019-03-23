#include <iostream>
#include <memory>
#include <vector>

#include "WriteBufferInterface.h"
#include "PPMBuffer.h"
#include "Rasterizer.h"
#include "Float4.h"
#include "Float4x4.h"
#include "VertexProcessor.h"
#include "Mesh.h"
#include "DirectionalLight.h"
#include "PointLight.h"

void testTriangle();
void testMath();

int main()
{
	//testMath();
	testTriangle();
	//testObjLoader();
	std::getchar();
	return 0;
}

void testTriangle()
{
	bool pixel = true;
	VertexProcessor vp;
	vp.setPerspective(45, 1, 1, 100);
	vp.setIdentityWorld2View();
	//vp.setLookAt(Float3(0, 0, 4), Float3(0, 0, 1), Float3(0, 1, 0));
	vp.setLookAt(Float3(0, 0, -25), Float3(0, 0, 0), Float3(0, 1, 0));
	vp.setIdentityObj2World();

	float scale = 1.0f;

	vp.multByTranslation(Float3(5.0f, -1.5f, 0.0f));
	vp.multByScale(Float3(scale, scale, scale));
	//vp.multByRotation(0, Float3(0, 1, 0));

	//vp.multByRotation(120, Float3(1, 0, 0));

	DirectionalLight* light1 = new DirectionalLight(Float3(0.0f, -0.5f, 0.0f), Float3(0.0f, 0.0f, 0.0f), Float3(255.0f, 255.0f, 255.0f), Float3(255.0f, 255.0f, 255.0f), 4.0f);
	DirectionalLight* light2 = new DirectionalLight(Float3(1.0f, 0.0f, 0.0f), Float3(10.0f, 10.0f, 10.0f), Float3(255.0f, 255.0f, 255.0f), Float3(255.0f, 255.0f, 255.0f), 4.0f);
	PointLight* pointLight = new PointLight(Float3(0.1f, 0.0f, 2.0f), Float3(0.0f, 0.0f, 0.0f), Float3(255.0f, 255.0f, 255.0f), Float3(255.0f, 255.0f, 255.0f), 6.0f);
	std::vector<Light*> lights;
	//lights.push_back(light1);
	lights.push_back(light2);
	lights.push_back(pointLight);

	vp.transform();
	std::shared_ptr<WriteBufferInterface> savePPMBuffer = std::make_shared<PPMBuffer>();
	std::shared_ptr<ColorBuffer> colorBuffer = std::make_shared<ColorBuffer>(512, 512);
	colorBuffer->setUniformColor(0x000000);
	Rasterizer rasterizer(colorBuffer); //przeciwnie do ruchu wskazówek zegara
	Float3 a(5, 0, 0);
	Float3 b(10, 5, 0);
	Float3 c(10, 0, 0);
	Float3 a1(-5, 0, 0);
	Float3 b1(10, -5, 0);
	Float3 c1(10, 0, 0);
	//Float3 colorA = Float3();
	//Float3 colorB = Float3();
	//Float3 colorC = Float3();
	//Vertex vertex1(a, Float3(0, 0, 1));
	//Vertex vertex2(b, Float3(0, 0, 1));
	//Vertex vertex3(c, Float3(0, 0, 1));
	//for (auto light : lights)
	//{
	//	colorA = colorA + light->calculate(vertex1, vp);
	//	colorB = colorB + light->calculate(vertex2, vp);
	//	colorC = colorC + light->calculate(vertex3, vp);
	//}
	//colorA = colorA.Saturate();
	//colorB = colorB.Saturate();
	//colorC = colorC.Saturate();
	//rasterizer.triangle(vp.tr(c), vp.tr(b), vp.tr(a), colorA, colorB, colorC);

	//vp.setIdentityObj2World();
	//vp.multByTranslation(Float3(-10, -4.8, 0));  //2
	//vp.transform();
	//colorA = Float3();
	//colorB = Float3();
	//colorC = Float3();
	//vertex1 = Vertex(a1, Float3(0, 0, 1));
	//vertex2 = Vertex(b1, Float3(0, 0, 1));
	//vertex3 = Vertex(c1, Float3(0, 0, 1));
	//for (auto light : lights)
	//{
	//	colorA = colorA + light->calculate(vertex1, vp);
	//	colorB = colorB + light->calculate(vertex2, vp);
	//	colorC = colorC + light->calculate(vertex3, vp);
	//}
	//colorA = colorA.Saturate();
	//colorB = colorB.Saturate();
	//colorC = colorC.Saturate();
	//rasterizer.triangle(vp.tr(c), vp.tr(b), vp.tr(a), colorA, colorB, colorC);
	//vp.multByTranslation(Float3(0.4, 0.4, 0.4));
	//vp.multByRotation(90, Float3(0, 0, 1));
	//vp.transform();
	//rasterizer.triangle(vp.tr(a), vp.tr(b), vp.tr(c));




	Mesh mesh;
	mesh.loadMesh("teapot.obj");

	//lights.push_back(light2);
	//PointLight light = PointLight(Float3(7.0f, 0.0f, 5.0f), Float3(10.0f, 10.0f, 10.0f), Float3(0.0f, 0.0f, 200.0f), Float3(200.0f, 200.0f, 200.0f), 10.0f);
	
	if(!pixel)
		mesh.drawMesh(rasterizer, vp, lights, false, true);
	else
		mesh.drawMeshPixel(rasterizer, vp, lights, true);
	
	//rasterizer.triangle(a1, b1, c1, Float3(244.0f, 232.0f, 66.0f), Float3(68.0f, 244.0f, 235.0f), Float3(238.0f, 10.0f, 255.0f));

	vp.setIdentityObj2World();
	vp.multByTranslation(Float3(4.0f, 4.0f, 0.0f));
	vp.multByScale(Float3(scale, scale, scale));
	vp.multByRotation(180, Float3(0, 1, 0));
	vp.multByRotation(45, Float3(0, 0, 1));
	vp.transform();
	Mesh mesh1;
	mesh1.loadMesh("teapot.obj");
	if (!pixel)
		mesh1.drawMesh(rasterizer, vp, lights, false, true);
	else
		mesh1.drawMeshPixel(rasterizer, vp, lights, false);

	vp.setIdentityObj2World();
	vp.multByTranslation(Float3(1.0f, -4.0f, 0.0f));
	vp.multByScale(Float3(1.0f, 1.0f, 1.0f));
	vp.transform();
	mesh1.loadMesh("teapot.obj"); //sphere
	if (!pixel)
		mesh1.drawMesh(rasterizer, vp, lights, false, false);
	else
		mesh1.drawMeshPixel(rasterizer, vp, lights, false);

	vp.setIdentityObj2World();
	vp.multByTranslation(Float3(-3.0f, -4.0f, 0.0f));
	vp.multByScale(Float3(2.0f, 2.0f, 2.0f));
	vp.transform();
	mesh1.loadMesh("sphere.obj"); //sphere
	if (!pixel)
		mesh1.drawMesh(rasterizer, vp, lights, false, false);
	else
		mesh1.drawMeshPixel(rasterizer, vp, lights, false);

	vp.setIdentityObj2World();
	vp.multByTranslation(Float3(0.0f, 4.0f, 0.0f));
	vp.multByScale(Float3(1.0f, 1.0f, 1.0f));
	vp.transform();
	mesh1.loadMesh("teapot.obj"); //sphere
	if (!pixel)
		mesh1.drawMesh(rasterizer, vp, lights, false, false);
	else
		mesh1.drawMeshPixel(rasterizer, vp, lights, false);


	vp.setIdentityObj2World();
	vp.multByScale(Float3(scale, scale, scale));
	vp.multByTranslation(Float3(-7.0f, -5.0f, 0.0f));
	//vp.multByRotation(90, Float3(0, 1, 0));
	vp.transform();
	mesh1.loadMesh("teapot.obj");
	//mesh1.drawMesh(rasterizer, vp, lights, false, true);
	//mesh1.drawMeshPixel(rasterizer, vp, lights);


	vp.setIdentityObj2World();
	vp.multByScale(Float3(scale, scale, scale));
	vp.multByTranslation(Float3(0.0f, 3.0f, 0.0f));
	vp.transform();
	//mesh1.loadMesh("teapot.obj"); 
	//mesh1.drawMesh(rasterizer, vp, lights, false);
	//mesh1.drawMeshPixel(rasterizer, vp, lights);


	savePPMBuffer->saveToFile("monkey.ppm", colorBuffer);

	std::cout << "Koniec" << std::endl;

	delete light1;
	delete light2;
	delete pointLight;
}

void testMath()
{
	//TODO: sprawdziæ czy dzia³a Float4

	Float4 a(1, 5, 8, 5);
	Float4 b(2, 5, 5, 8);
	Float4 c(3, 5, 8, 5);
	Float4 d(4, 5, 5, 8);
	Float4x4 m1(a, b, c, d);

	Float3 ee(5, 50, 45);
	Float4 e(5, 50, 45, 2);
	Float4 f(4, 5, 65, 8);
	Float4 g(2, 1, 68, 66);
	Float4 h(0, 9, 8, 78);
	Float4x4 m2(e, f, g, h);

	Float4x4 res = m1.mulByFloat4x4(m2);
	Float4 resFloat4 = m1.mulByFloat4(e);
	Float4 resFloat3 = m1.mulByFloat3(ee);

	m1.Display();
	std::cout << std::endl;
	resFloat3.Display();
	//m2.Display();
	std::cout << std::endl;
	//res.Display();
	//Float4x4 tran = res.transpose();
	//std::cout << std::endl;
	//tran.Display();
}